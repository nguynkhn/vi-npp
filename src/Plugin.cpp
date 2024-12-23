#include "Plugin.h"
#include "ViNpp.h"

Plugin plugin = {0};

void Plugin::CommandInit() {
	AddCommand(0, TEXT("Enable Vi mode"), []() { vi.Toggle(); }, vi.enabled, NULL);
}

void Plugin::AddCommand(size_t index, TCHAR *name, PFUNCPLUGINCMD func, bool check, ShortcutKey *shortcut) {
	_tcscpy_s(funcItems[index]._itemName, menuItemSize, name);
	funcItems[index]._cmdID = (int)index;
	funcItems[index]._pFunc = func;
	funcItems[index]._init2Check = check;
	funcItems[index]._pShKey = shortcut;
}

sptr_t Plugin::CallNotepadPP(unsigned int message, uptr_t wParam, sptr_t lParam) {
	return ::SendMessage(nppHandle, message, wParam, lParam);
}

sptr_t Plugin::CallScintilla(unsigned int message, uptr_t wParam, sptr_t lParam) {
	return directFunc(directPointer, message, wParam, lParam);
}

BOOL WINAPI DllMain(HINSTANCE /*hinstDLL*/, DWORD fdwReason, LPVOID /*lpvReserved*/) {
	try {
		switch (fdwReason) {
			case DLL_PROCESS_ATTACH:
				// plugin.PluginInit();
				break;
			case DLL_PROCESS_DETACH:
				// plugin.PluginCleanup();
				break;
		}
	} catch (...) {
		return FALSE;
	}

	return TRUE;
}

extern "C" __declspec(dllexport) void setInfo(NppData nppData) {
	plugin.nppHandle = nppData._nppHandle;

	int which = 0;
	::SendMessage(plugin.nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);

	HWND scintillaHandle = which == 0 ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
	plugin.directFunc = (SciFnDirect)::SendMessage(scintillaHandle, SCI_GETDIRECTFUNCTION, 0, 0);
	plugin.directPointer = ::SendMessage(scintillaHandle, SCI_GETDIRECTPOINTER, 0, 0);

	plugin.CommandInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName() {
	return TEXT(PLUGIN_NAME);
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF) {
	*nbF = PLUGIN_COMMAND_COUNT;
	return plugin.funcItems;
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *) {
}

extern "C" __declspec(dllexport) LRESULT messageProc(UINT, WPARAM, LPARAM) {
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode() {
    return TRUE;
}
#endif	//UNICODE

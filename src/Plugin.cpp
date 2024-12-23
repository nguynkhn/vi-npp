#include "Plugin.h"

void Plugin::CommandInit() {
}

void Plugin::AddCommand(size_t index, TCHAR *name, PFUNCPLUGINCMD func, bool check, ShortcutKey *shortcut) {
	memcpy(funcItems[index]._itemName, name, menuItemSize);
	funcItems[index]._cmdID = (int)index;
	funcItems[index]._pFunc = func;
	funcItems[index]._init2Check = check;
	funcItems[index]._pShKey = shortcut;
}

void Plugin::SendMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	::SendMessage(handle, msg, wParam, lParam);
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
	// get handle
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);

	if (which == -1) return;
	plugin.handle = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

	plugin.CommandInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName() {
	return TEXT(PLUGIN_NAME);
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF) {
	*nbF = PLUGIN_COMMAND_COUNT;
	return plugin.funcItems;
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *) {}

extern "C" __declspec(dllexport) LRESULT messageProc(UINT, WPARAM, LPARAM) {
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode() {
    return TRUE;
}
#endif	//UNICODE

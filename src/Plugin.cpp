#include "Plugin.h"
#include "ViNpp.h"

Plugin plugin = {0};

void Plugin::InitHandle() {
	int which = 0;
	::SendMessage(plugin.nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);

	HWND scintillaHandle = which == 0
		? plugin.nppData._scintillaMainHandle
		: plugin.nppData._scintillaSecondHandle;
	plugin.directFunc = (SciFnDirect)::SendMessage(scintillaHandle, SCI_GETDIRECTFUNCTION, 0, 0);
	plugin.directPointer = ::SendMessage(scintillaHandle, SCI_GETDIRECTPOINTER, 0, 0);
}

void Plugin::InitCommand() {
	AddCommand(0, TEXT("Enable Vi mode"), ToggleVi, vi.enabled, NULL);
}

void Plugin::AddCommand(size_t index, TCHAR *name, PFUNCPLUGINCMD func, bool check, ShortcutKey *shortcut) {
	_tcscpy_s(funcItems[index]._itemName, menuItemSize, name);
	funcItems[index]._cmdID = (int)index;
	funcItems[index]._pFunc = func;
	funcItems[index]._init2Check = check;
	funcItems[index]._pShKey = shortcut;
}

sptr_t Plugin::CallNotepadPP(unsigned int message, uptr_t wParam, sptr_t lParam) {
	return ::SendMessage(nppData._nppHandle, message, wParam, lParam);
}

sptr_t Plugin::CallScintilla(unsigned int message, uptr_t wParam, sptr_t lParam) {
	return directFunc(directPointer, message, wParam, lParam);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID) {
	return TRUE;
}

extern "C" __declspec(dllexport) void setInfo(NppData nppData) {
	plugin.nppData = nppData;

	plugin.InitHandle();
	plugin.InitCommand();
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

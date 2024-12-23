#pragma once

#include "npp/PluginInterface.h"

#define PLUGIN_NAME "ViNpp"
#define PLUGIN_COMMAND_COUNT 1

extern struct Plugin {
	FuncItem funcItems[PLUGIN_COMMAND_COUNT];

	HWND nppHandle;
	SciFnDirect directFunc;
	sptr_t directPointer;

	void PluginInit();
	void PluginCleanup();

	void CommandInit();
	void AddCommand(size_t, TCHAR *, PFUNCPLUGINCMD, bool, ShortcutKey *);

	sptr_t CallNotepadPP(unsigned int, uptr_t, sptr_t);
	sptr_t CallScintilla(unsigned int, uptr_t, sptr_t);
} plugin;

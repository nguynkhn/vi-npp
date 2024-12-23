#pragma once

#include "npp/PluginInterface.h"

#define PLUGIN_NAME "ViNpp"
#define PLUGIN_COMMAND_COUNT 1

static struct Plugin {
	FuncItem funcItems[PLUGIN_COMMAND_COUNT];

	HWND handle;
	SciFnDirect directFunc;
	sptr_t directPointer;

	void PluginInit();
	void PluginCleanup();

	void CommandInit();
	void AddCommand(size_t, TCHAR *, PFUNCPLUGINCMD, bool, ShortcutKey *);

	void InitScintilla(HWND handle);
	sptr_t CallScintilla(unsigned int, uptr_t, sptr_t);
} plugin;

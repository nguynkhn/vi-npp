#ifndef PLUGIN_H
#define PLUGIN_H

#include "npp/PluginInterface.h"

#define PLUGIN_NAME "ViNpp"
#define PLUGIN_COMMAND_COUNT 1

struct Plugin {
	FuncItem funcItems[PLUGIN_COMMAND_COUNT];
	HWND handle;

	void PluginInit();
	void PluginCleanup();

	void CommandInit();
	void AddCommand(size_t, TCHAR *, PFUNCPLUGINCMD, bool, ShortcutKey *);

	void SendMessage(UINT, WPARAM, LPARAM);
} plugin;

#endif	// PLUGIN_H

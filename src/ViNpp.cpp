#include "ViNpp.h"
#include "Plugin.h"

Vi vi = {0};

void Vi::Toggle() {
	enabled = !enabled;
	
	plugin.CallNotepadPP(NPPM_SETMENUITEMCHECK, plugin.funcItems[0]._cmdID, enabled);
}
#include "ViNpp.h"
#include "Plugin.h"

Vi vi = {0};

void Vi::SetMode(ViMode _mode) {
	mode = _mode;

	int caretStyle = CARETSTYLE_LINE;
	if (mode == NORMAL) {
		caretStyle = CARETSTYLE_BLOCK;
	}

	plugin.CallScintilla(SCI_SETCARETSTYLE, caretStyle, 0);
}

void ToggleVi() {
	vi.enabled = !vi.enabled;

	if (vi.enabled) {
		vi.SetMode(NORMAL);
	} else {
		plugin.CallScintilla(SCI_SETCARETSTYLE, CARETSTYLE_LINE, 0);
	}

	plugin.CallNotepadPP(NPPM_SETMENUITEMCHECK, plugin.funcItems[0]._cmdID, vi.enabled);
}
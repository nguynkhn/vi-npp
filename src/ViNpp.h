#pragma once

enum ViMode { NORMAL, INSERT };

extern struct Vi {
	bool enabled;
	ViMode mode;

	void SetMode(ViMode);
} vi;

void ToggleVi();

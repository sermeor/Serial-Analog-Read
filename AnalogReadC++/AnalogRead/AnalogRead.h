#pragma once

#include <wx/wx.h>
#include "cMain1.h"
//Forward declarations.
class cMain1;
class config_dialog;

class AnalogRead : public wxApp
{
public: 
	AnalogRead();
	~AnalogRead();

private: 
	cMain1* analog_read_frame = nullptr;
public:
	virtual bool OnInit();

	void reset_application();

};

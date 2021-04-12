#pragma once
#include <wx/wx.h>
#include "cMain1.h"

//Forward declaration. 
class cMain1;
class config_dialog;
class contact_dialog;

class help_dialog : public wxDialog
{
public:
	help_dialog(cMain1& main_frame);
public:
	wxPanel* panel;
	wxBoxSizer* vbox;
	wxBoxSizer* hbox;
	wxStaticText* help_label = nullptr;
	wxButton* close_button = nullptr;
	cMain1* main_frame_ptr;

	wxDECLARE_EVENT_TABLE();

public:
	//Callback declarations
	void close_button_clicked(wxCommandEvent& evt);
};
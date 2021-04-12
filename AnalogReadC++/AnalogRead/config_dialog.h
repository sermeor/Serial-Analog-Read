#pragma once
#include <wx/wx.h>
#include "cMain1.h"

//Forward declaration. 
class cMain1;
class help_dialog;
class contact_dialog;

class config_dialog : public wxDialog
{
public:
	config_dialog(cMain1& main_frame);
public:
	wxPanel* panel;
	wxBoxSizer* vbox;
	wxBoxSizer* hbox;
	wxStaticBox* refresh_label = nullptr;
	wxTextCtrl* refresh_input = nullptr;
	wxStaticBox* graph_width_label = nullptr;
	wxTextCtrl* graph_width_input = nullptr;
	wxButton* apply_button = nullptr;
	wxButton* close_button = nullptr;
	cMain1* main_frame_ptr;
	char period_string[63];

	wxMessageDialog* error_message = new wxMessageDialog(NULL, wxT("Input error: negative values"),
		wxT("Error"), wxOK | wxICON_ERROR);

	wxDECLARE_EVENT_TABLE();

public:
	//Callback declarations
	void apply_button_clicked(wxCommandEvent& evt);
	void close_button_clicked(wxCommandEvent& evt);
	void apply_changes_to_parameters();
};





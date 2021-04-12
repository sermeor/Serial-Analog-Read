
#include "help_dialog.h"
using namespace std;


wxBEGIN_EVENT_TABLE(help_dialog, wxDialog)

EVT_BUTTON(4001, close_button_clicked)

wxEND_EVENT_TABLE()

help_dialog::help_dialog(cMain1& main_frame) : wxDialog(NULL, 4000, "Help", wxDefaultPosition, wxSize(250, 230))
{
    panel = new wxPanel(this, -1);

    vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    close_button = new wxButton(this, 4001, wxT("Close"),
        wxDefaultPosition, wxSize(70, 30));

    main_frame_ptr = &main_frame;
    help_label = new wxStaticText(panel, wxID_ANY, "Application created by the Hashemi Lab.", wxPoint(10, 10));

    hbox->Add(close_button, 1, wxLEFT, 5);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);
}


void help_dialog::close_button_clicked(wxCommandEvent& evt) {
    this->EndModal(this->GetReturnCode());
    evt.Skip();
}




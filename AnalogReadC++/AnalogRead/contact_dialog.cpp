
#include "contact_dialog.h"
using namespace std;


wxBEGIN_EVENT_TABLE(contact_dialog, wxDialog)

EVT_BUTTON(5001, close_button_clicked)

wxEND_EVENT_TABLE()

contact_dialog::contact_dialog(cMain1& main_frame) : wxDialog(NULL, 5000, "Contact", wxDefaultPosition, wxSize(250, 230))
{
    panel = new wxPanel(this, -1);

    vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    close_button = new wxButton(this, 5001, wxT("Close"),
        wxDefaultPosition, wxSize(70, 30));

    main_frame_ptr = &main_frame;
    contact_label = new wxStaticText(panel, wxID_ANY, "sergio.mena19@imperial.ac.uk", wxPoint(10, 70));

    hbox->Add(close_button, 1, wxLEFT, 5);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);
}


void contact_dialog::close_button_clicked(wxCommandEvent& evt) {
    this->EndModal(this->GetReturnCode());
    evt.Skip();
}
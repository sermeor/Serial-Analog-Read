
#include "config_dialog.h"
using namespace std;


wxBEGIN_EVENT_TABLE(config_dialog, wxDialog)

EVT_BUTTON(1001, apply_button_clicked)
EVT_BUTTON(1002, close_button_clicked)

wxEND_EVENT_TABLE()

config_dialog::config_dialog(cMain1 &main_frame) : wxDialog(NULL, 1000, "Graph config.", wxDefaultPosition, wxSize(250, 230))
{
    panel = new wxPanel(this, -1);

    vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    refresh_label = new wxStaticBox(panel, wxID_ANY, "Refresh frequency (Hz)",
        wxPoint(5, 5), wxSize(225, 50));
    
    refresh_input = new wxTextCtrl(panel, -1, to_string(main_frame.reading_frequency),
        wxPoint(25, 25));

    graph_width_label = new wxStaticBox(panel, wxID_ANY, "Graph width (Samples)",
        wxPoint(5, 55), wxSize(225, 50));

    graph_width_input = new wxTextCtrl(panel, -1, to_string(main_frame.graph_width),
        wxPoint(25, 75));

    apply_button = new wxButton(this, 1001, wxT("Apply"),
        wxDefaultPosition, wxSize(70, 30));
    if (main_frame.reading_flag) { apply_button->Enable(false); };
    close_button = new wxButton(this, 1002, wxT("Close"),
        wxDefaultPosition, wxSize(70, 30));

    main_frame_ptr = &main_frame;


    hbox->Add(apply_button, 1);
 
    hbox->Add(close_button, 1, wxLEFT, 5);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);
}

void config_dialog::apply_button_clicked(wxCommandEvent& evt) {
    apply_changes_to_parameters();
    evt.Skip();
}

void config_dialog::close_button_clicked(wxCommandEvent& evt) {
    this->EndModal(this->GetReturnCode());
    evt.Skip();
}

void config_dialog::apply_changes_to_parameters() {
    int f = wxAtoi(refresh_input->GetValue().mb_str());
    int w = wxAtoi(graph_width_input->GetValue().mb_str());
    if (f > 0 && w > 0) {
        main_frame_ptr->reading_frequency = f;
        main_frame_ptr->graph_width = w;
        this->EndModal(this->GetReturnCode());
    }
    else {
        error_message->ShowModal();
    }
}



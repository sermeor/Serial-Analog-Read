#include "cMain1.h"
using namespace std;

wxBEGIN_EVENT_TABLE(cMain1, wxFrame)
EVT_MENU(1000, graph_configuration_clicked)
EVT_MENU(3000, close_application)
EVT_BUTTON(0001, connect_button_clicked)
EVT_BUTTON(0002, start_button_clicked)
EVT_BUTTON(0003, stop_button_clicked)
EVT_TIMER(0004, on_serial_timer)
EVT_TOGGLEBUTTON(0005, record_file_clicked)
EVT_MENU(2000, reset_button_clicked)
EVT_MENU(4000, help_button_pushed)
EVT_MENU(5000, contact_button_pushed)
wxEND_EVENT_TABLE()


cMain1::cMain1(AnalogRead &app) : wxFrame(nullptr, wxID_ANY, "AnalogRead", wxPoint(30,30), wxSize(600, 550))

{
	full_app = &app;
	//Definition of the menu bar. 
	
	file_menu = new wxMenu();
	file_menu->Append(1000, "Graph config.");
	file_menu->Append(2000, "Reset");
	file_menu->Append(3000, "Quit");
	
	about_menu = new wxMenu();
	about_menu->Append(4000, "Help");
	about_menu->Append(5000, "Contact");
	menu_bar = new wxMenuBar;
	menu_bar->Append(file_menu, "File");
	menu_bar->Append(about_menu, "Info");
	this->SetMenuBar(menu_bar);

	connect_button = new wxButton(this, 0001, "Connect", wxPoint(10, 10), wxSize(150, 50));
	serial_port_label = new wxStaticText(this, wxID_ANY, "Serial port", wxPoint(10, 70));
	serial_port_input = new wxTextCtrl(this, wxID_ANY, "COM5", wxPoint(90, 70), wxSize(50, 20));

	baud_rate_label = new wxStaticText(this, wxID_ANY, "Baud rate", wxPoint(10, 90));
	baud_rate_input = new wxTextCtrl(this, wxID_ANY, "115200", wxPoint(90, 90), wxSize(50, 20));

	bytes_label = new wxStaticText(this, wxID_ANY, "Bytes", wxPoint(10, 110));
	bytes_input = new wxTextCtrl(this, wxID_ANY, "8", wxPoint(90, 110), wxSize(50, 20));

	start_button = new wxButton(this, 0002, "Start", wxPoint(10, 140), wxSize(50, 50));
	stop_button = new wxButton(this, 0003, "Stop", wxPoint(70, 140), wxSize(50, 50));

	serial_timer = new wxTimer(this, 0004);

	temperature_label = new wxStaticText(this, wxID_ANY, "Temperature:", wxPoint(10, 200));
	temperature_value = new wxStaticText(this, wxID_ANY, " ", wxPoint(100, 200));
	ph_label = new wxStaticText(this, wxID_ANY, "pH:", wxPoint(10, 220));
	ph_value = new wxStaticText(this, wxID_ANY, " ", wxPoint(100, 220));

	record_file_button = new wxToggleButton(this, 0005, "Record", wxPoint(10, 280), wxSize(50, 20));

	filename_label = new wxStaticText(this, wxID_ANY, "Filename", wxPoint(10, 310));
	filename_input = new wxTextCtrl(this, wxID_ANY, "log.txt", wxPoint(90, 310), wxSize(50, 20));

	temperature_graph = create_graph(temperature_graph, time_vector, temperature_vector, temperature_XY_vector, 
	200, 10, 300, 200, "Samples", "Temperature (ºC)", 0, 0, 50, 50, 4, *wxBLUE);


	ph_graph = create_graph(ph_graph, time_vector, ph_vector, ph_XY_vector, 200, 250, 300, 200, "Samples", "pH", 0, 0, 50, 50, 4, *wxRED);




}

cMain1::~cMain1()
{
}
//Callbacks.
void cMain1::connect_button_clicked(wxCommandEvent& evt) {
	serial_connection = new SerialPort((serial_port_input->GetValue()).mb_str(),
		wxAtoi(baud_rate_input->GetValue()), wxAtoi(bytes_input->GetValue()));
	if (serial_connection->isConnected()) {
		connect_button->SetBackgroundColour(wxColour(117, 255, 112));
	}
	else {
		error_message->ShowModal();
	}
	evt.Skip();
}

void cMain1::start_button_clicked(wxCommandEvent& evt) {
	if (!reading_flag && serial_connection->isConnected()) {
		reading_flag = true;
		write_to_serial();
		start_reading();
	}
	else {
		error_message2->ShowModal();
	}
	evt.Skip();
}

void cMain1::start_reading() {
serial_timer->Start(int(500/reading_frequency)); //Twice the arduino frequency. 
}

void cMain1::stop_button_clicked(wxCommandEvent& evt) {
	if (serial_connection->isConnected()) {
		reading_flag = false;
		stop_reading();
		write_to_serial();
	}
	else {
		error_message2->ShowModal();
	}
	evt.Skip();
}

void cMain1::stop_reading() {
	serial_timer->Stop();
}

void cMain1::reset_button_clicked(wxCommandEvent& evt) {
	reset_application();
	evt.Skip();
}
void cMain1::reset_application() {
	full_app->reset_application();
}

//Functions
void cMain1::change_displayed_value(wxStaticText* label, char *value) {
	label->SetLabel(value);
	label->Refresh();
}

void cMain1::on_serial_timer(wxTimerEvent& evt) {
	read_from_serial();
	evt.Skip();
}

void cMain1::update_vector(vector<double> &vtr, double value) {
	if (vtr.size() > graph_width) { update_width_of_vector(vtr);};
	vtr.push_back(value);
}

void cMain1::update_width_of_vector(vector<double> &vtr) {
	int difference = vtr.size() - graph_width;
	vtr.erase(vtr.begin(), vtr.begin() + difference);
}

void cMain1::graph_new_vector(vector<double>& vtr_x, vector<double>& vtr_y, mpFXYVector* vtr_xy, mpWindow* graph) {
	vtr_xy->AddData(vtr_x, vtr_y, 300);
	graph->Fit();
}

void cMain1::record_file_clicked(wxCommandEvent& evt) {
	if (record_file_button->GetValue()) {
		initialise_file();
	}
	else {
		close_file();
	}
	evt.Skip();
}


void cMain1::initialise_file() {
	reading_file = fopen((filename_input->GetValue()).mb_str(), "w");
	fprintf(reading_file, "Time (s) \t Temp (C) \t pH \n");
	reading_file_flag = true;
}
void cMain1::write_to_file() {
	fprintf(reading_file, received_data);
}

void cMain1::close_file() {
	reading_file_flag = false;
	fclose(reading_file);
}

mpWindow* cMain1::create_graph(mpWindow* graph, vector<double>& vtr_x, vector<double>& vtr_y, mpFXYVector* vtr_xy, int px, int py, int sx, int sy,
	string x_label, string y_label, int m1, int m2, int m3, int m4, int size, wxColor color) {
	graph = new mpWindow(this, wxID_ANY, wxPoint(px, py), wxSize(sx, sy));
	mpScaleX* xaxis = new mpScaleX(x_label, mpALIGN_BOTTOM, true);
	mpScaleY* yaxis = new mpScaleY(y_label, mpALIGN_LEFT, true);
	graph->SetMargins(m1, m2, m3, m4);
	xaxis->SetDrawOutsideMargins(false);
	yaxis->SetDrawOutsideMargins(false);
	graph->AddLayer(xaxis);
	graph->AddLayer(yaxis);
	graph->EnableMousePanZoom(false);
	graph->Fit();
	vtr_xy->SetData(vtr_x, vtr_y);
	vtr_xy->SetPen(wxPen(color, size, wxPENSTYLE_SOLID));
	graph->AddLayer(vtr_xy);
	return graph;
}

void cMain1::graph_configuration_clicked(wxCommandEvent& evt) {
	configuration_popup = new config_dialog(*this);
	configuration_popup->ShowModal();
	evt.Skip();
}


void cMain1::read_from_serial() {
	reading_buffer = serial_connection->readSerialPort(received_data, input_buffer_size);
	if (reading_buffer == input_buffer_size) {
		if (reading_file_flag) { write_to_file(); };

		update_vector(time_vector, sample_count);
		//Temperature update.
		received_data_splitted = strtok(received_data, "\t\n");
		change_displayed_value(temperature_value, received_data_splitted);
		update_vector(temperature_vector, atof(received_data_splitted));
		graph_new_vector(time_vector, temperature_vector, temperature_XY_vector, temperature_graph);
		//pH update.
		received_data_splitted = strtok(NULL, "\t\n");
		change_displayed_value(ph_value, received_data_splitted);
		update_vector(ph_vector, atof(received_data_splitted));
		graph_new_vector(time_vector, ph_vector, ph_XY_vector, ph_graph);
		received_data_splitted = strtok(NULL, "\t\n");
		++sample_count;
	};
}
void cMain1::write_to_serial() {
	if (serial_connection->isConnected()) {
		snprintf(sending_data, output_buffer_size, "%d\t%d\n", reading_flag, int(1000 / reading_frequency));
		serial_connection->writeSerialPort(sending_data, output_buffer_size);
	}
}

void cMain1::help_button_pushed(wxCommandEvent& evt) {
	help_popup = new help_dialog(*this);
	help_popup->ShowModal();
	evt.Skip();
}

void cMain1::contact_button_pushed(wxCommandEvent& evt) {
	contact_popup = new contact_dialog(*this);
	contact_popup->ShowModal();
	evt.Skip();
}

void cMain1::close_application(wxCommandEvent& evt) {
	Close(true);
}



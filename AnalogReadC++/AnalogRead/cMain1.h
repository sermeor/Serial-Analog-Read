#pragma once

#include <wx/wx.h>
#include <wx/tglbtn.h>
#include <iostream>
#include <string.h>
#include "AnalogRead.h"
#include "mathplot.h"
#include "config_dialog.h"
#include "help_dialog.h"
#include "contact_dialog.h"
#include "SerialPort.hpp"
using namespace std;

//Forward declaration.
class config_dialog;
class help_dialog;
class contact_dialog;
class AnalogRead;

class cMain1 : public wxFrame
{
public:
	cMain1(AnalogRead& app);
	~cMain1();
public: 
	AnalogRead* full_app;
	wxButton *connect_button = nullptr;
	wxButton *start_button = nullptr;
	wxButton* stop_button = nullptr;
	wxToggleButton* record_file_button = nullptr;

	wxStaticText *serial_port_label = nullptr;
	wxTextCtrl *serial_port_input = nullptr;
	SerialPort  *serial_connection = nullptr;
	wxMessageDialog *error_message = new wxMessageDialog(NULL, wxT("Unsuccesful connection to serial port"),
		wxT("Error"), wxOK | wxICON_ERROR);

	wxMessageDialog* error_message2 = new wxMessageDialog(NULL, wxT("Serial connection not established"),
		wxT("Error"), wxOK | wxICON_ERROR);

	wxStaticText *baud_rate_label = nullptr;
	wxTextCtrl *baud_rate_input = nullptr;

	wxStaticText *bytes_label = nullptr;
	wxTextCtrl *bytes_input = nullptr;

	wxStaticText *temperature_label = nullptr;
	wxStaticText *ph_label = nullptr;
	wxStaticText* temperature_value = nullptr;
	wxStaticText* ph_value = nullptr;


	char received_data[63];
	char sending_data[63];
	char* received_data_splitted;
	const int input_buffer_size = 10;
	const int output_buffer_size = 64;
	bool reading_flag = false;
	bool reading_file_flag = false;
	int reading_buffer = 0;
	int reading_frequency = 10;
	unsigned long sample_count = 1;
	int graph_width = 200;
	
	wxTimer *serial_timer;

	//File logging. 
	FILE *reading_file; 
	wxStaticText* filename_label = nullptr;
	wxTextCtrl* filename_input = nullptr;

	//Vectors
	vector<double> time_vector;
	vector<double> temperature_vector;
	vector<double> ph_vector;
	//Graph vectors. 
	mpFXYVector* temperature_XY_vector = new mpFXYVector();
	mpFXYVector* ph_XY_vector = new mpFXYVector();
	//Graphs. 
	mpWindow* temperature_graph;
	mpWindow* ph_graph;

	//Menu
	wxMenuBar* menu_bar;
	wxMenu* file_menu;
	wxMenu* about_menu;
	config_dialog* configuration_popup = nullptr;
	help_dialog* help_popup = nullptr;
	contact_dialog* contact_popup = nullptr;


	//Function declarations.
	void change_displayed_value(wxStaticText* label, char *value);
	//Callback declarations. 
	void graph_configuration_clicked(wxCommandEvent& evt);
	void connect_button_clicked(wxCommandEvent& evt);
	void start_button_clicked(wxCommandEvent& evt);
	void reset_button_clicked(wxCommandEvent& evt);
	void contact_button_pushed(wxCommandEvent& evt);
	void help_button_pushed(wxCommandEvent& evt);
	void start_reading();
	void stop_button_clicked(wxCommandEvent& evt);
	void stop_reading();
	void read_from_serial();
	void write_to_serial();
	void reset_application();
	void close_application(wxCommandEvent& evt);
	void on_serial_timer(wxTimerEvent& evt);
	void record_file_clicked(wxCommandEvent& evt);
	void update_vector(vector<double> &vtr, double value);
	void update_width_of_vector(vector<double>& vtr);
	void graph_new_vector(vector<double>& vtr_x, vector<double>& vtr_y, mpFXYVector* vtr_xy, mpWindow* graph);
	void initialise_file();
	void write_to_file();
	void close_file();


	mpWindow* create_graph(mpWindow* graph, vector<double>& vtr_x, vector<double>& vtr_y, mpFXYVector* vtr_xy, int px, int py, int sx, int sy,
		string x_label, string y_label, int m1, int m2, int m3, int m4, int size, wxColor color);
	
	
	wxDECLARE_EVENT_TABLE();

	
};





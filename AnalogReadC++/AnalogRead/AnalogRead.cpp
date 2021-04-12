#include "AnalogRead.h"

wxIMPLEMENT_APP(AnalogRead);

AnalogRead::AnalogRead()
{
}

AnalogRead::~AnalogRead()
{
}

bool AnalogRead::OnInit()
{
	analog_read_frame = new cMain1(*this);
	analog_read_frame->Show();
	return true;
}

void AnalogRead::reset_application() {
	analog_read_frame->Destroy();
	analog_read_frame = new cMain1(*this);
	analog_read_frame->Show();
}

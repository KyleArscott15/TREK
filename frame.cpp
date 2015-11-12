#include <frame.h>

int Frame::setName(char * frame_name){
	int ret = name.length();
	name = std::string(frame_name);
	return ret;
}

int Frame::addSlot(char* slot_name, char* unit, All_type default_val){
	Slot slot(slot_name, unit, default_val);
	slots.push_back(slot);
}

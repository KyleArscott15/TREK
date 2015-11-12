#ifndef FRAME_H
#define FRAME_H

#include <top_level_inclusions.h>

enum SLOT_INFO{
	SLOT_TYPE = 0,
	SLOT_DEFAULT_VALUE,
	SLOT_NAME
};

class Slot{
public:
	Slot(char* slot_name, char* slot_unit, All_type slot_default_val){
		name = std::string(slot_name);
		unit = std::string(unit);
		default_val = slot_default_val;
	};
	virtual ~Slot(){};

	// return value in either an All_type returned or modify given pointer
	// If the pointer option is used then the returned All_type returns errors
	All_type get(SLOT_INFO get_type, All_type *at=NULL);

	// set a parameter of this slot based on what's in the All_type
	int set(SLOT_INFO set_type, All_type *at);

//	boost::function() callback_procedure; // pg. 234 BES:AT
private:
	std::string name;
	std::string unit; //ex. "km"
	All_type value;
	All_type default_val; 
};

class Frame{
public:
	//Frame();
	//virtual ~Frame(){};
	 std::string getName(){return name;};
	int setName(char* frame_name);
	int addSlot(char* slot_name, char* unit, All_type default_val);
private:
	std::vector<Slot> slots;
	std::string name;
		
};





#endif // FRAME_H

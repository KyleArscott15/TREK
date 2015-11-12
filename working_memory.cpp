#include <working_memory.h>

PromptHistory::PromptHistory(){
}
PromptHistory::~PromptHistory(){
}

PackingList::PackingList(){
}
PackingList::~PackingList(){
}

WorkingMemory::WorkingMemory(){
	//wmAccess(WM_ADD, WM_STATE, );

};
WorkingMemory::~WorkingMemory(){
};
WORKING_MEMORY_ERROR WorkingMemory::wmAccess(WORKING_MEMORY_ACTION action, WORKING_MEMORY_SECTION section, void* input, void* output){
	if(action == WM_ADD){
		printf("about to add to WM in section [%d]\n", section);
	}
	return WM_SUCCESS;
}
All_type WorkingMemory::wmAccess(WORKING_MEMORY_ACTION action, WORKING_MEMORY_SECTION section, void *input){
	All_type ret_val;

	if(action == WM_GET){
		if(section == WM_STATE){
			ret_val = getStateValue(input);			
		}
	}	
	
	return ret_val;
}

All_type WorkingMemory::getStateValue(void *input){
	All_type all(6);
	return all;
}

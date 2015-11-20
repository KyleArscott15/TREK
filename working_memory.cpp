#include <working_memory.h>

PromptHistory::PromptHistory(){
}
PromptHistory::~PromptHistory(){
}

PackingList::PackingList(){
}
PackingList::~PackingList(){
}

static StateTable initializeInitialStateTable(){
	StateTable st;
	st[SESSION_DURATION] = new IntegerState(SESSION_DURATION);
	return st;	
}
static StateTable initial_state_table = initializeInitialStateTable();

WorkingMemory::WorkingMemory(){
	// add in sessional information to initialize the working memory
	wmAccess(WM_ADD, WM_STATE, (void*)initial_state_table[SESSION_DURATION], NULL);
};
WorkingMemory::~WorkingMemory(){
};
WORKING_MEMORY_ERROR WorkingMemory::wmAccess(WORKING_MEMORY_ACTION action, WORKING_MEMORY_SECTION section, void* input, void* output){
	if(action == WM_ADD){
		printf("about to add to WM in section [%d]\n", section);
//		State *state = new State();
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

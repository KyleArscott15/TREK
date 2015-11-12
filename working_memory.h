#ifndef WORKING_MEMORY_H
#define WORKING_MEMORY_H

#include <state.h>
#include <frame.h>
#include <map>

enum WORKING_MEMORY_SECTION{
	WM_STATE = 1,
	WM_PROMPT_HISTORY = 2,
	WM_PACKING_LIST = 3
};
enum WORKING_MEMORY_ACTION{
	WM_EXISTS = 1,
	WM_ADD = 2,
	WM_REMOVE = 3,
	WM_GET = 4,
	WM_SET = 5
};
enum WORKING_MEMORY_ERROR{
	WM_ALREADY_EXISTS = 1, // tried to WM_ADD, but it already exists, not an error
	WM_SUCCESS = 0,
	WM_MISMATCH = -1, // combo of WMS and WMA is not meaningful
	WM_DNE = -2, // tried to remove or get, but that item does not exist in WM 
	WM_FAIL_ACTION = -3// generic error
};
class PromptHistory{
public:
	PromptHistory();
	~PromptHistory();
private:
	std::string raw_response;
	int prompt_response_id; // from [1, n] where n is number of user prompts
	std::string date_prompted; // output of `date`, used to timestamp user response for evidence in court
	All_type sanitized_response;
	static All_type sanitizeInput(std::string raw_response);
};

class PackingList{
public:
	 PackingList();
	~PackingList();
	WORKING_MEMORY_ERROR addFrame(Frame frame){
		
		std::string frame_name = frame.getName();
		if(packing_list.count(frame_name) > 0){
			return WM_ALREADY_EXISTS; 
		}

		packing_list[frame_name] = frame;
		return WM_SUCCESS;
	};

	WORKING_MEMORY_ERROR removeFrame(Frame frame){
		std::string frame_name = frame.getName();
		if(packing_list.count(frame_name) == 0){
			return WM_DNE;
		}
		int num_removed = packing_list.erase(frame_name);
		if(num_removed){
			return WM_SUCCESS;
		}else{
			return WM_FAIL_ACTION;
		}
	};
private:
	std::map<std::string, Frame> packing_list; //string key is the frame_name of the frame it stores, used a map for fast "existence" queries
};

class WorkingMemory{
public:
	WorkingMemory();
	~WorkingMemory();
	int getHikingDistance(){return 6;};
	WORKING_MEMORY_ERROR wmAccess(WORKING_MEMORY_ACTION action, WORKING_MEMORY_SECTION section, void *input, void *output);
	 // good for using in an antedendant statement, then use dot operator to get value that you want
	All_type wmAccess(WORKING_MEMORY_ACTION action, WORKING_MEMORY_SECTION section, void *input);
private:
	// these are the 3 main sections of the working memory
	std::vector<State*> state_vector;
	std::vector<PromptHistory*> prompt_history_vector;
	PackingList packing_list;	

	All_type getStateValue(void* input);
};

#endif

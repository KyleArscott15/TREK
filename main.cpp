#include <top_level_inclusions.h>
#include <application_specific_definitions.h>
#include <state.h>
#include <frame.h>
#include <knowledge_base.h>
#include <inference_engine.h>
#include <user_input.h>
int begin_consultation(){
	printf("Beginning consultation...\n");
	HLINE();
}
int end_consultation(){
	printf("Ending consultation...\n");
	HLINE();
	exit(-1);
}
static builtin_t initialize_built_in(){	
	builtin_t builtins;
	std::string doc("doc");
	std::string end("exit");
	boost::function<int(void)> f = documentation;
	boost::function<int(void)> f2 = end_consultation;	
	builtins[doc] = f;
	builtins[end] = f2;
	return builtins;
}
static builtin_t builtins = initialize_built_in();
int recognize_built_in(std::string response){
	int ret = GENERIC_ERROR;
	for(std::map<std::string,boost::function<int(void)>>::iterator it=builtins.begin(); it!=builtins.end(); ++it){
		if(response.compare(it->first) == 0){
			ret = it->second();
			goto done_builtin;
		}
	}
done_builtin:
	if(ret == 0)
		ret = GENERIC_SUCCESS;
	return ret;
}
int main(){

	UserInput ui;
	KnowledgeBase kb;
	WorkingMemory wm;
	InferenceEngine ie;

	Rule *rule = NULL;
	std::string response;
	int prompt_success = ~SCANF_SUCCESS;	

	welcome();
	description();
	list_special_commands();
	begin_consultation();
	
	for(;;){
		rule = NULL;
		response.clear();
		prompt_success = ~SCANF_SUCCESS;
	
		ie.infer_next_rule(&rule);

		if(rule == NULL){
			// intead of going to end of thing, make a change to WM that will make a rule fire next time
			// unless you think it will change by itself
			goto end_of_loop;
		}

		prompt_success = ui.issuePrompt(rule->prompt, rule->format, &response);
	
		if(recognize_built_in(response) == GENERIC_SUCCESS){
			goto end_of_loop;
		}

end_of_loop:
		usleep(1);
	}
	
	return 0;
}

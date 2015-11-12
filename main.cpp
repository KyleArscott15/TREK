#include <top_level_inclusions.h>
#include <application_specific_definitions.h>
#include <state.h>
#include <frame.h>
#include <knowledge_base.h>
#include <prompt.h>
int begin_consulation(){
	printf("Beginning consulation...\n");
	printf("=================================================\n");
	exit(-1); // xxx KA
}

// XXX issue: I want to input "no way", but scanf delimits at spaces.
int issue_prompt(char *prompt, char *format, char **response){
	printf("%s", prompt);
	int ret = scanf(format, response);
	//fflush(stdin);
	return ret;
}

int infer_next_rule(Rule **rule){
	//Rule *r = new Rule(); // xxx KA memory only for testing
	//r->setPrompt((char*)"Are you feeling well today?\n");
	//r->setFormat((char*)"%s");
	*rule = NULL;
}

int main(){

	KnowledgeBase kb;

	//State *s = new State();

	welcome();
	description();
	list_special_commands();
	begin_consulation();

	char response[RESPONSE_LENGTH];
	bzero(response, RESPONSE_LENGTH);
	int prompt_success = ~SCANF_SUCCESS;
	Rule *rule = NULL;	

	for(;;){
		//response = NULL;
		bzero(response, RESPONSE_LENGTH);
		prompt_success = ~SCANF_SUCCESS;
		rule = NULL;

		infer_next_rule(&rule);
		prompt_success = issue_prompt((char*)rule->prompt.c_str(), (char*)rule->format.c_str(), (char**)&response);

		printf("prompt_success[%d]\n", prompt_success);
		fflush(stdout);
		printf("response[%s]\n", response);

		// recongnize special commands from user
		if(strcmp("doc", response) == 0){
			documentation();
			goto end_of_loop;
		}
		if(strcmp("exit", response) == 0){
			break;
		}
		
		// no special commands, parse user input

end_of_loop:
		system("sleep 1");
	}
	
	return 0;
}

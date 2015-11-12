#ifndef PROMPT_H
#define PROMPR_H

#include <top_level_inclusions.h>

static int promptUser(std::string prompt, std::string raw_response){
	char response[STRING_LENGTH];
	bzero(response, STRING_LENGTH);
	int ret = GENERIC_ERROR;
	printf("%s", prompt.c_str());
	fflush(stdin);
	ret = scanf("%s", response);
	raw_response = std::string(response);
	return ret;
}

#endif

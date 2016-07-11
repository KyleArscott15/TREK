#include "user_input.h"

int UserInput::issuePrompt(string prompt, string format, string& response) {
  // issue the prompt to the console
  printf(format.c_str(), prompt.c_str());

  // get the user response
  getline(cin, response);

  response = sanitizeInput(response);

  return SUCCESS;
}

string UserInput::sanitizeInput(string raw_response) {
  string sanitized_response;

  sanitized_response = raw_response;
  return sanitized_response;
}

int parseResposeForRule(Rule  *rule,
                        string response) {
  // response can be:
  // a) binary, yes or no
  // b) m choose n, ex. 4 activities choose 2, or pick one of the following
  // c) input n numbers, ex. list your 5 favourite numbers
  // d) an All_type or enum DATA_TYPE

  return SUCCESS;
}


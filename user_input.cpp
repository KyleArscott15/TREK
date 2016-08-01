#include "user_input.h"
#include <stdexcept>

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

All_type UserInput::parseResposeForRule(Rule  *rule,
                                        string response) {
  // response can be:
  // a) binary, yes or no
  // b) m choose n, ex. 4 activities choose 2, or pick one of the following
  // c) input n numbers, ex. list your 5 favourite numbers
  // d) an All_type or enum DATA_TYPE

  All_type at;
  int BASE_10 = 10;

  at.type = rule->getResponseType();

  if (at.type == TYPE_BOOL) {
    // make sure {1,y,Y,true} or {0,n,N,false}
    if ((response == "1") || (response == "y") || (response == "Y") ||
        (response == "true")) {
      at.b = true;
    } else if ((response == "0") || (response == "n") || (response == "N") ||
               (response == "false")) {
      at.b = false;
    } else {
      at.b = false;
    }
  } else if (at.type == TYPE_STRING) {
    // put as is into wm
    at.type = TYPE_INVALID;
  } else if (at.type == TYPE_INTEGER) {
    try {
      int i = stoi(response, nullptr, BASE_10);
      at.i = i;
    } catch (const std::invalid_argument& ia) {
      // cerr << "Invalid argument: " << ia.what() << endl;
      at.type = TYPE_INVALID;
    } catch (const std::out_of_range& oor) {
      // cerr << "Out of Range error: " << oor.what() << '\n';
      at.type = TYPE_INVALID;
    }
  } else {
    at.type = TYPE_INVALID;
  }

  return at;
}


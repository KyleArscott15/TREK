#include "user_input.h"
#include <stdexcept>

int UserInput::issuePrompt(Rule *rule, string& response) {
  // issue the prompt to the console
  printf("%s %s\n", rule->getPrompt().c_str(), userOptions(
           rule->getResponseType()).c_str());

  // get the user response
  getline(cin, response);

  response = sanitizeInput(response);

  return SUCCESS;
}

int UserInput::issueBuiltInPrompt(string& response) {
  // issue the prompt to the console
  printf("%s %s\n", "Use any builtin command:", "::");

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

string UserInput::userOptions(TYPE promptType) {
  switch (promptType) {
  case TYPE_BOOL:
    return string("[1,y,Y,yes,true] or [0,n,N,no,false]");

    break;

  case TYPE_STRING:
    return string("[abc...]");

    break;

  case TYPE_INTEGER:
    return string("[123...]");

    break;

  default:
    return string("");
  }
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
        (response == "yes") ||
        (response == "true")) {
      at.b = true;
    } else if ((response == "0") || (response == "n") || (response == "N") ||
               (response == "no") ||
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


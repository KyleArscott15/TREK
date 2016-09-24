#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "top_level_inclusions.h"
#include "knowledge_base.h"

class UserInput {
public:

  UserInput() {}

  ~UserInput() {}

  int      issuePrompt(Rule   *rule,
                       string& response);
  int      issueBuiltInPrompt(string& response,
                              string  builtInCommands);
  All_type parseResposeForRule(Rule  *rule,
                               string response);
  string   userOptions(TYPE promptType);

private:

  string sanitizeInput(string raw_response);
};

#endif // ifndef USER_INPUT_H

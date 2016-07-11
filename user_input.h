#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "top_level_inclusions.h"
#include "knowledge_base.h"

class UserInput {
public:

  UserInput() {}

  ~UserInput() {}

  int issuePrompt(string  prompt,
                  string  format,
                  string& response);
  int parseResposeForRule(Rule  *rule,
                          string response);

private:

  string sanitizeInput(string raw_response);
};

#endif // ifndef USER_INPUT_H

#include "shell.h"
#include "knowledge_base.h"
#include "application_specific_definitions.h"

#include <unistd.h>

Shell::Shell(UserInput       *user_input,
             WorkingMemory   *working_memory,
             InferenceEngine *inference_engine)
{
  ui = user_input;
  wm = working_memory;
  ie = inference_engine;
}

Shell::~Shell()
{}

int Shell::beginConsultation() {
  printf("Beginning consultation...\n");
  HLINE();
}

int Shell::endConsultation() {
  printf("Ending consultation...\n");
  HLINE();
  wm->saveList(PACKING_LIST_FILENAME);
  _exit(0); // xxx KA using _exit instead of exit to remove warning, but we may
            // want to reintroduce later if we deal with signals
}

int Shell::usage() {
  printf("\n");
  printf("Run with no arguments.\n");
  printf("Built-in commands can be used at any time: [%s]\n",
         getBuiltInCommands().c_str());
}

int Shell::help() {
  usage();
  return SUCCESS;
}

int Shell::wmContents() {
  wm->printMemoryDump();
  return SUCCESS;
}

int Shell::printList() {
  wm->printList();
  return SUCCESS;
}

string Shell::getBuiltInCommands() {
  string commands;

  commands += string(DOC);
  commands += string(", ");
  commands += string(EXIT);
  commands += string(", ");
  commands += string(HELP);
  commands += string(", ");
  commands += string(WM_CONTENTS);
  commands += string(", ");
  commands += string(PRINT_LIST);

  return commands;
}

int Shell::recognizeBuiltIn(string response) {
  int ret = SUCCESS;

  if (response.compare(DOC) == 0) {
    documentation();
  } else if (response.compare(EXIT) == 0) {
    endConsultation();
  } else if (response.compare(HELP) == 0)  {
    help();
  } else if (response.compare(WM_CONTENTS) == 0)  {
    wmContents();
  } else if (response.compare(PRINT_LIST) == 0)  {
    printList();
  } else {
    ret = NO_MATCH;
  }
  return ret;
}

bool Shell::ruleNull(Rule *rule) {
  if (rule == NULL) {
    return true;
  }

  // check other fields, like rule type
  // to see if it is valid

  return false;
}

void Shell::run() {
  welcome();
  description();
  listSpecialCommands();
  beginConsultation();

  Rule *rule, rule2;
  string   response;
  int      prompt_success;
  All_type cleanResponse;

  Rule r;
  HikeDistanceRule hdr;

  for (;;) {
    // clear shell variables
    rule = NULL;
    response.clear();
    prompt_success = ~SCANF_SUCCESS;

    if (ie->inferNextRule(&rule, wm) < SUCCESS) {
      printf("No rule is true.\n");
      ui->issueBuiltInPrompt(response, getBuiltInCommands());

      // endConsultation();
      // goto end_of_loop;
      goto processBuiltIn;
    }

    if (rule != NULL) {
      ui->issuePrompt(rule, response);
    } else {
      goto end_of_loop;
    }

processBuiltIn:

    if (recognizeBuiltIn(response) == SUCCESS) {
      continue;
    }

    // no special commands, parse user input
    if (ruleNull(rule) == false) {
      cleanResponse = ui->parseResposeForRule(rule, response);
    }

    if (cleanResponse.getType() == TYPE_INVALID) {
      printf("Please format your input and try again...\n\n");
      goto end_of_loop;
    }

    if (ruleNull(rule) == false) {
      // attempt to add the new information to the working memory
      rule->setPromptResponseToWM(cleanResponse, wm);

      // if the prompt has an action, activate it now
      rule->evaluateAction(wm);
      rule->setRuleTriggered(true);
    }

    continue;

end_of_loop:

    // small delay between screen prompts
    // so that user is triggered by new data
    usleep(500000);
  }

  endConsultation();
}

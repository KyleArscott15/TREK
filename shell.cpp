#include "shell.h"
#include "knowledge_base.h"
#include "application_specific_definitions.h"

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
  exit(-1);
}

int Shell::usage() {
  printf("\n");
  printf("Run with no arguments.\n");
  printf("Built-in commands can be used at any time:\n");
}

int Shell::help() {
  usage();
  return SUCCESS;
}

int Shell::recognizeBuiltIn(string response) {
  int ret = SUCCESS;

  if (response.compare(DOC) == 0) {
    documentation();
  } else if (response.compare(EXIT) == 0) {
    endConsultation();
  } else if (response.compare(HELP) == 0)  {
    help();
  } else {
    ret = NO_MATCH;
  }
  return ret;
}

void Shell::run() {
  welcome();
  description();
  listSpecialCommands();
  beginConsultation();

  Rule  *rule;
  string response;
  int    prompt_success;

  for (;;) {
    // clear shell variables
    rule = NULL;
    response.clear();
    prompt_success = ~SCANF_SUCCESS;

    if (ie->inferNextRule(&rule) < SUCCESS) {
      printf("error with stuff\n");
      continue;
    }

    if (rule != NULL) {
      ui->issuePrompt(rule->prompt, rule->format, response);
    } else {
      goto end_of_loop;
    }

    if (recognizeBuiltIn(response) == SUCCESS) {
      continue;
    }

    // no special commands, parse user input
    if (ui->parseResposeForRule(rule, response) < SUCCESS) {}

    continue;

end_of_loop:
    system("sleep 1");
  }

  endConsultation();
}


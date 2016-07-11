#include "inference_engine.h"

InferenceEngine::InferenceEngine(KnowledgeBase *knowledgeBase) {
  kb = knowledgeBase;
}

InferenceEngine::~InferenceEngine() {}

int InferenceEngine::inferNextRule(Rule **rule) {
  vector<Rule> ruleSet = kb->contendingRules();

  if (ruleSet.size() > 0) {
    *rule = &(ruleSet[0]);
    return SUCCESS;
  }
  return NO_MATCH;
}


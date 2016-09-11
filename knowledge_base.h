#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <vector>

#include "top_level_inclusions.h"
#include "working_memory.h"
#include "frame.h"

#define RULE_IF(rule_name, condition)     \
  bool rule_name::evaluateAntecendant() { \
    return ((condition));                 \
  }

#define RULE_AC(rule_name, action)   \
  bool rule_name::evaluateAction() { \
    ((action));                      \
    return true;                     \
  }

#define RULE_PROPERTY(rule_name, property, value) \
  int rule_name::setProperties() {                \
    properties[((property))] = ((value));         \
    return SUCCESS;                               \
  }

#define INPUT_RULE(rule_name, format, prompt, response_type) \
  class rule_name : public Rule {                            \
public:                                                      \
    rule_name() {                                            \
      ruleName     = string(rule_name);                      \
      ruleType     = INPUT_RULE;                             \
      responseType = response_type;                          \
      setFormat(format);                                     \
      setPrompt(prompt);                                     \
    }                                                        \
    virtual bool evaluateAntecendant();                      \
    virtual bool evaluateAction();                           \
    virtual int  setPromptResponseToWM(All_type       at,    \
                                       WorkingMemory * wm);  \
    int setProperties();                                     \
protected:                                                   \
private:                                                     \
  }

class Rule;

class KnowledgeBase { // xxx TODO :public Singleton{
public:

  KnowledgeBase();
  ~KnowledgeBase();
  static map<string, Frame> frames;
  vector<Rule *>contendingRules(WorkingMemory *wm);

protected:

private:

  static map<string, Frame>initializeFrames();
  int                      initializeRules();

  vector<Rule *> rules;
};

typedef enum Rule_Type {
  UNASSIGNED_RULE = 0,
  INPUT_RULE      = 1,
  PROCESSING_RULE = 2,
  OUTPUT_RULE     = 3
} RuleType;

typedef enum Rule_Property {
  ONE_SHOT = 0,
  PRIORITY = 1
} RuleProperty;

class Rule {
public:

  Rule() {
    ruleTriggered = false;
    ruleType      = UNASSIGNED_RULE;
  }

  virtual ~Rule() {}

  bool         stateExists(WorkingMemory *wm,
                           string         state);
  bool         stateTrue(WorkingMemory *wm,
                         string         state);
  bool         stateFalse(WorkingMemory *wm,
                          string         state);
  bool         stateIsBool(WorkingMemory *wm,
                           string         state);
  bool         stateExistsAndTrue(WorkingMemory *wm,
                                  string         state);
  bool         stateExistsAndFalse(WorkingMemory *wm,
                                   string         state);

  virtual bool evaluateAntecendant(WorkingMemory *wm) {
    return false;
  }

  virtual bool evaluateAction(WorkingMemory *wm) {
    return false;
  }

  virtual int setProperty(RuleProperty property, int value) {
    properties[property] = value;
    return SUCCESS;
  }

  virtual int setPromptResponseToWM(All_type at, WorkingMemory *wm) {
    return -1;
  }

  virtual string getPrompt() {
    return prompt;
  }

  virtual string getFormat() {
    return format;
  }

  TYPE getResponseType() {
    return responseType;
  }

  bool setRuleTriggered(bool triggered) {
    bool returnTrig = getRuleTriggered();

    ruleTriggered = triggered;
    return returnTrig;
  }

  bool getRuleTriggered() {
    return ruleTriggered;
  }

  bool getProperty(RuleProperty property) {
    return properties[property];
  }

  string getRuleName() {
    return ruleName;
  }

  RuleType getRuleType() {
    return ruleType;
  }

  int setPrompt(char *input_prompt);
  int setPrompt(string input_prompt);
  int setFormat(char *input_format);
  int setFormat(string input_format);

protected:

  string   ruleName; // for output use only
  string   prompt;
  string   format;
  TYPE     responseType;
  RuleType ruleType;
  bool     ruleTriggered;
  bool     oneShot;

  // int is either
  // a) bool (0 false, 1 true)
  // b) the integer literal
  // c) an index to a string
  map<RuleProperty, int> properties;

private:
};

// input rules

#define INPUT_RULE_DEFINE(ruleName)                         \
  class ruleName : public Rule {                            \
public:                                                     \
    ruleName();                                             \
    ~ruleName();                                            \
    virtual bool   evaluateAntecendant(WorkingMemory * wm); \
    virtual bool evaluateAction(WorkingMemory * wm);        \
    virtual int  setPromptResponseToWM(All_type       at,   \
                                       WorkingMemory * wm); \
protected:                                                  \
private:                                                    \
  };                                                        \

INPUT_RULE_DEFINE(HikeTrueRule);
INPUT_RULE_DEFINE(CampingTrueRule);
INPUT_RULE_DEFINE(CarCampingTrueRule);
INPUT_RULE_DEFINE(KayakingTrueRule);
INPUT_RULE_DEFINE(KayakingNightTrueRule);
INPUT_RULE_DEFINE(HikeDistanceRule);

// processing rules

// output rules

#define OUTPUT_RULE_DEFINE(ruleName)                        \
  class ruleName : public Rule {                            \
public:                                                     \
    ruleName();                                             \
    ~ruleName();                                            \
    virtual bool   evaluateAntecendant(WorkingMemory * wm); \
    virtual bool evaluateAction(WorkingMemory * wm);        \
protected:                                                  \
private:                                                    \
  };

OUTPUT_RULE_DEFINE(BootsRule);
OUTPUT_RULE_DEFINE(AquaTabsRule);
OUTPUT_RULE_DEFINE(BasicHikingListRule);
OUTPUT_RULE_DEFINE(BasicCampingListRule);
OUTPUT_RULE_DEFINE(BasicKayakingListRule);
OUTPUT_RULE_DEFINE(BasicKayakingListNightRule);
OUTPUT_RULE_DEFINE(BasicCarCampingRule);
OUTPUT_RULE_DEFINE(NotCarCampingFoodRule);

// Ways to access WM
#define F(item) (&KnowledgeBase::frames[item])

// states
// string is used internally to differentiate states
#define NUM_NIGHTS              string("numNights")
#define HIKE_DISTANCE_M         string("hikeDistanceM")
#define OUTDOORS                string("outdoors")
#define HIKE_TRUE               string("hikeTrue")
#define CAMPING_TRUE            string("campingTrue")
#define CAR_CAMPING_TRUE        string("carCampingTrue")
#define KAYAKING_TRUE           string("kayakingTrue")
#define KAYAKING_NIGHT_TRUE     string("kayakingNightTrue")

#endif // ifndef KNOWLEDGE_H

#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <top_level_inclusions.h>
#include <working_memory.h>
#include <frame.h>
#include <vector>
//#include <singleton.h>
// NO. #include <application_specific_definitions.h>

class Rule;

class KnowledgeBase{// xxx TODO :public Singleton{
public:
	KnowledgeBase();
	~KnowledgeBase();
	static std::map<std::string, Frame> frames;
	static Frame boots;
	static Frame initializeBoots();	
	std::vector<Rule> contendingRules();
protected:
private:
	static std::map<std::string, Frame> initializeFrames();
	int initializeRules();

	std::vector<Rule*> rules;
};

class Rule:public WorkingMemory{
public:
	Rule();
	~Rule();
	virtual bool evaluateAntecendant(){return false;}; //TODO make pure virtual?
	virtual bool evaluateAction(){return false;}; //TODO make pure virtual?
	int setPrompt(char *input_prompt);
	int setFormat(char *input_format);
	std::string prompt;
	std::string format;
protected:
private:
};

//------------------------------------------------------------------------------
// Frame references

#define BOOTS       "boots"
#define AQUATABS    "aqua tabs"

//------------------------------------------------------------------------------
// Ways to access WM 

//------------------------------------------------------------------------------
//Ways to access WM

#define F(item) (&KnowledgeBase::frames[item])

// states
#define HIKING_DISTANCE      "hdist" // used internally to differentiate states, does not matter to user

//------------------------------------------------------------------------------

#define RULE_DEFINE(rule_name)\
	class rule_name:public Rule{\
		bool evaluateAntecendant();\
		bool evaluateAction();\
	}

// XXX KA for quick development, rules are implemted as c++ objects
RULE_DEFINE(HikeDistanceRule);
RULE_DEFINE(HikeDistanceWaterRule);



#endif 

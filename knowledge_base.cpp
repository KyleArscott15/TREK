#include <knowledge_base.h>

Rule::Rule()
{
}

Rule::~Rule()
{
}

int Rule::setPrompt(char *input_prompt)
{
	prompt = std::string(input_prompt);
}
int Rule::setFormat(char *input_format)
{
	format = std::string(input_format);
}

KnowledgeBase::KnowledgeBase()
{
	initializeRules();
}

KnowledgeBase::~KnowledgeBase()
{
}


Frame KnowledgeBase::boots = KnowledgeBase::initializeBoots();
std::map<std::string, Frame> KnowledgeBase::frames = KnowledgeBase::initializeFrames();

Frame KnowledgeBase::initializeBoots()
{
	// xxx KA this is application specific code to initialize frames that are useful for TREK only
	Frame b;

	b.setName((char*)"boots");
	All_type shoe_size(13);
	b.addSlot((char*)"shoe size", (char*)"US", shoe_size); //All_type(13))
	return b;
}

std::map<std::string, Frame> KnowledgeBase::initializeFrames()
{
	std::map<std::string, Frame> frames;
	frames[KnowledgeBase::boots.getName()] = KnowledgeBase::boots;

	return frames;
}

int KnowledgeBase::initializeRules()
{
	HikeDistanceRule *hdr = new HikeDistanceRule();

	rules.push_back(hdr); ///new HikeDistanceRule());
	return -1;
}
//*
std::vector<Rule> KnowledgeBase::contendingRules()
{
	std::vector<Rule> rule_set; // subset of all rules, all which are if(true). Let the inference enginer decide which one to run

	for (std::vector<Rule*>::iterator it = rules.begin(); it != rules.end(); it++) {
		Rule *r = *it;

		if (r->evaluateAntecendant())
			rule_set.push_back(*r);
	}
	return rule_set;
}
//*/

//------------------------------------------------------------------------------

#define RULE_IF(rule_name, condition) \
	bool rule_name::evaluateAntecendant(){ \
		return ((condition)); \
	}

#define RULE_AC(rule_name, action) \
	bool rule_name::evaluateAction(){ \
		((action)); \
		return true; \
	}

#define BOOT_SUGGESTION_DISTANCE_THRESHOLD            (5000)    // m
#define AQUATAB_SUGGESTION_DISTANCE_THRESHOLD         (10000)   // m

RULE_IF(HikeDistanceRule, wmAccess(WM_GET, WM_STATE, (void*)HIKING_DISTANCE).i > BOOT_SUGGESTION_DISTANCE_THRESHOLD);
RULE_AC(HikeDistanceRule, wmAccess(WM_ADD, WM_PACKING_LIST, F(BOOTS), NULL));

RULE_IF(HikeDistanceWaterRule, getHikingDistance() > AQUATAB_SUGGESTION_DISTANCE_THRESHOLD);
RULE_AC(HikeDistanceWaterRule, wmAccess(WM_ADD, WM_PACKING_LIST, F(AQUATABS), NULL));

/*
   bool HikeDistanceRule::evaluateAntecendant(){
        return (getHikingDistance() > BOOT_SUGGESTION_DISTANCE_THRESHOLD);
   }//*/
/*
   bool HikeDistanceRule::evaluateAction(){
        wmAccess(WM_ADD, WM_PACKING_LIST, &KnowledgeBase::frames["boots"], NULL);
        return true;
   }//*/


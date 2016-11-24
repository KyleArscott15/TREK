# TREK
An expert system shell, using rules and frames, to help pack camping, hiking and kayaking lists.

# How to compile and run, to get a fresh start
make clean && ./b

# How to normally compile and run, normally
./b

# Dependencies
pdflatex

# About Expert Systems
Expert systems solidify human knowledge by storing it in a Knowledge Base.
The explicit storage of expertise enables transparancy, review, archiving and unambiguity.
The computing nature of expert systems enables the systematic, automatic,
and more importantly, consistent application of the knowledge it stores.

# About Expert System "Shells"
An expert system shell is the rest of the program when you take away the Knowledge Base.
In theory, an expert system shell can be retooled for different domains by 
simply swapping the knowledge base, provided
the knowledge bases are in a similar format.

# Purpose of TREK
Explore problems in applying theory of expert system to applications.
Issues such as:
a) how to make a shells implementation decoupled from the knowledge base, as much as possible
b) how to specify rules in the knowledge base so that they have deterministic interactions,
   without losing their expressive power
c) how to make a tradeoff between implementing the simple and perfect theoretical description of an expert system,
   vs. making the design of an expert system more complex to accomodate secondary, but very imporant, goals.
   i.e. Theoretically, the knowledge is modular and insular: it only knows about itself and it 
   interacts with everything through an interface. Knowledges is decoupled, and satisfies the principle of least concern.
   It has a simple relationship with the part of the program that activates knowleges (the inference engine), because knowledge is simply invoked withouth question (from the perspective of the knowledge). Also, the inference engine
   should be agnostic to the details of the knowledge. The inference engines job is to schedule and activate knowledge based on that knowledge's meta information, not its real information.
   In practice, the expert system has other functions  than just designing or diagnosing something.
   An expert system is useless if it cannot justify its decisions to flesh-and-blood people. This means there is considerable meta-information baggage that must be carried through the channels of the code. This meta-data is different than the data needed by the inference engine, mentioned above. Accomidating this meta-data can potentially break well-established programming practices. These best-practices would be followed rather easily if the theoretical expert system was implemented without modification.

# Philosophy of Expert Systems
Knowledge is a fluid. Technology is the solid form of knowledge.
A reputation of consistency will lead to a new standard for fields that adopt Expert Systems; all they need to do is digitize their masters.
It needs to be complex to be complete. It does not need to be complex to be useful.
It is the hopes that one day, the pieces of knowledge that are added to 
a grand knowledge base will be modular enough to be reused
forever, and comprehensive enough to be a powerful tool for
creative minds of all discplines. 
Needless to say, powerful tools must be democritized. 
Beware the omni-tool; it does not exist (the search for it will drive you mad)
Beware the omni-rule; it is dangerous (corruption's hand is soft, then heavy).

# References
BESAT: Building Expert Systems: At Tutorial, James Martin & Steven Oxman
IES: Introduction to Expert Systems, First Edition, Peter Jackson
MTRP: Mastering the Requirements Process, Third Edition, Suzanne and James Robertson


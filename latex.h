#include "top_level_inclusions.h"
#include "frame.h"

#define SUBSTITUTE_ITEM string("ITEM & QUANTITY  & NOTESABOUTITEM \\ \hline")
#define SUBSTITURE_NOTE String("\item NOTE")

DNAMESPACE();

class Latex {
public:

  Latex();
  ~Latex();
  int savePackingList(map<string,
                          Frame>list,
                      map<string, All_type>optional);

protected:

private:
};

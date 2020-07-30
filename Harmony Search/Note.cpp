#include "Note.h"
#include "Instrument.h"
#include <vector>

using namespace std;

Note* Note::shiftRight(uint32_t plus)
{  
  vector<Note*> pbw = _parent->bw();
  auto pos = (idx + plus) % pbw.size();
  return pbw[pos];
}

Note* Note::shiftLeft(uint32_t less)
{  
  vector<Note*> pbw = _parent->bw();

  less %= pbw.size();

  auto pos = ((int)idx - (int)less + (int)pbw.size()) % (int)pbw.size();  
  //cout << "(l out, pos:" << pos << ")";
  return pbw[(uint32_t)pos];
}
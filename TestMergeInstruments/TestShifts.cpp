#include "Harmony Search/Note.h"
#include "Harmony Search/Instrument.h"

#include <iostream>

using namespace std;

extern void printPairs(Note*);
extern void printNotes(Instrument*);

void testShifts(Instrument* i)
{
  auto pbw = i->bw();
  Note* note;
  //cout << "p1.";
  //printNotes(pbw);
  cout << "pbw[0]:";
  printPairs(pbw[0]);
  cout << "pbw[1]:";
  printPairs(pbw[1]);

  note = pbw[pbw.size() - 1];
  cout << "Note as pbw[pbw.size()-1]: ";
  printPairs(note);
  cout << "nidx: " << note->idx << "\n";

  note = pbw[1];
  cout << "Note as pbw[1]: ";
  printPairs(note);
  cout << "nidx: " << note->idx << "\n";

  cout << "Note after shiftleft(30): ";
  note = note->shiftLeft(30);
  printPairs(note);
  cout << "nidx: " << note->idx << "\n";

  cout << "Note after shiftleft(20): ";
  note = note->shiftLeft(20);
  printPairs(note);
  cout << "nidx: " << note->idx << "\n";

  cout << "Note after shiftright(1000): ";
  note = note->shiftRight(1000);
  printPairs(note);
  cout << "nidx: " << note->idx << "\n";

  cout << "Saindo de testShift";
  exit(1);
}

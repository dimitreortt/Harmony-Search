#include "Approaches.h"

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "Harmony Search/Logs.h"

using namespace std;

//ofstream outharmony;

int main(int argc, char** argv)
{
  clock_t start = clock();  
  srand((unsigned)time(nullptr));

  string g1file{ argv[4] }, g2file{ argv[5] };

  //getInputFiles(g1file, g2file);
  startOutHarmony(argv[3]);


  /*auto iVector = createUnformatedIVector(g1file, g2file);
  testMergeInstruments(g1file, g2file);*/
  if (argc == 4)
  {
    if (std::string{ argv[1] } == "1")
      aproach1(g1file, g2file);
    else if (std::string{ argv[1] } == "2")
      aproach2(g1file, g2file);
  }
  else if (argc == 5) 
  {
    if(std::string{ argv[1] } == "3")
      aproach3(g1file, g2file, argv);
  }
  else if (argc == 6)
  {    
    if (std::string{ argv[1] } == "4")
      aproach4(g1file, g2file, argv);
  }
    

  closeOutHarmony();

  return 0;
}
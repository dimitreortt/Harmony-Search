#include "Assets.h"
#include <iomanip>
#include <iostream>

using namespace std;

long long int numberOfPossibilities(vector<Instrument*>& iVector)
{
  long long int num = 1;
  for (auto& i : iVector)
  {
    num *= i->size();
  }
  return num;
}

double
timeSpent(clock_t start, clock_t end)
{
  static int count;
  static double soma;

  // Calculating total time taken by the program. 
  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

  soma += time_taken;
  double media = soma / double(++count);

  cout << "Time taken by program is : " << fixed
    << time_taken << setprecision(5) << ", average is: " << media;
  cout << " sec " << endl;

  return time_taken;
}


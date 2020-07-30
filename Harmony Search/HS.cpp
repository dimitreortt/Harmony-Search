#include "HS.h"
#include <time.h>
#include <iostream>

using namespace std;

HS::HS(float PAR, float HMCR, vector<Instrument*> instrumentsVec, uint32_t HMS,
  uint32_t numInterations) : _PAR(PAR), _HMCR(HMCR), _numIterations(numInterations)
{
	_iVector = instrumentsVec;

	size_t hmDim = _iVector.size();
	_hm = new HM(HMS, hmDim);
	_hm->initialize(_iVector);
  _numInstruments = hmDim;
}

HS::HS(float hmcrMin, float hmcrMax, float parMin, float parMax, 
  uint32_t bwMax, uint32_t bwMin, vector<Instrument*> instrumentsVec, uint32_t HMS, uint32_t numInterations):
  _hmcrMax{hmcrMax}, _hmcrMin{ hmcrMin }, 
  _parMax { parMax}, _parMin{parMin},
  _bwMax{bwMax}, _bwMin{bwMin},
  _numIterations(numInterations)
{
  _iVector = instrumentsVec;

  size_t hmDim = _iVector.size();
  _hm = new HM(HMS, hmDim);
  _hm->initialize(_iVector);
  _numInstruments = hmDim;
}

int
HS::run()
{  
  srand((unsigned)time(nullptr));
  _start = clock();
	//test hs
	for (uint32_t i = 0; i < _numIterations; i++)
	{
		auto h = _hm->improviseHM();
		hmcr(h);
		par(h);
    //cascadePar(h);
		h->measureQuality();
		_hm->addIfGoodEnough(h);
	}
	return _hm->currentBestQuality();
}

float ran()
{
  return (float)rand()/RAND_MAX;
}

void showDynamics(float dhmcr, float dpar, uint32_t dbw)
{
  cout << "(Values: hmcr: " << dhmcr << " par: " << dpar << " dbw: " << dbw << "),";
}

double HS::timeTaken()
{
  return _timeTaken;
}

void HS::calculateTimeTaken()
{
  _timeTaken = double(clock() - _start) / double(CLOCKS_PER_SEC);
}

void HS::logResults()
{
  ofstream out;
  out.open(_logname, std::ofstream::app);
  out << _bestQuality << ' ' << _timeTaken << "\n";
  outharmony << _bestQuality << " " << _timeTaken << "\n";
}

void HS::setLogname(string logname)
{
  _logname = logname;
}

// MHS (kumara et. al.)
int HS::runDynamic()
{
  srand((unsigned)time(nullptr));
  _start = clock();

  cout << "numintes " << _numIterations << "\n";
  for (uint32_t i = 0; i < _numIterations; i++)
  {   
    auto dhmcr = dynamicHmcr(i);
    auto dpar = dynamicPar(i);
    auto dbw = dynamicBw(i);

    //showDynamics(dhmcr, dpar, dbw);

    vector<Note*> nv;
    for (auto j = 0; j < _numInstruments; j++)
    {
      Note* note;
      if (ran() > dhmcr) // arbitrary pitch
      {
        note = _iVector[j]->improviseNote();
      }
      else // consider hm
      {
        note = _hm->improviseAt(j);

        auto r = ran();
        if (r < dpar)
        {
          auto randval = (uint32_t)ceil(ran() * dbw);
          if (r < dpar / 2) // par left adjustment 
          {
            note = note->shiftLeft(randval);
          }  
          else // par right adjustment
          {
            note = note->shiftRight(randval);
          } 
        }
      }
      nv.push_back(note);
    }
    // Modeling Behavior
    // TODO: Save samples of harmony    
    /*if (i > 100 && i <= 110) {
      saveHarmonySample(nv);
    }*/
    _hm->addIfGoodEnough(new Harmony(nv));
  }

  calculateTimeTaken();
  _bestQuality = _hm->currentBestQuality();
  logResults();

  return _bestQuality;
}

void
HS::par(Harmony* h)
{
	for (auto note : h->noteVector()) {

		if (note->_parent->hasMoreThanOneNote) {

			float attempt = (float)rand() / RAND_MAX;
			if (attempt < _PAR) //improvise
			{
				Note* n;
				attempt < _PAR / 2 ? n = note->_parent->left(note) : n = note->_parent->right(note);
				//attempt < _PAR / 2 ? n = note->left() : n = note->right();
				h->swap(note, n);
			}
		}
	}
}

void 
HS::cascadePar(Note* note, int idx)
{
  static int cascadeIndexes[1024] = {0};
  int pos = idx;
  if (note->_parent->hasMoreThanOneNote) {

    float attempt = (float)rand() / RAND_MAX;
    if (attempt < _PAR) //improvise
    {
      Note* n;
      if (attempt < _PAR / 2)
      {
        n = note->_parent->left(note);
        for(int i = 0; i < cascadeIndexes[pos] % n->_parent->size() / 4; i++)
          n = n->_parent->left(n);
      }
      else
      {
        n = note->_parent->right(note);
        for (int i = 0; i < cascadeIndexes[pos] % n->_parent->size(); i++)
          n = n->_parent->right(n);
      }
      //swap(*note, *n);
      *note = *n;
      cascadeIndexes[pos]++;
    }
  }
  //pos++;
}

void
HS::hmcr(Harmony* h)
{
  int pos = 0;
	for (auto note : h->noteVector()) {

		if (note->_parent->hasMoreThanTwoNotes) {

			float attempt = (float)rand() / RAND_MAX;
			if (attempt > _HMCR) // new random note
			{
				Note* n = note->_parent->improviseNote();
				if (note != n)
				{
					h->swap(note, n);
				}
			}
      else
      {
        //cascadePar(note, pos);
      }
		}
    pos++;
	}
}

uint32_t HS::dynamicBw(uint32_t itNumber)
{
  // source: (kumara et. al.)
  return (uint32_t) (_bwMax * exp((log((float)_bwMin / _bwMax) / _numIterations) * itNumber));
}

float HS::dynamicHmcr(uint32_t itNumber)
{
  // source: (kumara et. al.)
  return _hmcrMin + ((_hmcrMax - _hmcrMin) * itNumber) / _numIterations;
}

float HS::dynamicPar(uint32_t itNumber)
{
  // source: (kumara et. al.)
  return _parMax - ((_parMax - _parMin) * itNumber) / _numIterations;
}

HS::~HS()
{
}

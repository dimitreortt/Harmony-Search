#pragma once 

#include <vector>
#include <ctime>
#include "HM.h"
#include "Instrument.h"
#include "Note.h"

#include <fstream>

class HS
{
private:
	HM* _hm;
	std::vector<Instrument*> _iVector;
  size_t _numInstruments;
	float _PAR;
	float _parMin;
	float _parMax;
	float _HMCR;
	float _hmcrMin;
	float _hmcrMax;
	uint32_t _numIterations;
  uint32_t _BW;
  uint32_t _bwMin;
  uint32_t _bwMax;
  uint32_t _bestQuality;
	clock_t _start;
	double _timeTaken;
	std::string _logname;
	void calculateTimeTaken();

public:
	HS(float PAR, float HMRC, std::vector<Instrument*> iVector, uint32_t HMS, uint32_t numInterations);
	HS(float hmcrMin, float hmcrMax, float parMin, float parMax, uint32_t bwMax, uint32_t bwMin,
		std::vector<Instrument*> iVector, uint32_t HMS, uint32_t numInterations);

	int run();
	int runDynamic();
	void hmcr(Harmony*);
	void par(Harmony*);
  void cascadePar(Note* h, int idx);
  //uint32_t bw();
  uint32_t dynamicBw(uint32_t itNumber);
  float dynamicHmcr(uint32_t itNumber);
  float dynamicPar(uint32_t itNumber);
	double timeTaken();
	void logResults();
	void setLogname(std::string logname);
	HM* getHM() { return _hm; }
	~HS();
};

extern std::ofstream outharmony;
void saveHarmonySample(std::vector<Note*>);
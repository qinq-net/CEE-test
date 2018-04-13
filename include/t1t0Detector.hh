#ifndef t1t0Detector_H
#define t1t0Detector_H

#include <G4MultiFunctionalDetector.hh>

class t1t0Detector: public G4MultiFunctionalDetector
{
	public:
	t1t0Detector(G4String name, G4int depth);
	virtual ~t1t0Detector();
};

#endif//t1t0Detector_H

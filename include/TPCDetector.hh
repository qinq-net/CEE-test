#ifndef TPCDetector_H
#define TPCDetector_H

#include <G4MultiFunctionalDetector.hh>

class TPCDetector: public G4MultiFunctionalDetector
{
	public:
	TPCDetector(G4String name, G4int depth);
	virtual ~TPCDetector();
};

#endif//TPCDetector_H

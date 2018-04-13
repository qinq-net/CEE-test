#ifndef PixDetector_H
#define PixDetector_H

#include <G4MultiFunctionalDetector.hh>

class PixDetector: public G4MultiFunctionalDetector
{
	public:
	PixDetector(G4String name, G4int depth);
	virtual ~PixDetector();
};

#endif//PixDetector_H

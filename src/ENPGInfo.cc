#include "ENPGInfo.hh"
#include <G4ios.hh>

ENPGInfo::ENPGInfo(G4String str)
{
	this->str = str;
}

ENPGInfo::~ENPGInfo()
{;}

void ENPGInfo::Print() const
{
	G4cout << this->str;
}

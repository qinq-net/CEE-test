#include <G4Element.hh>
#include <G4Isotope.hh>
#include <G4Material.hh>

class CEEMaterials {
	public:
	CEEMaterials();
	~CEEMaterials();
	
	// CEE Materials
	G4Element *elSi, *elO;
	G4Material *SiO2;
	G4Element *elAr, *elC;
	G4Material *CO2, *ArCO2;
	G4Element *elH;
	G4Material *CH4, *ArCH4;
};

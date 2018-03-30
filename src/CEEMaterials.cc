#include "CEEMaterials.hh"

#include <G4SystemOfUnits.hh>

CEEMaterials::CEEMaterials() {
	G4double density;
	this->elSi = new G4Element(
		"CEESilicon",	//name
		"Si",		//symbol
		14.,		//z
		28.09 * g/mole);//a
	this->elO = new G4Element(
		"CEEOxygen",	//name
		"O",		//symbol
		8.,		//z
		16.00 * g/mole);//a
	this->SiO2 = new G4Material(
		"CEEQuartz",	//name
		2.200*g/cm3,	//density
		2);		//nComponents
	this->SiO2->AddElement(this->elO, 2);
	this->SiO2->AddElement(this->elSi,1);
	
	this->elAr = new G4Element(
		"CEEArgon",
		"Ar",
		18.,
		39.948 * g/mole);
	this->elC = new G4Element(
		"CEECarbon",
		"C",
		6.,
		12.0107 * g/mole);
	this->CO2 = new G4Material(
		"CEECarbonDioxide",
		1.98*mg/cm3,//density
		2,//nComponents
		kStateGas,//state of material
		273.15*kelvin,//temprature
		1.*atmosphere);//pressure
	this->CO2->AddElement(this->elC,1);
	this->CO2->AddElement(this->elO,2);
	this->ArCO2 = new G4Material(
		"CEEArCO2",
		density=(1.784*0.7+1.98*0.3)*mg/cm3,
		2,
		kStateGas,
		273.15*kelvin,
		1.*atmosphere);
	this->ArCO2->AddElement(this->elAr,0.4*1.784*mg/cm3/density);
	this->ArCO2->AddMaterial(this->CO2,0.6*1.98*mg/cm3/density);

	this->elH = new G4Element(
		"CEEHitrogen",
		"H",
		1.,
		1.00794*g/cm3);
	this->CH4 = new G4Material(
		"CEEMethane",
		density=0.656*mg/cm3,
		2,
		kStateGas,
		273.15*kelvin,
		1.*atmosphere);
	this->CH4->AddElement(this->elC,1);
	this->CH4->AddElement(this->elH,4);
	this->ArCH4 = new G4Material(
		"CEEArCH4",
		density=(1.784*0.9+0.656*0.1)*mg/cm3,
		2,
		kStateGas,
		273.15*kelvin,
		1.*atmosphere);
	this->ArCH4->AddElement(this->elAr, 0.9*1.784*mg/cm3/density);
	this->ArCH4->AddMaterial(this->CH4, 0.1*0.656*mg/cm3/density);
}

CEEMaterials::~CEEMaterials() {
	delete this->ArCH4;
	delete this->CH4;
	delete this->elH;
	delete this->ArCO2;
	delete this->CO2;
	delete this->elC;
	delete this->elAr;
	delete this->SiO2;
	delete this->elO;
	delete this->elSi;
}

#include "T1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"  //yuanzhu guanzi
#include "G4Cons.hh"
#include "G4Orb.hh"  //shixinqiu
#include "G4Torus.hh"  //quan
#include "G4Sphere.hh" //qiu  (duocanshu)
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4UnionSolid.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
//



#include "T1T0.hh"
#include "T1TPC.hh"
#include "T1iTOF.hh"
#include "T1eTOF.hh"
#include "T1ZDC.hh"
#include "T1MWDC.hh"

// Sensitive detectors
#include <G4SDManager.hh>
#include "T1TPCDigi.hh"
#include "T1MWDCDigi.hh"
#include "T1MRPCDigi.hh"
#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>
// Electromagnetic field
#include <G4UniformMagField.hh>
#include <G4UniformElectricField.hh>
#include <G4FieldManager.hh>

std::vector<G4String> CEEZDCTowerIDs;

using namespace std;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1DetectorConstruction::T1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1DetectorConstruction::~T1DetectorConstruction()
{
	delete CEE_TPC;
	delete CEE_MWDC;
	delete CEE_ZDC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* T1DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4VisAttributes* default_Vis = new G4VisAttributes(G4Colour(0,0,0,0));

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //////////////////////CEE-1

  G4double CEE_world_sx = 5*m;  //kuan
  G4double CEE_world_sy = 5*m;  //gao
  G4double CEE_world_sz = 15*m;  //chang  zhouxiang
  G4ThreeVector CEE_world_p = G4ThreeVector(0*cm, 0*cm, 0*cm);
  G4Material* CEE_world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4VisAttributes* CEE_world_Vis = new G4VisAttributes(G4Colour(0.0,0.0,0.0,0.0));

/*
  G4double CEE_Pix_sx = 3*cm;
  G4double CEE_Pix_sy = 3*cm;
  G4double CEE_Pix_sz = 3*cm;
  G4double CEE_Pix_px = 0*cm;
  G4double CEE_Pix_py = 0*cm;
  G4double CEE_Pix_pz = -8*cm;
  G4ThreeVector CEE_Pix_p = G4ThreeVector(CEE_Pix_px, CEE_Pix_py, CEE_Pix_pz);
  G4Material* CEE_Pix_mat = nist->FindOrBuildMaterial("G4_Galactic");//Ar:CO2 7:3
  G4VisAttributes* CEE_Pix_Vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,1));
*/
/*
  G4double CEE_TPC_sx = 100*cm;
  G4double CEE_TPC_sy = 80*cm;
  G4double CEE_TPC_sz = 80*cm;
  G4double CEE_TPC_px = 0*cm;
  G4double CEE_TPC_py = 0*cm;
  G4double CEE_TPC_pz = 60*cm;
  G4ThreeVector CEE_TPC_p = G4ThreeVector(CEE_TPC_px, CEE_TPC_py, CEE_TPC_pz);
  G4Material* CEE_TPC_mat = nist->FindOrBuildMaterial("G4_Galactic");//Ar:CH4 9:1
  G4VisAttributes* CEE_TPC_Vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
*/






  //////////////////////CEE-1






  //
  // CEE_World
  //

  G4Box* CEE_world_solid =
    new G4Box("CEE_world_solid",                       //its name
       0.5*CEE_world_sx, 0.5*CEE_world_sy, 0.5*CEE_world_sz);     //its size

  G4LogicalVolume* CEE_world_logic =
    new G4LogicalVolume(CEE_world_solid,          //its solid
                        CEE_world_mat,           //its material
                        "CEE_world_logic");            //its name

  G4VPhysicalVolume* CEE_world_phys =
    new G4PVPlacement(0,                     //no rotation
                      CEE_world_p,       //at (,,)
                      CEE_world_logic,            //its logical volume
                      "CEE_world_phys",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  CEE_world_logic -> SetVisAttributes(CEE_world_Vis);
//
/*
// CEE_Pix
//

G4Box* CEE_Pix_solid =
  new G4Box("CEE_Pix_solid",                       //its name
     0.5*CEE_Pix_sx, 0.5*CEE_Pix_sy, 0.5*CEE_Pix_sz);     //its size

G4LogicalVolume* CEE_Pix_logic =
  new G4LogicalVolume(CEE_Pix_solid,          //its solid
                      CEE_Pix_mat,           //its material
                      "CEE_Pix_logic");            //its name


  new G4PVPlacement(0,                     //no rotation
                    CEE_Pix_p,       //at (,,)
                    CEE_Pix_logic,            //its logical volume
                    "CEE_Pix_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
CEE_Pix_logic -> SetVisAttributes(CEE_Pix_Vis);
*/
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_T0
//


  CEE_T0 = new T1T0();
  new G4PVPlacement(CEE_T0->transT0,
                    CEE_T0->logicT0,            //its logical volume
                    "CEE_T0_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_TPC
//
  CEE_TPC = new T1TPC();
  new G4PVPlacement(CEE_TPC->transTPC,
                    CEE_TPC->logicTPC,            //its logical volume
                    "CEE_TPC_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_iTOF
//

  CEE_iTOF = new T1iTOF();
  new G4PVPlacement(CEE_iTOF->transiTOF[0],
                    CEE_iTOF->logiciTOF[0],            //its logical volume
                    "CEE_iTOF1_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
  //
  new G4PVPlacement(CEE_iTOF->transiTOF[1],
                    CEE_iTOF->logiciTOF[1],            //its logical volume
                    "CEE_iTOF2_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_eTOF
//
  CEE_eTOF = new T1eTOF();
  new G4PVPlacement(CEE_eTOF->transeTOF[0],
                    CEE_eTOF->logiceTOF[0],            //its logical volume
                    "CEE_eTOF1_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking
  //
  new G4PVPlacement(CEE_eTOF->transeTOF[1],
                    CEE_eTOF->logiceTOF[1],            //its logical volume
                    "CEE_eTOF2_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_ZDC
//
  CEE_ZDC=new T1ZDC();
  new G4PVPlacement(CEE_ZDC->transZDC,
                    CEE_ZDC->logicZDC,            //its logical volume
                    "CEE_ZDC_phys",               //its name
                    CEE_world_logic,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CEE_MWDC
//
  CEE_MWDC=new T1MWDC();
  for(int id=1;id<=6;id++){
    new G4PVPlacement(CEE_MWDC->transMWDC[id-1],
                      CEE_MWDC->logicMWDC[id-1],            //its logical volume
                      "CEE_MWDC"+to_string(id)+"_phys",               //its name
                      CEE_world_logic,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  }
//////////////////////////////////////////////////////////////////////////////
/*

G4Box*  box =
  new G4Box("Box",1*m,2*m,3*m);
G4Tubs* cyl =
  new G4Tubs("Cylinder",0,20*cm,3*m,0,twopi);  // r:     0 mm -> 50 mm
                                                 // z:   -50 mm -> 50 mm
                                                 // phi:   0 ->  2 pi


G4RotationMatrix* yRot = new G4RotationMatrix;  // Rotates X and Z axes only
yRot->rotateY(pi/6.*rad);                     // Rotates 45 degrees
yRot->rotateZ(pi/4.*rad);
G4ThreeVector zTrans(0, 0, 2*m);
*/
  /*
G4UnionSolid* unionMoved =
  new G4UnionSolid("Box+CylinderMoved", box, cyl, yRot, zTrans);
  */
 //
 // The new coordinate system of the cylinder is translated so that
 // its centre is at +50 on the original Z axis, and it is rotated
 // with its X axis halfway between the original X and Z axes.

 // Now we build the same solid using the alternative method
 //
/*
 //G4RotationMatrix invRot = *yRot;//->invert();
G4Transform3D transform(*yRot, zTrans);
G4UnionSolid* unionMoved =
  new G4UnionSolid("Box+CylinderMoved", box, cyl, transform);


G4LogicalVolume* testlogic =
  new G4LogicalVolume(unionMoved,          //its solid
                      CEE_TPC_mat,           //its material
                      "CEE_testlogic");            //its name

new G4PVPlacement(0,                     //no rotation
                  G4ThreeVector(0,0,0),       //at (,,)
                  testlogic,            //its logical volume
                  "CEE_testphys",               //its name
                  CEE_world_logic,                     //its mother  volume
                  false,                 //no boolean operation
                  0,                     //copy number
                  checkOverlaps);        //overlaps checking
testlogic -> SetVisAttributes(CEE_TPC_Vis);
*/

  //
  //always return the physical World
  //
  return CEE_world_phys;
}

void T1DetectorConstruction::ConstructSDandField()
{
	this->SetupDetectors();
	this->SetupField();
}

template<typename Geom_t, typename Digi_t> G4bool MRPCSetup(Geom_t* Geometry, G4int number, CEEMRPCDirection direction, G4int depth=1)
{
	for(G4int i=1; i<=number; i++)
	{
		G4String detName = "CEE_";
		detName+=typeid(Geom_t).name();
		std::vector<G4LogicalVolume*> SLVList;
		if(number==1)
		{
			detName+="_det";
			SLVList = Geometry->GetSensitiveLVs();
		}
		else
		{
			detName+=(std::to_string(i)+"_det");
			SLVList = Geometry->GetSensitiveLVs(i-1);
		}
		std::cerr << "CEE_MRPC " << detName << std::endl;
		Digi_t* det = new Digi_t(detName, direction, depth);
		G4SDManager::GetSDMpointer()->AddNewDetector(det);
		for(auto itr: SLVList)
		{
			itr->SetSensitiveDetector(det);
		}
	}
}

void T1DetectorConstruction::SetupDetectors()
{
	// sensitive detectors
	G4SDManager::GetSDMpointer()->SetVerboseLevel(2);
	// TPC
	{
		G4String detName = CEE_TPC->logicTPC->GetName() + "_det";
		G4int depth = 0;
		T1TPCDigi* det = new T1TPCDigi(detName, depth);
		G4SDManager::GetSDMpointer()->AddNewDetector(det);
		for(auto itr: CEE_TPC->GetSensitiveLVs())
			itr->SetSensitiveDetector(det);
		// Magnetic Field
		G4UniformMagField* field = new G4UniformMagField(
			G4ThreeVector(0., -0.5*tesla, 0.));
		G4FieldManager* fieldManager = new G4FieldManager(field);
		CEE_TPC->logicTPC->SetFieldManager(fieldManager, TRUE);
	}
	// MWDC
	{
		for(int MWDC_id=1; MWDC_id<=6; MWDC_id++)
		{
			std::cerr << "Setting SD for MWDC" << MWDC_id << std::endl;
			G4String detName = CEE_MWDC->logicMWDC[MWDC_id-1]->GetName()+"_det";
			std::cerr << "CEE_MWDC " << detName << std::endl;
			G4int depth=2;
			T1MWDCDigi* det = new T1MWDCDigi(detName, depth);
			G4SDManager::GetSDMpointer()->AddNewDetector(det);
			for(auto itr: CEE_MWDC->GetSensitiveLVs(MWDC_id))
				itr->SetSensitiveDetector(det);
			// No field will be built
		}
	}
	// ZDC
	{
		G4int depth=3;
		CEEZDCTowerIDs.clear();
		for(auto towerItr: CEE_ZDC->GetSensitiveLVs())
		{
			G4String detName = "CEE_ZDC_Tower_"+towerItr.first+"_det";
			CEEZDCTowerIDs.push_back(towerItr.first);
			std::cerr << detName << std::endl;
			G4MultiFunctionalDetector* det=new G4MultiFunctionalDetector(detName);
			G4PSEnergyDeposit* primitive=new G4PSEnergyDeposit("energyDeposit", "MeV", depth);
			det->RegisterPrimitive(primitive);
			G4SDManager::GetSDMpointer()->AddNewDetector(det);
			for(auto layerItr: towerItr.second)
				layerItr->SetSensitiveDetector(det);
		}
	}
	// MRPC
	{
		G4int depth=1;
		// T0
		/* MRPCSetup<T1T0, T1MRPCDigi>(CEE_T0, 1, depth);
		 */
		// iTOF
		MRPCSetup<T1iTOF, T1MRPCDigi>(CEE_iTOF, 2, CEEMRPCDirection::Z, depth);
		// eTOF
		MRPCSetup<T1eTOF, T1MRPCDigi>(CEE_eTOF, 2, CEEMRPCDirection::Y, depth);
	}
}

void T1DetectorConstruction::SetupField()
{
}

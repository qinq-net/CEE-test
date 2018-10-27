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



// Sensitive detectors
#include <G4SDManager.hh>
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
  G4Material* CEE_world_mat = nist->FindOrBuildMaterial("G4_Galactic");
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

  G4double ENPG_SSD_Size[3]={10.*cm, 10.*cm, 1540.*um};//x,y,z
  G4ThreeVector ENPG_SSD_position = G4ThreeVector(0.*cm, 0.*cm, 0.*cm);

  G4Box* ENPG_SSD_solid = 
    new G4Box("ENPG_SSD_solid",
        ENPG_SSD_Size[0],ENPG_SSD_Size[1],ENPG_SSD_Size[2]);
  G4Material* ENPG_SSD_material = nist->FindOrBuildMaterial("G4_Si");
  ENPG_SSD_logic = 
    new G4LogicalVolume(ENPG_SSD_solid,
                        ENPG_SSD_material,
                        "ENPG_SSD_logic");
  G4VPhysicalVolume* ENPG_SSD_phys =
    new G4PVPlacement(0,
                      ENPG_SSD_position,
                      ENPG_SSD_logic,
                      "ENPG_SSD_phys",
                      CEE_world_logic,
                      false, 0, checkOverlaps);


  G4double ENPG_CsI_Size[3]={10.*cm, 10.*cm, 50.*mm};
  G4ThreeVector ENPG_CsI_position = G4ThreeVector(0.*cm, 0.*cm, ENPG_SSD_position.z() + 5.*mm + (ENPG_SSD_Size[2]+ENPG_CsI_Size[2]));
  
  G4Box* ENPG_CsI_solid = 
    new G4Box("ENPG_CsI_solid",
        ENPG_CsI_Size[0], ENPG_CsI_Size[1], ENPG_CsI_Size[2]);
  G4Material* ENPG_CsI_material = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  ENPG_CsI_logic =
    new G4LogicalVolume(ENPG_CsI_solid,
                        ENPG_CsI_material,
                        "ENPG_CsI_material");
  G4VPhysicalVolume* ENPG_CsI_phys =
    new G4PVPlacement(0,
                      ENPG_CsI_position,
                      ENPG_CsI_logic,
                      "ENPG_CsI_phys",
                      CEE_world_logic,
                      false, 0, checkOverlaps);


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
/*
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
*/
void T1DetectorConstruction::SetupDetectors()
{
	// sensitive detectors
	G4SDManager::GetSDMpointer()->SetVerboseLevel(2);
        G4MultiFunctionalDetector* ENPG_SSD_det = new G4MultiFunctionalDetector("ENPG_SSD_det");
        G4PSEnergyDeposit* ENPG_SSD_energy = new G4PSEnergyDeposit("eDep", "MeV", 1);
        ENPG_SSD_det->RegisterPrimitive(ENPG_SSD_energy);
        G4SDManager::GetSDMpointer()->AddNewDetector(ENPG_SSD_det);
        ENPG_SSD_logic->SetSensitiveDetector(ENPG_SSD_det);
        G4MultiFunctionalDetector* ENPG_CsI_det = new G4MultiFunctionalDetector("ENPG_CsI_det");
        G4PSEnergyDeposit* ENPG_CsI_energy = new G4PSEnergyDeposit("eDep", "MeV", 1);
        ENPG_CsI_det->RegisterPrimitive(ENPG_CsI_energy);
        G4SDManager::GetSDMpointer()->AddNewDetector(ENPG_CsI_det);
        ENPG_CsI_logic->SetSensitiveDetector(ENPG_CsI_det);

        /*
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
		// iTOF
		MRPCSetup<T1iTOF, T1MRPCDigi>(CEE_iTOF, 2, CEEMRPCDirection::Z, depth);
		// eTOF
		MRPCSetup<T1eTOF, T1MRPCDigi>(CEE_eTOF, 2, CEEMRPCDirection::Y, depth);
	}
        */
}

void T1DetectorConstruction::SetupField()
{
}

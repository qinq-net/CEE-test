// vim: set nofoldenable :
#include "T1EventAction.hh"
#include "T1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <G4SDManager.hh>
#include <G4VPrimitiveScorer.hh>
#include "CEEEventLoggingSession.hh"
#include <G4UImanager.hh>
#include <G4THitsMap.hh>
#include <G4HCofThisEvent.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4SystemOfUnits.hh>

#include <fstream>
#include "G4VUserPrimaryVertexInformation.hh"
using namespace std;
//extern ofstream shuchu;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1EventAction::T1EventAction(T1RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1EventAction::~T1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T1EventAction::BeginOfEventAction(const G4Event*)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

template<class SDType> inline G4bool PrintMultiPrimitive(SDType* det)
{
	if(!det) { G4cerr << "### TODO:" << typeid(SDType).name() << " NOT Found!"; return FALSE;}
	else
	{
		G4cout << "### {{{ G4MultiFunctionalDetector " << det->GetName() << G4endl;
		for(G4int i=0; i<det->GetNumberOfPrimitives(); i++)
		{
			G4cout << "#### {{{ Primitive " << i << std::flush;
			G4cout << " " << det->GetPrimitive(i)->GetName() << G4endl;
			det->GetPrimitive(i)->PrintAll();
			G4cout << "#### }}}" << G4endl;
		}
		G4cout << "### }}}" << G4endl;
	}
	return TRUE;
}
extern std::vector<G4String> CEEZDCTowerIDs;
void T1EventAction::EndOfEventAction(const G4Event* evt)
{
	G4cout << " >>> End of Event " << evt->GetEventID() << G4endl;
	{ //SD record
		G4SDManager* SDMan = G4SDManager::GetSDMpointer();
		G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
		if(!SDMan) { G4cerr << "No SDManager!" << G4endl;}
		else
		{
		/*
			G4String outFileName = "results/Event" + std::to_string(evt->GetEventID()) + "Out.txt";
			G4String errFileName = "results/Event" + std::to_string(evt->GetEventID()) + "Err.txt";
			
			G4cout << "Relocating G4cout to file: " << outFileName << G4endl;
			CEEEventLoggingSession* session = new CEEEventLoggingSession(
				outFileName, errFileName);
			G4UImanager* UI=G4UImanager::GetUIpointer();
			G4UIsession* oldSession = UI->GetSession();
			if(UI) UI->SetCoutDestination(session);
			// G4cout has been relocated.
			G4cout << "### Event " << evt->GetEventID() << G4endl;
			G4cout << "# vim: set foldmethod=marker :" << G4endl;
			if(evt->GetUserInformation()) evt->GetUserInformation()->Print();

			G4MultiFunctionalDetector* detSSD = dynamic_cast<G4MultiFunctionalDetector*>(SDMan->FindSensitiveDetector("ENPG_SSD_det"));
			PrintMultiPrimitive<G4MultiFunctionalDetector>(detSSD);
			G4MultiFunctionalDetector* detCsI = dynamic_cast<G4MultiFunctionalDetector*>(SDMan->FindSensitiveDetector("ENPG_CsI_det"));
			PrintMultiPrimitive<G4MultiFunctionalDetector>(detCsI);
			*/
			G4String outFileName = "results.txt";
			G4String errFileName = "errors.txt";
			G4cout << "Relocating G4cout to file: " << outFileName << G4endl;
			CEEEventLoggingSession* session = new CEEEventLoggingSession(
				outFileName, errFileName);
			G4UImanager* UI=G4UImanager::GetUIpointer();
			G4UIsession* oldSession = UI->GetSession();
			if(UI) UI->SetCoutDestination(session);
			// G4cout has been relocated.
			if(evt->GetUserInformation()) evt->GetUserInformation()->Print();
			G4int colIDSSD=SDMan->GetCollectionID("ENPG_SSD_det/eDep");
			G4int colIDCsI=SDMan->GetCollectionID("ENPG_CsI_det/eDep");
			std::cerr << colIDSSD << colIDCsI << std::endl;
			auto SSDMap = ((G4THitsMap<G4double>*)HCE->GetHC(colIDSSD))->GetMap();
			auto CsIMap = ((G4THitsMap<G4double>*)HCE->GetHC(colIDCsI))->GetMap();
			G4double DeltaE=0.,E=0.;
			if(SSDMap && (*SSDMap)[0]) DeltaE=*((*SSDMap)[0]);
			if(CsIMap && (*CsIMap)[0])      E=*((*CsIMap)[0]);
			G4cout << '\t' << DeltaE/MeV << '\t' << E/MeV << G4endl;

/*
			{ //TPC
				T1TPCDigi* tpcDigi = dynamic_cast<T1TPCDigi*>(SDMan->FindSensitiveDetector("CEE_TPC_logic_det"));
				PrintMultiPrimitive<T1TPCDigi>(tpcDigi);
			}
			//MWDC
			for(int MWDC_id=1; MWDC_id<=6; MWDC_id++)
			{
				T1MWDCDigi* mwdcDigi = dynamic_cast<T1MWDCDigi*>(SDMan->FindSensitiveDetector("CEE_MWDC"+std::to_string(MWDC_id)+"_logic_det"));
				PrintMultiPrimitive<T1MWDCDigi>(mwdcDigi);
			}
			//ZDC
			G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
			for(auto towerID: CEEZDCTowerIDs)
			{
				G4MultiFunctionalDetector* zdcDigi = dynamic_cast<G4MultiFunctionalDetector*>(SDMan->FindSensitiveDetector("CEE_ZDC_Tower_"+towerID+"_det"));
				if(((G4THitsMap<G4double>*)(HCE->GetHC(zdcDigi->GetPrimitive(0)->GetCollectionID(0))))->entries())
					PrintMultiPrimitive<G4MultiFunctionalDetector>(zdcDigi);
			}
			//TOF
			//iTOF
			{
				PrintMultiPrimitive<T1MRPCDigi>(dynamic_cast<T1MRPCDigi*>(SDMan->FindSensitiveDetector("CEE_6T1iTOF1_det")));
				PrintMultiPrimitive<T1MRPCDigi>(dynamic_cast<T1MRPCDigi*>(SDMan->FindSensitiveDetector("CEE_6T1iTOF2_det")));
				PrintMultiPrimitive<T1MRPCDigi>(dynamic_cast<T1MRPCDigi*>(SDMan->FindSensitiveDetector("CEE_6T1eTOF1_det")));
				PrintMultiPrimitive<T1MRPCDigi>(dynamic_cast<T1MRPCDigi*>(SDMan->FindSensitiveDetector("CEE_6T1eTOF2_det")));
			}
*/
			// relocating G4cout back to screen
			if(UI) UI->SetCoutDestination(oldSession);
			delete session;
		}
	}
	return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

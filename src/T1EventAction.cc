
#include "T1EventAction.hh"
#include "T1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"


#include <fstream>
using namespace std;
//extern ofstream shuchu;

// For getting HitsMap and output
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4THitsMap.hh>

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

void T1EventAction::EndOfEventAction(const G4Event* evt)
{
	// Get Collection ID
	const size_t detN=3, primN=1;
	G4String detName[detN] = { "CEE_Pix_logic_det", "CEE_TPC_logic_det", "CEE_T0_logic_det" };
	G4String primName[primN] = { "eDep" };
	/*  {"eDep","nGamma","nElectron","nPositron","trackLength","nStep"};
	 *  {"minEkinGamma","minEkinElectron","minEkinPositron"}; */

	G4SDManager* SDMan = G4SDManager::GetSDMpointer();
	G4cerr << "---> SDManager has collection capacity " << SDMan->GetCollectionCapacity() << G4endl;
	G4String fullName;
	G4int colID[detN][primN] = { 0 };
	for(size_t i=0; i<detN; i++)
	{
		for(size_t j=0; j<primN; j++)
		{
			fullName = detName[i] + "/" + primName[j];
			colID[i][j] = SDMan->GetCollectionID(fullName);
			if(colID[i][j]<0)
			{
				G4cerr << "===> detector invalid for event " << evt->GetEventID()
					<< "." << G4endl;
				return;
			}
		}
	}

	// Record hits
	G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
	if(!HCE)
	{
		G4cerr << "===> No Hits collected or HitsCollection invalid for event " << evt->GetEventID()
			<< "." << G4endl;
		return;
	}
	G4cerr<< "--> HitsCollection for event " << evt->GetEventID() << " has capacity of " << HCE->GetCapacity() << G4endl;
	G4String fileName = "results/Event" + std::to_string(evt->GetEventID()) + ".txt";
	std::ofstream evtOut;
	G4cout << "Outputing result to file " << fileName << G4endl;
	evtOut.open(fileName, std::ofstream::out|std::ofstream::trunc);
	evtOut << "### Event " << evt->GetEventID() << std::endl;

	for(size_t i=0; i<detN; i++)
	{
		for(size_t j=0; j<primN; j++)
		{
			G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(colID[i][j]));
			evtOut << "## G4THitsMap<G4double> for " << detName[i] << "/" << primName[j] << std::endl;
			evtOut << "# key\tvalue" << std::endl;
			for(auto it: *(evtMap->GetMap()))
			{
				evtOut << it.first << "\t" << *(it.second) << std::endl;
			}
		}
	}
	evtOut.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

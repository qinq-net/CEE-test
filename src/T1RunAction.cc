#include "T1RunAction.hh"
//#include "T1PrimaryGeneratorAction.hh"
#include "T1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4ParameterManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "CEEEventLoggingSession.hh"
#include <G4UImanager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1RunAction::T1RunAction()
: G4UserRunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1RunAction::~T1RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T1RunAction::BeginOfRunAction(const G4Run* aRun)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  G4String outFileName = "results.txt";
  G4String errFileName = "errors.txt";
  G4cout << "Relocating G4cout to file: " << outFileName << G4endl;
  CEEEventLoggingSession* session = new CEEEventLoggingSession(
  	outFileName, errFileName);
  G4UImanager* UI=G4UImanager::GetUIpointer();
  G4UIsession* oldSession = UI->GetSession();
  if(UI) UI->SetCoutDestination(session);
  // G4cout has been relocated.
  
  G4cout << "## RunID: " << aRun->GetRunID() << G4endl;
  G4cout << "#EventID\tX0[mm]\tY0[mm]\tZ\tA\tEnergy[MeV]\tDeltaE[MeV]\tECsI[MeV]" << G4endl;
  
  // relocating G4cout back to screen
  	if(UI) UI->SetCoutDestination(oldSession);
  	delete session;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T1RunAction::EndOfRunAction(const G4Run*)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

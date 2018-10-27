#include "T1PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "Randomize.hh"
#include "ENPGInfo.hh"
#include <sstream>

extern G4double energy; //dai danwei

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1PrimaryGeneratorAction::T1PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
                    = particleTable->FindParticle("chargedgeantino");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-80*cm));
  fParticleGun->SetParticleEnergy(12*energy);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1PrimaryGeneratorAction::~T1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
  //if (particle == G4ChargedGeantino::ChargedGeantino()) {
    G4int Z = 2, A = 4;//H
    G4double ionCharge   = 6.*eplus;
    G4double excitEnergy = 0.*keV;

    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  //}
std::cerr << "Generating Primaries" << std::endl;
  G4double energyChanged = energy * (anEvent->GetEventID()/10+1) ;
  fParticleGun->SetParticleEnergy(energyChanged);
  G4double x0 = 1.*mm * (G4UniformRand()-0.5);
  G4double y0 = 1.*mm * (G4UniformRand()-0.5);
  G4double z0 = -800.*mm;
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  std::stringstream infoss1, infoss2;
  infoss1 << "EventID:" << anEvent->GetEventID() <<
            " Energy: " << energyChanged/MeV << "MeV" <<
            " X0: " << x0/mm << "mm" <<
            " Y0: " << y0/mm << "mm" <<
	    " Z: " << Z <<
	    " A: " << A << std::endl;
std::cerr << infoss1.str() << std::endl;
  infoss2 << anEvent->GetEventID() << '\t' //EventID
          << x0/mm << '\t' //X0
          << y0/mm << '\t' //Y0
	  << Z << '\t' //Z
	  << A << '\t' // A
          << energyChanged/MeV;//Energy
  ENPGInfo* info = new ENPGInfo(infoss2.str());
  anEvent->SetUserInformation(info);


  //create vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
  
}

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
  if (particle == G4ChargedGeantino::ChargedGeantino()) {
    //C12
    G4int Z = 6, A = 12;
    G4double ionCharge   = 6.*eplus;
    G4double excitEnergy = 0.*keV;

    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  }
std::cerr << "Generating Primaries" << std::endl;
  G4double energyChanged = energy * anEvent->GetEventID();
  fParticleGun->SetParticleEnergy(energyChanged);
  G4double x0 = 1.*mm * (G4UniformRand()-0.5);
  G4double y0 = 1.*mm * (G4UniformRand()-0.5);
  G4double z0 = -800.*mm;
  std::stringstream infoss;
  infoss << "Energy: " << energyChanged/MeV << "MeV" <<
            " X0: " << x0/mm << "mm" <<
            " Y0: " << y0/mm << "mm" << std::endl;
std::cerr << infoss.str() << std::endl;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  //create vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
  ENPGInfo* info = new ENPGInfo(infoss.str());
  anEvent->SetUserInformation(info);
  
}

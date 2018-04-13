#ifndef T1DetectorConstruction_h
#define T1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include <G4LogicalVolume.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class T1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    T1DetectorConstruction();
    virtual ~T1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    void ConstructSDandField();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    virtual void SetupDetectors();

  protected:
    G4LogicalVolume*  fScoringVolume;
    //std::vector<G4LogicalVolume*> sensitiveDetectors;
    std::vector<G4LogicalVolume*> PixDetectorLVs;
    std::vector<G4LogicalVolume*> TPCDetectorLVs;
    std::vector<G4LogicalVolume*>  t1t0DetectorLVs;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

// $Id: B4cCalorimeterSD.hh 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file B4cCalorimeterSD.hh
/// \brief Definition of the B4cCalorimeterSD class

#ifndef B4cDetectorSD_h
#define B4cDetectorSD_h 1

#include "G4VSensitiveDetector.hh"

#include "B4cDetectorHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

/// Calorimeter sensitive detector class
///
/// In Initialize(), it creates one hit for each calorimeter layer and one more
/// hit for accounting the total quantities in all layers.
///
/// The values are accounted in hits in ProcessHits() function which is called
/// by Geant4 kernel at each step.

class B4cDetectorSD : public G4VSensitiveDetector
{
  public:
    B4cDetectorSD(const G4String& name, 
                     const G4String& hitsCollectionName);
    virtual ~B4cDetectorSD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    B4cDetectorHitsCollection* fHitsCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


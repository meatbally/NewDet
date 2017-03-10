// $Id: B4cDetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4cDetectorConstruction.hh
/// \brief Definition of the B4cDetectorConstruction class

#ifndef B4cDetectorConstruction_h
#define B4cDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In ConstructSDandField() sensitive detectors of B4cCalorimeterSD type
/// are created and associated with the Absorber and Gap volumes.
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class B4cDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B4cDetectorConstruction();
    virtual ~B4cDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    
    const G4VPhysicalVolume* GetTest1PV() const;
    const G4VPhysicalVolume* GetTest2PV() const;

    G4VPhysicalVolume*  fTest1;
    G4VPhysicalVolume*  fTest2;

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

inline const G4VPhysicalVolume* B4cDetectorConstruction::GetTest1PV() const { return fTest1; }
inline const G4VPhysicalVolume* B4cDetectorConstruction::GetTest2PV() const { return fTest2; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


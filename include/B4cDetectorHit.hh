// $Id: B4cCalorHit.hh 69223 2013-04-23 12:36:10Z gcosmo $
//
/// \file B4cCalorHit.hh
/// \brief Definition of the B4cCalorHit class

#ifndef B4cDetectorHit_h
#define B4cDetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

/// Calorimeter hit class
///
/// It defines data members to store the the energy deposit and track lengths
/// of charged particles in a selected volume:
/// - fEdep, fTrackLength

class B4cDetectorHit : public G4VHit
{
  public:
    B4cDetectorHit();
    B4cDetectorHit(const B4cDetectorHit&);
    virtual ~B4cDetectorHit();

    // operators
    const B4cDetectorHit& operator=(const B4cDetectorHit&);
    G4int operator==(const B4cDetectorHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw() {}
    virtual void Print();

    // methods to handle data
    void Add(G4double de, G4double dt);

    // get methods
    G4double GetEdep() const;
    G4double GetTime() const;
      
  private:
    G4double fEdep;        ///< Energy deposit in the sensitive volume
    G4double fTime;        ///< Record time
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<B4cDetectorHit> B4cDetectorHitsCollection;

extern G4ThreadLocal G4Allocator<B4cDetectorHit>* B4cDetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* B4cDetectorHit::operator new(size_t)
{
  if(!B4cDetectorHitAllocator)
    B4cDetectorHitAllocator = new G4Allocator<B4cDetectorHit>;
  void *hit;
  hit = (void *) B4cDetectorHitAllocator->MallocSingle();
  return hit;
}

inline void B4cDetectorHit::operator delete(void *hit)
{
  if(!B4cDetectorHitAllocator)
    B4cDetectorHitAllocator = new G4Allocator<B4cDetectorHit>;
  B4cDetectorHitAllocator->FreeSingle((B4cDetectorHit*) hit);
}

inline void B4cDetectorHit::Add(G4double de, G4double dt) {
  fEdep += de; 

  if (fTime == 0.) { fTime = dt; }
}

inline G4double B4cDetectorHit::GetEdep() const { 
  return fEdep; 
}

inline G4double B4cDetectorHit::GetTime() const { 
  return fTime; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

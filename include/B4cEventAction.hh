// $Id: B4cEventAction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4cEventAction.hh
/// \brief Definition of the B4cEventAction class

#ifndef B4cEventAction_h
#define B4cEventAction_h 1

#include "G4UserEventAction.hh"

#include "B4cDetectorHit.hh"

#include "globals.hh"

/// Event action class
///
/// In EndOfEventAction(), it prints the accumulated quantities of the energy 
/// deposit and track lengths of charged particles in Absober and Gap layers 
/// stored in the hits collections.

class B4cEventAction : public G4UserEventAction
{
public:
  B4cEventAction();
  virtual ~B4cEventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);

  void FindEnergy1(G4double ke);
  void FindEnergy2(G4double ke);
    
private:
  // methods
  B4cDetectorHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;
  // void PrintEventStatistics(G4double NaI1Edep, G4double NaI1TrackLength,
  //                           G4double NaI2Edep, G4double NaI2TrackLength) const;
  
  // data members                   
  G4int  fScint1HCID;
  G4int  fScint2HCID;
  G4int  fScint3HCID;
  G4int  fScint4HCID;
  G4int  fScint5HCID;
  G4int  fScint6HCID;
  G4int  fScint7HCID;
  G4int  fScint8HCID;
  G4int  fScint9HCID;
  G4int  fScint10HCID;
  G4int  fScint11HCID;
  G4int  fScint12HCID;
  G4int  fScint13HCID;
  G4int  fScint14HCID;
  G4int  fScint15HCID;
  G4int  fScint16HCID;
  G4int  fScint17HCID;
  G4int  fScint18HCID;
  G4int  fScint19HCID;
  G4int  fScint20HCID;

  G4double fTest1, fTest2;
};

inline void B4cEventAction::FindEnergy1(G4double ke) { fTest1 += ke; }
inline void B4cEventAction::FindEnergy2(G4double ke) { fTest2 += ke; }
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    

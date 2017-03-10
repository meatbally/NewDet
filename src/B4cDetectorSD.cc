// $Id: B4cCalorimeterSD.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B4cCalorimeterSD.cc
/// \brief Implementation of the B4cCalorimeterSD class

#include "B4cDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4TouchableHistory.hh"
#include "G4Track.hh"

#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorSD::B4cDetectorSD(
                            const G4String& name, 
                            const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(0)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorSD::~B4cDetectorSD() 
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection = new B4cDetectorHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 

  fHitsCollection->insert(new B4cDetectorHit());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool B4cDetectorSD::ProcessHits(G4Step* step, 
                                     G4TouchableHistory*)
{  
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  
  G4StepPoint* preStepPoint = step->GetPreStepPoint();

  G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4double hitTime = preStepPoint->GetGlobalTime();   

  // G4TouchableHistory* touchable = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
  
  // Get hit for total accounting
  B4cDetectorHit* hitTotal = (*fHitsCollection)[fHitsCollection->entries()-1];

  B4cDetectorHit* hit = hitTotal;

  // B4cDetectorHit* hit = new B4cDetectorHit();

  // G4cout << "hitEnergy = " << G4BestUnit(edep, "Energy") << G4endl;
  
  // Add values
  hit->Add(edep,hitTime);
  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>1 ) { 
     G4int nofHits = fHitsCollection->entries();
     G4cout
       << G4endl 
       << "-------->Hits Collection: in this event they are " << nofHits 
       << " hits in the tracker chambers: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

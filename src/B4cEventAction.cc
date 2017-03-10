// $Id: B4cEventAction.cc 89037 2015-03-18 09:25:01Z gcosmo $
// 
/// \file B4cEventAction.cc
/// \brief Implementation of the B4cEventAction class

#include "B4cEventAction.hh"
#include "B4cDetectorSD.hh"
#include "B4cDetectorHit.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cEventAction::B4cEventAction()
 : G4UserEventAction(),
   fScint1HCID(-1), fScint2HCID(-1), fScint3HCID(-1), fScint4HCID(-1), fScint5HCID(-1),
   fScint6HCID(-1), fScint7HCID(-1), fScint8HCID(-1), fScint9HCID(-1), fScint10HCID(-1),
   fScint11HCID(-1), fScint12HCID(-1), fScint13HCID(-1), fScint14HCID(-1), fScint15HCID(-1),
   fScint16HCID(-1), fScint17HCID(-1), fScint18HCID(-1), fScint19HCID(-1), fScint20HCID(-1)

   //fTest1(0.), fTest2(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cEventAction::~B4cEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorHitsCollection* 
B4cEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  B4cDetectorHitsCollection* hitsCollection 
    = static_cast<B4cDetectorHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void B4cEventAction::PrintEventStatistics(
//                               G4double NaI1Edep, G4double NaI1TrackLength,
//                               G4double NaI2Edep, G4double NaI2TrackLength) const
// {
//   // print event statistics
//   G4cout
//      << "NaI1: total energy: " 
//      << std::setw(7) << G4BestUnit(NaI1Edep, "Energy")
//      << "total track length: " 
//      << std::setw(7) << G4BestUnit(NaI1TrackLength, "Length")
//      << G4endl
//      << "NaI2: total energy: " 
//      << std::setw(7) << G4BestUnit(NaI2Edep, "Energy")
//      << "total track length: " 
//      << std::setw(7) << G4BestUnit(NaI2TrackLength, "Length")
//      << G4endl;
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  // fTest1 = 0;
  // fTest1 = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::EndOfEventAction(const G4Event* event)
{  
  // Get hits collections IDs (only once)
  if ( fScint1HCID == -1 ) {
    fScint1HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint1HitsCollection");
    fScint2HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint2HitsCollection");
    fScint3HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint3HitsCollection");
    fScint4HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint4HitsCollection");
    fScint5HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint5HitsCollection");
    fScint6HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint6HitsCollection");
    fScint7HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint7HitsCollection");
    fScint8HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint8HitsCollection");
    fScint9HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint9HitsCollection");
    fScint10HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint10HitsCollection");
    fScint11HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint11HitsCollection");
    fScint12HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint12HitsCollection");
    fScint13HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint13HitsCollection");
    fScint14HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint14HitsCollection");
    fScint15HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint15HitsCollection");
    fScint16HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint16HitsCollection");
    fScint17HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint17HitsCollection");
    fScint18HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint18HitsCollection");
    fScint19HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint19HitsCollection");
    fScint20HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Scint20HitsCollection");
    // fTest1HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Test1HitsCollection");
    // fTest2HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Test2HitsCollection");
  }

  // Get hits collections
  B4cDetectorHitsCollection* Scint1HC = GetHitsCollection(fScint1HCID, event);
  B4cDetectorHitsCollection* Scint2HC = GetHitsCollection(fScint2HCID, event);
  B4cDetectorHitsCollection* Scint3HC = GetHitsCollection(fScint3HCID, event);
  B4cDetectorHitsCollection* Scint4HC = GetHitsCollection(fScint4HCID, event);
  B4cDetectorHitsCollection* Scint5HC = GetHitsCollection(fScint5HCID, event);
  B4cDetectorHitsCollection* Scint6HC = GetHitsCollection(fScint6HCID, event);
  B4cDetectorHitsCollection* Scint7HC = GetHitsCollection(fScint7HCID, event);
  B4cDetectorHitsCollection* Scint8HC = GetHitsCollection(fScint8HCID, event);
  B4cDetectorHitsCollection* Scint9HC = GetHitsCollection(fScint9HCID, event);
  B4cDetectorHitsCollection* Scint10HC = GetHitsCollection(fScint10HCID, event);
  B4cDetectorHitsCollection* Scint11HC = GetHitsCollection(fScint11HCID, event);
  B4cDetectorHitsCollection* Scint12HC = GetHitsCollection(fScint12HCID, event);
  B4cDetectorHitsCollection* Scint13HC = GetHitsCollection(fScint13HCID, event);
  B4cDetectorHitsCollection* Scint14HC = GetHitsCollection(fScint14HCID, event);
  B4cDetectorHitsCollection* Scint15HC = GetHitsCollection(fScint15HCID, event);
  B4cDetectorHitsCollection* Scint16HC = GetHitsCollection(fScint16HCID, event);
  B4cDetectorHitsCollection* Scint17HC = GetHitsCollection(fScint17HCID, event);
  B4cDetectorHitsCollection* Scint18HC = GetHitsCollection(fScint18HCID, event);
  B4cDetectorHitsCollection* Scint19HC = GetHitsCollection(fScint19HCID, event);
  B4cDetectorHitsCollection* Scint20HC = GetHitsCollection(fScint20HCID, event);
  // B4cDetectorHitsCollection* Test1HC = GetHitsCollection(fTest1HCID, event);
  // B4cDetectorHitsCollection* Test2HC = GetHitsCollection(fTest2HCID, event);

  // Get hit with total values
  B4cDetectorHit* Scint1Hit = (*Scint1HC)[Scint1HC->entries()-1];
  B4cDetectorHit* Scint2Hit = (*Scint2HC)[Scint2HC->entries()-1];
  B4cDetectorHit* Scint3Hit = (*Scint3HC)[Scint3HC->entries()-1];
  B4cDetectorHit* Scint4Hit = (*Scint4HC)[Scint4HC->entries()-1];
  B4cDetectorHit* Scint5Hit = (*Scint5HC)[Scint5HC->entries()-1];
  B4cDetectorHit* Scint6Hit = (*Scint6HC)[Scint6HC->entries()-1];
  B4cDetectorHit* Scint7Hit = (*Scint7HC)[Scint7HC->entries()-1];
  B4cDetectorHit* Scint8Hit = (*Scint8HC)[Scint8HC->entries()-1];
  B4cDetectorHit* Scint9Hit = (*Scint9HC)[Scint9HC->entries()-1];
  B4cDetectorHit* Scint10Hit = (*Scint10HC)[Scint10HC->entries()-1];
  B4cDetectorHit* Scint11Hit = (*Scint11HC)[Scint11HC->entries()-1];
  B4cDetectorHit* Scint12Hit = (*Scint12HC)[Scint12HC->entries()-1];
  B4cDetectorHit* Scint13Hit = (*Scint13HC)[Scint13HC->entries()-1];
  B4cDetectorHit* Scint14Hit = (*Scint14HC)[Scint14HC->entries()-1];
  B4cDetectorHit* Scint15Hit = (*Scint15HC)[Scint15HC->entries()-1];
  B4cDetectorHit* Scint16Hit = (*Scint16HC)[Scint16HC->entries()-1];
  B4cDetectorHit* Scint17Hit = (*Scint17HC)[Scint17HC->entries()-1];
  B4cDetectorHit* Scint18Hit = (*Scint18HC)[Scint18HC->entries()-1];
  B4cDetectorHit* Scint19Hit = (*Scint19HC)[Scint19HC->entries()-1];
  B4cDetectorHit* Scint20Hit = (*Scint20HC)[Scint20HC->entries()-1];
  // B4cDetectorHit* Test1Hit = (*Test1HC)[Test1HC->entries()-1];
  // B4cDetectorHit* Test2Hit = (*Test2HC)[Test2HC->entries()-1];

  // B4cDetectorHit* PlasticHit = (*PlasticHC)[PlasticHC->entries()-1];
 
  // Print per event (modulo n)
  // G4int eventID = event->GetEventID();
  // G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  // if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
  //   G4cout << "---> End of event: " << eventID << G4endl;     

    // PrintEventStatistics(
      // NaI1Hit->GetEdep(), NaI1Hit->GetTrackLength(),
      //  NaI2Hit->GetEdep(), NaI2Hit->GetTrackLength());
  // }  
  
  // Fill histograms, ntuple
  //

  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
  // fill histograms
  analysisManager->FillH1(1, Scint1Hit->GetEdep());
  analysisManager->FillH1(2, Scint2Hit->GetEdep());
  analysisManager->FillH1(3, Scint3Hit->GetEdep());
  analysisManager->FillH1(4, Scint4Hit->GetEdep());
  analysisManager->FillH1(5, Scint5Hit->GetEdep());
  analysisManager->FillH1(6, Scint6Hit->GetEdep());
  analysisManager->FillH1(7, Scint7Hit->GetEdep());
  analysisManager->FillH1(8, Scint8Hit->GetEdep());
  analysisManager->FillH1(9, Scint9Hit->GetEdep());
  analysisManager->FillH1(10, Scint10Hit->GetEdep());

  // analysisManager->FillH1(11, fTest1);
  // analysisManager->FillH1(12, fTest2);

  //G4double SiPM3Time = SiPM3Hit->GetTime();
  //G4double ScintTime = ScintHit->GetTime();
  //G4double tof = ScintTime - SiPM3Time;
  // G4cout << " Lead1 Energy = " << G4BestUnit(Lead1Hit->GetEdep(), "Energy") 
  //        << G4endl;
  //if ( SiPM3Time != 0. && ScintTime != 0. ) { analysisManager->FillH1(5, tof); }

  // fill Nturple
  analysisManager->FillNtupleDColumn(0, Scint1Hit->GetEdep());
  analysisManager->FillNtupleDColumn(1, Scint2Hit->GetEdep());
  analysisManager->FillNtupleDColumn(2, Scint3Hit->GetEdep());
  analysisManager->FillNtupleDColumn(3, Scint4Hit->GetEdep());
  analysisManager->FillNtupleDColumn(4, Scint5Hit->GetEdep());
  analysisManager->FillNtupleDColumn(5, Scint6Hit->GetEdep());
  analysisManager->FillNtupleDColumn(6, Scint7Hit->GetEdep());
  analysisManager->FillNtupleDColumn(7, Scint8Hit->GetEdep());
  analysisManager->FillNtupleDColumn(8, Scint9Hit->GetEdep());
  analysisManager->FillNtupleDColumn(9, Scint10Hit->GetEdep());
  analysisManager->FillNtupleDColumn(10, Scint11Hit->GetEdep());
  analysisManager->FillNtupleDColumn(11, Scint12Hit->GetEdep());
  analysisManager->FillNtupleDColumn(12, Scint13Hit->GetEdep());
  analysisManager->FillNtupleDColumn(13, Scint14Hit->GetEdep());
  analysisManager->FillNtupleDColumn(14, Scint15Hit->GetEdep());
  analysisManager->FillNtupleDColumn(15, Scint16Hit->GetEdep());
  analysisManager->FillNtupleDColumn(16, Scint17Hit->GetEdep());
  analysisManager->FillNtupleDColumn(17, Scint18Hit->GetEdep());
  analysisManager->FillNtupleDColumn(18, Scint19Hit->GetEdep());
  analysisManager->FillNtupleDColumn(19, Scint20Hit->GetEdep());
  analysisManager->AddNtupleRow();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

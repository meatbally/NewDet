// $Id: B4RunAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B4RunAction.cc
/// \brief Implementation of the B4RunAction class

#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4RunAction::B4RunAction()
 : G4UserRunAction()
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);

  // Book histograms, ntuple
  //
  
  // Creating histograms
  G4double lowbound = 0.5*MeV;
  G4double upbound = 5*MeV;
  analysisManager->CreateH1("Scint1","Edep in Scint1", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint2","Edep in Scint2", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint3","Edep in Scint3", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint4","Edep in Scint4", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint5","Edep in Scint5", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint6","Edep in Scint6", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint7","Edep in Scint7", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint8","Edep in Scint8", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint9","Edep in Scint9", 500, lowbound, upbound);
  analysisManager->CreateH1("Scint10","Edep in Scint10", 500, lowbound, upbound);

  // analysisManager->CreateH1("Test1","Kinetic Energy in Plane 1", 500, 0., 100*MeV);
  // analysisManager->CreateH1("Test2","Kinetic Energy in Plane 2", 500, 0., 100*MeV);

  // Creating ntuple
  analysisManager->CreateNtuple("NewDetector", "Edep and Pos");
  analysisManager->CreateNtupleDColumn("Edep1");
  analysisManager->CreateNtupleDColumn("Edep2");
  analysisManager->CreateNtupleDColumn("Edep3");
  analysisManager->CreateNtupleDColumn("Edep4");
  analysisManager->CreateNtupleDColumn("Edep5");
  analysisManager->CreateNtupleDColumn("Edep6");
  analysisManager->CreateNtupleDColumn("Edep7");
  analysisManager->CreateNtupleDColumn("Edep8");
  analysisManager->CreateNtupleDColumn("Edep9");
  analysisManager->CreateNtupleDColumn("Edep10");
  analysisManager->CreateNtupleDColumn("Edep11");
  analysisManager->CreateNtupleDColumn("Edep12");
  analysisManager->CreateNtupleDColumn("Edep13");
  analysisManager->CreateNtupleDColumn("Edep14");
  analysisManager->CreateNtupleDColumn("Edep15");
  analysisManager->CreateNtupleDColumn("Edep16");
  analysisManager->CreateNtupleDColumn("Edep17");
  analysisManager->CreateNtupleDColumn("Edep18");
  analysisManager->CreateNtupleDColumn("Edep19");
  analysisManager->CreateNtupleDColumn("Edep20");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4RunAction::~B4RunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "NewDetector";
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl; 
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl; 
    }
    
    G4cout << " EdepScint1 : mean = " << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy") << G4endl;
    G4cout << " EdepScint2 : mean = " << G4BestUnit(analysisManager->GetH1(2)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint3 : mean = " << G4BestUnit(analysisManager->GetH1(3)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint4 : mean = " << G4BestUnit(analysisManager->GetH1(4)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint5 : mean = " << G4BestUnit(analysisManager->GetH1(5)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint6 : mean = " << G4BestUnit(analysisManager->GetH1(6)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint7 : mean = " << G4BestUnit(analysisManager->GetH1(7)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint8 : mean = " << G4BestUnit(analysisManager->GetH1(8)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint9 : mean = " << G4BestUnit(analysisManager->GetH1(9)->mean(), "Energy") << G4endl;
    G4cout << " EDepScint10 : mean = " << G4BestUnit(analysisManager->GetH1(10)->mean(), "Energy") << G4endl;
  }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

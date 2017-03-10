// $Id: B4cCalorHit.cc 69586 2013-05-08 14:20:11Z gcosmo $
//
/// \file B4cCalorHit.cc
/// \brief Implementation of the B4cCalorHit class

#include "B4cDetectorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<B4cDetectorHit>* B4cDetectorHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorHit::B4cDetectorHit()
 : G4VHit(),
   fEdep(0.),
   fTime(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorHit::~B4cDetectorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorHit::B4cDetectorHit(const B4cDetectorHit& right)
  : G4VHit()
{
  fEdep = right.fEdep;
  fTime = right.fTime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const B4cDetectorHit& B4cDetectorHit::operator=(const B4cDetectorHit& right)
{
  fEdep = right.fEdep;
  fTime = right.fTime;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int B4cDetectorHit::operator==(const B4cDetectorHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorHit::Print()
{
  G4cout
     << "Edep: " 
     << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << "Time: " 
     << std::setw(7) << G4BestUnit(fTime,"Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

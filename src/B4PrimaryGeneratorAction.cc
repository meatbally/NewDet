//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4PrimaryGeneratorAction.cc 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4PrimaryGeneratorAction.cc
/// \brief Implementation of the B4PrimaryGeneratorAction class

#include "B4PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4PrimaryGeneratorAction::B4PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");

  // bean properties
  G4double z0 = -(15+30+0.1)*cm;
  // G4double z0 = -1.5*m;
  G4double pin = 100*MeV;
								
  G4double sig_xp = 0;
  G4double sig_yp = 0;
  G4double sig_x0 = 0;
  G4double sig_y0 = 0;
  G4double mean_xp = 0;
  G4double mean_yp = 0;
  G4double mean_x0 = 0;
  G4double mean_y0 = 0;
  G4double fpx =  0.;
  G4double fpy =  0.;
            
  // negatively charged particles, or neutrals, geantino          
  if (pin < 130.0 * MeV) {
    mean_xp = -8./1000.;
    mean_yp = +8./1000.;
    mean_x0 = 3. * mm;
    mean_y0 = 2. * mm;
    sig_xp = 18./1000.;
    sig_yp =  6./1000.;
    sig_x0 = 0. * mm;
    sig_y0 = 6. * mm;
    fpx =  0. * mm;
    fpy =  -300. * mm;
  } else if (pin < 180.0 * MeV) {
    mean_xp = -8./1000.;
    mean_yp = +4./1000.;
    mean_x0 = 2. * mm;
    mean_y0 = 1. * mm;
    sig_xp = 15./1000.;
    sig_yp = 10./1000.;
    sig_x0 = 2. * mm;
    sig_y0 = 5. * mm;
    fpx =  -20. * mm;
    fpy =  -300. * mm;
  } else {
    mean_xp = -2./1000.;
    mean_yp = +4./1000.;
    mean_x0 = 0. * mm;
    mean_y0 = -1. * mm;
    sig_xp = 10./1000.;
    sig_yp = 7./1000.;
    sig_x0 = 2. * mm;
    sig_y0 = 4. * mm;
    fpx =  -20. * mm;
    fpy =  -400. * mm;
  }
        
  // gunMode_ == BEAMLINE_2015_CENTER) 
  // no positional or directional offset 
  mean_xp = 0.0;
  mean_yp = 0.0;
  mean_x0 = 0.0;
  mean_y0 = 0.0;
  
  G4double xp = CLHEP::RandGauss::shoot(mean_xp, sig_xp);
  G4double yp = CLHEP::RandGauss::shoot(mean_yp, sig_yp);
  G4double x0 = CLHEP::RandGauss::shoot(mean_x0, sig_x0) + (z0 - fpx) * xp;
  G4double y0 = CLHEP::RandGauss::shoot(mean_y0, sig_y0) + (z0 - fpy) * yp;
        
  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, -z0));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xp, yp, -1.));
  // G4double kinEnergy = std::sqrt(pin*pin+mass*mass) - mass;
  // particleGun->SetParticleEnergy(kinEnergy);
  
  fParticleGun->SetParticleDefinition(particle);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.,0.,0.));
  fParticleGun->SetParticleMomentum(pin);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4PrimaryGeneratorAction::~B4PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore
  //
  G4double worldZHalfLength = 0;
  G4LogicalVolume* worlLV
    = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox = 0;
  if ( worlLV) worldBox = dynamic_cast< G4Box*>(worlLV->GetSolid()); 
  if ( worldBox ) {
    worldZHalfLength = worldBox->GetZHalfLength();  
  }
  else  {
    G4ExceptionDescription msg;
    msg << "World volume of box not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()",
		"MyCode0002", JustWarning, msg);
  } 
  
  // Set gun position
  // fParticleGun
  //  ->SetParticlePosition(G4ThreeVector((193.1+30+4.5+0.1)*cm, 0., 0.));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


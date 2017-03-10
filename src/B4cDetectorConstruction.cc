// $Id: B4cDetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
// 
/// \file B4cDetectorConstruction.cc
/// \brief Implementation of the B4cDetectorConstruction class

#include "B4cDetectorConstruction.hh"
#include "B4cDetectorSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorConstruction::B4cDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
   // fTest1(0),
   // fTest2(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorConstruction::~B4cDetectorConstruction()
{ 
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4cDetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::DefineMaterials()
{ 
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_GLASS_LEAD");


 // Tedlar material
  G4Element* C = new G4Element("Carbon"  , "C", 6., 12.011*g/mole);
  G4Element* H = new G4Element("Hydrogen", "H", 1., 1.0079*g/mole);
  G4Element* F = new G4Element("Fluoride", "F", 9., 18.998*g/mole);
  G4Material* Tedlar = new G4Material("PolyvinylFluoride", 1.5*g/cm3, 3);
  Tedlar->AddElement(C, 2);
  Tedlar->AddElement(H, 3);
  Tedlar->AddElement(F, 1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4cDetectorConstruction::DefineVolumes()
{
  // World Geometry
  G4double worldSizeX = 100*cm;
  G4double worldSizeY = 100*cm;
  G4double worldSizeZ = 282*cm; 

  // rotation matrix
  G4double theta = 0.8593722*deg, phi = 0.*deg;
  G4double ax1 = cos(theta)*cos(phi), ax2 = -sin(phi), ax3 = sin(theta)*cos(phi);
  G4double ay1 = cos(theta)*sin(phi), ay2 =  cos(phi), ay3 = sin(theta)*sin(phi);
  G4double az1 = -sin(theta),         az2 =  0,        az3 = cos(theta);
  
  G4ThreeVector xAxis(ax1, ax2, ax3);
  G4ThreeVector yAxis(ay1, ay2, ay3);
  G4ThreeVector zAxis(az1, az2, az3);
  G4RotationMatrix* rot = new G4RotationMatrix();
  rot->rotateAxes(xAxis, yAxis, zAxis);
  rot->invert();
  
  // Get materials
  G4Material* air = G4Material::GetMaterial("G4_AIR");
  G4Material* lead = G4Material::GetMaterial("G4_Pb");
  // G4Material* glass = G4Material::GetMaterial("G4_SILICON_DIOXIDE");
  G4Material* plastic = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  //G4Material* Tedlar = G4Material::GetMaterial("PolyvinylFluoride");
  G4Material* leadglass = G4Material::GetMaterial("G4_GLASS_LEAD");
      
  // World
  G4VSolid* worldS = new G4Box("World",worldSizeX/2, worldSizeY/2, worldSizeZ/2); 
  G4LogicalVolume* worldLV = new G4LogicalVolume(worldS,air,"World");
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,G4ThreeVector(),worldLV,"World",0,false,0,fCheckOverlaps);

  // To Record Energy
  // G4Box* testSolid = new G4Box("TestSolid", 15.*cm, 15.*cm, 0.15*mm);
  // G4LogicalVolume* testLog1 = new G4LogicalVolume(testSolid, air, "TestLog1");
  // G4LogicalVolume* testLog2 = new G4LogicalVolume(testSolid, air, "TestLog2");
  // G4ThreeVector test1Pos = G4ThreeVector(0*cm, 0*cm, 15*cm);
  // G4ThreeVector test2Pos = G4ThreeVector(0*cm, 0*cm, 30*cm);
  // fTest1 = 
  // new G4PVPlacement(0, test1Pos, testLog1, "testPhys1", worldLV, false, 0, fCheckOverlaps);
  // fTest2 = 
  // new G4PVPlacement(0, test2Pos, testLog2, "testPhys2", worldLV, false, 0, fCheckOverlaps);

  // Scintillators
  G4double gap = 12.5*mm;
  G4Box* scintBox = new G4Box("Scint", 15*cm, 15*cm, 1.5*mm);
  G4LogicalVolume* scintLog1 = new G4LogicalVolume(scintBox, plastic, "Scintlog1");
  G4LogicalVolume* scintLog2 = new G4LogicalVolume(scintBox, plastic, "Scintlog2");
  G4LogicalVolume* scintLog3 = new G4LogicalVolume(scintBox, plastic, "Scintlog3");
  G4LogicalVolume* scintLog4 = new G4LogicalVolume(scintBox, plastic, "Scintlog4");
  G4LogicalVolume* scintLog5 = new G4LogicalVolume(scintBox, plastic, "Scintlog5");
  G4LogicalVolume* scintLog6 = new G4LogicalVolume(scintBox, plastic, "Scintlog6");
  G4LogicalVolume* scintLog7 = new G4LogicalVolume(scintBox, plastic, "Scintlog7");
  G4LogicalVolume* scintLog8 = new G4LogicalVolume(scintBox, plastic, "Scintlog8");
  G4LogicalVolume* scintLog9 = new G4LogicalVolume(scintBox, plastic, "Scintlog9");
  G4LogicalVolume* scintLog10 = new G4LogicalVolume(scintBox, plastic, "Scintlog10");
  G4LogicalVolume* scintLog11 = new G4LogicalVolume(scintBox, plastic, "Scintlog11");
  G4LogicalVolume* scintLog12 = new G4LogicalVolume(scintBox, plastic, "Scintlog12");
  G4LogicalVolume* scintLog13 = new G4LogicalVolume(scintBox, plastic, "Scintlog13");
  G4LogicalVolume* scintLog14 = new G4LogicalVolume(scintBox, plastic, "Scintlog14");
  G4LogicalVolume* scintLog15 = new G4LogicalVolume(scintBox, plastic, "Scintlog15");
  G4LogicalVolume* scintLog16 = new G4LogicalVolume(scintBox, plastic, "Scintlog16");
  G4LogicalVolume* scintLog17 = new G4LogicalVolume(scintBox, plastic, "Scintlog17");
  G4LogicalVolume* scintLog18 = new G4LogicalVolume(scintBox, plastic, "Scintlog18");
  G4LogicalVolume* scintLog19 = new G4LogicalVolume(scintBox, plastic, "Scintlog19");
  G4LogicalVolume* scintLog20 = new G4LogicalVolume(scintBox, plastic, "Scintlog20");
  G4ThreeVector scint1  = G4ThreeVector(0*cm, 0*cm, -(15*mm+1*gap));
  G4ThreeVector scint2  = G4ThreeVector(0*cm, 0*cm, -(15*mm+3*gap));
  G4ThreeVector scint3  = G4ThreeVector(0*cm, 0*cm, -(15*mm+5*gap));
  G4ThreeVector scint4  = G4ThreeVector(0*cm, 0*cm, -(15*mm+7*gap));
  G4ThreeVector scint5  = G4ThreeVector(0*cm, 0*cm, -(15*mm+9*gap));
  G4ThreeVector scint6  = G4ThreeVector(0*cm, 0*cm, -(15*mm+11*gap));
  G4ThreeVector scint7  = G4ThreeVector(0*cm, 0*cm, -(15*mm+13*gap));
  G4ThreeVector scint8  = G4ThreeVector(0*cm, 0*cm, -(15*mm+15*gap));
  G4ThreeVector scint9  = G4ThreeVector(0*cm, 0*cm, -(15*mm+17*gap));
  G4ThreeVector scint10  = G4ThreeVector(0*cm, 0*cm, -(15*mm+19*gap));
  G4ThreeVector scint11  = G4ThreeVector(0*cm, 0*cm, -(15*mm+21*gap));
  G4ThreeVector scint12  = G4ThreeVector(0*cm, 0*cm, -(15*mm+23*gap));
  G4ThreeVector scint13  = G4ThreeVector(0*cm, 0*cm, -(15*mm+25*gap));
  G4ThreeVector scint14  = G4ThreeVector(0*cm, 0*cm, -(15*mm+27*gap));
  G4ThreeVector scint15  = G4ThreeVector(0*cm, 0*cm, -(15*mm+29*gap));
  G4ThreeVector scint16  = G4ThreeVector(0*cm, 0*cm, -(15*mm+31*gap));
  G4ThreeVector scint17  = G4ThreeVector(0*cm, 0*cm, -(15*mm+33*gap));
  G4ThreeVector scint18  = G4ThreeVector(0*cm, 0*cm, -(15*mm+35*gap));
  G4ThreeVector scint19  = G4ThreeVector(0*cm, 0*cm, -(15*mm+37*gap));
  G4ThreeVector scint20  = G4ThreeVector(0*cm, 0*cm, -(15*mm+39*gap));
  new G4PVPlacement(0, scint1, scintLog1, "SCINT1", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint2, scintLog2, "SCINT2", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint3, scintLog3, "SCINT3", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint4, scintLog4, "SCINT4", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint5, scintLog5, "SCINT5", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint6, scintLog6, "SCINT6", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint7, scintLog7, "SCINT7", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint8, scintLog8, "SCINT8", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint9, scintLog9, "SCINT9", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint10, scintLog10, "SCINT10", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint11, scintLog11, "SCINT11", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint12, scintLog12, "SCINT12", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint13, scintLog13, "SCINT13", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint14, scintLog14, "SCINT14", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint15, scintLog15, "SCINT15", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint16, scintLog16, "SCINT16", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint17, scintLog17, "SCINT17", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint18, scintLog18, "SCINT18", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint19, scintLog19, "SCINT19", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, scint20, scintLog20, "SCINT20", worldLV, false, 0, fCheckOverlaps);

  // Leads
  G4Box* leadPlate = new G4Box("Lead", 15*cm, 15*cm, (2.5/4.)*mm); //2.5*mm
  G4LogicalVolume* leadLog1 = new G4LogicalVolume(leadPlate, lead, "Leadlog1");
  G4LogicalVolume* leadLog2 = new G4LogicalVolume(leadPlate, lead, "Leadlog2");
  G4LogicalVolume* leadLog3 = new G4LogicalVolume(leadPlate, lead, "Leadlog3");
  G4LogicalVolume* leadLog4 = new G4LogicalVolume(leadPlate, lead, "Leadlog4");
  G4LogicalVolume* leadLog5 = new G4LogicalVolume(leadPlate, lead, "Leadlog5");
  G4LogicalVolume* leadLog6 = new G4LogicalVolume(leadPlate, lead, "Leadlog6");
  G4LogicalVolume* leadLog7 = new G4LogicalVolume(leadPlate, lead, "Leadlog7");
  G4LogicalVolume* leadLog8 = new G4LogicalVolume(leadPlate, lead, "Leadlog8");
  G4LogicalVolume* leadLog9 = new G4LogicalVolume(leadPlate, lead, "Leadlog9");
  G4LogicalVolume* leadLog10 = new G4LogicalVolume(leadPlate, lead, "Leadlog10");
  G4LogicalVolume* leadLog11 = new G4LogicalVolume(leadPlate, lead, "Leadlog11");
  G4LogicalVolume* leadLog12 = new G4LogicalVolume(leadPlate, lead, "Leadlog12");
  G4LogicalVolume* leadLog13 = new G4LogicalVolume(leadPlate, lead, "Leadlog13");
  G4LogicalVolume* leadLog14 = new G4LogicalVolume(leadPlate, lead, "Leadlog14");
  G4LogicalVolume* leadLog15 = new G4LogicalVolume(leadPlate, lead, "Leadlog15");
  G4LogicalVolume* leadLog16 = new G4LogicalVolume(leadPlate, lead, "Leadlog16");
  G4LogicalVolume* leadLog17 = new G4LogicalVolume(leadPlate, lead, "Leadlog17");
  G4LogicalVolume* leadLog18 = new G4LogicalVolume(leadPlate, lead, "Leadlog18");
  G4LogicalVolume* leadLog19 = new G4LogicalVolume(leadPlate, lead, "Leadlog19");
  G4LogicalVolume* leadLog20 = new G4LogicalVolume(leadPlate, lead, "Leadlog20");
  G4ThreeVector lead1  = G4ThreeVector(0*cm, 0*cm, -(15*mm+0*gap));
  G4ThreeVector lead2  = G4ThreeVector(0*cm, 0*cm, -(15*mm+2*gap));
  G4ThreeVector lead3  = G4ThreeVector(0*cm, 0*cm, -(15*mm+4*gap));
  G4ThreeVector lead4  = G4ThreeVector(0*cm, 0*cm, -(15*mm+6*gap));
  G4ThreeVector lead5  = G4ThreeVector(0*cm, 0*cm, -(15*mm+8*gap));
  G4ThreeVector lead6  = G4ThreeVector(0*cm, 0*cm, -(15*mm+10*gap));
  G4ThreeVector lead7  = G4ThreeVector(0*cm, 0*cm, -(15*mm+12*gap));
  G4ThreeVector lead8  = G4ThreeVector(0*cm, 0*cm, -(15*mm+14*gap));
  G4ThreeVector lead9  = G4ThreeVector(0*cm, 0*cm, -(15*mm+16*gap));
  G4ThreeVector lead10  = G4ThreeVector(0*cm, 0*cm, -(15*mm+18*gap));
  G4ThreeVector lead11  = G4ThreeVector(0*cm, 0*cm, -(15*mm+20*gap));
  G4ThreeVector lead12  = G4ThreeVector(0*cm, 0*cm, -(15*mm+22*gap));
  G4ThreeVector lead13  = G4ThreeVector(0*cm, 0*cm, -(15*mm+24*gap));
  G4ThreeVector lead14  = G4ThreeVector(0*cm, 0*cm, -(15*mm+26*gap));
  G4ThreeVector lead15  = G4ThreeVector(0*cm, 0*cm, -(15*mm+28*gap));
  G4ThreeVector lead16  = G4ThreeVector(0*cm, 0*cm, -(15*mm+30*gap));
  G4ThreeVector lead17  = G4ThreeVector(0*cm, 0*cm, -(15*mm+32*gap));
  G4ThreeVector lead18  = G4ThreeVector(0*cm, 0*cm, -(15*mm+34*gap));
  G4ThreeVector lead19  = G4ThreeVector(0*cm, 0*cm, -(15*mm+36*gap));
  G4ThreeVector lead20  = G4ThreeVector(0*cm, 0*cm, -(15*mm+38*gap));
  new G4PVPlacement(0, lead1, leadLog1, "LEAD1", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead2, leadLog2, "LEAD2", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead3, leadLog3, "LEAD3", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead4, leadLog4, "LEAD4", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead5, leadLog5, "LEAD5", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead6, leadLog6, "LEAD6", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead7, leadLog7, "LEAD7", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead8, leadLog8, "LEAD8", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead9, leadLog9, "LEAD9", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead10, leadLog10, "LEAD10", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead11, leadLog11, "LEAD11", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead12, leadLog12, "LEAD12", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead13, leadLog13, "LEAD13", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead14, leadLog14, "LEAD14", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead15, leadLog15, "LEAD15", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead16, leadLog16, "LEAD16", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead17, leadLog17, "LEAD17", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead18, leadLog18, "LEAD18", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead19, leadLog19, "LEAD19", worldLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, lead20, leadLog20, "LEAD20", worldLV, false, 0, fCheckOverlaps);

  //Lead Glass
  G4Box* leadGlass = new G4Box("LeadGlass", 15*cm, 15*cm, 10*cm);
  G4LogicalVolume* leadglassLog1 = new G4LogicalVolume(leadGlass, leadglass, "LeadGlasslog1");
  G4ThreeVector leadglass1 = G4ThreeVector(0*cm, 0*cm, -610*mm);
  new G4PVPlacement(0, leadglass1, leadglassLog1, "LeadGlass1", worldLV, false, 0, fCheckOverlaps);


  // Return the physical World
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors
  B4cDetectorSD* Scint1 = new B4cDetectorSD("SCINT1SD", "Scint1HitsCollection");
  SetSensitiveDetector("Scintlog1", Scint1);

  B4cDetectorSD* Scint2 = new B4cDetectorSD("SCINT2SD", "Scint2HitsCollection");
  SetSensitiveDetector("Scintlog2", Scint2);

  B4cDetectorSD* Scint3 = new B4cDetectorSD("SCINT3SD", "Scint3HitsCollection");
  SetSensitiveDetector("Scintlog3", Scint3);

  B4cDetectorSD* Scint4 = new B4cDetectorSD("SCINT4SD", "Scint4HitsCollection");
  SetSensitiveDetector("Scintlog4", Scint4);

  B4cDetectorSD* Scint5 = new B4cDetectorSD("SCINT5SD", "Scint5HitsCollection");
  SetSensitiveDetector("Scintlog5", Scint5);

  B4cDetectorSD* Scint6 = new B4cDetectorSD("SCINT6SD", "Scint6HitsCollection");
  SetSensitiveDetector("Scintlog6", Scint6);

  B4cDetectorSD* Scint7 = new B4cDetectorSD("SCINT7SD", "Scint7HitsCollection");
  SetSensitiveDetector("Scintlog7", Scint7);

  B4cDetectorSD* Scint8 = new B4cDetectorSD("SCINT8SD", "Scint8HitsCollection");
  SetSensitiveDetector("Scintlog8", Scint8);

  B4cDetectorSD* Scint9 = new B4cDetectorSD("SCINT9SD", "Scint9HitsCollection");
  SetSensitiveDetector("Scintlog9", Scint9);

  B4cDetectorSD* Scint10 = new B4cDetectorSD("SCINT10SD", "Scint10HitsCollection");
  SetSensitiveDetector("Scintlog10", Scint10);

  B4cDetectorSD* Scint11 = new B4cDetectorSD("SCINT11SD", "Scint11HitsCollection");
  SetSensitiveDetector("Scintlog11", Scint11);

  B4cDetectorSD* Scint12 = new B4cDetectorSD("SCINT12SD", "Scint12HitsCollection");
  SetSensitiveDetector("Scintlog12", Scint12);

  B4cDetectorSD* Scint13 = new B4cDetectorSD("SCINT13SD", "Scint13HitsCollection");
  SetSensitiveDetector("Scintlog13", Scint13);

  B4cDetectorSD* Scint14 = new B4cDetectorSD("SCINT14SD", "Scint14HitsCollection");
  SetSensitiveDetector("Scintlog14", Scint14);

  B4cDetectorSD* Scint15 = new B4cDetectorSD("SCINT15SD", "Scint15HitsCollection");
  SetSensitiveDetector("Scintlog15", Scint15);

  B4cDetectorSD* Scint16 = new B4cDetectorSD("SCINT16SD", "Scint16HitsCollection");
  SetSensitiveDetector("Scintlog16", Scint16);

  B4cDetectorSD* Scint17 = new B4cDetectorSD("SCINT17SD", "Scint17HitsCollection");
  SetSensitiveDetector("Scintlog17", Scint17);

  B4cDetectorSD* Scint18 = new B4cDetectorSD("SCINT18SD", "Scint18HitsCollection");
  SetSensitiveDetector("Scintlog18", Scint18);

  B4cDetectorSD* Scint19 = new B4cDetectorSD("SCINT19SD", "Scint19HitsCollection");
  SetSensitiveDetector("Scintlog19", Scint19);

  B4cDetectorSD* Scint20 = new B4cDetectorSD("SCINT20SD", "Scint20HitsCollection");
  SetSensitiveDetector("Scintlog20", Scint20);

  // B4cDetectorSD* Test1 = new B4cDetectorSD("TEST1SD", "Test1HitsCollection");
  // SetSensitiveDetector("Testlog1", Test1);

  // B4cDetectorSD* Test2 = new B4cDetectorSD("TEST2SD", "Test2HitsCollection");
  // SetSensitiveDetector("Testlog2", Test2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

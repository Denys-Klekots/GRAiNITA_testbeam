#include "GRAiNTIADetectorConstruction.hh"

#include <G4SystemOfUnits.hh>

#include <G4NistManager.hh>
#include <G4Element.hh>
#include <G4Material.hh>

#include <G4Box.hh>

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>

#include "GRAiNTIAScintillatorSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIADetectorConstruction::GRAiNTIADetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIADetectorConstruction::~GRAiNTIADetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* GRAiNTIADetectorConstruction::Construct()
{

    //////////////////////////
    // materials
    //////////////////////////

    G4NistManager* manager = G4NistManager::Instance();

    // LHC vacuum
    G4Element* elN = new G4Element("Nitrogen", "N", 7.0, 14.01*g/mole);
    G4Element* elO = new G4Element("Oxygen", "O", 8.0, 16.00*g/mole);
    G4Material* vacuum = new G4Material("Vacuum", 1.164e-32*g/cm3, 2, kStateGas);
    vacuum->AddElement(elN, 70.0*perCent);
    vacuum->AddElement(elO, 30.0*perCent); 


    // ZnW04
    G4double ZnW04_denc = 4.53*g/cm3;
    G4Element *elZn = new G4Element("Zinc", "Zn", 30, 65.38*g/mole);
    G4Element *elW  = new G4Element("Tungsten", "W", 74, 183.84*g/mole);
    G4Material* ZnWO4 = new G4Material("ZnWO4", ZnW04_denc, 3, kStateSolid);
    ZnWO4->AddElement(elZn, 1);
    ZnWO4->AddElement(elW,  1);
    ZnWO4->AddElement(elO,  4);
    
    //water
    G4Material* water = manager->FindOrBuildMaterial("G4_WATER");

    //heavy liquid
    G4double heavLiq_denc = 1.1872*g/cm3;
    G4Element *elNa = new G4Element("Sodium", "Na", 11, 22.989768*g/mole);
    G4Material *heavLiq = new G4Material("Heavy Liquid", heavLiq_denc, 4, kStateLiquid);
    heavLiq->AddMaterial(water, 25*perCent);
    heavLiq->AddElement(elW, 56*perCent);
    heavLiq->AddElement(elNa, 3*perCent);
    heavLiq->AddElement(elO, 16*perCent);


    //Scintilator mixture of ZnW04 and heavy liquid
    G4double ZnW04_frac = ZnW04_denc/(ZnW04_denc+heavLiq_denc);
    G4double heavLiq_frac = heavLiq_denc/(ZnW04_denc+heavLiq_denc);
    G4Material* scintilatorMixture = new G4Material("ScintilatorMixture", 5.72*g/cm3, 2, kStateUndefined);
    scintilatorMixture->AddMaterial(ZnWO4, ZnW04_frac);                                             
    scintilatorMixture->AddMaterial(heavLiq, heavLiq_frac); 

    G4cout<<"===========================================================" 
          << "The radiation length os the scintilatorMixture is "
          << scintilatorMixture->GetRadlen()/cm << " cm"
          << "==========================================================="
          << G4endl;

    //////////////////////////
    // world volume
    //////////////////////////

    G4double wrd_hl = 0.5 * m;
    G4VSolid *worldS = new G4Box("World_Box", wrd_hl, wrd_hl, wrd_hl);

    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, vacuum, "worldLV");

    G4VPhysicalVolume* worldPV = new G4PVPlacement(nullptr,         // no rotation
                                                   G4ThreeVector(), // plasement possition at (0,0,0)
                                                   worldLV,         // logical volume
                                                   "world",         // name
                                                   nullptr,         // no mother volume for world volume
                                                   false,           // no boolean oparations
                                                   0,               // copy number
                                                   true);           // chech overlaps


    //////////////////////////
    // Scintilator volume
    //////////////////////////

    G4double sct_hxy = 87.5 * mm;
    G4double sct_hz  = 200 * mm;

    G4VSolid *sctS = new G4Box("Scintilator_box", sct_hxy, sct_hxy, sct_hz);
    G4LogicalVolume* scintilatorLV = new G4LogicalVolume(sctS, scintilatorMixture, "scintilatorLV");

    G4VPhysicalVolume* scintilatorPV = new G4PVPlacement(nullptr,         // no rotation
                                                         G4ThreeVector(), // plasement possition at (0,0,0)
                                                         scintilatorLV,   // logical volume
                                                         "scintilator",   // name
                                                         worldLV,         // no mother volume for world volume
                                                         false,           // no boolean oparations
                                                         0,               // copy number
                                                         true);           // chech overlaps


    return worldPV;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIADetectorConstruction::ConstructSDandField()
{
    GRAiNTIAScintillatorSD* scintSD = new GRAiNTIAScintillatorSD("scintSD", "scintSDHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(scintSD);
    SetSensitiveDetector("scintilatorLV", scintSD);
}
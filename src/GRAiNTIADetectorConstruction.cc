#include "GRAiNTIADetectorConstruction.hh"

#include <G4SystemOfUnits.hh>

#include <G4NistManager.hh>
#include <G4Element.hh>
#include <G4Material.hh>

#include <G4Box.hh>
#include <G4Tubs.hh>

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>

#include <G4ScoringManager.hh>
#include <G4ScoringBox.hh>
#include <G4AnalysisManager.hh>

#include "GRAiNTIAPSEnegyDeposit3D.hh"

#include <vector>

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

    G4cout << "===========================================================" 
           << "The radiation length os the scintilatorMixture is "
           << scintilatorMixture->GetRadlen()/cm << " cm"
           << "==========================================================="
           << G4endl;


    G4Element* hydrogen = manager->FindOrBuildElement(1);
    G4Element* carbon   = manager->FindOrBuildElement(6);
    G4Material* fiber_plastic = new G4Material("FigerPlastic", 1*g/cm3, 2, kStateSolid);
    fiber_plastic->AddElement(hydrogen, 1);
    fiber_plastic->AddElement(carbon, 1);


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

    G4double sct_hx = 84.0 * mm;
    G4double sct_hy = 84.0 * mm;
    G4double sct_hz  = 200 * mm;

    G4VSolid *sctS = new G4Box("Scintilator_box", sct_hx, sct_hy, sct_hz);
    G4LogicalVolume* scintilatorLV = new G4LogicalVolume(sctS, scintilatorMixture, "scintilatorLV");


    G4VPhysicalVolume* scintilatorPV = new G4PVPlacement(nullptr,        // no rotation
                                                        G4ThreeVector(), // plasement possition
                                                        scintilatorLV,   // logical volume
                                                        "scintilator",   // name
                                                        worldLV,         // a mother volume
                                                        false,           // no boolean oparations
                                                        0,               // copy number
                                                        true);           // chech overlaps

    //////////////////////////
    // Lightguide fibers
    //////////////////////////

    G4double lg_r  = 0.5 * mm;
    G4double lg_hz = 200 * mm;

    G4VSolid* lgS = new G4Tubs("LightGuideFiber",
                               0,         // inner radius
                               lg_r,      // outer radius
                               lg_hz,     // z-half length
                               0,         // starting Phi
                               360.*deg); // segment angle)


    G4LogicalVolume* lightGuideLV = new G4LogicalVolume(lgS, fiber_plastic, "lightGuideLV");


    for(int i = 0; i < 24; ++i)
    {
        for(int j = 0; j < 24; ++j)
        {
            G4ThreeVector plasement = G4ThreeVector(-80.5*mm + i*7*mm, -80.5*mm + j*7*mm, 0);

            G4VPhysicalVolume* lightGuidePV = new G4PVPlacement(nullptr,         // no rotation
                                                                plasement,       // plasement possition
                                                                lightGuideLV,    // logical volume
                                                                "lightguide",    // name
                                                                scintilatorLV,   // a mother volume
                                                                false,           // no boolean oparations
                                                                0,               // copy number
                                                                true);           // chech overlaps
        }
    }


    return worldPV;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIADetectorConstruction::ConstructSDandField()
{

    G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();

    G4VScoringMesh* mesh = new G4ScoringBox("Hardcoded_mesh");
    scManager->RegisterScoringMesh(mesh);
    
    G4double size[] = {83.5*mm, 83.5*mm, 200.0*mm};
    mesh->SetSize(size);
    
    G4int nSegment[] = {167, 167, 1};
    mesh->SetNumberOfSegments(nSegment);


    GRAiNTIAPSEnegyDeposit3D* ps = new GRAiNTIAPSEnegyDeposit3D("eDep", "MeV");
    mesh->SetPrimitiveScorer(ps);
    scManager->CloseCurrentMesh();


    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->CreateNtuple("Edep", "deposited energy");
    analysisManager->CreateNtupleFColumn(0, "xPrimPos");                   // column id = 0
    analysisManager->CreateNtupleFColumn(0, "yPrimPos");                   // column id = 1   
    analysisManager->CreateNtupleFColumn(0, "EdepVec", ps->GetEdepVec());  // column id = 2
    analysisManager->CreateNtupleIColumn(0, "EdepIdx", ps->GetIdxVec());   // column id = 3
    analysisManager->FinishNtuple(0);

}
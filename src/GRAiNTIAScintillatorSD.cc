#include "GRAiNTIAScintillatorSD.hh"

#include <G4SDManager.hh>
#include <G4Step.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

#include <G4VProcess.hh>
#include <G4RunManager.hh>

#include <cmath>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAScintillatorSD::GRAiNTIAScintillatorSD(const G4String& name, const 
                           G4String& histCollectionName)
:G4VSensitiveDetector(name)
{
    collectionName.insert(histCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAScintillatorSD::~GRAiNTIAScintillatorSD()
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAScintillatorSD::Initialize(G4HCofThisEvent* hce)
{

    fHitsCollection 
        = new GRAiNTIACalorimeterHitsCollection(SensitiveDetectorName, collectionName[0]);


    // Add this collection in hce
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection(hcID, fHitsCollection); 

    for(G4int i = 0; i < 6; ++i)
    {
        GRAiNTIACalorimeterHit* newHit = new GRAiNTIACalorimeterHit;
        newHit->SetCellNumber(i);
        fHitsCollection->insert(newHit);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4bool GRAiNTIAScintillatorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
    /////////////////////////////////////////////////
    // Accumulation of the deposited energy
    /////////////////////////////////////////////////    
    G4double edep = step->GetTotalEnergyDeposit();
    // if (edep == 0) return 0;

    const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();
    G4VPhysicalVolume* cellPV = touchable->GetVolume(0);
    G4int cellNumber = cellPV->GetCopyNo();

    GRAiNTIACalorimeterHit* hit = (*fHitsCollection)[cellNumber];
    if ( ! hit ) {
        G4cerr << "Cannot access hit " << cellNumber <<":"<< cellPV << G4endl;
        exit(1);
    }  

    hit->AddEdep(edep);



    ////////////////////////////////////////////////////
    // Writing escaped particle properties in output.
    //////////////////////////////////////////////////// 

    G4double xPos_mm = step->GetPostStepPoint()->GetPosition().getX() / mm;
    G4double yPos_mm = step->GetPostStepPoint()->GetPosition().getY() / mm;
    G4double zPos_mm = step->GetPostStepPoint()->GetPosition().getZ() / mm;

    if(step->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName() == "world" &&
        ( (fabs(xPos_mm)>69.9999) || (fabs(yPos_mm)>69.9999) || (fabs(zPos_mm)>199.9999)) )
    {
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

        G4int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        G4double escapedEnergy;
        if( step->GetTrack()->GetTrackID() > 1 && //There will be a crush without his line. The primary track has no creator process.
            step->GetTrack()->GetCreatorProcess()->GetProcessName() == "conv")
        {
            escapedEnergy = step->GetPostStepPoint()->GetTotalEnergy();
        }
        else
        {
            escapedEnergy = step->GetPostStepPoint()->GetKineticEnergy();
        }



        analysisManager->FillNtupleIColumn(0, 0, evID);
        analysisManager->FillNtupleDColumn(0, 1, escapedEnergy/MeV);
        analysisManager->FillNtupleDColumn(0, 2, xPos_mm);
        analysisManager->FillNtupleDColumn(0, 3, yPos_mm);
        analysisManager->FillNtupleDColumn(0, 4, zPos_mm);
        analysisManager->FillNtupleIColumn(0, 5, cellNumber);
        analysisManager->AddNtupleRow(0);
    }

    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAScintillatorSD::EndOfEvent(G4HCofThisEvent* hce)
{

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int nofHits = fHitsCollection->entries();

    G4int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    for(G4int i = 0; i < nofHits; ++i) 
    {
        GRAiNTIACalorimeterHit* hit = (GRAiNTIACalorimeterHit*)(*fHitsCollection)[i];
        G4double edep = hit->GetEdep();
        analysisManager->FillNtupleDColumn(1, 0, edep/MeV);
        analysisManager->FillNtupleIColumn(1, 1, i);
        analysisManager->FillNtupleIColumn(1, 2, evID);
        analysisManager->AddNtupleRow(1);   
    } 

}
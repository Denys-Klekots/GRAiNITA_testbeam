#include "GRAiNTIASteppingAction.hh"

#include <G4Step.hh>
#include <G4AnalysisManager.hh>
#include <G4RunManager.hh>

#include <G4SystemOfUnits.hh>

#include <G4VProcess.hh>

#include "GRAiNTIAEventAction.hh"// TODO: implements this in a better way

GRAiNTIASteppingAction::GRAiNTIASteppingAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIASteppingAction::~GRAiNTIASteppingAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIASteppingAction::UserSteppingAction(const G4Step* aStep)
{

    // If it is a track particle that escaping from the calorimeter volume. 
    // The 1st track is excluded as it is a primary particle and is created outside of the calorimeter
    if(aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName() == "world" &
       aStep->GetTrack()->GetTrackID() != 1 )
    {
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

        G4int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        G4double escapedEnergy;
        if(aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "conv")
        {
            escapedEnergy = aStep->GetPreStepPoint()->GetTotalEnergy();
        }
        else
        {
            escapedEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();
        }

        analysisManager->FillNtupleIColumn(0, 0, evID);
        analysisManager->FillNtupleFColumn(0, 1, escapedEnergy/ MeV);
        analysisManager->FillNtupleFColumn(0, 2, aStep->GetPreStepPoint()->GetPosition().getX() / mm);
        analysisManager->FillNtupleFColumn(0, 3, aStep->GetPreStepPoint()->GetPosition().getY() / mm);
        analysisManager->FillNtupleFColumn(0, 4, aStep->GetPreStepPoint()->GetPosition().getZ() / mm);
        analysisManager->AddNtupleRow(0);

        aStep->GetTrack()->SetTrackStatus(fStopAndKill);

    }
    else if(aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName() == "scintilator")// TODO: implements this in a better way
    {
        eventDepositedEnergy += aStep->GetTotalEnergyDeposit();
    }

}
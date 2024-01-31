
#include "GRAiNTIAEventAction.hh"

#include <G4Event.hh>
#include <G4AnalysisManager.hh>
#include <G4SystemOfUnits.hh>

G4ThreadLocal G4double eventDepositedEnergy; // TODO: implements this in a better way

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAEventAction::GRAiNTIAEventAction()
 : G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAEventAction::~GRAiNTIAEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAEventAction::BeginOfEventAction(const G4Event* event)
{
    eventDepositedEnergy = 0;// TODO: implements this in a better way
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAEventAction::EndOfEventAction(const G4Event* event)
{
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleFColumn(1, 0, eventDepositedEnergy/MeV);// TODO: implements this in a better way
  analysisManager->AddNtupleRow(1);

}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
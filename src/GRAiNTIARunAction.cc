#include "GRAiNTIARunAction.hh"

#include <G4AnalysisManager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIARunAction::GRAiNTIARunAction()
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetVerboseLevel(1);

    analysisManager->CreateNtuple("Eecs", "escaped energy");

    analysisManager->CreateNtupleIColumn(0,"evntID");    // column id = 0
    analysisManager->CreateNtupleDColumn(0,"escE");      // column id = 1
    analysisManager->CreateNtupleDColumn(0,"Xpos");      // column id = 2
    analysisManager->CreateNtupleDColumn(0,"Ypos");      // column id = 3
    analysisManager->CreateNtupleDColumn(0,"Zpos");      // column id = 4
    analysisManager->FinishNtuple(0); 

    analysisManager->CreateNtuple("Edep", "deposited energy");
    analysisManager->CreateNtupleDColumn(1,"eDep");      // column id = 0
    analysisManager->FinishNtuple(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIARunAction::~GRAiNTIARunAction()
{
    delete G4AnalysisManager::Instance(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIARunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIARunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

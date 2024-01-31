#include "GRAiNTIARunAction.hh"

#include <G4AnalysisManager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIARunAction::GRAiNTIARunAction()
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetVerboseLevel(1);

    analysisManager->CreateNtuple("Eecs", "escaped energy");

    analysisManager->CreateNtupleIColumn("evntID");    // column id = 0
    analysisManager->CreateNtupleFColumn("escE");      // column id = 1
    analysisManager->CreateNtupleFColumn("Xpos");      // column id = 2
    analysisManager->CreateNtupleFColumn("Ypos");      // column id = 3
    analysisManager->CreateNtupleFColumn("Zpos");      // column id = 4
    analysisManager->FinishNtuple(0); 

    analysisManager->CreateNtuple("Edep", "deposited energy");// TODO: implements this in a better way
    analysisManager->CreateNtupleFColumn("eDep");      // column id = 0
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

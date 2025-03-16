#include <G4RunManagerFactory.hh>

#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>
#include <G4UImanager.hh>

#include <FTFP_BERT.hh>

#include <G4ScoringManager.hh>

#include "GRAiNTIADetectorConstruction.hh"
#include "GRAiNTIAActionInitialization.hh"

int main(int argc, char **argv)
{

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);


    G4RunManager* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::MT);

    runManager->SetUserInitialization(new GRAiNTIADetectorConstruction());
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserInitialization(new GRAiNTIAActionInitialization());

    //initialize Scorin manager
    G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
    scManager->SetVerboseLevel(1);



    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialise();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if(argc == 2)
    {
        G4String macro = argv[1];
        
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);

    }
    else
    {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;

    return 0;
}
#include "GRAiNTIACommander.hh"

#include <G4UImanager.hh>

#include <string>

const int NumOfEvents = 10000;

void runComands()
{

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/control/verbose 2");
    UImanager->ApplyCommand("/control/saveHistory");
    UImanager->ApplyCommand("/run/verbose 2");

    UImanager->ApplyCommand("/run/initialize");
    
    UImanager->ApplyCommand("/gps/direction 0 0 1");

    UImanager->ApplyCommand("/score/create/boxMesh CallorimeterBox");
    UImanager->ApplyCommand("/score/mesh/boxSize 84.0 84.0 200.0 mm ");
    UImanager->ApplyCommand("/score/mesh/nBin 1 1 400");
    UImanager->ApplyCommand("/score/quantity/energyDeposit eDep MeV");
    UImanager->ApplyCommand("/score/close");


    //////////////////////////////////////
    // 25 Gev electron
    //////////////////////////////////////

    UImanager->ApplyCommand("/gps/particle e-");
    UImanager->ApplyCommand("/gps/energy 25 GeV");

    UImanager->ApplyCommand("/gps/position 0 0 -0.25 m");

    for(int evtN = 0; evtN < NumOfEvents; ++evtN)
    {

        G4String score_comand = "/score/dumpQuantityToFile CallorimeterBox eDep evnt_";
        score_comand += std::to_string(evtN) + "_electron_25GeV.txt";


        UImanager->ApplyCommand("/run/beamOn 1");
        UImanager->ApplyCommand(score_comand);

    }



}
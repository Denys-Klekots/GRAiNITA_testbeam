#include "GRAiNTIACommander.hh"

#include <G4UImanager.hh>

#include <string>

const int NumOfEvents = 3000;

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
    UImanager->ApplyCommand("/score/mesh/nBin 336 336 1");
    UImanager->ApplyCommand("/score/quantity/energyDeposit eDep MeV");
    UImanager->ApplyCommand("/score/close");


    //////////////////////////////////////
    // 1 Gev gamma
    //////////////////////////////////////

    UImanager->ApplyCommand("/gps/particle gamma");
    UImanager->ApplyCommand("/gps/energy 1 GeV");




    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            G4double xPos = i*0.001;
            G4double yPos = j*0.001;
 
            for(int evtN = 0; evtN < NumOfEvents; ++evtN)
            {
                G4String gps_comand = "/gps/position ";
                gps_comand += std::to_string(xPos) + " " + 
                              std::to_string(yPos) + " -0.25 m";

                G4String score_comand = "/score/dumpQuantityToFile CallorimeterBox eDep evnt_";
                score_comand += std::to_string(evtN) + "_gamma_1GeV_" + std::to_string(i) + ","+
                                std::to_string(j) + ".txt";


                UImanager->ApplyCommand(gps_comand);
                UImanager->ApplyCommand("/run/beamOn 1");
                UImanager->ApplyCommand(score_comand);

            }
        }    
    }



}
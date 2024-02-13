#include "GRAiNTIAActionInitialization.hh"

#include "GRAiNTIAPrimaryGeneratorAction.hh"
#include "GRAiNTIARunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAActionInitialization::GRAiNTIAActionInitialization()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAActionInitialization::~GRAiNTIAActionInitialization()
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAActionInitialization::BuildForMaster() const
{
    SetUserAction(new GRAiNTIARunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAActionInitialization::Build() const
{
    SetUserAction(new GRAiNTIARunAction);
    SetUserAction(new GRAiNTIAPrimaryGeneratorAction);
}
#include "GRAiNTIAPrimaryGeneratorAction.hh"

#include <G4Event.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAPrimaryGeneratorAction::GRAiNTIAPrimaryGeneratorAction()
{
    fParticleSource = new G4GeneralParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAPrimaryGeneratorAction::~GRAiNTIAPrimaryGeneratorAction()
{
    delete fParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleSource->GeneratePrimaryVertex(event);
}
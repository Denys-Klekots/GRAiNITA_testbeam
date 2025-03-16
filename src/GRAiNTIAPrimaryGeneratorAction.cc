#include "GRAiNTIAPrimaryGeneratorAction.hh"

#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include <G4AnalysisManager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAPrimaryGeneratorAction::GRAiNTIAPrimaryGeneratorAction()
{
    G4int nofParticles = 1;
    fParticleGun = new G4ParticleGun(nofParticles);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAPrimaryGeneratorAction::~GRAiNTIAPrimaryGeneratorAction()
{
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{

    // ----------------------------------------
    // Generate primary particle position
    // ----------------------------------------

    G4double x;
    G4double y;
    
    do
    {
        x = G4UniformRand()*4*mm;
        y = G4UniformRand()*4*mm;

    } while( (floor(y) >= ceil(x)) || ( pow(x-4, 2) + pow(y-4, 2) < 0.25*mm ) );
    
    x -= 0.5*mm;
    y -= 0.5*mm;

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleFColumn(0, x);
    analysisManager->FillNtupleFColumn(1, y);
    // the analysisManager->AddNtupleRow(0) function is invoked in GRAiNTIAPSEnegyDeposit3D::EndOfEvent


    G4ThreeVector pos(x, y, -0.25*m);
    G4ThreeVector dir(0, 0, 1);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(dir);

    fParticleGun->GeneratePrimaryVertex(event);
}
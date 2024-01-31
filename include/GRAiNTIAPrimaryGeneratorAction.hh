#ifndef __GRAiNTIAPrimaryGeneratorAction_HH__
#define __GRAiNTIAPrimaryGeneratorAction_HH__

#include <G4VUserPrimaryGeneratorAction.hh>

#include <G4GeneralParticleSource.hh>

class GRAiNTIAPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:

    GRAiNTIAPrimaryGeneratorAction();
    ~GRAiNTIAPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* );

private:

    G4GeneralParticleSource* fParticleSource;    

};


#endif //__GRAiNTIAPrimaryGeneratorAction_HH__
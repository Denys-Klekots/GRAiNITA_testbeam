#ifndef __GRAiNTIAPSEnegyDeposit3D__hh__
#define __GRAiNTIAPSEnegyDeposit3D__hh__


#include <G4PSEnergyDeposit3D.hh>
#include <G4String.hh>

#include <G4SystemOfUnits.hh>
#include <G4VSensitiveDetector.hh>

#include <vector>

class GRAiNTIAPSEnegyDeposit3D: public G4PSEnergyDeposit3D
{

public:
    GRAiNTIAPSEnegyDeposit3D(G4String name, G4int ni = 1, G4int nj = 1, G4int nk = 1,
                             G4int depi = 2, G4int depj = 1, G4int depk = 0);

    GRAiNTIAPSEnegyDeposit3D(G4String name, const G4String& unit, G4int ni = 1,
                             G4int nj = 1, G4int nk = 1, G4int depi = 2,
                             G4int depj = 1, G4int depk = 0);
  
    ~GRAiNTIAPSEnegyDeposit3D();

    void EndOfEvent(G4HCofThisEvent*);

    std::vector<G4float>& GetEdepVec() {return fEdepVec;};
    std::vector<G4int>& GetIdxVec() {return fIdxVec;};

protected:
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;

private:

    std::vector<G4float> fEdepVec;
    std::vector<G4int> fIdxVec;

};


#endif //__GRAiNTIAPSEnegyDeposit3D__hh__
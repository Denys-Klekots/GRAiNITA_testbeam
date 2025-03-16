#include "GRAiNTIAPSEnegyDeposit3D.hh"

#include <G4SDManager.hh>
#include <G4TransportationManager.hh>
#include <G4Navigator.hh>

#include <G4AnalysisManager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAPSEnegyDeposit3D::GRAiNTIAPSEnegyDeposit3D(G4String name, G4int ni, G4int nj, G4int nk,
                                                   G4int depi, G4int depj, G4int depk)
:G4PSEnergyDeposit3D(name, ni, nj, nk, depi, depj, depk)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


GRAiNTIAPSEnegyDeposit3D::GRAiNTIAPSEnegyDeposit3D(G4String name, const G4String& unit, G4int ni,
                                                   G4int nj, G4int nk, G4int depi,
                                                   G4int depj, G4int depk)
:G4PSEnergyDeposit3D(name, unit, ni, nj, nk, depi, depj, depk)
{  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIAPSEnegyDeposit3D::~GRAiNTIAPSEnegyDeposit3D()
{  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIAPSEnegyDeposit3D::EndOfEvent(G4HCofThisEvent* hce)
{

    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(GetName());
    G4THitsMap<G4double>* hm = static_cast<G4THitsMap<G4double>*>(hce->GetHC(hcID));

    G4double eDep = 0;

    fEdepVec.clear();
    fIdxVec.clear();

    for(auto it = hm->begin(); it != hm->end(); it++)
    {
        fEdepVec.push_back(*(it->second));
        fIdxVec.push_back(it->first);
    }


    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->AddNtupleRow(0);
    

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool GRAiNTIAPSEnegyDeposit3D::ProcessHits(G4Step* aStep, G4TouchableHistory* th)
{

    G4Navigator* massNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();

    // this approach each time create navTH with a "new" operator,
    // probably it is not the optimal way to do this, but it's a way to get to
    // the volume of the "mass" wodls, as in this function sStep is in parallel world
    // consider improving
    G4TouchableHistory* navTH = massNavigator->CreateTouchableHistory(); // returns copy of touchable history in navigator
    G4VPhysicalVolume* massVolume = navTH->GetVolume();
    delete navTH;

    if(massVolume->GetLogicalVolume()->GetName() == "lightGuideLV")
    {
        return true;
        // Juat skip, not calling G4PSEnergyDeposit3D::ProcessHits
        // ans this step not going to the score
    }
    else
    {
        return G4PSEnergyDeposit3D::ProcessHits(aStep, th);
    }

}
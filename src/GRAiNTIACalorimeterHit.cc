#include "GRAiNTIACalorimeterHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<GRAiNTIACalorimeterHit>* GRAiNTIACalorimeterHitAllocator = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIACalorimeterHit::GRAiNTIACalorimeterHit():G4VHit()
{
    fCellNum = -1;
    fEdep = 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIACalorimeterHit::~GRAiNTIACalorimeterHit()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIACalorimeterHit::GRAiNTIACalorimeterHit(const GRAiNTIACalorimeterHit& right):G4VHit()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const GRAiNTIACalorimeterHit& 
GRAiNTIACalorimeterHit::operator=(const GRAiNTIACalorimeterHit& right)
{
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int GRAiNTIACalorimeterHit::operator==(const GRAiNTIACalorimeterHit&) const
{
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

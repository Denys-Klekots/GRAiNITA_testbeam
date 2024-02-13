#ifndef __GRAiNTIACalorimeterHit__HH__
#define __GRAiNTIACalorimeterHit__HH__

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>

class GRAiNTIACalorimeterHit: public G4VHit
{
public:

    GRAiNTIACalorimeterHit();
    virtual ~GRAiNTIACalorimeterHit();
    GRAiNTIACalorimeterHit(const GRAiNTIACalorimeterHit &right);
    const GRAiNTIACalorimeterHit& operator=(const GRAiNTIACalorimeterHit& right);
    int operator==(const GRAiNTIACalorimeterHit& ) const;

    inline void* operator new(size_t);
    inline void operator delete(void* hit);

    void SetCellNumber(G4int aCellNumber){fCellNum = aCellNumber;};
    void AddEdep(G4double aEdep){fEdep += aEdep;};

    G4int GetCellNumber() const {return fCellNum;};
    G4double GetEdep() const {return fEdep;};


private:

    G4int fCellNum;
    G4double fEdep;

};

typedef G4THitsCollection<GRAiNTIACalorimeterHit> GRAiNTIACalorimeterHitsCollection;

extern G4ThreadLocal G4Allocator<GRAiNTIACalorimeterHit>* GRAiNTIACalorimeterHitAllocator;

inline void* GRAiNTIACalorimeterHit::operator new(size_t)
{
    if(!GRAiNTIACalorimeterHitAllocator)
        GRAiNTIACalorimeterHitAllocator = new G4Allocator<GRAiNTIACalorimeterHit>;
    return (void*)GRAiNTIACalorimeterHitAllocator->MallocSingle();
}

inline void GRAiNTIACalorimeterHit::operator delete(void* hit)
{
    GRAiNTIACalorimeterHitAllocator->FreeSingle( (GRAiNTIACalorimeterHit*)hit );
}



#endif //GRAiNTIACalorimeterHit
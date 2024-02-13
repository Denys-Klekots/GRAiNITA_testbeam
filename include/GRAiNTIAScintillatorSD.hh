#ifndef __GRAiNTIAScintillatorSD_HH__
#define __GRAiNTIAScintillatorSD_HH__

#include <G4VSensitiveDetector.hh>

#include "GRAiNTIACalorimeterHit.hh"

class GRAiNTIAScintillatorSD: public G4VSensitiveDetector
{
public:

    GRAiNTIAScintillatorSD(const G4String& name, const 
                           G4String& histCollectionName);
    virtual ~GRAiNTIAScintillatorSD();

    virtual void   Initialize(G4HCofThisEvent* hce);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hce);
    
private:
  
    GRAiNTIACalorimeterHitsCollection* fHitsCollection;
    
};

#endif //__GRAiNTIAScintillatorSD_HH__
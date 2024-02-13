#ifndef __GRAiNTIADetectorConstruction_HH__
#define __GRAiNTIADetectorConstruction_HH__

#include <G4VUserDetectorConstruction.hh>

class GRAiNTIADetectorConstruction: public G4VUserDetectorConstruction
{
public:

    GRAiNTIADetectorConstruction();
    ~GRAiNTIADetectorConstruction();

    G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

private:

};

#endif //__GRAiNTIADetectorConstruction_HH__
#ifndef __GRAiNTIARunAction_HH__
#define __GRAiNTIARunAction_HH__

#include <G4UserRunAction.hh>

class GRAiNTIARunAction: public G4UserRunAction
{
public: 

    GRAiNTIARunAction();
    virtual ~GRAiNTIARunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

};

#endif //__GRAiNTIARunAction_HH__
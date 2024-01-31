#ifndef __GRAiNTIAActionInitialization_HH__
#define __GRAiNTIAActionInitialization_HH__

#include <G4VUserActionInitialization.hh>

class GRAiNTIAActionInitialization: public G4VUserActionInitialization
{
public:

    GRAiNTIAActionInitialization();
    ~GRAiNTIAActionInitialization();

    void BuildForMaster() const override;
    void Build() const override;
};



#endif //__GRAiNTIAActionInitialization_HH__
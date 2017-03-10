// $Id: B4cActionInitialization.hh 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file B4cActionInitialization.hh
/// \brief Definition of the B4cActionInitialization class

#ifndef B4cActionInitialization_h
#define B4cActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

class B4cActionInitialization : public G4VUserActionInitialization
{
  public:
    B4cActionInitialization();
    virtual ~B4cActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    

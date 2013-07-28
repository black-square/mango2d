#ifndef IEngineParams_h__
#define IEngineParams_h__

#include "Core/Size.hpp"
#include "Gui/State.h"

struct IEngineParams
{
  virtual ~IEngineParams() {}

  virtual Size GetInitialScreenSize() const { return Size(800, 600); }
  virtual float GetUpdateStepTimeDelta() const { return 0.1f; }
  virtual const char *GetWindowTitle() const { return "mango2d engine demo"; }
  virtual Gui::State::TPtr MakeMainState() const = 0;

};

//You have to implement this function
extern IEngineParams *EngineParams();

#endif // IEngineParams_h__

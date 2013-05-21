//==============================================================================
#ifndef _CEVENT_H_
	#define _CEVENT_H_

#include <SDL.h>
#include <boost/chrono/system_clocks.hpp>

class GlobalInitHelper
{
public:
  GlobalInitHelper();
  ~GlobalInitHelper();
};

//==============================================================================
class AppBase: private GlobalInitHelper 
{
public:
  int Execute( Point screenSize );

protected:
  virtual void OnInit() {}
  virtual void OnUpdate( float deltaTime ) {}
  virtual void OnRender() const {}
  virtual void OnCleanup() {}

  virtual void OnInputFocus() {}
  virtual void OnInputBlur() {}
  virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {}
  virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {}
  virtual void OnMouseFocus() {}
  virtual void OnMouseBlur() {}
  
  virtual void OnMouseButtonDown( Point pos, Uint8 button ) {}
  virtual void OnMouseButtonUp( Point pos, Uint8 button ) {}
  virtual void OnMouseMove( Point pos ) {}

  virtual void OnMinimize() {}
  virtual void OnRestore()  {}
  virtual void OnResize(int w,int h) {}
  virtual void OnExpose() {}

private:
  typedef boost::chrono::system_clock TClock;

private:
  void MainLoop();
  bool DispatchEvent( SDL_Event *e );
  void DispatchActiveEvent( SDL_Event* e );

};

//==============================================================================

#endif
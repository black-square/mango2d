#include "stdafx.h"
#include "Main.h"

#include "App.h"

int main(int argc, char* argv[]) 
{
  App theApp;

  return theApp.Execute( point_t(755, 600) );
}
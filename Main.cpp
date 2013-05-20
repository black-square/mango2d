#include "stdafx.h"
#include "Main.h"

#include "System/App.h"

int main(int argc, char* argv[]) 
{
  App theApp;

  return theApp.Execute( Point(755, 600) );
}
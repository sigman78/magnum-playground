#include <Corrade/Corrade.h>
#include <Corrade/Utility/Directory.h>
#include <Corrade/Utility/Debug.h>
#include <iostream>

using namespace Corrade::Utility;

int main() {

  Debug() << "Sandboxed: " << Directory::isSandboxed();
  Debug() << "Executable dir: " << Directory::executableLocation();
  Debug() << "Home: " << Directory::home();
  Debug() << "Tmp: " << Directory::tmp();
  
  return 0;
}
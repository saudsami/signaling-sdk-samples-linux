#include <sstream>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <fstream> 
#include <nlohmann/json.hpp>

#include "SignalingManager.h"
#include "QuickstartUI.h"

SignalingManager signalingManager;


int main(int argc, const char * argv[]) {   
  QuickStartUI quickStartUI(signalingManager);
  quickStartUI.run();

  return 0;
}
  
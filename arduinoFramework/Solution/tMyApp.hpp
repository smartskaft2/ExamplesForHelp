#pragma once
#include "framework.hpp"

#include "Arduino.h"
#include <cstring>

namespace MrOrange
{

///////////////////////////////////////
// tMyApp application
///////////////////////////////////////
class tMyApp : public iApp {
  public:
    ~tMyApp() = default;
    tMyApp() 
    {
      std::strcpy(Text, "");
    };

    void initialize()
    {
      std::strcpy(Text, "Hello World!");
    };

    void execute()
    {
      Serial.println(Text);
    };
    
  private:
    char Text[10];
};

} // namespace MrOrange
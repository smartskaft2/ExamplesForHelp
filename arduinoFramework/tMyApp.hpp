#pragma once
#include "tMinExClasses.hpp"

#include "Arduino.h"
#include <string>

///////////////////////////////////////
// tMyApp application
///////////////////////////////////////
class tMyApp : public iMinExApplication {
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
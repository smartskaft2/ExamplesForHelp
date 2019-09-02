#pragma once

#include <cstring>

namespace MrOrange
{

///////////////////////////////////////
// Application interface    - For user define class inhertance
///////////////////////////////////////

class iApp 
{
    public:
        virtual void initialize() = 0; // pure virtual
        virtual void execute()    = 0; // pure virtual
        
        virtual ~iApp() = default; // Virtual destructor
};


///////////////////////////////////////
// Application class    - For coordinator
///////////////////////////////////////
class tApp
{
    public:
        tApp() = delete;
        ~tApp() = default;
        
        tApp(iApp* app, const char name[]) : App(app)
        {
            std::strcpy(Name, name);
        };
        
        void initialize() { App->initialize(); };
        void execute()    { App->execute();    };
        
    private:
        iApp* App;
        char Name[32]; // char[] because of low heap memory on microprocessors.
        
        // Callback frequency variables
        // ...
};


///////////////////////////////////////
// Coordinator class    - Handles apps
///////////////////////////////////////
#include "tStaticVector.hpp"
#include <functional>

#define WRAP_CONSTRUCTOR(fcn) []{ std::function<fcn>; }

template<std::size_t MaxNumApps>
class tCoordinator
{
    public:
        tCoordinator() : Applications() {};
        ~tCoordinator() = default;
    
        // Add app to array.
        void addApp(iApp* app, const char name[]) 
        {
            Applications.emplace_back(app, name);
        };
        void addApp(std::function<iApp()> app, const char name[]) 
        {
            Applications.emplace_back(app(), name);
        };
        
        // Initialize all apps
        void initializeApps()
        {
            for (auto& app : Applications) {
                app.initialize();
            }
        };
        
        // Run all apps if conditions are right
        void runApps()
        {
            for (auto& app : Applications) {
                // Frequency check
                // ...
                app.execute();
            }
        };
        
    private:
        tStaticVector<tApp, MaxNumApps> Applications;
};

} // namespace MrOrange
#pragma once
#include <memory>
#include <cstring>

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
            strcpy(Name, name);
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
class tCoordinator
{
    public:
        tCoordinator() : Applications(), NumApps(0) {};
        ~tCoordinator() = default;
    
        // Add app to array.
        void addApp(iApp* app, const char name[]) 
        {
            tApp* tmpPtr = new tApp(app, name);
            Applications[++NumApps] = tmpPtr;
            tmpPtr = nullptr;
        };
        
        // Initialize all apps
        void initializeApps()
        {
            for (auto& app : Applications) {
                app->initialize();
            }
        };
        
        // Run all apps if conditions are right
        void runApps()
        {
            for (auto& app : Applications) {
                // Frequency check
                // ...
                app->execute();
            }
        };
        
    private:
        tApp* Applications[];
        int NumApps;
};
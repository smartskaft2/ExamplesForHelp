#pragma once
#include <memory>
#include <cstring>

///////////////////////////////////////
// Application interface    - For user define class inhertance
///////////////////////////////////////

class iMinExApplication 
{
    public:
        virtual void initialize() = 0; // pure virtual
        virtual void execute()    = 0; // pure virtual
        
        ~iMinExApplication() = default; // Virtual destructor
};


///////////////////////////////////////
// Application class    - For coordinator
///////////////////////////////////////
class tMinExApplication
{
    public:
        tMinExApplication() = delete;
        ~tMinExApplication() = default;
        
        tMinExApplication(iMinExApplication* app, const char name[]) : App(app)
        {
            strcpy(Name, name);
        };
        
        void initialize() { App->initialize(); };
        void execute()    { App->execute();    };
        
    private:
        iMinExApplication* App;
        char Name[32]; // char[] because of low heap memory on microprocessors.
        
        // Callback frequency variables
        // ...
};


///////////////////////////////////////
// Coordinator class    - Handles apps
///////////////////////////////////////
class tMinExCoordinator
{
    public:
        tMinExCoordinator() : Applications(), NumApps(0) {};
        ~tMinExCoordinator() = default;
    
        // Add app to array.
        void addApp(iMinExApplication* app, const char name[]) 
        {
            tMinExApplication* tmpPtr = new tMinExApplication(app, name);
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
        tMinExApplication* Applications[];
        int NumApps;
};
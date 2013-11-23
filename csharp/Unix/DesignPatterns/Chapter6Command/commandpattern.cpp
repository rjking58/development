#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
// #include <list>
#include <string>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;

class Light
{
public:
    void On()
    {
        cout << "light command received: ON" << endl;
    }
    void Off()
    {
        cout << "light command received: OFF" << endl;
    }
};

class GarageDoor
{
public:
    void up()
    {
        cout << "Garage Door is OPEN" << endl;
    }
    void down()
    {
        cout << "Garage Door is CLOSED" << endl;
    }
    void stop()
    {
        cout << "Garage Door is STOPPED" << endl;
    }
    void lightOn()
    {
        cout << "Garage Door light is ON" << endl;

    }
    void lightOff()
    {
        cout << "Garage Door light is OFF" << endl;
    }
};

class Command
{
public:
    virtual ~Command()
    {
    }
    virtual void execute() = 0;
};

class LightOnCommand : public Command
{
private:
    Light *m_light;
public:
    LightOnCommand(Light *light)
        :   m_light(light)
    {
    }
    virtual void execute() 
    {
        m_light->On();
    }
};

class GarageDoorOpen : public Command
{
private:
    GarageDoor *m_garage_door;
public:
    GarageDoorOpen(GarageDoor *garage_door)
        :   m_garage_door(garage_door)
    {
    }
    virtual void execute() 
    {
        m_garage_door->up();
    }
};

class SimpleRemoteControl
{
public:
    Command *m_slot;
    void setCommand(Command *command)
    {
        m_slot = command;
    }
    void ButtonWasPressed()
    {
        m_slot->execute();
    }
};

void TestCommandPattern()
{
    SimpleRemoteControl *remote         = new SimpleRemoteControl();
    Light               *light          = new Light();
    LightOnCommand      *lightOn        = new LightOnCommand(light);
    GarageDoor          *garageDoor     = new GarageDoor();
    GarageDoorOpen      *garageDoorOpen = new GarageDoorOpen(garageDoor);

    remote->setCommand(lightOn);
    remote->ButtonWasPressed();
    delete light;
    delete lightOn;

    remote->setCommand(garageDoorOpen);
    remote->ButtonWasPressed();
    delete garageDoor;
    delete garageDoorOpen;

    delete remote;
}

void main()
{
    TestCommandPattern();
    _CrtDumpMemoryLeaks();
}


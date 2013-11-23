// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#include <iostream>

#include <list>
#include <algorithm>

using namespace std;

// basic observer pattern..

// abstract interface.. Observer side.
class Observer
{
public:
    virtual ~Observer() {}
    virtual void update(float temp, float humidity, float pressure) = 0;
};

// abstract interface.. Subject Side
class Subject
{
public:
    virtual ~Subject(){}
    virtual void registerObserver(Observer *o) = 0;
    virtual void removeObserver(Observer *o) = 0;
    virtual void notifyObservers() = 0;
};

// abstract interface.. a Display element.
class DisplayElement
{
public:
    virtual ~DisplayElement() {}
    virtual void display() = 0;
};


class WeatherData : public Subject
{
private:
    list<Observer *>    observers;
    float               m_temperature;
    float               m_humidity;
    float               m_pressure;

public:
    virtual void registerObserver(Observer *o) 
    {
        list<Observer *>::iterator result;

        result = find(  observers.begin(),
                        observers.end(),
                        o);
        if (result == observers.end())
        {
            // not found.. 
            observers.push_back(o);
        }
        else
        {
            cout << "oops.. already added this observer!\n";
        }

        cout << "WeatherData::registerObserver>> observers.size()[" << observers.size() << "]\n";

    }
    virtual void removeObserver(Observer *o) 
    {
        list<Observer *>::iterator result;

        result = find(  observers.begin(),
                        observers.end(),
                        o);
        if (result != observers.end())
        {
            observers.erase(result);
        }
        else
        {
            cout << "oops!  Observer not found!!\n";
        }
        cout << "WeatherData::removeObserver>> observers.size()[" << observers.size() << "]\n";
    }
    virtual void notifyObservers() 
    {
        list<Observer *>::iterator current = observers.begin();
        list<Observer *>::iterator last    = observers.end();

        while (current != last)
        {
            (*current)->update(m_temperature,m_humidity,m_pressure);
            current++;
        }
    }
    void measurementsChanged()
    {
        notifyObservers();
    }

    void setMeasurements(float temperature,
                         float humidity,
                         float pressure)
    {
        m_temperature = temperature;
        m_humidity = humidity;
        m_pressure = pressure;
        //start notification..
        measurementsChanged();
    }
};



class CurrentPressureDisplay : public DisplayElement, Observer
{
private:
    float       m_pressure;
    Subject     *m_weatherData;

public:
    
    
    CurrentPressureDisplay(Subject * weatherData)
        :   m_weatherData(weatherData)
    {
        // we WANT to be observed
        m_weatherData->registerObserver(this);
    }
    virtual ~CurrentPressureDisplay()
    {
        m_weatherData->removeObserver(this);
    }

    virtual void display() 
    {
        cout << "Current Pressure: " << m_pressure << "millis\n";
    }
    virtual void update(float temp, float humidity, float pressure) 
    {
        m_pressure = pressure;
        display();
    }
};

class CurrentConditionsDisplay : public DisplayElement, Observer
{
private:
    float       m_temperature;
    float       m_humidity;
    // retained so we can de-register ourselves as an observer.
    Subject     *m_weatherData;
public:

    CurrentConditionsDisplay(Subject * weatherData)
        :   m_weatherData(weatherData)
    {
        // we WANT to be observed
        m_weatherData->registerObserver(this);
    }
    virtual ~CurrentConditionsDisplay()
    {
        m_weatherData->removeObserver(this);
    }
    virtual void display() 
    {
        cout << "Current conditions: " << m_temperature << "F degrees and " << m_humidity << "% humidity\n";
    }
    virtual void update(float temperature, 
                        float humidity, 
                        float pressure) 
    {
        m_temperature = temperature;
        m_humidity = humidity;
        display();
    }
};

int main()
{
    // TODO: Please replace the sample code below with your own.

    WeatherData wd;
    CurrentConditionsDisplay *cd = new CurrentConditionsDisplay(&wd);
    CurrentPressureDisplay   *cp = new CurrentPressureDisplay(&wd);

    wd.setMeasurements(80,65,30.4f);
    wd.setMeasurements(82,70,29.2f);
    wd.setMeasurements(78,90,29.2f);

    delete cd;
    delete cp;


	return 0;
}



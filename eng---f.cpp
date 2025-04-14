#include <iostream>
using namespace std;

const double PANEL_POWER = 300;
const double PANEL_AREA = 1.6;
const double PANEL_COST = 100;
const double BATTERY_CAPACITY = 5;
const double BATTERY_COST = 150;
const double INVERTER_COST_PER_KW = 100;

class SolarPanels {
private:
    int panels ;  
public:
    void calculate(double consumption, double sunHours, double area) {
    	
        double DailyEnergyFor_1 = (PANEL_POWER * sunHours) / 1000.0;
        
        panels = consumption/DailyEnergyFor_1;
        
        int maxPanels = area / PANEL_AREA;
        if (panels > maxPanels) panels = maxPanels;
    }
    
    int getPanels() const { return panels; }
    double getCost() const { return panels * PANEL_COST; }
    double getUsedArea() const { return panels * PANEL_AREA; }
};

class Batteries {
private:
    int batteries;
public:
    void calculate(double consumption) {
        batteries = consumption / BATTERY_CAPACITY;
    }
       int getBatteries() const { return batteries; }
    double getCost() const { return batteries * BATTERY_COST; }
};

class Inverter {
private:
    double size ;
    double requiredSize;
public:
    void calculate(double peakLoad) {
        requiredSize = (peakLoad * 1.2) / 1000.0;
       size = (requiredSize <= 5.0) ? 5.0 :
              (requiredSize <= 7.5) ? 7.5 :
               10.0;
    }
    
    double getSize() const { return size; }
    double getCost() const { return size * INVERTER_COST_PER_KW; }
};

int main() {
    double consumption, sunHours, area, peakLoad;
    
    cout << "Enter daily consumption (kWh): "; cin >> consumption;
    cout << "Enter peak sun hours: "; cin >> sunHours;
    cout << "Enter available area (m²): "; cin >> area;
    cout << "Enter peak load (Watts): "; cin >> peakLoad;
    
    SolarPanels panels;
    Batteries batteries;
    Inverter inverter;
    
    panels.calculate(consumption, sunHours, area);
    batteries.calculate(consumption);
    inverter.calculate(peakLoad);
    
    double totalCost = panels.getCost() + batteries.getCost() + inverter.getCost();
    
    cout << "\n==== Solar System Estimate ====\n";
    cout << "Solar panels needed: " << panels.getPanels() << "\n";
    cout << "Batteries needed: " << batteries.getBatteries() << "\n";
    cout << "Inverter size: " << inverter.getSize() << " kW\n";
    cout << "Area used: " << panels.getUsedArea() << " m²\n";
    cout << "Total cost: " << totalCost << " $\n";
     cout << "Total cost: " << totalCost*1.5 << ",000 DIQ\n";
    return 0;
}

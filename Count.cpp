//Made to count the number of seats within a region given a per district population and population devation
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int regionPop, districtPop;
    double devation;
    cout << "What is your District Population and Devation? ";
    cin >> districtPop >> devation;
    devation /= 200;
    
    while (1)
    {
        cout << "What is your Region Population? ";
        cin >> regionPop;
        if (regionPop < 0) break;
        double ndistricts = regionPop * 1.0 / districtPop;
        double bound = districtPop * round(ndistricts) * devation;
        int diff = regionPop - districtPop * round(ndistricts);
        if (abs(diff) < bound)
            cout << "It is in bounds with " << round(ndistricts) << " districts and an average devation of " << diff / round(ndistricts) << '\n';
        else
            cout << "It is not in bounds, lower: " << floor(ndistricts) << " ,diff: " << regionPop - districtPop * floor(ndistricts) <<
            " | upper: " << ceil(ndistricts) << " ,diff: " << regionPop - districtPop * ceil(ndistricts) << '\n';
    }

    return 0;
}
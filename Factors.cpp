#include <iostream>  //Final as of 1/27/23
#include <iomanip>
#include <cmath>
#include <forward_list>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    ofstream fout ("Output.txt");
    fout << left << "Nth_term Euler_Phi Factors (not including one or itself)\n";
    steady_clock::time_point t1 = steady_clock::now();

    for (int n {2}; n <= 10000; n++)
    {
        int size{2};
        double x{sqrt(n)};
        forward_list<int> flist;
        if (x == static_cast<int>(x)) 
        {
            flist.push_front(x);
            size++;
        }
        if (n % 2 == 0)
        {
            for (int i {2}; i < x; i++)
            {
                if (n % i == 0) 
                {
                flist.push_front(i);
                flist.push_front(n/i);
                size += 2;
                }
                
            }
        }
        else
        {
            for (int i {3}; i < x; i += 2)
            {
                if (n % i == 0) 
                {
                flist.push_front(i);
                flist.push_front(n/i);
                size += 2;
                }
            }
        }

        flist.sort();
        fout << setw(9) << n << setw(9) << size;
        for (auto it = flist.cbegin(); it != flist.cend(); it++) fout << ' ' << *it;
        fout << '\n';
    }

    steady_clock::time_point t2 = steady_clock::now();
    fout.close();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "It took " << time_span.count() << " seconds";

    return 0;
}
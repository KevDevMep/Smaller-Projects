#include<iostream>
#include<fstream>
#include<cmath>
#include<queue>
#include<vector>
#include<map>
using namespace std;

struct State
{
    string name{0};
    int pop{0};
    int seats{1};
    int priority{0};
};
auto my_comp = [](const State& s1, const State& s2) {return s1.priority < s2.priority;};
int geometricMean(const int pop, const int seat) {return (pop / sqrt(seat * (seat + 1)));}

int main()
{
    int avgPop{0}, nseats{0};
    cout << "how many seats? ";
    cin >> nseats;
    priority_queue<State,vector<State>,decltype(my_comp)> pq{};
    map<string, State> map{};
    ifstream fin("Apportionment_Data.txt");
    if (!fin)
    {
        cerr << "Input file not found";
        return 1;
    }
    while(!fin.eof())
    {
        State s{};
        fin >> s.name >> s.pop;
        s.priority = geometricMean(s.pop, s.seats);
        map[s.name] = s;
        pq.push(s);
    }
    fin.close();

    ofstream log("log.txt");
    string prev{}, waiting{};
    for (int i{51}; i <= nseats; i++)
    {
        if (waiting != "")
        {
            pq.push(map[waiting]);
            waiting = "";
        }
        prev = pq.top().name;
        map[prev].seats++;
        map[prev].priority = geometricMean(map[prev].pop, map[prev].seats);
        log << "The " << i << "th seat is given to " << prev << ", it's " << map[prev].seats << "th seat\n";
        pq.pop();
        waiting = prev;
    }
    pq.push(map[waiting]);
    log.close();

    ofstream fout("output.txt");
    for (auto it = map.begin(); it != map.end(); it++)
    {
        fout << it->first << " has " << it->second.seats << " seats with an pop/seat of " << it->second.pop/it->second.seats << '\n';
        avgPop += it->second.pop;
    }
    avgPop /= nseats;
    fout << "The Average District Population is " << avgPop << '\n';

    fout << "| Priority | Name |\n";
    while(!pq.empty())
    {
        fout << (51 - pq.size()) << " " << pq.top().name << '\n';
        pq.pop();
    }
    fout.close();

    return 0;
}
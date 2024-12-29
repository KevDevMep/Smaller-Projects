#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int PID = -1;
    int arrivalTime = -1;
    int priority = -1;
    int executionTime = -1;
    int startTime = -1;
    int completionTime = -1;
    int turnaroundTime = -1; // Completion - arrival    
};

void FCFS_np(const vector<Process>& v) {
    int t = 0, i = 1;
    double total = 0;
    queue<Process> q;
    for (const Process& p : v) q.push(p);
    Process pc;
    cout << "| PID | Start Time | Comp Time | TAT | Order |\n";
    while (!q.empty()) {
        pc = q.front();
        if (t >= pc.arrivalTime) {
            pc.startTime = t;
            t += pc.executionTime;
            pc.completionTime = t;
            pc.turnaroundTime = t - pc.arrivalTime;
            total += pc.turnaroundTime;
            q.pop();
            cout << left << " " << setw(6) << pc.PID << setw(13) << pc.startTime << setw(12) << pc.completionTime << setw(6) << pc.turnaroundTime << i << '\n';
            i++;
        }
        else t++;
    }
    cout << "Avg TAT: " << total/v.size() << '\n';
}

auto comp1 = [](const Process& p1, const Process& p2) {return p1.executionTime > p2.executionTime;};
auto comp0 = [](const Process& p1, const Process& p2) {return p1.arrivalTime > p2.arrivalTime;};
void SJF_np(vector<Process>& v) {
    vector<Process> vA;
    for (const Process& p : v) vA.push_back(p);
    sort(vA.begin(),vA.end(),comp0);
    int t = vA.back().arrivalTime, i = 1;
    double total = 0;
    vector<Process> vE;
    Process pc;
    cout << "| PID | Start Time | Comp Time | TAT | Order |\n";
    while (!vE.empty() || !vA.empty()) {
        while (t >= vA.back().arrivalTime && !vA.empty()) {
            vE.push_back(vA.back());
            sort(vE.begin(),vE.end(), comp1);
            vA.pop_back();
        }
        pc = vE.back();
        if (!vE.empty()) {
            pc.startTime = t;
            t += pc.executionTime;
            pc.completionTime = t;
            pc.turnaroundTime = t - pc.arrivalTime;
            total += pc.turnaroundTime;
            vE.pop_back();
            cout << left << " " << setw(6) << pc.PID << setw(13) << pc.startTime << setw(12) << pc.completionTime << setw(6) << pc.turnaroundTime << i << '\n';
            i++;
        }
        else t++;
    }
    cout << "Avg TAT: " << total/v.size() << '\n';
}

auto comp2 = [](Process& p1, Process& p2) {return p1.priority >= p2.priority;};
void priority(vector<Process>& v) {
    vector<Process> vA;
    for (const Process& p : v) vA.push_back(p);
    sort(vA.begin(),vA.end(),comp0);
    int t = vA.back().arrivalTime, i = 1, prev = -1;
    double total = 0;
    vector<Process> vc;
    cout << "| PID | Start Time | Comp Time | TAT | Order |\n";
    while (!vc.empty() || !vA.empty()) {
        while (t >= vA.back().arrivalTime && !vA.empty()) {
            vc.push_back(vA.back());
            sort(vc.begin(),vc.end(), comp2);
            vA.pop_back();
        }
        vc.back().executionTime--;
        if (prev != -1 && vc.back().PID == prev) {            
            if (vc.back().executionTime < 1) {
                vc.back().completionTime = t;
                vc.back().turnaroundTime = t - vc.back().arrivalTime;
                total += vc.back().turnaroundTime;
                cout << left << " " << setw(6) << vc.back().PID << setw(13) << vc.back().startTime << setw(12) << vc.back().completionTime << setw(6) << vc.back().turnaroundTime << i << '\n';
                prev = vc.back().PID;
                vc.pop_back();
                i++;
            }
        }
        else prev = vc.back().PID;
        if (vc.back().startTime == -1)vc.back().startTime = t;
        t++;        
    }
    cout << "Avg TAT: " << total/v.size() << '\n';

}

int main() {
    vector<Process> v = {{1,2,3,3},{2,2,2,4},{3,3,1,1},{4,5,3,2}};
    
    cout << "FCFS:\n";
    FCFS_np(v);

    cout << "SJF:\n";
    SJF_np(v);

    cout << "Priorty:\n";
    priority(v);

    return 0;
}
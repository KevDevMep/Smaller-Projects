#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
using namespace std;

struct Job {
    int processID{-1};
    bool status{0}; // 1 = Run, 0 = Wait
    int partitionID{-1};
    int size{-1};
};

struct Partition {
    int partitionID{-1};
    bool used{0}; // 1 = used, 0 = not used
    int assigned{-1};
    int size = {-1};
};

void firstFit(vector<Job>& joblist, vector<Partition>& partitionlist) {
    for (Job& j : joblist) {
        for (Partition& p : partitionlist) {
            if (j.size <= p.size && !p.used) {
                j.status = 1;
                j.partitionID = p.partitionID;
                p.used = 1;
                p.assigned = j.processID;
                break;
            }
        }
    }
}

void nextFit(vector<Job>& joblist, vector<Partition>& partitionlist, int nPartitions) {
    int i = 0;
    for (Job& j : joblist) {
        for (i; i < nPartitions; i++) {
            if (j.size <= partitionlist[i].size && !partitionlist[i].used) {
                j.status = 1;
                j.partitionID = partitionlist[i].partitionID;
                partitionlist[i].used = 1;
                partitionlist[i].assigned = j.processID;
                break;
            }
        }
        if (i >= nPartitions - 1) i = 0;
    }
}

void bestFit(vector<Job>& joblist, vector<Partition>& partitionlist, int nPartitions) {
    int waste, previous;
    for (Job& j : joblist) {
        waste = INT_MAX;
        for (int i = 0; i < nPartitions; i++) {
            if (j.size <= partitionlist[i].size && !partitionlist[i].used) {
                if (waste > partitionlist[i].size - j.size) {
                    waste = partitionlist[i].size - j.size;
                    previous = i;
                }
            }
        }
        if (waste != INT_MAX) {
            j.status = 1;
            j.partitionID = partitionlist[previous].partitionID;
            partitionlist[previous].used = 1;
            partitionlist[previous].assigned = j.processID;
        }
    }
}

void worstFit(vector<Job>& joblist, vector<Partition>& partitionlist, int& nPartitions) {
    int waste, previous;
    for (Job& j : joblist) {
        waste = INT_MIN;
        for (int i = 0; i < nPartitions; i++) {
            if (j.size <= partitionlist[i].size && !partitionlist[i].used) {
                if (waste < partitionlist[i].size - j.size) {
                    waste = partitionlist[i].size - j.size;
                    previous = i;
                }
            }
        }
        if (waste != INT_MIN) {
            j.status = 1;
            j.partitionID = partitionlist[previous].partitionID;
            partitionlist[previous].used = 1;
            partitionlist[previous].assigned = j.processID;
            partitionlist[previous].size -= waste;
            Partition p = {nPartitions + 1, 0, -1, waste};
            partitionlist.push_back(p);
            nPartitions++;
        }
    }
}

void output(vector<Job>& joblist, vector<Partition>& partitionlist) {
    int totalWaste = 0;
    cout << left << "Job_ID | Part_ID | Waste | Status\n";
    for (Job j : joblist) {
        cout << setw(9) << j.processID;
        if (!j.status) cout << setw(10) << "N/A";
        else cout << setw(10) << j.partitionID;
        if (!j.status) cout << setw(8) << "N/A";
        else {
            cout << setw(8) << partitionlist[j.partitionID].size - j.size;
            totalWaste += partitionlist[j.partitionID].size - j.size;
        }
        if (!j.status) cout << setw(6) << "Wait";
        else cout << setw(8) << "Run";
        cout << '\n';
    }
    cout << "total waste = " << totalWaste << '\n';
}

int main() {
    int nPartitions, nJobs;
    cout << "How many jobs: ";
    cin >> nJobs;
    cout << "How many partition: ";
    cin >> nPartitions;

    vector<Job> joblist(nJobs);
    cout << "\nJob size:\n";
    for (int i = 0; i < nJobs; i++) {
        joblist[i].processID = i;
        cin >> joblist[i].size;
    }

    vector<Partition> partitionlist(nPartitions);
    cout << "\nPartition size:\n";
    for (int i = 0; i < nPartitions; i++) {
        partitionlist[i].partitionID = i;
        cin >> partitionlist[i].size;
    }
    cout << "\n";

    vector<Job> copyJ = joblist;
    vector<Partition> copyP = partitionlist;
    cout << "\nFirst_Fit:\n";
    firstFit(joblist, partitionlist);
    output(joblist, partitionlist);
    joblist = copyJ;
    partitionlist = copyP;
    cout << "\nNext_Fit:\n";
    nextFit(joblist, partitionlist, nPartitions);
    output(joblist, partitionlist);
    joblist = copyJ;
    partitionlist = copyP;
    cout << "\nBest_Fit:\n";
    bestFit(joblist, partitionlist, nPartitions);
    output(joblist, partitionlist);
    joblist = copyJ;
    partitionlist = copyP;
    cout << "\nWorst_Fit:\n";
    worstFit(joblist, partitionlist, nPartitions);
    output(joblist, partitionlist);

    return 0;
}
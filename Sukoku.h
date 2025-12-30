#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Sukoku
{
public:
    int grid[9][9] {};
    void loadF();
    void print() const;
    bool check() const;
    bool checkF() const;
};

void Sukoku::print() const
{
    for (int i {0}; i < 9; i++)
    {
        for (int j {0}; j < 9; j++) cout << grid[i][j] << " ";
        cout << '\n';
    } 
}
bool Sukoku::check() const
{
    for (int i {0}; i < 9; i++)
    {
        bool r[10] {0};
        bool c[10] {0};
        for (int j {0}; j < 9; j++)
        {
            if (grid[i][j] == 0);
            else if (r[ grid[i][j] ]) return 0;
            else r[ grid[i][j] ] = 1;
            if (grid[j][i] == 0);
            else if (c[ grid[j][i] ]) return 0;
            else c[ grid[j][i] ] = 1;
        }
    }
        
    for (int x {0}; x < 3; x++)
    {
        for (int y {0}; y < 3; y++)
        {
            bool s[10] {0};
            for (int i {x * 3}; i < (x + 1) * 3 ; i++)
            {
                for (int j {y * 3}; j < (y + 1) * 3; j++)
                {
                    if (grid[i][j] == 0);
                    else if (s[ grid[i][j] ]) return 0;
                    else s[ grid[i][j] ] = 1;
                }
            }   
        }
    }

        return 1;
}
bool Sukoku::checkF() const
{
    for (int i {0}; i < 9; i++)
    {
        bool r[10] {0};
        bool c[10] {0};
        for (int j {0}; j < 9; j++)
        {
            if (grid[i][j] == 0 || grid[j][i] == 0) return 0;
            if (r[ grid[i][j] ] || c[ grid[j][i] ]) return 0;
            r[ grid[i][j] ] = 1;
            c[ grid[j][i] ] = 1;
        }
    }

    for (int x {0}; x < 3; x++)
    {
        for (int y {0}; y < 3; y++)
        {
            bool s[10] {0};
            for (int i {x * 3}; i < (x + 1) * 3 ; i++)
            {
                for (int j {y * 3}; j < (y + 1) * 3; j++)
                {
                    if (grid[i][j] == 0) return 0;
                    if (s[ grid[i][j] ]) return 0;
                    s[ grid[i][j] ] = 1;
                }
            }   
        }
    }

        return 1;
    }
void Sukoku::loadF()
{
    ifstream fin("input.txt");
    if (!fin) throw "Input file not found";
    for (int i {0}; i < 9; i++)
        for (int j {0}; j < 9; j++) fin >> grid[i][j];
    fin.close();
}

class Sudoku_Solver : public Sukoku //Back Tracking + Bitsets, From LeetCode User
{
	bool Row[9][9] {};
    bool Col[9][9] {};
    bool Block[9][9] {};
    vector<pair<int, int>> uncertain {};
public:
    void set3Cond(int i, int j, int x, bool val=1)
    {
        Row[i][x] = val;
        Col[j][x] = val;
        int bidx = (i/3)*3 + j/3;
        Block[bidx][x] = val;
    }
    void setup();
    bool solve();
    bool isValid(int row, int col, int k) const;
    void solveSudoku() {setup(); solve();}
};

void Sudoku_Solver::setup()
{
    uncertain.reserve(81);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int k = grid[i][j];
            if (k == 0) {uncertain.push_back(make_pair(i, j));}
            else
            {
                int x = k%9;
                set3Cond(i, j, x);
            }
        }
    }
}
bool Sudoku_Solver::solve()
{
    if (uncertain.empty()) return 1;
    auto [i, j] = uncertain.back();
    for (int k = 1; k <= 9; k++) 
    {
        if (isValid(i, j, k)) 
        {
            grid[i][j] = k;
            uncertain.pop_back();
            int x = k%9; 
            set3Cond(i, j, x);
            if (solve()) return 1;
            grid[i][j] = 0; // trace back
            uncertain.push_back(make_pair(i, j));
            set3Cond(i, j, x, 0);
        }
    }

    return 0; 
}
bool Sudoku_Solver::isValid(int row, int col, int k) const
{
    int x = k%9; 
    return !Row[row][x] && !Col[col][x] && !Block[(row/3)*3+col/3][x];
}

#include "Sukoku.h"

int main()
{
    cout << "This is Sudoku\n";
    cout << "The Grid goes from 0 - 8 (row, column)\n";
    cout << "Numbers goes from 0 - 9\n";
    cout << "10 is for checking, 11 is for final check, 12 to solve, -1 to stop\n";
    int input{}, turns{};
    Sudoku_Solver s;
    //s.loadF();
    cout << "Your Sukoku is\n";
    s.print();
    
    while (1)
    {
        cout << "Choose a number? ";
        cin >> input;
        switch(input)
        {
            case -1: return 1;
            case 10:
            if (s.check()) 
            {
                cout << "There are no mistake\n";
                break;
            }
                cout << "There are mistakes\n";
                break;
            case 11:
            if (s.checkF()) 
            {
                cout << "You completed it in " << turns << " turns\n";
                return 0;
            }
                cout << "You have not completed it\n";
                break;
            case 12:
                s.solveSudoku();
                cout << "Your solved sukoku is\n";
                s.print();
                return 0;
            default:
                cout << "Choose a square? (row, column) ";
                pair<int,int> coords;
                cin >> coords.first >> coords.second;
                s.grid[coords.first][coords.second] = input;
                ++turns;
                cout << "Your Sudoku is now\n";
                s.print();
            break;
        }
    }

    return 0;
}   
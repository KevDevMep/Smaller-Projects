#include <iostream>
#include "point2D.h"
using namespace std;

void printMatrix (const int m[][3])
{
    for (int i {0}; i < 3; i++)
    {
        for (int j {0}; j < 3; j++) cout << m[i][j] << " ";
        cout << '\n';
    } 
}
bool check(const int m[][3])
{
    if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[0][0] != 0) return 1;
    if (m[2][0] == m[1][1] && m[1][1] == m[0][2] && m[2][0] != 0) return 1;
    for (int i {0}; i < 3; i++)
    {
        if (m[i][0] == m[i][1] && m[i][1] == m[i][2] && m[i][0] != 0 ) return 1;
        if (m[0][i] == m[1][i] && m[1][i] == m[2][i] && m[0][i] != 0) return 1;
    }
    return 0;
}
void taken (int t[][3], Point& point)
{
    while (t[point.m_x][point.m_y] != 0)
    {
        cout << point << " is taken\n";
        cout << "Choose a different square? (x,y)\n";
        cin >> point;
    }
}

int main()
{
    Point point{};
    cout << "This is Tick Tack Toe\n";
    cout << "X goes first (X = 1, O = -1)\n";
    cout << "Grid goes from 0 - 2 (x - row, y - column)\n";
    int t[3][3] {};
    
    for (int i {0}; i < 9; i++)
    {
        if (i % 2 == 0)
        {
            cout << "It is X turn\n";
            cout << "Choose a square? (x,y)\n";
            cin >> point;
            taken (t, point);
            t[point.m_x][point.m_y] = 1;
            printMatrix(t);
            if (check(t)) 
            {
                cout << "X wins in " << i + 1 << " turns";
                break;
            }
            if (i == 8) cout << "It is a tie";
        }
        else
        {
            cout << "It is O turn\n";
            cout << "Choose a square? (x,y)\n";
            cin >> point;
            taken (t, point);
            t[point.m_x][point.m_y] = -1;
            printMatrix(t);
            if (check(t)) 
            {
                cout << "O wins in " << i + 1 << " turns";
                break;
            }
        }
    }

    return 0;
}
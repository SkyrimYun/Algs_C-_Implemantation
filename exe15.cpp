#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>

using namespace std;

struct unset
{
    int row;
    int col;
    int val;
    unset(int r, int c, int v) : row(r), col(c), val(v){};
};

bool check(unset point, vector<vector<int>> &currentMp)
{
    //check row
    for (int i = 0; i < 9; i++)
    {
        if (currentMp[point.row][i] == point.val)
            return false;
    }

    //check column
    for (int i = 0; i < 9; i++)
    {
        if (currentMp[i][point.col] == point.val)
            return false;
    }

    //check square
    int squareR = point.row / 3;
    int squareC = point.col / 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (currentMp[squareR * 3 + i][squareC * 3 + j] == point.val)
                return false;
        }
    }
    return true;
}

unset findZero(vector<vector<int>> &mp)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (mp[i][j] == 0)
            {
                unset point(i, j, 0);
                return point;
            }
        }
    }
    unset point(-1, -1, -1);
    return point;
}

vector<vector<int>> findAnswer(list<vector<vector<int>>> &state)
{
    vector<vector<int>> currentMp = state.back();
    state.pop_back();

    unset point = findZero(currentMp);
    if (point.val == 0)
    {

        for (int num = 1; num < 10; num++)
        {
            point.val = num;
            if (check(point, currentMp))
            {
                state.push_back(currentMp);
                currentMp[point.row][point.col] = num;
                state.push_back(currentMp);
                currentMp = findAnswer(state);
                if (findZero(currentMp).val == -1)
                {
                    return currentMp;
                }
            }
        }

        currentMp = state.back();
        state.pop_back();
        return currentMp;
    }
    return currentMp;
}

int main()
{
    vector<vector<int>> mp;

    for (int i = 0; i < 9; i++)
    {
        vector<int> v;
        mp.push_back(v);
        string row;
        getline(cin, row);
        stringstream ss(row);
        char c;
        ss >> c;
        for (int j = 0; j < 9; j++)
        {
            int val;
            ss >> val;
            mp[i].push_back(val);
            ss >> c;
        }
    }

    list<vector<vector<int>>> state;
    state.push_back(mp);

    vector<vector<int>> solution = findAnswer(state);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << solution[i][j] << " ";
        }
        cout << '\n';
    }
}
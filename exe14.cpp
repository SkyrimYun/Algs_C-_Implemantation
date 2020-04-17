#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int main()
{
    int T, n;
    cin >> T;
    vector<string> output;
    for (int i = 0; i < T; i++)
    {
        string binary;
        cin >> n;
        cin >> binary;
        //cout << binary<<endl;

        for (int j = 0; j < n - 2; j++)
        {
            string tc;
            tc.push_back(binary[j]);
            tc.push_back(binary[j + 1]);
            tc.push_back(binary[j + 2]);
            if (tc == "010")
            {
                binary[j + 1] = '0';
                binary[j + 2] = '1';
            }
        }

        for (int j = 0; j < n - 1; j++)
        {
            string tc;
            tc.push_back(binary[j]);
            tc.push_back(binary[j + 1]);
            if (tc == "00")
            {
                binary[j] = '1';
            }
        }
        output.push_back(binary);
    }
    for (string ss : output)
    {
        cout << ss << endl;
    }
}
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int main()
{
    string s;
    string output;
    getline(cin, s);
    for (int i = s.size() - 1; i > -1; i--)
    {
        if (output.empty())
            output.push_back(s[i]);
        else if (output.find(s[i]) == string::npos)
            output.push_back(s[i]);
    }
    cout << output << endl;
}
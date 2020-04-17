#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void estring(string &s)
{
    if (s.size() <= 8)
    {
        for (int i = s.size(); i < 8; i++)
        {
            s += "0";
        }
        cout << s << endl;
    }
    else if (s.size() > 8)
    {
        string lefts;
        string rights;
        for (int i = 0; i < s.size(); i++)
        {
            if (i < 8)
                lefts.push_back(s[i]);
            else
                rights.push_back(s[i]);
        }
        cout << lefts << endl;
        estring(rights);
    }
}

int main()
{
    string s;
    while (getline(cin, s))
    {
        estring(s);
    }
}
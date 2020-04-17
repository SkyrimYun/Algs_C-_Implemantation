#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

bool hasMore(map<char, int> &charNum)
{
    typedef map<char, int>::iterator mit;
    for (mit i = charNum.begin(); i != charNum.end(); i++)
    {
        if (i->second != 0)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    string s;
    map<char, int> charNum;
    getline(cin, s);
    for (char c : s)
    {
        charNum[c]++;
    }
    typedef map<char, int>::iterator mit;

    while (hasMore(charNum))
    {
        for (mit i = charNum.begin(); i != charNum.end(); i++)
        {
            if (i->second != 0)
            {
                cout << i->first;
                i->second--;
            }
        }
    }
}
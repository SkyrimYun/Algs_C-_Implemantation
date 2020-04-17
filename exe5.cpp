#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{

    while (1)
    {
        string s;
        getline(cin, s);
        string ss;
        getline(cin, ss);
        int count = 0;

        for (char cc : s)
        {
            ss[0] = tolower(ss[0]);
            cc = tolower(cc);
            cout << ss[0] << " " << cc << endl;
            if (cc == ss[0])
                count++;
        }
        cout << count << endl;
        s.clear();
    }
}
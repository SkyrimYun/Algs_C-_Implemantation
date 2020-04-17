#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

int main()
{
    int total;
    cin >> total;
    vector<int> vc;
    for (int i = 0; i < total; i++)
    {
        int n;
        cin >> n;
        vc.push_back(n);
    }

    int count = 0;
    for (int i = 0; i < vc.size(); i++)
    {
        count++;
        i += vc[i];
    }
    cout << count << endl;
}
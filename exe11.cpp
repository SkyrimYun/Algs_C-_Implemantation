#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int main()
{
    int n;
    cin >> n;

    map<int, int> kv;
    for (int i = 0; i < n; i++)
    {
        int key, val;
        cin >> key >> val;
        kv[key] += val;
    }
    for (map<int, int>::iterator it = kv.begin(); it != kv.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
}
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>

using namespace std;

int main()
{
    int N = -1;
    int L = -1;
    vector<unsigned long long int> SUM;
    cin >> N >> L;
    while (N != 0 && L != 0)
    {
        unsigned long long int sum = 0;
        for (int l = 1; l <= L; l++)
        {
            sum += pow(N, l);
            sum %= 1000000007;
        }
        SUM.push_back(sum);
        cin >> N >> L;
    }
    for (unsigned long long int n : SUM)
        cout << n << endl;
}
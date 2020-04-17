#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    float f = 3.5;
    int n = int(f);
    if (f - n >= 0.5)
        n++;
    cout << n;
}
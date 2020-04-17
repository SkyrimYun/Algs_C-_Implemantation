#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        vector<int> input;
        int num;
        for (int i = 0; i < n; i++)
        {
            cin >> num;
            input.push_back(num);
        }

        sort(input.begin(), input.end());
        vector<int> output;
        for (int i = 0; i < input.size(); i++)
        {
            if (i != 0 && input[i] != input[i - 1])
                output.push_back(input[i]);
            else if (i == 0)
                output.push_back(input[i]);
        }
        for (int nn : output)
            cout << nn << endl;
    }
}
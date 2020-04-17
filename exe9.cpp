#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool isPrime(long n)
{
    for (long i = 2; i < n; i++)
    {
        if (n % i == 0 && n != i)
        {
            return false;
        }
    }
    return true;
}

string getResult(long ulDataInput)
{
    vector<int> prime;
    for (long i = 2; i < ulDataInput + 1; i++)
    {
        if (ulDataInput % i == 0 && isPrime(i))
        {
            prime.push_back(i);
            ulDataInput /= i;
            i = 1;
        }
    }
    sort(prime.begin(), prime.end());
    string s;
    for (long n : prime)
    {
        s += (to_string(n) + " ");
    }
    return s;
};

int main()
{
    long n;
    cin >> n;
    cout << getResult(180) << endl;
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> suffixes(string &s)
{
    int N = s.length();
    vector<string> suffixes = vector<string>(N);
    for (int i = 0; i < N; i++)
        suffixes[i] = s.substr(i, N);
    return suffixes;
}

// longest common prefix
int lcp(string &s, string &t)
{
    int N = s.length() < t.length() ? s.length() : t.length();
    for (int i = 0; i < N; i++)
    {
        if (s[i] != t[i])
            return i;
    }
    return N;
}

//longest repeated substring
string lrs(string &s)
{
    int N = s.length();
    vector<string> suffixes = vector<string>(N);
    for (int i = 0; i < N; i++)
        suffixes[i] = s.substr(i, N);

    sort(suffixes.begin(), suffixes.end());

    string lrs;
    for (int i = 0; i < N - 1; i++)
    {
        int len = lcp(suffixes[i], suffixes[i + 1]);
        if (len > lrs.length())
            lrs = suffixes[i].substr(0, len);
    }
    return lrs;
}

void keyIndexedCount(string &s, int R)
{
    int N = s.length();
    vector<int> count(R + 1);
    string aux = s;

    for (int i = 0; i < N; i++)
    {
        count[s[i] + 1]++;
    }

    for (int r = 0; r < R; r++)
    {
        count[r + 1] += count[r];
    }

    for (int i = 0; i < N; i++)
    {
        aux[count[s[i]]++] = s[i];
    }

    for (int i = 0; i < N; i++)
    {
        s[i] = aux[i];
    }
}

class LSD
{
public:
    //fixed-length W strings
    void sort(vector<string> s, int W)
    {
        int R = 256; //radix R
        int N = s.size();
        vector<string> aux(N);

        //do key-indexed counting for each digit from right to left
        for (int d = W - 1; d >= 0; d--)
        {
            //key-indexed counting
            vector<int> count(R + 1);
            for (int i = 0; i < N; i++)
            {
                count[s[i][d] + 1]++;
            }

            for (int r = 0; r < R; r++)
            {
                count[r + 1] += count[r];
            }

            for (int i = 0; i < N; i++)
            {
                aux[count[s[i][d]]++] = s[i][d];
            }

            for (int i = 0; i < N; i++)
            {
                s[i] = aux[i];
            }
        }
    }
};

class MSD
{
private:
    int R = 256;
    void sort(vector<string> &s, vector<string> &aux, int lo, int hi, int d)
    {
        if (lo >= hi)
            return;

        vector<int> count(R + 1);
        for (int i = lo; i <= hi; i++)
            count[s[i][d] + 1]++;

        for (int r = 0; r < R + 1; r++)
            count[r + 1] += count[r];

        for (int i = lo; i < hi; i++)
            aux[count[s[i][d]]++] = s[i];

        for (int i = lo; i <= hi; i++)
            s[i] = aux[i - lo];

        for (int r = 0; r < R; r++)
            sort(s, aux, lo + count[r], lo + count[r + 1] - 1, d + 1);
    }

public:
    void sort(vector<string> &s)
    {
        vector<string> aux(s.size());
        sort(s, aux, 0, s.size() - 1, 0);
    }
};

class threeWayStringQuicksort
{
private:
    void sort(vector<string> &s, int lo, int hi, int d)
    {
        if (lo >= hi)
            return;

        int lt = lo;
        int gt = hi;
        int v = s[lo][d]; // first key is the parpatitioning key
        int i = lo + 1;
        while (i <= gt)
        {
            int t = s[i][d];
            if (t > v)
                swap(s[i], s[gt--]);
            else if (t < v)
                swap(s[lt++], s[i++]);
            else
                i++;
        }

        // sort 3 subarrays recursively
        sort(s, lo, lt - 1, d);
        if (v >= 0)
            sort(s, lt, gt, d + 1);
        sort(s, gt + 1, hi, d);
    }

public:
    void sort(vector<string> &s)
    {
        sort(s, 0, s.size() - 1, 0);
    }
}
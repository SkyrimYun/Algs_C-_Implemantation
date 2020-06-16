#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int bruteForceSearch(string text, string pattern)
{
    int m = pattern.length();
    int n = text.length();
    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m)
            return i;
    }
    return n;
}

// another approach of brute force search
int BFsearch(string pat, string txt)
{
    int i, N = txt.length();
    int j, M = pat.length();
    for (i = 0, j = 0; i < N && j < M; i++)
    {
        if (txt[i] == pat[j])
            j++;
        else
        {
            i -= j;
            j = 0;
        }
    }
    if (j == M)
        return i - M;
    else
        return N;
}

class KMP
{
private:
    static const int R = 256;
    string pat;
    int m;
    vector<vector<int>> dfa;

public:
    KMP(string pattern)
    {
        pat = pattern;
        m = pat.length();
        dfa.resize(R);
        for (int i = 0; i < R; i++)
            dfa[i].resize(m);
        dfa[pat[0]][0] = 1;
        for (int x = 0, j = 1; j < m; j++)
        {
            for (int c = 0; c < R; c++)
            {
                dfa[c][j] = dfa[c][x]; //copy mismatch cases
            }
            dfa[pat[pat[j]]][j] = j + 1; //set match case
            x = dfa[pat[j]][x];          //update restart state
        }
    }

    int search(string text)
    {
        int i, j, n = text.length();
        for (i, j = 0; i < n && j < m; i++)
        {
            j = dfa[text[i]][j];
        }
        if (j == m)
            return i - m;
        else
            return n;
    }

    int search(istream in)
    {
        int i, j;
        char c;
        for (i, j = 0; !in.eof() && j < m; i++)
        {
            in >> c;
            j = dfa[c][j];
        }
        if (j == m)
            return i - m;
        else
            return -1;
    }
};

class BoyerMoore
{
private:
    const static int R = 256;
    string pat;
    int m;
    vector<int> right;

public:
    BoyerMoore(string pattern)
    {
        pat = pattern;
        m = pat.length();
        right.resize(R);

        // index of rightmost occurrence of character c in pattern
        //(-1 if character not in pattern)
        for (int c = 0; c < R; c++)
            right[c] = -1;
        for (int j = 0; j < m; j++)
            right[pat[j]] = j;
    }

    int search(string text)
    {
        int n = text.length();
        int skip;
        for (int i = 0; i <= n - m; i += skip)
        {
            skip = 0;
            for (int j = m - 1; j >= 0; j--)
            {
                if (pat[j] != text[i + j])
                {
                    skip = max(1, j - right[text[i + j]]);
                    break;
                }
            }
            if (skip == 0)
                return i;
        }
        return n;
    }
};
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// expensive; n^2 complexity
class UF
{
private:
    vector<int> id;

public:
    //initialize union-find data structure with N objects(0 to N – 1)
    UF(int N)
    {
        id.resize(N);
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
        }
    }

    //add connection between p and q
    void Union(int p, int q)
    {
        int pid = p;
        int qid = q;
        for (int i = 0; i < id.size(); i++)
        {
            if (id[i] == pid)
                id[i] = qid;
        }
    }

    //are p and q in the same component?
    bool connected(int p, int q)
    {
        return id[p] == id[q];
    }
};

// quick implementation using tree structure; lgN complexity
class QuickUF
{
private:
    vector<int> id;

public:
    //initialize union-find data structure with N objects(0 to N – 1)
    QuickUF(int N)
    {
        id.resize(N);
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
        }
    }

    // chase parent pointers until reach root
    int root(int i)
    {
        while (i != id[i])
        {
            id[i] = id[id[i]]; // path compression
            i = id[i];
        }

        return i;
    }

    //add connection between p and q
    void Union(int p, int q)
    {
        int i = root(p);
        int j = root(q);
        if (i == j)
            return;

        id[i] == id[j];
    }

    //are p and q in the same component?
    bool connected(int p, int q)
    {
        return root(q) == root(p);
    }
};

// even quicker implementation using weighted-tree structure
class WeightedQuickUF
{
private:
    vector<int> id;
    vector<int> sz;

public:
    //initialize union-find data structure with N objects(0 to N – 1)
    WeightedQuickUF(int N)
    {
        id.resize(N);
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
        }

        sz.resize(N);
        for (int i = 0; i < N; i++)
        {
            sz[i] = 1;
        }
    }

    // chase parent pointers until reach root
    int root(int i)
    {
        while (i != id[i])
            i = id[i];
        return i;
    }

    //add connection between p and q
    void Union(int p, int q)
    {
        int i = root(p);
        int j = root(q);

        if (i == j)
            return;

        if (sz[i] <= sz[j])
        {
            id[i] = j;
            sz[j] += sz[i];
            cout << "sz[" << j << "]: " << sz[j] << endl;
        }
        else
        {
            id[j] = id[i];
            sz[i] += sz[j];
            cout << "sz[" << i << "]: " << sz[i] << endl;
        }
    }

    //are p and q in the same component?
    bool connected(int p, int q)
    {
        return root(p) == root(q);
    }
};

int main()
try
{
    ifstream ifs("tinyUF.txt");
    if (!ifs)
        throw runtime_error("cannot open input file!");

    int N = 0;
    ifs >> N;
    WeightedQuickUF uf(N);
    int p = 0;
    int q = 0;
    while (!ifs.eof())
    {
        ifs >> p >> q;
        if (!uf.connected(p, q))
        {
            uf.Union(p, q);
            //cout << p << " " << q << endl;
        }
    }
}
catch (runtime_error &e)
{
    cerr << "runtime error: " << e.what() << endl;
    return 1;
}
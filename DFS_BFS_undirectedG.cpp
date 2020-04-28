#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// max value is in arr[1]
// so real capacity is cap + 1
template <class T, class Comp = less<T>>
class PQ
{
private:
    T *arr;
    int capacity;
    int size = 0;
    Comp compare;

public:
    PQ(int cap, Comp cmp = less<T>())
    {
        capacity = cap + 1;
        arr = new T[capacity];
        compare = cmp;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    // check if child's key becomes larger key than its parents
    void swim(int k)
    {
        while (k > 1 && !compare(arr[k], arr[k / 2]))
        {
            swap(arr[k], arr[k / 2]);
            k = k / 2;
        }
    }

    // check if parent's key becomes smaller than one or both of its children's
    void sink(int k)
    {
        while (2 * k <= size)
        {
            int j = 2 * k;
            // get the larger child
            //if (2 * k + 1 <= size)
            if (compare(arr[2 * k], arr[2 * k + 1]))
                j++;
            if (compare(arr[j], arr[k]))
                break;
            swap(arr[k], arr[j]);
            k = j;
        }
    };

    void enquene(T item)
    {
        arr[++size] = item;
        swim(size);
    }

    T dequene()
    {
        T item = arr[1];
        swap(arr[1], arr[size--]);
        // prvent loitering
        arr[size + 1] = T();
        sink(1);

        return item;
    }

    ~PQ()
    {
        delete[] arr;
    }
};

//Adjacency-matrix graph representation
class MGraph
{
private:
    int vertex;
    int edge;
    vector<vector<int>> Adj;

public:
    MGraph() {}
    MGraph(istream &ist)
    {
        ist >> vertex;
        ist >> edge;
        int v, w;
        int count = 0;
        while (!ist.eof())
        {
            ist >> v >> w;
            addEdge(v, w);
            count++;
        }
        if (count != edge)
            throw runtime_error("the input Edge number is wrong!");
    }
    MGraph(int v)
    {
        vertex = v;
        Adj = vector<vector<int>>(vertex);
    }

    void addEdge(int v, int w)
    {
        Adj[v][w] = 1;
        Adj[w][v] = 1;
    }

    vector<int> adj(int v)
    {
        vector<int> adjv;
        for (int i = 0; i < Adj[v].size(); i++)
        {
            if (Adj[v][i] == 1)
                adjv.push_back(i);
        }
        return adjv;
    }

    int V()
    {
        return vertex;
    }

    int E()
    {
        return edge;
    }
};

// Adjacency-list graph representation
class LGraph
{
private:
    int vertex;
    int edge;
    vector<vector<int>> ADJ;

public:
    LGraph() {}
    LGraph(istream &ist)
    {
        ist >> vertex;
        ist >> edge;
        ADJ.resize(vertex);

        int v, w;
        int count = 0;
        while (!ist.eof())
        {
            ist >> v >> w;
            addEdge(v, w);
            count++;
        }
        if (count != edge)
            throw runtime_error("the input Edge number is wrong!");
    }
    LGraph(int v)
    {
        this->vertex = v;
        ADJ = vector<vector<int>>(this->vertex);
    }

    void addEdge(int v, int w)
    {
        ADJ[v].push_back(w);
        ADJ[w].push_back(v);
    }

    vector<int> adj(int v)
    {
        return ADJ[v];
    }

    int V()
    {
        return vertex;
    }

    int E()
    {
        return edge;
    }
};

class DepthFirstPaths
{
private:
    // marked[v] = true if v connected to s
    vector<bool> marked;
    // edgeTo[v] = previous vertex on path from s to v
    vector<int> edgeTo;

    int s;

    void dfs(LGraph G, int v)
    {
        marked[v] = true;
        for (int w : G.adj(v))
        {
            if (!marked[w])
            {
                dfs(G, w);
                edgeTo[w] = v;
            }
        }
    }

public:
    DepthFirstPaths(LGraph G, int s)
    {
        marked = vector<bool>(G.V());
        edgeTo = vector<int>(G.V());
        this->s = s;
        dfs(G, s);
    }

    bool hasPathTo(int v)
    {
        return marked[v];
    }

    vector<int> pathTo(int v)
    {
        if (!hasPathTo(v))
            return vector<int>();
        vector<int> path;
        for (int p = v; p != s; p = edgeTo[p])
        {
            path.push_back(p);
        }
        path.push_back(s);
        return path;
    }
};

class BreadthFirstPaths
{
private:
    vector<bool> marked;
    vector<int> edgeTo;
    int s;

    void bfs(LGraph G, int s)
    {
        PQ<int, greater<int>> pqv(G.V(), greater<int>());
        marked[s] = true;
        pqv.enquene(s);

        while (!pqv.isEmpty())
        {
            int v = pqv.dequene();
            for (int x : G.adj(v))
            {
                if (!marked[x])
                {
                    marked[x] = true;
                    pqv.enquene(x);
                    edgeTo[x] = v;
                }
            }
        }
    }

public:
    BreadthFirstPaths(LGraph G, int s)
    {
        marked = vector<bool>(G.V());
        edgeTo = vector<int>(G.V());
        this->s = s;
        bfs(G, s);
    }

    bool hasPathTo(int v)
    {
        return marked[v];
    }

    vector<int> pathTo(int v)
    {
        if (!hasPathTo(v))
            return vector<int>();
        vector<int> path;
        for (int p = v; p != s; p = edgeTo[p])
        {
            path.push_back(p);
        }
        path.push_back(s);
        return path;
    }
};

class CC
{
private:
    vector<bool> marked;
    vector<int> id;
    int count;

    void dfs(LGraph G, int v)
    {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v))
        {
            if (!marked[w])
            {
                dfs(G, w);
            }
        }
    }

public:
    CC(LGraph G)
    {
        marked = vector<bool>(G.V());
        id = vector<int>(G.V());
        for (int v = 0; v < G.V(); v++)
        {
            if (!marked[v])
            {
                dfs(G, v);
                count++;
            }
        }
    }
};

int main()
try
{
    ifstream ifs("tinyG.txt");
    if (!ifs)
        throw runtime_error("cannot open file");
    LGraph G(ifs);

    BreadthFirstPaths paths(G, 0);
    for (int v = 1; v < G.V(); v++)
    {
        vector<int> path = paths.pathTo(v);
        if (!path.empty())
        {
            for (int i = 0; i < path.size() - 1; i++)
            {
                cout << path[i] << "->";
            }
            cout << path[path.size() - 1] << endl;
        }
    }
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
}

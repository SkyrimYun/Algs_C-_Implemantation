#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template <class T, class Comp = less<T>>
class PQ
{
private:
    T *arr;
    int capacity;
    int size = 0;
    Comp compare;

public:
    PQ(int cap = 0, Comp cmp = Comp())
    {
        capacity = cap + 1;
        arr = new T[capacity];
        compare = cmp;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    // copy assignment
    PQ &operator=(const PQ &a)
    {
        this->capacity = a.capacity;
        this->arr = a.arr;
        this->compare = a.compare;
        return *this;
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
        sink(1);
        // prvent loitering
        arr[size + 1] = T();

        return item;
    }

    ~PQ()
    {
        delete[] arr;
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

        // smaller subtree attach to bigger subtree
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

class Edge
{
private:
    int v1;
    int v2;
    double Weight;

public:
    Edge() {}
    Edge(int v, int w, double weight) : v1(v), v2(w), Weight(weight) {}

    int either()
    {
        return v1;
    }

    int other(int v)
    {
        if (v == v1)
            return v2;
        if (v == v2)
            return v1;
        return -1;
    }

    friend ostream &operator<<(ostream &ost, const Edge &e)
    {
        ost << e.v1 << "-" << e.v2 << " " << e.Weight << endl;
        return ost;
    }

    double weight()
    {
        return Weight;
    }
};

class EWG
{
private:
    int vertex;
    int edge;
    vector<vector<Edge>> ADJ;
    vector<Edge> EDGES;

public:
    EWG() {}
    EWG(istream &ist)
    {
        ist >> vertex;
        ist >> edge;
        ADJ.resize(vertex);

        int v, w;
        double weight;
        int count = 0;
        while (!ist.eof())
        {
            ist >> v >> w >> weight;
            Edge e(v, w, weight);
            addEdge(e);
            count++;
        }
        if (count != edge)
            throw runtime_error("the input Edge number is wrong!");
    }
    EWG(int v)
    {
        vertex = v;
        ADJ.resize(vertex);
    }

    void addEdge(Edge e)
    {
        int v = e.either();
        int w = e.other(v);
        ADJ[v].push_back(e);
        ADJ[w].push_back(e);
        EDGES.push_back(e);
    }

    vector<Edge> adj(int v)
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

    vector<Edge> edges()
    {
        return EDGES;
    }
};

struct edgeCmp
{
    edgeCmp() {}

    bool operator()(Edge &e1, Edge &e2)
    {
        if (e1.weight() > e2.weight())
            return true;
        else
            return false;
    }
};

class KruskalMST
{
private:
    vector<Edge> mst;

public:
    KruskalMST(EWG G)
    {
        PQ<Edge, edgeCmp> epq(G.E());
        for (Edge e : G.edges())
        {
            epq.enquene(e);
        }
        WeightedQuickUF uf(G.V());

        // mst should have v-1 edges
        while (!epq.isEmpty() && mst.size() != G.V() - 1)
        {
            Edge e = epq.dequene();
            int v = e.either();
            int w = e.other(v);
            if (!uf.connected(v, w))
            {
                uf.Union(v, w);
                mst.push_back(e);
            }
        }
    }

    vector<Edge> edges()
    {
        return mst;
    }

    double weights()
    {
        double weight = 0;
        for (Edge e : mst)
        {
            weight += e.weight();
        }
        return weight;
    }
};

class PrimMST
{
private:
    PQ<Edge, edgeCmp> epq;
    vector<bool> marked;
    vector<Edge> mst;
    vector<Edge> adj;

    void visit(EWG G, int v)
    {
        marked[v] = true;
        adj = G.adj(v);
        for (Edge e : adj)
        {
            if (!marked[e.other(v)])
                epq.enquene(e);
        }
    }

public:
    PrimMST(EWG G)
    {
        epq = PQ<Edge, edgeCmp>(G.E());
        marked.resize(G.V());

        visit(G, 0);

        while (!epq.isEmpty() && mst.size() != G.V() - 1)
        {
            Edge e = epq.dequene();
            int v = e.either();
            int w = e.other(v);
            if (marked[v] && marked[w])
                continue;
            mst.push_back(e);
            if (!marked[v])
                visit(G, v);
            if (!marked[w])
                visit(G, w);
        }
    }

    vector<Edge> edges()
    {
        return mst;
    }

    double weights()
    {
        double weight = 0;
        for (Edge e : mst)
        {
            weight += e.weight();
        }
        return weight;
    }
};

int main()
try
{
    ifstream ifs("tinyEWG.txt");
    if (!ifs)
        throw runtime_error("cannot open file");
    EWG G(ifs);

    PrimMST mst(G);
    for (Edge e : mst.edges())
    {
        cout << e;
    }
    cout << mst.weights() << endl;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
}
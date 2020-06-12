#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
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

class FlowEdge
{
private:
    int v, w; // from  v to w
    double capacity;
    double flow;

public:
    //create a flow edge v→w
    FlowEdge(int v, int w, double capacity) : v(v), w(w), capacity(capacity) {}

    //vertex this edge points from
    int from()
    {
        return v;
    }

    //vertex this edge points to
    int to()
    {
        return w;
    }

    //other endpoint
    int other(int vertex)
    {
        if (vertex == v)
            return w;
        else if (vertex == w)
            return v;
        else
            throw runtime_error("invalid vertex value");
    }

    //capacity of this edge
    double capacity()
    {
        return capacity;
    }

    //flow in this edge
    double flow()
    {
        return flow;
    }

    //residual capacity toward v
    double residualCapacityTo(int vertex)
    {
        if (vertex == v)
            return flow;
        else if (vertex == w)
            return capacity - flow;
        else
            throw runtime_error("invalid vertex value!");
    }
    //add delta flow toward v
    void addResidualFlowTo(int vertex, double delta)
    {
        if (vertex == v)
            flow -= delta;
        else if (vertex == w)
            flow += delta;
        else
            throw runtime_error("invalid vertex when adding flow");
    }
};

class FlowNetwork
{
private:
    int VV;
    vector<vector<FlowEdge>> ADJ;

public:
    //create an empty flow network with V vertices
    FlowNetwork(int V)
    {
        VV = V;
        ADJ.resize(V);
    }

    //construct flow network input stream
    FlowNetwork(istream &in) {}

    //add flow edge e to this flow network
    void addEdge(FlowEdge e)
    {
        int v = e.from();
        int w = e.to();
        ADJ[v].push_back(e);
        ADJ[w].push_back(e);
    }

    //forward and backward edges incident to v
    vector<FlowEdge> adj(int v)
    {
        return ADJ[v];
    }

    int V()
    {
        return VV;
    }
};

class FordFulkerson
{
private:
    vector<bool> marked;
    vector<FlowEdge> edgeTo; // last edge on s->v path
    double value;

public:
    FordFulkerson(FlowNetwork G, int s, int t)
    {
        value = 0.0;
        while (hasAugmentingPath(G, s, t))
        {
            //compute bottlenect capacity
            double bottle = numeric_limits<double>::infinity();
            for (int v = t; v != s; v = edgeTo[v].other(v))
            {
                bottle = min(bottle, edgeTo[v].residualCapacityTo(v));
            }

            //augment flow
            for (int v = t; v != s; v = edgeTo[v].other(v))
            {
                edgeTo[v].addResidualFlowTo(v, bottle);
            }

            value += bottle;
        }
    }

    double value()
    {
        return value;
    }

    bool inCut(int v)
    {
        return marked[v];
    }

    bool hasAugmentingPath(FlowNetwork G, int s, int t)
    {
        // BFS
        //reset edgeTo and marked
        edgeTo = vector<FlowEdge>(G.V());
        marked = vector<bool>(G.V());

        PQ<int> quene(G.V());

        quene.enquene(s);
        marked[s] = true;
        while (!quene.isEmpty())
        {
            int v = quene.dequene();

            for (FlowEdge e : G.adj(v))
            {
                int w = e.other(v);
                //found path from s to w in the residual network
                if (e.residualCapacityTo(w) > 0 && !marked[w])
                {
                    edgeTo[w] = e;    //save last edge on path to w
                    marked[w] = true; //mark w
                    quene.enquene(w); //add w to the quene
                }
            }
        }
        return marked[t];
    }
};
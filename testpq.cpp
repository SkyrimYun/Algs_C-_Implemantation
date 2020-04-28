#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template <class T, class Comp>
class PQ
{
private:
    T *arr;
    int capacity;
    int size = 0;
    Comp compare;

public:
    PQ(int cap, Comp cmp = Comp())
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
            if (j < size && compare(arr[2 * k], arr[2 * k + 1]))
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

class Edge
{
private:
    int v1;
    int v2;
    double Weight;

public:
    Edge() : v1(-1), v2(-1), Weight(-1) {}
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

int main()
{
    ifstream ifs("tinyEWG.txt");
    if (!ifs)
        throw runtime_error("cannot open file");

    int vertex, edge;
    ifs >> vertex;
    ifs >> edge;

    int v, w;
    double weight;
    PQ<Edge, edgeCmp> epq(edge);
    while (!ifs.eof())
    {
        ifs >> v >> w >> weight;
        Edge e(v, w, weight);
        epq.enquene(e);
    }

    // mst should have v-1 edges
    while (!epq.isEmpty())
    {
        Edge e = epq.dequene();
        cout << e;
    }
}
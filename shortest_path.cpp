#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// red black binary search tree
template <class Key, class Value>
class RBBST
{
private:
    const static bool RED = true;
    const static bool Black = false;
    struct Node
    {
        Key key;
        Value value;
        int count = 1;
        Node *left = nullptr;
        Node *right = nullptr;
        bool color;
        Node(Key k, Value val, bool col = RED)
        {
            this->key = k;
            this->value = val;
            this->color = col;
        }
        Node(){};
    };

    Node *root;

    bool isRed(Node *x)
    {
        if (x == nullptr)
            return Black;
        return x->color == RED;
    }

    Node *rotateLeft(Node *h)
    {
        Node *x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }

    Node *rotateRight(Node *h)
    {
        Node *x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }

    void filpColor(Node *x)
    {
        x->right->color = Black;
        x->left->color = Black;
        x->color = RED;
    }

    Node *put(Node *x, Key key, Value val)
    {
        if (x == nullptr)
            return new Node(key, val, RED);

        if (key > x->key)
            x->right = put(x->right, key, val);
        else if (key < x->key)
            x->left = put(x->left, key, val);
        else
            x->value = val;

        // the only difference between BST and RBBST in coding
        // rely on recursion to address red link direction
        if (isRed(x->right) && !isRed(x->left))
            x = rotateLeft(x);
        if (isRed(x->left) && isRed(x->left->left))
            x = rotateRight(x);
        if (isRed(x->right) && isRed(x->left))
            filpColor(x);

        x->count = 1 + size(x->left) + size(x->right);

        return x;
    }

    Node *floor(Node *x, Key key)
    {
        if (x == nullptr)
            return nullptr;

        //Case 1. [k is less than the key at root]
        //The floor of k is in the left subtree.
        if (key < x->key)
            x = floor(x->left, key);

        //Case 2. [k equals the key at root]
        //The floor of k is k.
        if (key == x->key)
            return x;

        //Case 3. [k is greater than the key at root]
        //The floor of k is in the right subtree(if there is any key ≤ k in right subtree);
        //otherwise it is the key in the root.
        Node *t = x->right;
        t = floor(t, key);
        if (t != nullptr)
            return t;
        else
            return x;
    }

    Node *ceiling(Node *x, Key key)
    {
        if (x == nullptr)
            return nullptr;

        if (key > x->key)
            x = ceiling(x->ritgt, key);

        if (key == x->key)
            return x;

        Node *t = x->left;
        t = ceiling(t, key);
        if (t != nullptr)
            return t;
        else
            return x;
    }

    int size(Node *x)
    {
        if (x == nullptr)
            return 0;
        return x->count;
    }

    int rank(Node *x, Key key)
    {
        if (x == nullptr)
            return 0;

        if (key > x->key)
            return 1 + size(x->left) + rank(x->right, key);
        else if (key < x->key)
            return rank(x->left, key);
        else
            return size(x->left);
    }

    Key select(Node *x, int k)
    {
        if (x == nullptr)
            return Key();

        if (k > rank(x->key))
            return select(x->right, k);
        else if (k < rank(x->key))
            return select(x->left, k);
        else
            return x->key;
    }

    void inorder(vector<Key> &keys, Node *x)
    {
        if (x == nullptr)
            return;
        inorder(keys, x->left);
        keys.push_back(x->key);
        inorder(keys, x->right);
    }

    Node *deleteMin(Node *x)
    {
        if (x->left == nullptr)
            return x->right;

        x->left = deleteMin(x->left);
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    Node *deleteMax(Node *x)
    {
        if (x->right == nullptr)
            return x->left;

        x->right = deleteMax(x->right);
        x.count = 1 + size(x->left) + size(x->right);
        return x;
    }

    Key min(Node *x)
    {
        if (x == nullptr)
            return Key();

        while (x->left != nullptr)
            x = x->left;
        return x->key;
    }

    Key max(Node *x)
    {
        if (x == nullptr)
            return nullptr;

        while (x->right != nullptr)
            x = x - right;
        return x->key;
    }

    Node *deleteKey(Node *x, Key key)
    {
        if (x == nullptr)
            return nullptr;

        // Hibbard deletion
        // search for key
        if (key > x->key)
            x->right = deleteKey(x->right, key);
        else if (key < x->key)
            x->left = deleteKey(x->left, key);
        else
        {
            //no right child
            if (x->left == nullptr)
                return x->right;
            // no left child
            if (x->right == nullptr)
                return x->left;

            //have two children
            //use the min on the right subtree to replace
            Node *t = x;
            x = min(t->right);
            x->right = deleteMin(t->right, key);
            x->left = t->left;
        }

        // update count
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

public:
    RBBST(){};

    void put(Key key, Value val)
    {
        root = put(root, key, val);
    }

    Value get(Key key)
    {
        Node *x = root;
        while (x != nullptr)
        {
            if (key > x->key)
                x = x->right;
            else if (key < x->key)
                x = x->left;
            else
                return x->value;
        }
        return Value();
    }

    void deleteKey(Key key)
    {
        root = deleteKey(root, key);
    }

    bool contains(Key key)
    {
        Node *x = root;
        while (x != nullptr)
        {
            if (key > x->key)
                x = x->right;
            else if (key < x->key)
                x = x->left;
            else
                return true;
        }
        return false;
    }

    bool isEmpty()
    {
        return size(root) == 0;
    }

    int size()
    {
        return size(root);
    }

    Key min()
    {
        return min(root);
    }

    Key max()
    {
        return max(root);
    }

    // largest key ≤ a given key.
    Key floor(Key key)
    {
        Node *x = floor(root, key);
        if (x == nullptr)
            return Key();
        return x->key;
    }

    // Smallest key ≥ a given key.
    Key ceiling(Key key)
    {
        Node *x = ceiling(root, key);
        if (x == nullptr)
            return Key();
        return x->key;
    }

    //How many keys < key
    int rank(Key key)
    {
        return rank(root, key);
    }

    // the key that ranks k th
    Key select(int k)
    {
        return select(root, k);
    }

    void deleteMin()
    {
        root = deleteMin(root);
    }

    void deleteMax()
    {
        root = deleteMax(root);
    }

    vector<Key> keys()
    {
        vector<Key> k;
        inorder(k, root);
        return k;
    }
};

// directed edge with weight
class Edge
{
private:
    int v1;
    int v2;
    double Weight;

public:
    Edge() {}
    Edge(int v, int w, double weight) : v1(v), v2(w), Weight(weight) {}

    int from()
    {
        return v1;
    }

    int to()
    {
        return v2;
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

// edge weighted diagraph
class EWD
{
private:
    int vertex;
    int edge;
    vector<vector<Edge>> ADJ;
    vector<Edge> EDGES;

public:
    EWD() {}
    EWD(istream &ist)
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
    EWD(int v)
    {
        vertex = v;
        ADJ.resize(vertex);
    }

    void addEdge(Edge e)
    {
        int v = e.from();
        ADJ[v].push_back(e);
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

//
class Toposort
{
private:
    // marked[v] = true if v connected to s
    vector<bool> marked;
    vector<int> order;

    void dfs(EWD G, int v)
    {
        marked[v] = true;
        for (Edge e : G.adj(v))
        {
            int w = e.to();
            if (!marked[w])
            {
                dfs(G, w);
            }
        }
        order.push_back(v);
    }

public:
    Toposort(EWD G)
    {
        marked = vector<bool>(G.V());

        for (int v = 0; v < G.V(); v++)
        {
            if (!marked[v])
                dfs(G, v);
        }
    }

    vector<int> reversePost()
    {
        vector<int> reverserOrder;
        for (int i = order.size() - 1; i >= 0; i--)
        {
            reverserOrder.push_back(order[i]);
        }
        return reverserOrder;
    }
};

// can handle cycle; but not negative edge
class DijkstraSP
{
private:
    // the path s to v
    vector<vector<Edge>> pathto;
    // last edge on the SP to v
    vector<Edge> edgeto;
    // distance of the SP
    vector<double> distto;
    RBBST<int, double> pq;

    void relax(Edge e)
    {
        int v = e.from();
        int w = e.to();
        if (distto[w] > distto[v] + e.weight())
        {
            distto[w] = distto[v] + e.weight();
            edgeto[w] = e;
            pathto[w] = pathto[v];
            pathto[w].push_back(e);
            pq.put(w, distto[w]); //update pq
        }
    }

public:
    DijkstraSP(EWD G, int s)
    {
        pathto.resize(G.V());
        distto.resize(G.V());
        edgeto.resize(G.V());

        // the initial distance to any vertex should be large enough (infinite)
        for (int i = 0; i < distto.size(); i++)
        {
            distto[i] = 100000;
        }
        distto[s] = 0.0;

        pq.put(s, 0);
        while (!pq.isEmpty())
        {
            // based on order, pop out vertex
            // relax all adjacent edges
            int v = pq.min();
            pq.deleteMin();
            for (Edge e : G.adj(v))
            {
                relax(e);
            }
        }
    }

    double distTo(int v)
    {
        return distto[v];
    }

    vector<Edge> pathTo(int v)
    {
        return pathto[v];
    }

    bool hasPathTo(int v)
    {
        return !pathto[v].empty();
    }
};

// if no cycle; can handle negative edge
class AcyclicSP
{
private:
    vector<Edge> edgeto;
    vector<vector<Edge>> pathto;
    vector<double> distto;

    void relax(Edge e)
    {
        int v = e.from();
        int w = e.to();
        if (distto[w] > distto[v] + e.weight())
        {
            distto[w] = distto[v] + e.weight();
            edgeto[w] = e;

            pathto[w] = pathto[v];
            pathto[w].push_back(e);
        }
    }

public:
    AcyclicSP(EWD G, int s)
    {
        edgeto.resize(G.V());
        pathto.resize(G.V());
        distto.resize(G.V());

        for (int i = 0; i < distto.size(); i++)
        {
            distto[i] = 100000;
        }
        distto[s] = 0;

        // vertex pop out order based on topo order
        Toposort top(G);

        for (int v : top.reversePost())
        {
            for (Edge e : G.adj(v))
            {
                relax(e);
            }
        }
    }

    vector<Edge> pathTo(int v)
    {
        return pathto[v];
    }

    double distTo(int v)
    {
        return distto[v];
    }
};

int main()
try
{
    ifstream ifs("tinyEWD.txt");
    if (!ifs)
        throw runtime_error("cannot open file");
    EWD G(ifs);

    AcyclicSP sp(G, 0);

    for (int v = 0; v < G.V(); v++)
    {
        cout << 0 << " to " << v << " (" << sp.distTo(v) << "): " << endl;
        for (Edge e : sp.pathTo(v))
        {
            cout << e;
        }
        cout << '\n';
    }
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class trie
{
private:
    const static int R = 256;
    struct Node
    {
        int *value;
        vector<Node *> next;
        Node()
        {
            value = nullptr;
            next = vector<Node *>(R);
        }
    };

    Node *root = new Node;

    Node *put(Node *x, string key, int value, int d)
    {
        if (x == nullptr)
            x = new Node;
        if (d == key.length())
        {
            x->value = &value;
            return x;
        }
        char c = key[d];
        x->next[c] = put(x->next[c], key, value, d + 1);
        return x;
    }

    Node *get(Node *x, string key, int d)
    {
        if (x == nullptr)
            return nullptr;
        if (d == key.length())
            return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

    void collect(Node *x, string prefix, vector<string> &quene)
    {
        if (x == nullptr)
            return;
        if (x->value != nullptr)
            quene.push_back(prefix);
        for (char r = 0; r < R; r++)
        {
            collect(x->next[r], prefix + r, quene);
        }
    }

    int search(Node *x, string query, int length, int d)
    {
        if (x == nullptr)
            return length;
        if (x->value != nullptr)
            length = d;
        if (d == query.length())
            return length;

        char c = query[d];
        return search(x->next[c], query, length, d + 1);
    }

public:
    void put(string key, int value)
    {
        root = put(root, key, value, 0);
    }

    bool contains(string key)
    {
        return get(key) != -1;
    }

    int get(string key)
    {
        Node *x = get(root, key, 0);
        if (x == nullptr)
            return -1;
        return *(x->value);
    }

    vector<string> keys()
    {
        vector<string> quene;
        collect(root, "", quene);
        return quene;
    }

    vector<string> keysWithPrefix(string prefix)
    {
        vector<string> quene;
        Node *x = get(root, prefix, 0);
        collect(x, prefix, quene);
        return quene;
    }

    string longestPrefixOf(string query)
    {
        int length = search(root, query, 0, 0);
        return query.substr(0, length);
    }
};

class TST
{
private:
    const static int R = 256;
    struct Node
    {
        int *value;
        char c;
        Node *left, *mid, *right;
        Node()
        {
            value = nullptr;
            left, mid, right = nullptr;
        }
    };

    Node *root = new Node;

    Node *put(Node *x, string key, int value, int d)
    {
        char c = key[d];
        if (x == nullptr)
            x = new Node;

        if (c < x->c)
            x->left = put(x->left, key, value, d);
        else if (c > x->c)
            x->right = put(x->right, key, value, d);
        else if (d < key.length() - 1)
            x->mid = put(x->mid, key, value, d + 1);
        else
            x->value = &value;

        return x;
    }

    Node *get(Node *x, string key, int d)
    {
        if (x == nullptr)
            return nullptr;

        char c = key[d];
        if (c < x->c)
            x->left = get(x->left, key, d);
        else if (c > x->c)
            x->right = get(x->right, key, d);
        else if (d < key.length() - 1)
            x->mid = get(x->mid, key, d + 1);
        else
            return x;
    }

public:
    void put(string key, int value)
    {
        root = put(root, key, value, 0);
    }

    bool contains(string key)
    {
        return get(key) != -1;
    }

    int get(string key)
    {
        Node *x = get(root, key, 0);
        if (x == nullptr)
            return -1;
        return *(x->value);
    }
};
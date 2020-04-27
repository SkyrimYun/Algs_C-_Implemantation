#include <iostream>
#include <vector>
using namespace std;

template <class Key, class Value>
class BST
{
private:
    struct Node
    {
        Key key;
        Value value;
        int count = 1;
        Node *left;
        Node *right;
        Node(key k, value val)
        {
            this.key = k;
            this.value = val;
        }
        Node(){};
    };

    Node *root;

    Node *put(Node *x, Key key, Value val)
    {
        if (x == nullptr)
            return new Node(key, val);

        if (key > x->key)
            x->right = put(x->right, key, val);
        else if (key < x->key)
            x->left = put(x->left, key, val);
        else
            x->val = val;

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
        x.count = 1 + size(x->left) + size(x->right);
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
            return nullptr;

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
            if (x->left == null)
                return x->right;
            // no left child
            if (x->right == null)
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
    ST(){};

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

    Key max(){
        return max(root)}

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

int main()
try
{
    /* code */
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
}

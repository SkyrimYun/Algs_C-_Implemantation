#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<class Key, class Value>
class BST {
public:

    struct Node {
        Key key;
        Value value;
        int count = 1;
        shared_ptr<Node> left;
        shared_ptr<Node> right;

        Node(Key k, Value val) {
            this->key = k;
            this->value = val;
        }

        Node() = default;
    };
    using NodePtr = shared_ptr<Node>;

    BST() = default;

    void put(Key key, Value val) {
        root = put(root, key, val);
    }

    Value get(Key key) {
        NodePtr x = root;
        while (x != nullptr) {
            if (key > x->key) {
                x = x->right;
            } else if (key < x->key) {
                x = x->left;
            } else {
                return x->value;
            }
        }

        return Value();
    }

    void deleteKey(Key key) {
        root = deleteKey(root, key);
    }

    bool contains(Key key) {
        NodePtr x = root;
        while (x != nullptr) {
            if (key > x->key) {
                x = x->right;
            } else if (key < x->key) {
                x = x->left;
            } else {
                return true;
            }
        }
        return false;
    }

    bool isEmpty() {
        return size(root) == 0;
    }

    int size() {
        return size(root);
    }

    Key min() {
        return min(root);
    }

    Key max() {
        return max(root);
    }

    // largest key ≤ a given key.
    Key floor(Key key) {
        NodePtr x = floor(root, key);
        if (x == nullptr) {
            return Key();
        }
        return x->key;
    }

    // Smallest key ≥ a given key.
    Key ceiling(Key key) {
        NodePtr x = ceiling(root, key);
        if (x == nullptr) {
            return Key();
        }
        return x->key;
    }

    //How many keys < key
    int rank(Key key) {
        return rank(root, key);
    }

    // the key that ranks k th
    Key select(int k) {
        return select(root, k);
    }

    void deleteMin() {
        root = deleteMin(root);
    }

    void deleteMax() {
        root = deleteMax(root);
    }

    vector<Key> keys() {
        vector<Key> k;
        inorder(k, root);
        return k;
    }


private:

    NodePtr put(NodePtr x, Key key, Value val) {
        if (x == nullptr) {
            return make_shared<Node>(key, val);
        }

        if (key > x->key) {
            x->right = put(x->right, key, val);
        } else if (key < x->key) {
            x->left = put(x->left, key, val);
        } else {
            x->value = val;
        }

        x->count = 1 + size(x->left) + size(x->right);

        return x;
    }

    NodePtr floor(NodePtr x, Key key) {
        if (x == nullptr) {
            return nullptr;
        }

        //Case 1. [key is less than the value at root]
        //The floor of key is in the left subtree.
        if (key < x->key) {
            return floor(x->left, key);
        }

        //Case 2. [key equals the root]
        //The floor of key is root.
        if (key == x->key) {
            return x;
        }

        //Case 3. [key is greater than the value at root]
        //The floor of key is in the right subtree(if there is any value ≤ key in right subtree);
        //otherwise it is the value in the root.
        NodePtr t = x->right;
        t = floor(t, key);
        if (t != nullptr) {
            return t;
        } else {
            return x;
        }
    }

    NodePtr ceiling(NodePtr x, Key key) {
        if (x == nullptr) {
            return nullptr;
        }

        if (key > x->key) {
            return ceiling(x->ritgt, key);
        }

        if (key == x->key) {
            return x;
        }

        NodePtr t = x->left;
        t = ceiling(t, key);
        if (t != nullptr) {
            return t;
        } else {
            return x;
        }
    }

    int size(NodePtr x) {
        if (x == nullptr) {
            return 0;
        }

        return x->count;
    }

    int rank(NodePtr x, Key key) {
        if (x == nullptr) {
            return 0;
        }

        if (key > x->key) {
            return 1 + size(x->left) + rank(x->right, key);
        } else if (key < x->key) {
            return rank(x->left, key);
        } else {
            return size(x->left);
        }
    }

    Key select(NodePtr x, int k) {
        if (x == nullptr) {
            return Key();
        }

        int rankK = rank(x->key);

        if (k > rankK) {
            return select(x->right, k);
        } else if (k < rankK) {
            return select(x->left, k);
        } else {
            return x->key;
        }
    }

    void inorder(vector<Key> &keys, NodePtr x) {
        if (x == nullptr) {
            return;
        }
        inorder(keys, x->left);
        keys.push_back(x->key);
        inorder(keys, x->right);
    }

    NodePtr deleteMin(NodePtr x) {
        if (x->left == nullptr) {
            return x->right;
        }

        x->left = deleteMin(x->left);

        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    Node* deleteMax(Node* x) {
        if (x->right == nullptr)
            return x->left;

        x->right = deleteMax(x->right);
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

    Key min(NodePtr x) {
        if (x == nullptr) {
            return nullptr;
        }

        while (x->left != nullptr) {
            x = x->left;
        }
        return x->key;
    }

    Key max(Node* x) {
        if (x == nullptr) {
            return nullptr;
        }

        while (x->right != nullptr) {
            x = x->right;
        }

        return x->key;
    }

    NodePtr deleteKey(NodePtr x, Key key) {
        if (x == nullptr) {
            return nullptr;
        }

        // Hibbard deletion
        // search for key
        if (key > x->key) {
            x->right = deleteKey(x->right, key);
        } else if (key < x->key) {
            x->left = deleteKey(x->left, key);
        } else {
            //no right child
            if (x->left == nullptr) {
                return x->right;
            }
            // no left child
            if (x->right == nullptr) {
                return x->left;
            }

            //have two children
            //use the min on the right subtree to replace
            NodePtr t = x;
            x = min(t->right);
            x->right = deleteMin(t->right);
            x->left = t->left;
        }

        // update count
        x->count = 1 + size(x->left) + size(x->right);
        return x;
    }

private:

    NodePtr root = nullptr;
};

int main()
{
    BST<int, int> map;
    map.put(1,4);
    map.put(2,4);
    map.put(3,4);
    map.put(4,4);
    map.put(5,4);

    map.select(4);
}



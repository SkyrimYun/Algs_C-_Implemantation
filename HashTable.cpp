#include <vector>

// Default hash function class
template <typename Key>
struct KeyHash
{
    unsigned long operator()(const Key &key) const
    {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

template <class Key, class Value, class F = KeyHash<Key>>
class separteChainHashMap
{
private:
    struct Node
    {
        Key key;
        Value val;
        Node *next;
        Node(k, v, n) : key(k), val(v), next(n) {}
    };
    int M = 97;
    vector<Node *> st(M);
    F hashFunc;

public:
    separteChainHashMap() {}
    Value get(Key key)
    {
        int i = hashFunc(key);
        for (Node *x = st[i]; x != nullptr; x = x->next)
        {
            if (x->key == key)
                return x->val;
        }
        return Value();
    }
    void put(Key key, Value val)
    {
        int i = hashFunc(key);
        for (Node *x = st[i]; x != nullptr; x = x->next)
        {
            if (x->key == key)
                x->val = val;
        }
        st[i] = new Node(key, val, st[i]);
    }
};

template <class Key, class Value, class F = KeyHash<Key>>
class linearProbHashMap
{
private:
    int M = 30001;
    vector<Value *> vals(M);
    vector<Key *> keys(M);
    F hashFunc;

public:
    linearProbHashMap() {}
    Value get(Key key)
    {
        for (int i = hashFunc(key); keys[i] != nullptr; i = (i + 1) % M)
        {
            if (keys[i] == key)
                return vals[i];
        }
        return Value();
    }
    void put(Key key, Value val)
    {
        for (int i = hashFunc(key); keys[i] != nullptr; i = (i + 1) % M)
        {
            if (keys[i] == key)
                break;
        }
        keys[i] = key;
        vals[i] = val;
    }
}
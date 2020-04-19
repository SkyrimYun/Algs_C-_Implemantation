#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//linked_list representation
template <typename T>
class linkListStack
{
private:
    struct Node
    {
        T item;
        Node *next;
        Node() : item(T()), next(nullptr){};
    };

    Node *first = nullptr;

public:
    linkListStack(){};

    void push(T item)
    {
        Node *oldfirst = first;
        first = new Node;
        first->item = item;
        first->next = oldfirst;
    }

    T pop()
    {
        if (first == nullptr)
            throw runtime_error("underflow!");
        T item = first->item;
        Node *oldFirst = first;
        first = first->next;
        delete oldFirst;
        return item;
    }

    bool isEmpty()
    {
        return first == nullptr;
    }

    ~linkListStack()
    {
        Node *next = nullptr;
        while (first != nullptr)
        {
            next = first;
            first = first->next;
            delete next;
        }
    }
};

//array implementation
template <typename T>
class arrayStack
{
private:
    T *s;
    int sz = 0;
    int capacity = 1;

public:
    arrayStack()
    {
        s = new T[capacity];
    }

    bool isEmpty()
    {
        return sz == 0;
    }

    void resize(int cap)
    {
        T *old = s;
        s = new T[cap];
        for (int i = 0; i < sz; i++)
        {
            s[i] = old[i];
        }
        delete[] old;
    }

    void push(T item)
    {
        if (capacity == sz)
        {
            resize(capacity * 2);
            capacity *= 2;
        }
        s[sz++] = item;
    }

    T pop()
    {
        if (sz <= 0)
            throw runtime_error("underflow!");
        T item = s[--sz];
        if (sz > 0 && sz == capacity / 4)
        {
            resize(capacity / 2);
            capacity /= 2;
        }
        return item;
    }

    ~arrayStack()
    {
        delete[] s;
    }
};

// link list implementated quene
template <class T>
class linkListQuene
{
private:
    struct Node
    {
        T item;
        Node *next;
        Node() : item(T()), next(nullptr){};
    };
    Node *first = nullptr;
    Node *last = nullptr;

public:
    linkListQuene() {}

    bool isEmpty()
    {
        return first == nullptr;
    }

    // add new item at q[tail].
    void enquene(T item)
    {
        Node *oldLast = last;
        last = new Node;
        last->item = item;
        last->next = nullptr;
        if (isEmpty())
            first = last;
        else
            oldLast->next = last;
    }

    // remove item from q[head].
    T dequene()
    {
        if (isEmpty())
            throw runtime_error("underflow!");
        T item = first->item;
        Node *oldFirst = first;
        first = first->next;
        if (isEmpty())
            last == nullptr;
        delete oldFirst;
        return item;
    }

    ~linkListQuene()
    {
        Node *oldFirst;
        while (!isEmpty())
        {
            oldFirst = first;
            first = first->next;
            delete oldFirst;
        }
    }
};

template <class T>
class arrayQuene
{
private:
    int sz = 0;
    int capacity = 1;
    int first = 0;
    T *s;

public:
    arrayQuene()
    {
        s = new T[capacity];
    }

    bool isEmpty()
    {
        return sz == 0;
    }

    void resize(int cap)
    {
        T *old = s;
        s = new T[cap];
        for (int i = 0; i < sz; i++)
        {
            s[i] = old[i + first];
        }
        first = 0;
        delete[] old;
    }

    void enquene(T item)
    {
        if (sz == capacity)
        {
            resize(2 * capacity);
            capacity *= 2;
        }
        s[sz++] = item;
    }

    T dequene()
    {
        if (isEmpty())
            throw runtime_error("underflow!");

        T item = s[first++];
        sz--;
        if (sz > 0 && sz == capacity / 4)
        {
            resize(capacity / 2);
            capacity /= 2;
        }
        return item;
    }

    ~arrayQuene()
    {
        delete[] s;
    }
};

int main()
try
{
    arrayQuene<string> st;
    ifstream ifs("tobe.txt");
    if (!ifs)
        throw runtime_error("cannot open file!");

    while (!ifs.eof())
    {
        string s;
        ifs >> s;
        st.enquene(s);
    }

    while (!st.isEmpty())
    {
        cout << st.dequene() << endl;
    }
}
catch (exception &e)
{
    cerr << e.what() << '\n';
}

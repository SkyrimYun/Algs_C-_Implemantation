#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

template <class T, class Comp>
class UnorderedMaxPQ
{
private:
    T *arr;
    Comp cmp;
    int size = 0;
    int capacity;

public:
    UnorderedMaxPQ(int cap, Comp compare)
    {
        capacity = cap;
        cmp = compare;
        arr = new T[capacity];
    }

    void insert(T v)
    {
        if (size == capacity)
            throw runtime_error("overflow!");
        arr[size++] = v;
    }

    T delMax()
    {
        if (size == 0)
            throw runtime_error("underflow!");
        int max = 0;
        for (int i = 0; i < size; i++)
        {
            if (cmp(arr[max], arr[i]))
                max = i;
        }
        swap(arr[max], arr[size - 1]);
        return arr[--size];
    }

    bool isEmpty()
    {
        return size == 0;
    }

    ~UnorderedMaxPQ()
    {
        delete[] arr;
    }
};

template <class T, class Comp>
class orderedMaxPQ
{
private:
    T *arr;
    Comp cmp;
    int size = 0;
    int capacity;

public:
    orderedMaxPQ(int cap, Comp compare)
    {
        capacity = cap;
        cmp = compare;
        arr = new T[capacity];
    }

    void insert(T v)
    {
        if (size == capacity)
            throw runtime_error("overflow!");
        int current = size;
        arr[size++] = v;

        for (int i = size - 2; i >= 0; i--)
        {
            if (cmp(arr[current], arr[i]))
            {
                swap(arr[i], arr[current]);
                current = i;
            }
        }
    }

    T delMax()
    {
        if (size == 0)
            throw runtime_error("underflow!");

        return arr[--size];
    }

    bool isEmpty()
    {
        return size == 0;
    }

    ~orderedMaxPQ()
    {
        delete[] arr;
    }
};

// max value is in arr[1]
// so real capacity is cap + 1
template <class T, class Comp>
class MaxPQ
{
private:
    T *arr;
    int capacity;
    int size = 0;
    Comp compare;

public:
    MaxPQ(int cap, Comp cmp)
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
            // j+1 needs <= size; thus j<size
            if (j < size && compare(arr[2 * k], arr[2 * k + 1]))
                j++;
            if (compare(arr[j], arr[k]))
                break;
            swap(arr[k], arr[j]);
            k = j;
        }
    };

    void insert(T item)
    {
        arr[++size] = item;
        swim(size);
    }

    T delMax()
    {
        T item = arr[1];
        swap(arr[1], arr[size--]);
        // prvent loitering
        arr[size + 1] = T();
        sink(1);

        return item;
    }

    ~MaxPQ()
    {
        delete[] arr;
    }
};

struct time
{
    int year;
    int month;
    int day;
    time(string s)
    {
        char c;
        stringstream ss(s);
        ss >> month;
        ss >> c;
        ss >> day;
        ss >> c;
        ss >> year;
    }
    time(){};
    bool operator>(time &t)
    {
        if (year > t.year)
            return true;
        else if (year == t.year)
        {
            if (month > t.month)
                return true;
            else if (month == t.month)
            {
                if (day > t.day)
                    return true;
            }
        }
        return false;
    }
};

struct Transaction
{
    string name;
    time t;
    double value;
    Transaction(){};
    Transaction(string s)
    {
        stringstream ss(s);
        ss >> name;
        string stime;
        ss >> stime;
        t = time(stime);
        ss >> value;
    }
};

ostream &operator<<(ostream &ost, Transaction item)
{
    ost << item.name << " " << item.t.year << "." << item.t.month << "." << item.t.day << " " << item.value;
    return ost;
}

struct cmpTrans
{
    int flag = -1;
    cmpTrans(){};
    cmpTrans(string s)
    {
        if (s == "compare by name")
            flag = 0;
        else if (s == "compare by time")
            flag = 1;
        else if (s == "compare by value")
            flag = 2;
        else
            throw logic_error("invalid argument!");
    }
    bool operator()(Transaction &t1, Transaction &t2)
    {
        switch (flag)
        {
        case 0:
            return t1.name < t2.name;
        case 1:
            return t2.t > t1.t;
        case 2:
            return t1.value < t2.value;
        default:
            return false;
        }
    }
};

int main()
try
{
    MaxPQ<Transaction, cmpTrans> pq(16, cmpTrans("compare by value"));
    ifstream ifs("tinyBatch.txt");
    if (!ifs)
        throw runtime_error("cannot open file!");
    string line;
    while (!ifs.eof())
    {
        getline(ifs, line);
        Transaction item(line);
        pq.insert(item);
        //cout << item << endl;
    }
    int i = 1;
    while (!pq.isEmpty())
    {
        cout << i << ": " << pq.delMax() << endl;
        i++;
    }
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
}

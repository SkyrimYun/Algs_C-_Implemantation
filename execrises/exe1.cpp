#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct goods
{
    int cost;
    int profit;
    int index;
};

struct cmp_profit
{
    bool operator()(const goods &goodA, const goods &goodB)
    {
        return goodA.profit > goodB.profit;
    }
};

bool still_can_buy(int money, vector<goods> &goodList)
{
    for (goods good : goodList)
    {
        if (good.cost < money)
            return true;
    }
    return false;
}

int main()
{
    vector<int> buy;
    vector<int> sell;
    string m;
    string n;
    getline(cin, m);
    getline(cin, n);
    stringstream ss(m);
    while (!ss.eof())
    {
        int n;
        char c;
        ss >> n;
        buy.push_back(n);
        ss >> c;
    }
    stringstream ss2(n);
    while (!ss2.eof())
    {
        int n;
        char c;
        ss2 >> n;
        sell.push_back(n);
        ss2 >> c;
    }

    int money;
    cin >> money;

    vector<goods> goodList;
    for (int i = 0; i < buy.size(); i++)
    {
        goods good;
        good.cost = buy[i];
        good.index = i;
        good.profit = sell[i] - buy[i];

        goodList.push_back(good);
    }
    sort(goodList.begin(), goodList.end(), cmp_profit());

    while (still_can_buy(money, goodList))
    {
        for (int i = 0; i < goodList.size(); i++)
        {
            if (money > goodList[i].cost)
            {
                money += goodList[i].profit;
                goodList.erase(goodList.begin() + i);
            }
        }
    }
    cout << money << endl;
    ;
}
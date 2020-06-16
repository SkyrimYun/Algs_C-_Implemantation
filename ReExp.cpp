#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

class Digraph
{
private:
    int vertex;
    int edge;
    vector<vector<int>> ADJ;

public:
    Digraph() {}
    Digraph(istream &ist)
    {
        ist >> vertex;
        ist >> edge;
        ADJ.resize(vertex);

        int v, w;
        int count = 0;
        while (!ist.eof())
        {
            ist >> v >> w;
            addEdge(v, w);
            count++;
        }
        if (count != edge)
            throw runtime_error("the input Edge number is wrong!");
    }
    Digraph(int v)
    {
        this->vertex = v;
        ADJ.resize(vertex);
    }

    // one way connection in directed graph
    void addEdge(int v, int w)
    {
        ADJ[v].push_back(w);
    }

    vector<int> adj(int v)
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

    Digraph reverse()
    {
        Digraph reverseG(vertex);
        for (int v = 0; v < vertex; v++)
        {
            for (int w : ADJ[v])
            {
                reverseG.addEdge(w, v);
            }
        }
        return reverseG;
    }
};

class DirectedDFS
{
private:
    // marked[v] = true if v connected to s
    vector<bool> marked;
    // edgeTo[v] = previous vertex on path from s to v
    vector<int> edgeTo;

    vector<int> s;

    void dfs(Digraph G, int v)
    {
        marked[v] = true;
        for (int w : G.adj(v))
        {
            if (!marked[w])
            {
                dfs(G, w);
                edgeTo[w] = v;
            }
        }
    }

public:
    DirectedDFS(Digraph G, int s)
    {
        marked = vector<bool>(G.V());
        edgeTo = vector<int>(G.V());
        this->s.push_back(s);
        dfs(G, this->s[0]);
    }

    DirectedDFS(Digraph G, vector<int> s)
    {
        marked = vector<bool>(G.V());
        edgeTo = vector<int>(G.V());
        for (int ss : s)
            dfs(G, ss);
    }

    bool hasPathTo(int v)
    {
        return marked[v];
    }
};

class NFA
{
private:
    string re;
    int M;
    Digraph G;

public:
    NFA(string reExp)
    {
        re = reExp;
        M = re.size();
        G = buildEpsilonTransitionDigraph();
    }

    bool recogize(string txt)
    {
        vector<int> pc;
        DirectedDFS dfs(G, 0);
        for (int v = 0; v < G.V(); v++)
        {
            if (dfs.hasPathTo(v))
                pc.push_back(v);
        }

        for (int i = 0; i < txt.size(); i++)
        {
            vector<int> match;
            for (int j : pc)
            {
                if (j == M)
                    continue;
                if (re[j] == txt[i] || re[j] == '.')
                    match.push_back(j + 1);
            }

            dfs = DirectedDFS(G, match);
            pc.clear();
            for (int v = 0; v < G.V(); v++)
            {
                if (dfs.hasPathTo(v))
                    pc.push_back(v);
            }
        }

        for (int v : pc)
        {
            if (v == M)
                return true;
        }
        return false;
    }

    Digraph buildEpsilonTransitionDigraph()
    {
        Digraph G = Digraph(M + 1);
        stack<int> ops;

        for (int i = 0; i < M; i++)
        {
            int lp = i;

            if (re[i] == '(' || re[i] == '|')
                ops.push(i);
            else if (re[i] == ')')
            {
                int or = ops.top();
                ops.pop();
                if (re[or] == '|')
                {
                    lp = ops.top();
                    ops.pop();
                    G.addEdge(lp, or +1);
                    G.addEdge(lp, i);
                }
                else
                    lp = or ;
            }

            if (re[i + 1] == '*' && i < M - 1)
            {
                G.addEdge(i, i + 1);
                G.addEdge(i + 1, i);
            }

            if (re[i] == '(' || re[i] == '*' || re[i] == ')')
                G.addEdge(i, i + 1);
        }
        return G;
    }
};

#include <iostream>
#include <vector>
#include <stack>

#define UNVISITED -1

using namespace std;

// A class that represents an directed graph
class Graph
{
    int V; // No. of vertices
    vector<int> *adj;

public:
    Graph(int V); // Constructor
    void addEdge(int v, int w);
    void first_dfs(int n, int ids[], int low[], bool onStack[], stack<int> *pilha);
    void second_dfs(int n, int dp[], bool visited[]);
    int *SCC();
    int getV();
    int getLongestPath();
    vector<int> getAdj(int n);
};

int Graph::getV()
{
    return V;
}

vector<int> Graph::getAdj(int n)
{
    return adj[n];
}

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::first_dfs(int n, int ids[], int low[], bool onStack[], stack<int> *pilha)
{
    pilha->push(n);
    onStack[n] = true;
    static int id = 0;
    ids[n] = low[n] = id++;

    vector<int>::iterator i;
    
    for (i = adj[n].begin(); i != adj[n].end(); ++i)
    {

        if (ids[*i] == UNVISITED)
        {
            first_dfs(*i, ids, low, onStack, pilha);
            low[n] = min(low[n], low[*i]);
        }

        else
        {
            if (onStack[*i] == true)
            {
                low[n] = min(low[n], ids[*i]);
            }
        }
    }

    if (ids[n] == low[n])
    {
        while (!pilha->empty())
        {
            int v = pilha->top();
            pilha->pop();
            onStack[v] = false;
            low[v] = ids[n];
            if (v == n)
            {
                break;
            }
        }
    }
}

int *Graph::SCC()
{
    int *ids = new int[V];
    int *low = new int[V];
    bool *onStack = new bool[V];
    stack<int> *pilha = new stack<int>();

    for (int i = 0; i < V; i++)
    {
        ids[i] = UNVISITED;
        low[i] = UNVISITED;
        onStack[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        if (ids[i] == UNVISITED)
            first_dfs(i, ids, low, onStack, pilha);
    }

    return low;
}

Graph newGraph(int low[], Graph g)
{
    Graph ret(g.getV());

    for (int i = 0; i < g.getV(); i++)
    {
        vector<int> adj = g.getAdj(i);

        vector<int>::iterator j;

        for (j = adj.begin(); j != adj.end(); ++j)
        {
            if (low[i] != low[*j])
                ret.addEdge(low[i], low[*j]);
        }
    }

    return ret;
}

void Graph::second_dfs(int n, int dp[], bool visited[])
{
    visited[n] = true;
    vector<int>::iterator i;

    for (i = adj[n].begin(); i != adj[n].end(); i++)
    {

        if (!visited[*i])
            second_dfs(*i, dp, visited);

        dp[n] = max(dp[n], 1 + dp[*i]);
    }
}

int Graph::getLongestPath()
{
    int *dp = new int[V];
    bool *visited = new bool[V];

    for (int i = 0; i < V; i++)
    {
        dp[i] = 0;
        visited[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            second_dfs(i, dp, visited);
    }

    int result = 0;

    for (int i = 0; i < V; i++)
    {
        result = max(result, dp[i]);
    }

    return result;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m;

    cin >> n >> m;

    Graph g(n);
    int *low;

    for (int i = 0; i < m; i++)
    {
        int a, b;

        cin >> a >> b;

        g.addEdge(a - 1, b - 1);
    }

    low = g.SCC();

    Graph DAG = newGraph(low, g);

    cout << DAG.getLongestPath() << endl;

    return 0;
}
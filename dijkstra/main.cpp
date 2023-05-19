#include <bits/stdc++.h>

using namespace std;

void dijkstra(vector<vector<int>> adj_list, int n, int **pesos, int v, int w)
{
    for (int i = 0; i < n; i++)
    {
        cout << "v" << i << ":";

        for (int j = 0; j < adj_list[i].size(); j++)
        {
            cout << " v" << adj_list[i][j];
        }

        cout << " vizinhos\n";

    }

    
    cout << "   ";
    for (int i = 0; i < n; i++)
        cout << " v" << i + 1;

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "v" << i + 1 << ": ";

        for (int j = 0; j < n; j++)
        {
            if (pesos[i][j] == INT_MAX)
            {
                cout << "-1 ";
            }
            else
            {
                cout << pesos[i][j] << " ";
            }

        }

        cout << endl;

    }

    vector<int> dist(n);
    vector<int> prev(n);
    vector<int> visited(n);

    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = 0;
        visited[i] = false;
    }
    
    dist[0] = 0;

    priority_queue <int, vector<int>, greater<int> > h;
    h.push(v);

    vector <int> print;

    while (!h.empty())
    {
        int u = h.top();
        h.pop();
        visited[u] = true;

        for (int i = 0; i < adj_list[u].size(); i++)
        {
            int k = adj_list[u][i];

            if (dist[k] > dist[u] + pesos[u][k])
            {
                dist[k] = dist[u] + pesos[u][k];
                prev[k] = u;
                h.push(k);
            }
        }
        
    }


    
}

int main(int argc, char **argv)
{
    if (argc < 1)
        return 1;

    ifstream arquivo;
    arquivo.open(argv[1]);

    int n, m;
    arquivo >> n >> m;

    vector<vector<int>> adj_list(n);

    int **pesos = new int *[n];

    for (int i = 0; i < n; i++)
        pesos[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            pesos[i][j] = INT_MAX;

    for (int i = 0; i < n; i++)
        adj_list[i] = vector<int>();

    for (int i = 0; i < m; i++)
    {
        int v1, v2, p;
        arquivo >> v1 >> v2 >> p;
        pesos[v1 - 1][v2 - 1] = p;
        pesos[v2 - 1][v1 - 1] = p;
        adj_list[v1 - 1].push_back(v2 - 1);
        adj_list[v2 - 1].push_back(v1 - 1);
    }

    dijkstra(adj_list, n, pesos, 0, n - 1);

    ifstream file;
    string s ("test/test.mtx");
    cout << s << endl;
    file.open(s);

    return 0;
}
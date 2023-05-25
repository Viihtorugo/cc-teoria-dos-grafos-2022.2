#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 1)
        return 1;

    ifstream arquivo;
    arquivo.open(argv[1]);

    int n, m;
    arquivo >> n >> m;

    vector <vector <pair<int,int>>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int v, w, p;
        arquivo >> v >> w >> p;
        graph[w - 1].push_back( {v - 1, p} );
        graph[v - 1].push_back( {w - 1, p} );
    }
    
    priority_queue<pair<int, int>> pq;
    vector <int> dist (n, INT_MAX);

    dist[0] = 0;
    pq.push ( {0, 0} );

    while (pq.size() > 0)
    {
        int v = pq.top().second;
        int custo = -pq.top().first;

        pq.pop();

        // remover os casos de vertices visitados com menor custo!
        if (custo != dist[v]) continue;

        for (auto edge: graph[v])
        {
            int u = edge.first;
            int peso = edge.second;

            if (dist[u] > dist[v] + peso)
            {
                dist[u] = dist[v] + peso;
                pq.push ({-dist[u], u});
            }
        }
    }

    for (int i = 0; i < dist.size(); i++)
        cout << i + 1 << ":" << dist[i] << " ";

    cout << endl;

    return 0;
}
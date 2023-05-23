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

    vector<vector<pair<int, int>>> graph(n);

    for (int i = 0; i < m; i++)
    {
        int v, w, p;

        arquivo >> v >> w >> p;

        graph[v - 1].push_back({w - 1, p});
        graph[w - 1].push_back({v - 1, p});
    }

    priority_queue < pair <int, int> > pq;

    vector<int> agm(n, -1);

    vector<bool> visited(n, false);
    vector<int> pesos(n, INT_MAX);

    // origem -> pesos[origem]
    pesos[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        pair<int, int> edge = pq.top();
        pq.pop();
        visited[edge.second] = true;

        for (pair<int, int> edges : graph[edge.second])
        {
            if (visited[edges.first] == false && edges.second < pesos[edges.first])
            {
                pesos[edges.first] = edges.second;
                pq.push({-edges.second, edges.first});
                agm[edges.first] = edge.second;
            }
        }
    }

    int soma = 0;

    for (int peso : pesos)
        soma += peso;

    cout << soma << endl;

    // criando o grafo agm ordenado!
    vector< vector <int> > graph_agm(n);

    for (int i = 0; i < n; i++)
    {
        if (agm[i] != -1)
        {
            if (i > agm[i])
            {
                graph_agm[agm[i]].push_back(i);
            }
            else
            {
                graph_agm[i].push_back(agm[i]);
            }
        }
    }

    for (int i = 0; i < graph_agm.size(); i++)
    {
        if (graph_agm[i].size() > 0)
        {
            for (int v : graph_agm[i])
            {
                cout << "(" << i + 1 << "," << v + 1 << ")";
            }
        }
    }

    cout << endl;

    return 0;
}
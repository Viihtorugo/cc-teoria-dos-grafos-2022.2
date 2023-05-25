#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int v;
    int w;
    int peso;
};

int find(int u, vector<int> &pai)
{
    return (pai[u] != u) ? find(pai[u], pai): pai[u];
}

void union_tree(int u, int v, vector<int> &pai, vector<int> &rank)
{
    int orig = find(u, pai);
    int dest = find(v, pai);

    if (rank[orig] >= rank[dest])
    {
        pai[dest] = orig;
        
        if (rank[orig] == rank[dest])
        {
            rank[orig]++;
        }
    }
    else
    {
        pai[orig] = dest;
    }
}

static bool parametro_peso(const edge &e1, const edge &e2)
{
    return e1.peso < e2.peso;
}

static bool parametro_sort_agm(const edge &e1, const edge &e2)
{
    return (e1.v == e2.v) ? e1.w < e2.w : e1.v < e2.v;
}

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

    arquivo.close();

    vector<edge> edges(n);

    for (int i = 0; i < n; i++)
    {
        for (auto ed : graph[i])
        {
            if (ed.first < i)
                continue;

            edge e;
            e.v = i;
            e.w = ed.first;
            e.peso = ed.second;
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), parametro_peso);

    vector<int> pai(n);
    vector<int> rank(n, 0);
    vector<edge> agm;

    for (int i = 0; i < n; i++)
        pai[i] = i;

    for (int i = 0; i < edges.size(); i++)
    {
        int orig = edges[i].v;
        int dest = edges[i].w;
        
        if (find(orig, pai) != find(dest, pai))
        {
            union_tree(orig, dest, pai, rank);
            agm.push_back(edges[i]);
        }
    }

    sort(agm.begin(), agm.end(), parametro_sort_agm);

    int soma = 0;
    for (auto edge: agm)
    {
        cout << "(" << edge.v + 1 << "," << edge.w + 1 << ") ";    
        soma += edge.peso;
    }

    cout << endl;

    cout << soma << endl;

    return 0;
}
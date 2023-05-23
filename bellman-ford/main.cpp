#include <bits/stdc++.h>

using namespace std;

int find_parent (int x, vector <int> pai)
{
    int aux = x;

    while (pai[aux] != aux)
        aux = pai[aux];
    
    return aux;
}

int main(int argc, char **argv)
{
    if (argc < 1)
        return 1;

    ifstream arquivo;
    arquivo.open(argv[1]);

    int n, m;

    arquivo >> n >> m;

    vector<vector < pair<int, int> > > graph(n);
    vector <int> pai (n, -1);
    vector <int> pesos (n);

    for (int i = 0; i < m; i++)
    {
        int v, w, p;

        arquivo >> v >> w >> p;

        graph[v - 1].push_back({w - 1, p});
        graph[w - 1].push_back({v - 1, p});
    }

    for (int i = 0; i < n; i++)
    {
        pai[i] = i;

        for (pair <int, int> edges: graph[i])
        {
            if (find_parent(i, pai) != find_parent(edges.first, pai))
            {
                pai[i] = edges.first;
            }
        }
        
    }
    
    for (int i = 0; i < n; i++)
    {
        cout << "(" << i + 1 << "," << pai[i] + 1 << ")";
    }
    
    cout << endl;

    return 0;
}
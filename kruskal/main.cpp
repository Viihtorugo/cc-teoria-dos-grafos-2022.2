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
    int arq_in = 0, arq_out = 0;
    bool ord_agm = false, set_arq = false, output = false;
    ifstream arquivo;

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-f"))
        {
            set_arq = true;
            arq_in = i + 1;
        }

        if (!strcmp(argv[i], "-s"))
            ord_agm = true;

        if (!strcmp(argv[i], "-o"))
        {
            arq_out = i + 1;
            output = true;
        }

        if (!strcmp(argv[i], "-h"))
        {
            cout << "\n---- HELP ---- " << endl;
            cout << "\n-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
            cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
            cout << "-s : mostra a solução (em ordem crescente)" << endl;
        }
    }

    if (set_arq)
        arquivo.open(argv[arq_in]);

    if (arquivo.fail() == 1)
    {
        cout << "O arquivo não foi encontrado, digite o nome do arquivo após o -f!\n\nExemplo: ./bin -f arquivo.txt\n\n";
        return 1;
    }

    // input o grafo com valores do arquivo!
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

    arquivo.close(); //finalizando os arquivos

    //Iniciando o algoritmo de kruskal
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
    //Finalizando o algoritmo de kruskal

    //calculando o custo
    int soma = 0;

    for (auto edge: agm)
        soma += edge.peso;

    cout << soma << endl;

    //saida ordenada
    if (ord_agm)
    {
        sort(agm.begin(), agm.end(), parametro_sort_agm);
        
        for (auto edge: agm)
            cout << "(" << edge.v + 1 << "," << edge.w + 1 << ") ";    
        
        cout << endl;
    }
    
    //criando o arquivo de saida
    if (output)
    {
        ofstream out_file;
        out_file.open(argv[arq_out]);

        if (out_file.fail() == 1)
        {
            cout << "Erro ao criar o arquivo, digite o nome do arquivo após -o!\n\nExemplo: ./bin -o arquivo.txt\n\n";
            return 1;
        }
        
        out_file << "agm: ";

        for (auto edge: agm)
            out_file << "(" << edge.v + 1 << "," << edge.w + 1 << ") "; 
        
        out_file << endl << "Custo: " << soma << endl;
    }

    return 0;
}
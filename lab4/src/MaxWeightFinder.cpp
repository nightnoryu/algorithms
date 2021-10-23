#include "MaxWeightFinder.h"

int MaxWeightFinder::findPathWithMaxWeight(const Graph& graph, int from, int to)
{
    std::vector<int> D(graph.size(), -1);
    std::vector<int> C(graph.size(), -1);

    C[from] = INT_MAX;
    int i = from;
    do
    {
        for (int j = 0; j < graph.size(); ++j)
        {
            if (graph[i][j] != INT_MAX)
            {
                auto M = std::min(C[i], graph[i][j]);
                auto oldD = D[j];
                D[j] = std::max(M, D[j]);
            }
        }

        auto maxD = std::max_element(D.begin(), D.end());
        if (maxD != D.end())
        {
            int k = std::distance(D.begin(), maxD);
            C[k] = *maxD;
            D[k] = -1;
            i = k;
        }
        else
        {
            throw std::logic_error("there are no way");
        }
    } while (C[to] == -1);

    return C[to];
}

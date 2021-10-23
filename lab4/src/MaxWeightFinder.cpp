#include "MaxWeightFinder.h"

std::vector<PathWithWeight> MaxWeightFinder::findPathWithMaxWeight(const Graph& graph, int from, int to)
{
    std::vector<int> D(graph.size(), -1);
    std::vector<int> C(graph.size(), -1);
    std::vector<int> nodes;

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
                if (D[j] > oldD)
                {
                    nodes.push_back(i);
                }
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
            break; // No way
        }
    } while (C[to] == -1);

    std::cout << C[to] << std::endl;

    return {};
}

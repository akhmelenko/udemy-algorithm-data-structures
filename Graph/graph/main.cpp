
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>

class MatrixGraph
{
protected:
    int size;
    int **G;
    int *visited;

public:
    MatrixGraph(int size) : size(size)
    {
        G = new int *[size];
        for (int i = 0; i < size; i++)
            G[i] = new int[size];

        visited = new int[size];
    }
    virtual ~MatrixGraph()
    {
        for (int i = 0; i < size; i++)
            delete[] G[i];

        delete[] G;
    }

    bool InsertEdge(int vertA, int vertB)
    {
        if (vertA > size || vertB > size)
            return false;
        G[vertA][vertB] = 1;
        G[vertB][vertA] = 1;
        return true;
    }

    bool DeleteEdge(int vertA, int vertB)
    {
        if (vertA > size || vertB > size)
            return false;
        G[vertA][vertB] = 0;
        G[vertB][vertA] = 0;
    }

    void DisplayMatrix()
    {
        std::cout << "[ ";
        for (int i = 0; i < size; i++)
        {
            std::cout << "\n";
            for (int j = 0; j < size; j++)
                std::cout << G[i][j] << " ";
        }
        std::cout << "]\n";
    }

    // Breadth first search
    bool BFS(int start)
    {
        if (start > size)
            return false;
        int visited[size]; // = {0};
        memset(visited, 0, sizeof(visited));
        std::cout << "[ ";
        visited[start] = 1;
        std::queue<int> q;
        q.push(start);
        std::cout << start << " ";
        while (q.size())
        {
            for (int i = 0; i < size; i++)
            {
                if (G[q.front()][i] != 0 && visited[i] == 0)
                {
                    visited[i] = 1;
                    q.push(i);
                    std::cout << i << " ";
                }
            }
            if (q.size())
                q.pop();
        }
        std::cout << "]\n";
        return true;
    }

    void DFSRec(int vertex)
    {
        visited[vertex] = 1;
        std::cout << vertex << " ";
        for (int i = 0; i < size; i++)
        {
            if (G[vertex][i] != 0 && visited[i] == 0)
            {
                DFSRec(i);
            }
        }
    }

    // depth first search
    bool DFS()
    {
        if (!size)
            return false;
        // clear table
        memset(visited, 0, sizeof(visited));
        std::cout << "[ ";
        // start from 0
        DFSRec(0);
        std::cout << "]\n";
        return true;
    }
};

class SpanCostGraph : public MatrixGraph
{
private:
public:
    SpanCostGraph(int size) : MatrixGraph(size) {}
    ~SpanCostGraph() {}

    bool InsertEdge(int vertA, int vertB, int cost)
    {
        if (vertA > size || vertB > size)
            return false;
        G[vertA][vertB] = cost;
        G[vertB][vertA] = cost;
        return true;
    }

    void CoastMinimalCostTraverseRec(int vertex)
    {
        std::cout << vertex;
        visited[vertex] = 1;
        // find minimal not visited
        int min = INT_MAX;
        int minCostInd = -1;
        for (int i = 0; i < size; i++)
        {
            if (G[vertex][i] > 0 && visited[i] == 0 && G[vertex][i] < min)
            {
                min = G[vertex][i];
                minCostInd = i;
            }
        }
        if (minCostInd == -1)
            return;
        std::cout << "<" << G[vertex][minCostInd] << ">";
        CoastMinimalCostTraverseRec(minCostInd);
    }

    // !!! traverse allow only for not separated graph
    bool CoastMinimalCostTraverse()
    {
        if (!size)
            return false;
        memset(visited, 0, sizeof(int) * size);
        std::cout << "[";
        CoastMinimalCostTraverseRec(0);
        std::cout << "]\n";
        return true;
    }

    void KruskalTraverseRec(int lastCost)
    {
        // search minimal cost age
        int minAgeCost = INT_MAX;
        int minAgeIndFirst = -1;
        int minAgeIndSecond = -1;
        for (int i = 0; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                int currentCost = G[i][j];
                if (currentCost != 0 && currentCost <= minAgeCost && currentCost > lastCost && (visited[i] == 0 || visited[j] == 0))
                {
                    if (visited[i] == 0)
                        minAgeIndFirst = i;
                    if (visited[j] == 0)
                        minAgeIndSecond = j;
                    minAgeCost = currentCost;
                }
            }
        }
        if (minAgeCost == INT_MAX)
            return;
        // process vertexes
        if (minAgeIndFirst != -1)
        {
            visited[minAgeIndFirst] = 1;
            std::cout << " v=" << minAgeIndFirst << " ";
        }
        if (minAgeIndSecond != -1)
        {
            visited[minAgeIndSecond] = 1;
            std::cout << " v=" << minAgeIndSecond << " ";
        }
        std::cout << " c=" << minAgeCost << " ";
        KruskalTraverseRec(minAgeCost);
    }

    // traverse allow for not separated graph
    // taraverse by ages (from minimal cost)
    bool KruskalTraverse()
    {
        if (!size)
            return false;
        memset(visited, 0, sizeof(int) * size);
        std::cout << "[";
        // start traverse
        KruskalTraverseRec(0);
        std::cout << "]\n";
        return true;
    }
};

class CompactGraph
{
protected:
    int vertexNum = 0;
    int *g = nullptr;
    int maxTableSize;

public:
    CompactGraph(int size) : vertexNum(size)
    {
        if (!size)
            return;
        // init max table size = vert num + ages num + 1
        maxTableSize = vertexNum + size * size + 1;
        // table allocate
        g = new int[maxTableSize];
        // clear vertexes
        for (int i = 0; i < vertexNum; i++)
            g[i] = 0;
        // set end of vertexes sentinel = table size
        g[vertexNum] = vertexNum + 1;
    }
    virtual ~CompactGraph()
    {
        delete[] g;
    }

    void InsertOnePart(int first, int second)
    {
        // search first element index
        int ind = first;
        while (g[ind] == 0 && ind <= vertexNum)
            ind++;
        ind = g[ind];
        // insert
        if (g[first] == 0)
            g[first] = ind;
        // shift all interconnections data after ind
        for (int i = g[vertexNum] - 1; i > ind; i--)
            g[i] = g[i - 1];
        // increment pointers after first until sentinel
        for (int i = first + 1; i <= vertexNum; i++)
        {
            if (g[i] > 0)
                g[i]++;
        }
        // insert new interconnect
        g[ind] = second;
    }

    void InsertEdge(int first, int second)
    {
        if (first >= vertexNum || second >= vertexNum)
            return;
        // search first insert index
        InsertOnePart(first, second);
        InsertOnePart(second, first);
    }

    bool DeleteOnePart(int first, int second)
    {
        // search first element index
        if (!g[first])
            return false;
        // search stop search interval
        int ind = first + 1;
        while (g[ind] == 0)
            ind++;
        int stopSearchInd = g[ind];
        // search start search interval
        ind = g[first];
        while (ind < g[vertexNum] && g[ind] != second)
            ind++;
        if (ind == g[vertexNum])
            return false;
        // detect exact index
        for (int i = ind; i < stopSearchInd; i++)
            if (g[i] == second)
            {
                ind = i;
                break;
            }
        // shift connections
        for (int i = ind; i < g[vertexNum] - 1; i++)
            g[i] = g[i + 1];
        // check for nulling first pointer
        if (g[first] + 1 == g[first + 1])
            g[first] = 0;
        // decrement pointers from first + 1
        for (int i = first + 1; i <= vertexNum; i++)
            if (g[i] != 0)
                g[i]--;
    }

    void DeleteEdge(int first, int second)
    {
        if (first >= vertexNum || second >= vertexNum)
            return;
        // search first insert index
        DeleteOnePart(first, second);
        DeleteOnePart(second, first);
    }

    void Display()
    {
        if (!g)
            return;
        std::cout << "[ ";
        for (int i = 0; i < g[vertexNum]; i++)
        {
            if (i == vertexNum)
                std::cout << "<" << g[i] << "> ";
            else
                std::cout << g[i] << " ";
        }
        std::cout << "]\n";
    }
};

class AdjacentGraph
{
protected:
    struct Node
    {
        int val;
        Node *next;
    };

protected:
    Node **g;
    int size;

public:
    AdjacentGraph(int size) : size(size)
    {
        if (!size)
            return;
        g = new Node *[size];
        for (int i = 0; i < size; i++)
            g[i] = nullptr;
    }
    ~AdjacentGraph()
    {
        for (int i = 0; i < size; i++)
            delete g[i];
        delete g;
    }

    bool InsertEdgeOnePart(int first, int second)
    {
        // insert to first
        Node *node = g[first];
        if (!node)
        {
            node = new Node;
            node->val = second;
            node->next = nullptr;
            g[first] = node;
            return true;
        }
        Node *prev = node;
        while (node)
        {
            if (node->val == second)
                return false;
            prev = node;
            node = node->next;
        }
        prev->next = new Node;
        prev->next->val = second;
        prev->next->next = nullptr;
        return true;
    }

    bool InsertEdge(int first, int second)
    {
        if (first >= size || second >= size || first < 0 || second < 0)
            return false;
        return InsertEdgeOnePart(first, second) && InsertEdgeOnePart(second, first);
    }

    bool DeleteEdgeOnePart(int first, int second)
    {
        // delete from first
        if (!g[first])
            return false;
        // first memeber
        if (g[first]->val == second)
        {
            Node *temp = g[first]->next;
            delete g[first];
            g[first] = temp;
            return true;
        }
        // not first member
        Node *node = g[first];
        Node *prev = node;
        while (node)
        {
            if (node->val == second)
            {
                prev->next = node->next;
                delete node;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }

    bool DeleteEdge(int first, int second)
    {
        if (first >= size || second >= size || first < 0 || second < 0)
            return false;
        return DeleteEdgeOnePart(first, second) && DeleteEdgeOnePart(second, first);
    }

    void Display()
    {
        if (!g)
            return;
        std::cout << "[ ";
        for (int i = 0; i < size; i++)
        {
            Node *node = g[i];
            if (!node)
                std::cout << "NULL";
            while (node)
            {
                std::cout << node->val << " ";
                node = node->next;
            }
            std::cout << "\n";
        }
        std::cout << "]\n";
    }
};

int main()
{
    MatrixGraph mg(4);
    mg.InsertEdge(0, 1);
    mg.InsertEdge(0, 2);
    mg.InsertEdge(0, 3);
    mg.InsertEdge(2, 3);
    mg.DisplayMatrix();
    mg.BFS(3);
    mg.DFS();

    SpanCostGraph spg(7);
    spg.InsertEdge(0, 5, 5);
    spg.InsertEdge(0, 1, 25);
    spg.InsertEdge(5, 4, 18);
    spg.InsertEdge(4, 6, 16);
    spg.InsertEdge(4, 3, 12);
    spg.InsertEdge(3, 2, 10);
    spg.InsertEdge(3, 6, 11);
    spg.InsertEdge(2, 1, 9);
    spg.InsertEdge(1, 6, 6);
    spg.DisplayMatrix();
    spg.BFS(3);
    spg.DFS();
    spg.CoastMinimalCostTraverse();
    spg.KruskalTraverse();

    // std::cout << "\n =CG:\n";
    // CompactGraph cg(4);
    // cg.Display();
    // cg.InsertEdge(0, 1);
    // cg.Display();
    // cg.InsertEdge(1, 2);
    // cg.Display();
    // cg.InsertEdge(2, 3);
    // cg.Display();
    // cg.InsertEdge(0, 2);
    // cg.Display();
    // cg.DeleteEdge(2, 3);
    // cg.Display();

    std::cout << "\n =AG:\n";
    AdjacentGraph ag(4);
    ag.InsertEdge(0, 1);
    ag.Display();
    ag.InsertEdge(2, 3);
    ag.Display();
    ag.InsertEdge(2, 0);
    ag.Display();

    ag.DeleteEdge(0, 1);
    ag.Display();
    ag.DeleteEdge(2, 3);
    ag.Display();
    ag.DeleteEdge(2, 0);
    ag.Display();

    return 0;
}
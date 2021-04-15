#include <iostream>
#include <vector>

using namespace std;

class Graph {
    struct Edge {
        int fromNode;
        int toNode;
        int weight;
    };

    vector<int> adjacencyList[40000];
    vector<Edge> edgeList;

    int nodeCount;

public:
    Graph() {
        nodeCount = -1;
    }

    void addEdge(int node1, int node2, int weight) {
        adjacencyList[node1].push_back(node2);
        adjacencyList[node2].push_back(node1);
        if (nodeCount < max(node1, node2))nodeCount = max(node1, node2);
        edgeList.push_back({node1, node2, weight});
    }

    void printAdjacencyList() {
        cout << "Adjacency list:\n";
        for (int i = 0; i <= nodeCount; i++) {
            cout << i << ": ";
            for (int j = 0; j < adjacencyList[i].size(); j++) {
                cout << adjacencyList[i][j] << " -> ";
            }
            cout << "end\n";
        }
    }

    static int compareEdge(const void *inputItem1, const void *inputItem2) {
        Edge edge1 = *((Edge *) inputItem1);
        Edge edge2 = *((Edge *) inputItem2);
        if (edge1.weight > edge2.weight) {
            return 1;
        } else if (edge1.weight < edge2.weight) {
            return -1;
        } else {
            if (edge1.fromNode > edge2.fromNode) {
                return 1;
            } else if (edge1.fromNode < edge2.fromNode) {
                return -1;
            }
            if (edge1.toNode > edge2.toNode) {
                return 1;
            } else if (edge1.toNode < edge2.toNode) {
                return -1;
            }
            return 0;
        }
    }

    void sortEdge() {
        qsort(&edgeList[0], edgeList.size(), sizeof(Edge), Graph::compareEdge);
    }

    void unionSet(vector<int> &relations, int dest, int org) {
        if (dest > org)swap(dest, org);
        if (relations[dest] != -1) {
            unionSet(relations, relations[dest], org);
        } else {
            relations[org] = dest;
        }
    }

    int findLeader(vector<int> &relations, int node) {
        if (relations[node] == -1) { return node; }
        findLeader(relations, relations[node]);
    }

    void printMinSpanTree() {
        vector<int> relationTable;
        for (int i = 0; i <= nodeCount; i++)relationTable.push_back(-1);
        cout << "minimum spanning tree:\n";
        int hasPrintedCount = 0;
        int costSum = 0;
        for (int i = 0; i < edgeList.size(); i++) {
            if (hasPrintedCount == nodeCount)break;
            if (findLeader(relationTable, edgeList[i].fromNode) == findLeader(relationTable, edgeList[i].toNode)) {
                continue;
            }
            unionSet(relationTable, findLeader(relationTable, edgeList[i].fromNode),
                     findLeader(relationTable, edgeList[i].toNode));
            cout << hasPrintedCount + 1 << ": " << "<" << edgeList[i].fromNode << "," << edgeList[i].toNode << ">"
                 << endl;
            costSum += edgeList[i].weight;
            hasPrintedCount += 1;
        }
        cout << "\nThe cost of minimum spanning tree: " << costSum << endl;
    }
};

int main() {
    Graph graph;
    int inputNode1, inputNode2, inputWeight;
    while (cin >> inputNode1 >> inputNode2 >> inputWeight) {
        graph.addEdge(inputNode1, inputNode2, inputWeight);
    }
    graph.printAdjacencyList();
    graph.sortEdge();
    cout << endl;
    graph.printMinSpanTree();
}
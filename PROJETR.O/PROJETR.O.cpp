#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

const long long INF = numeric_limits<long long>::max();

struct Edge {
    int source, destination;
    long long weight;
};

void printShortestPath(int source, int destination, const vector<int>& predecessor) {
    cout << "Plus court chemin de " << source << " à " << destination << " : ";
    int current = destination;
    vector<int> path;
    while (current != -1) {
        path.push_back(current);
        current = predecessor[current];
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i];
        if (i != 0) cout << " -> ";
    }
    cout << endl;
}

void bellmanFord(vector<Edge>& edges, int numVertices, int source, int destinationVertex) {
    vector<long long> distance(numVertices, INF);
    vector<int> predecessor(numVertices, -1);

    distance[source] = 0;
    bool hasNegativeCycle = false;

    // Itération principale de l'algorithme de Bellman-Ford
    for (int k = 1; k <= numVertices - 1; ++k) {
        for (const Edge& edge : edges) {
            if (distance[edge.source] < INF && distance[edge.destination] > distance[edge.source] + edge.weight) {
                distance[edge.destination] = distance[edge.source] + edge.weight;
                predecessor[edge.destination] = edge.source;

            }
        }
    }

    // Vérification des circuits absorbants
    for (const Edge& edge : edges) {
        if (distance[edge.source] < INF && distance[edge.destination] > distance[edge.source] + edge.weight) {
            // Un circuit absorbant a été trouvé
            hasNegativeCycle = true;
            break;
        }
    }

    // Affichage des résultats en fonction de la présence d'un circuit absorbant
    if (hasNegativeCycle) {
        cout << "Le graphe contient un circuit absorbant." << endl;
    }
    else {
        // Vérification de l'existence d'un chemin jusqu'à la destination
        if (distance[destinationVertex] == INF) {
            cout << "Il n'existe pas de chemin entre le sommet source et le sommet destination." << endl;
        }
        else {
            // Affichage du plus court chemin et de son poids
            printShortestPath(source, destinationVertex, predecessor);
            cout << "Poids du plus court chemin : " << distance[destinationVertex] << endl;
        }
    }
}

int main() {
    ifstream inputFile("dohaa.txt");
    if (!inputFile.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
        return 1;
    }

    int numVertices;
    inputFile >> numVertices;

    vector<Edge> edges;
    int source, destination;
    long long weight;

    while (inputFile >> source >> destination >> weight) {
        edges.push_back({ source, destination, weight });
    }

    inputFile.close();

    int sourceVertex = 2;
    int destinationVertex = 4;

    bellmanFord(edges, numVertices, sourceVertex, destinationVertex);

    return 0;
}

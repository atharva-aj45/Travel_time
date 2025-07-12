#include <bits/stdc++.h>
using namespace std;

vector<string> stationNames = {
    "Patancheru", "RC_Puram", "BHEL", "Lingampally",
    "Miyapur", "KPHB", "SR_Nagar", "Ameerpet",
    "Punjagutta", "Khairatabad", "Lakdikapul", "Nampally",
    "Abids", "Koti", "Dilsukhnagar", "LB_Nagar",
    "Mehdipatnam", "Tolichowki", "Gachibowli", "Hitech_City",
    "Jubilee_Hills", "Yusufguda", "Panjagutta"
};

struct Edge { 
    int to, time;
};

class Graph {
    int V;
    vector<vector<Edge>> adj; 
public:
    Graph(int v): V(v), adj(v) {}

    void addEdge(int u, int v, int t) {
        adj[u].push_back({v, t});
        adj[v].push_back({u, t}); 
    }

    void dijkstra(int src, vector<int>& dist, vector<int>& parent) {
        dist.assign(V, INT_MAX);
        parent.assign(V, -1);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, src); 

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d>dist[u]) continue;
            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int time = edge.time;
                if (dist[u] + time < dist[v]) {
                    dist[v]= dist[u] + time;
                    parent[v] =u;
                    pq.emplace(dist[v], v);
                }
            }
        }
    }
};

// to print the Path
void printPath(int node, const vector<int>& parent) {
    vector<int> path;
    for (int v = node; v != -1; v = parent[v]){
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout<<"\nPath followed: ";
    for (int i = 0; i<path.size(); i++) {
        cout << stationNames[path[i]];
        if (i + 1 < path.size())
            cout << " -> ";
    }
    cout << "\n";
}

// returns the node for respective Station name
int stationIndex(const string& name) {
    for (int i = 0; i < stationNames.size(); ++i)
        if (stationNames[i] == name)
            return i;
    return -1;
}

int main() {
    const int n = 23;
    Graph g(n);

    // Vector which stores the edges (i.e Roads and respective time to travel via that road)
    vector<tuple<int, int, int>> edges = {
        // Main corridor from Patancheru to LB Nagar
        {0, 1, 12},
        {1, 2, 5},
        {2, 3, 6},
        {3, 4, 10},
        {4, 5, 8},
        {5, 6, 6},
        {6, 7, 5},
        {7, 8, 5},
        {8, 9, 4},
        {9, 10, 5},
        {10, 11, 4},
        {11, 12, 5},
        {12, 13, 5},
        {13, 14, 10},
        {14, 15, 8},

        // Mehdipatnam side route
        {10, 16, 10},
        {16, 17, 8},
        {17, 18, 10},

        // IT corridor
        {3, 18, 15},
        {18, 19, 7},
        {19, 20, 6},
        {20, 21, 5},
        {21, 8, 5},

        // Additional connections
        {6, 21, 7},
        {19, 7, 15},
        {20, 9, 12},
        {16, 9, 10},
        {14, 13, 9}
    };

    for (const auto& [u, v, c] : edges) { // structured binding
        g.addEdge(u, v, c);
    }

    // Taking input of Starting station and end station
    string startName, endName;
    cout << "Enter starting point: ";
    getline(cin, startName);
    cout << "Enter destination point: ";
    getline(cin, endName);

    int start = stationIndex(startName), end = stationIndex(endName);
    if (start == -1 || end == -1) {
        cout << "Invalid station name.\n";
        return 1;
    }

    // Dijkshatra Algorithm
    vector<int> dist, parent;
    g.dijkstra(start, dist, parent);

    // print output as time requred and path
    cout << "\nShortest path from " << startName << " to " << endName << " (" << dist[end] << " mins): ";
    printPath(end, parent);
    return 0;
}

// Format: node_id, node_name

// 0, Patancheru  
// 1, RC_Puram  
// 2, BHEL  
// 3, Lingampally  
// 4, Miyapur  
// 5, KPHB  
// 6, SR_Nagar  
// 7, Ameerpet  
// 8, Punjagutta  
// 9, Khairatabad  
// 10, Lakdikapul  
// 11, Nampally  
// 12, Abids  
// 13, Koti  
// 14, Dilsukhnagar  
// 15, LB_Nagar  
// 16, Mehdipatnam  
// 17, Tolichowki  
// 18, Gachibowli  
// 19, Hitech_City  
// 20, Jubilee_Hills  
// 21, Yusufguda  
// 22, Panjagutta

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

// Convert string to lowercase
string toLower(string s) {
    int n=s.length();
    for(int i=0;i<n;i++){
        if(s[i]>='A' && s[i]<='Z'){
            s[i] = s[i] - 32;
        }
    }
    return s;
}

// Levenshtein Distance (Edit Distance)
int editDistance(const string& a, const string& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int i=0;i<= m; ++i) dp[i][0] = i;
    for(int j=0;j<=n; ++j) dp[0][j] = j;

    for (int i= 1; i<=m; i++) {
        for (int j= 1;j<= n; j++) {
            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[m][n];
}

// Suggest the closest matching station name
string suggestClosestStation(const string& input) {
    int minDist = INT_MAX;
    string closest = "";
    for (const auto& station : stationNames) {
        int dist = editDistance(toLower(input), toLower(station));
        if (dist < minDist) {
            minDist = dist;
            closest = station;
        }
    }
    return closest;
}

// Get station index with input validation and suggestion
int stationIndex(const string& name) {
    string lowerName = toLower(name);
    for (size_t i = 0; i < stationNames.size(); ++i) {
        if (toLower(stationNames[i]) == lowerName)
            return i;
    }
    return -1;
}

// Repeated prompt until valid station is entered
int getValidStationIndex(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        int index = stationIndex(input);
        if (index != -1)
            return index;

        cout << "Invalid station name.\n";
        cout << "Did you mean: " << suggestClosestStation(input) << "?\n";
    }
}
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
        {14, 13, 9},
        {6, 14, 6},  {4, 13, 6},        
        {2, 14, 8},  {13, 21, 10},{3, 5, 7},         
        {8, 13, 5},  {1, 4, 9},   {12, 15, 6}
    };

    for (const auto& [u, v, c] : edges) { // structured binding
        g.addEdge(u, v, c);
    }

    int start = getValidStationIndex("Enter starting point: ");
    int end = getValidStationIndex("Enter destination point: ");

    vector<int> dist, parent;
    g.dijkstra(start, dist, parent);

    cout << "\nShortest path: ";
    printPath(end, parent);
    cout << "Estimated Time: "<< dist[end] << "mins" <<endl;

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

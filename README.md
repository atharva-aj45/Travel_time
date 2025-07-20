# Hyderabad Transit Route Planner
C++ implementation of a Transit Routing System designed to compute the shortest path (in terms of travel time) between two stations in a simplified model of Hyderabad’s transit network using Dijkstra's Algorithm.

---
## Features
- Computes the **fastest route** between any two stations based on travel time  
- **Interactive input correction**: detects mistyped station names and suggests the closest match using the Levenshtein (edit distance) algorithm  
- **Case-insensitive** station name handling for robust user input  
- **Re-prompts** on invalid input until a valid station is entered  
- Displays both the **ordered list of stations** on the optimal path and the **total estimated travel time**  
- Efficient graph representation with **priority queue** (min‑heap) for Dijkstra’s algorithm
  
---
## Concepts used
- **Graph Data Structure**: adjacency list representation of a weighted, undirected graph  
- **Dijkstra’s Shortest Path Algorithm**: finds the minimum travel-time path in O((V + E) log V) time  
- **Levenshtein Distance**: dynamic programming approach for computing edit distance to suggest closest station names  
- **Priority Queue / Min Heap**: for selecting the next vertex with the smallest tentative distance  
- **Path Reconstruction**: tracking parent pointers to build the route in reverse order  

---
##  Working

The program proceeds through five clearly defined stages:

1. **Graph Initialization**  
   - A `Graph` object is created with V = 23 vertices, one per station in `stationNames`.  
   - All station names are stored in a global vector for name‑to‑index and index‑to‑name lookups.  

2. **Edge Construction**  
   - A list of bidirectional edges with estimated travel times is defined as tuples `<u, v, time>`.  
   - `addEdge(u, v, time)` populates the adjacency list, modeling the transit network.  

3. **User Input & Validation**  
   - The program prompts for **source** and **destination** names via `getline()`.  
   - `getValidStationIndex()` loops until `stationIndex()` returns a valid index.  
   - On invalid input, the program prints:  
     ```
     Invalid station name.  
     Did you mean: <suggestion>?  
     ```
     and re-prompts.  

4. **Shortest-Path Computation**  
   - dijkstra(src, dist, parent) initializes all distances to INT_MAX except dist[src] = 0.  
   - A min‑heap stores (distance, vertex).  
   - In each iteration, the vertex with the smallest distance is extracted and its edges relaxed.  

5. **Output & Path Reconstruction**  
   - After Dijkstra’s run, dist[destination] holds the **minimum travel time**.  
   - printPath(destination, parent) backtracks via the parent array, reverses the station indices, and prints the route:  
     ```
     StationA -> StationB -> ... -> StationZ
     ```
   - The program also outputs the total estimated time:  
     ```
     Estimated Time: XX mins
     ```
This workflow ensures the program consistently returns the fastest available route through the predefined Hyderabad‑area network while maintaining a clear, modular structure for future extensions.
---
##  Limitations
- **Estimated Travel Times**: edge weights are approximations and not based on live traffic or official schedules.  
- **Simplified Network**: only 23 stations are modeled; many real-life connections and modes of transit are omitted.  
- **No Real-Time Data**: the system does not integrate GPS, dynamic traffic, or schedule APIs.  
---
  # Authur
  -**Atharva Joshi**<br>
  -**IIT Hyderabad**

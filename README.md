# Hyderabad Transit Route Planner
C++ implementation of a Transit Routing System designed to compute the shortest path (in terms of travel time) between two stations in a simplified model of Hyderabad’s transit network using Dijkstra's Algorithm.

---
## Features
- Calculates the shortest travel time between two stations
- Displays the full path followed from source to destination
- Uses Dijkstra’s algorithm for optimal routing
- Simple terminal-based interaction
- Efficient implementation using priority queues
---
## Concepts used
- Graph Data sturcture
- Dijkstra’s Shortest Path Algorithm
- Priority Queue / Min Heap
- Path Reconstruction using parent tracking

---
##  Working

The program proceeds through five clearly defined stages:

1. **Graph Initialisation**  
   * A Graph object is instantiated with *V = 23* vertices, one for each station in the network.  
   * All stations are stored in the global stationNames vector for straightforward name‑to‑index look‑ups.

2. **Edge Construction**  
   * The vector edges lists every bidirectional road segment along with its travel time (in minutes).  
   * Each tuple ⟨*u, v, t*⟩ is inserted into the adjacency list using addEdge(u, v, t), creating a *weighted, undirected* graph that models the transit network.

3. **User Interaction**  
   * The program prompts the user for **source** and **destination** station names via getline.  
   * stationIndex() converts each name to its corresponding numeric index.  
   * Invalid input is detected immediately; if either station is missing from the list, the program terminates with an error message.

4. **Shortest‑Path Computation (Dijkstra’s Algorithm)**  
   * dijkstra(src, dist, parent) initialises all distances to INT_MAX, except dist[src] = 0, and pushes the source into a **min‑priority queue**.  
   * While the queue is non‑empty, the vertex with the smallest tentative distance is extracted.  
   * For every adjacent edge (*u → v*, *cost*), the *relaxation* step updates dist[v] and records parent[v] = u when a shorter path is discovered.  
   * The algorithm runs in *O((V + E) log V)* time thanks to the heap‑based priority queue and terminates when all vertices have been settled.

5. **Path Reconstruction & Output**  
   * After Dijkstra completes, dist[destination] holds the **minimum travel time**.  
   * printPath(destination, parent) backtracks from the destination to the source via the parent vector, reverses the resulting sequence, and prints a human‑readable route such as  
     ```
     Patancheru -> RC_Puram -> … -> LB_Nagar
     ```  
   * The final output therefore consists of both  
     * the *numeric* shortest travel time in minutes, and  
     * the *ordered* list of stations on the optimal path.

This workflow ensures the program consistently returns the fastest available route through the predefined Hyderabad‑area network while maintaining a clear, modular structure for future extensions.
---
##  Limitations
- **Estimated Travel Times**  
  The travel durations are manually set and only serve as approximations. They do not reflect real-time traffic or official transit data.
- **Simplified Network**  
  The network is a simplified model of Hyderabad's transit system. The roads and paths used are **not exact** and may be slightly away from actual routes.
- **No Real-Time or Geo-Based Data**  
  The system does not use live traffic updates, GPS coordinates, or dynamic routing based on current conditions.
- **Limited Station Coverage**  
  Only 23 major stations are included for demonstration. Many real-life connections are excluded.
---
  # Authur
  -**Atharva Joshi**<br>
  -**IIT Hyderabad**

# IP Routing
## Project Description
Implement Dijkstra's algorithm to find the shortest path from a specified source to destination.  For the graph below, the source is U.

#### Graph/Network
![graph-cs435](https://github.com/user-attachments/assets/8d705fc7-d9e1-4bcc-9989-c9884d44fed9)

## Project Implementation 
Create a Vertex class (or whatever you think is appropriate for a router / node / vertex in a graph).

Your Vertex class will contain all of the items to compute the shortest path from the source to all destinations.  This will include:
- Vertex name  (most examples use letters)
- previous - to track previous when computing the algorithm (could be same as name or Vertex*)
- cost - unsigned int to track the cost during computation
- visited - boolean to track when the vertex is added to N'
- adjacent - vector of adjacent vertices and edge weights - the vector might contain std::pair items or you may create a small class or struct for an Edge.

We will use a [priority queue](https://en.cppreference.com/w/cpp/container/priority_queue.html) in this assignment to select the next, least-cost vertex to process. 

To sort items in the queue we'll need a method in the Vertex class, e.g.:
```
 // Add operator< for priority queue
        bool operator<(const Vertex& other) const {
            return cost > other.cost;
        }
```

## Project Algorithm
For each vertex in the graph, initialize the cost, or distance to infinity.
Initialize the source vertex cost to 0.

while the queue is not empty, remove the next item, mark it Visited
for each of the item's adjacent vertices
   1. continue if visited
   2. recompute costs / previous if there's a better path
   3. add to priority queue if distance is now lower

## Project Requirements
- The program must compile and run on thomas.butler.edu.
- Your program should not exceed 100 lines (if you think that it should, let's discuss your implementation).
- Your submission should be well organized and include remarks where needed.
- Your submission should be based on the code from class and not copy-pasted from the Internet.
- If you wish to take a different approach you should discuss it with me first. Otherwise, especially if it appears to be an Internet example, you will receive no credit for this assignment.

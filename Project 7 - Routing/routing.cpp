// IP Routing: Main - Vadella and Baker
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "vertex.h"

int main()
{
    std::priority_queue<Vertex*> pq;
    std::vector<Vertex*> vertices;

    std::ifstream fileReader("routing-vertices.txt");                                                       // reading vertices in from .txt file

    int vertices_number;
    char source_vertex_name;
    fileReader >> vertices_number >> source_vertex_name;

    Vertex* sourceVertex = new Vertex(source_vertex_name);
    vertices.push_back(sourceVertex);

    char source_vertex;
    char dest_vertex;
    unsigned int vertex_weight;

    while(fileReader >> source_vertex >> dest_vertex >> vertex_weight)
    {
        Vertex* source = Vertex::findVertex(vertices, source_vertex);
        if(!source) 
        {
            source = new Vertex(source_vertex);
            vertices.push_back(source);
        }

        Vertex* dest = Vertex::findVertex(vertices, dest_vertex);
        if (!dest) 
        {
            dest = new Vertex(dest_vertex);
            vertices.push_back(dest);
        }

        source->addAdjacent(dest, vertex_weight);
    }

    fileReader.close();

    sourceVertex->setCost(0);                                                                               // initialize source vertex's cost to 0
    pq.push(sourceVertex);                                                                                  // priority queue uses operator function to maintain ordering (i think!)

    // while the queue is not empty, remove next item, mark as visited
    while(!pq.empty())
    {
        Vertex* currentVertex = pq.top();                                                                   // determine top-most element of queue, then delete it
        pq.pop();

        if(currentVertex->isVisited())                                                                      // continue if already visited -- is this necessary?
            continue;

        currentVertex->setVisited(true);                                                                    // mark as visited

        // for each of the item's adjacent vertices...
        std::vector<std::pair<Vertex*, unsigned int>> adjacentVertex = currentVertex->getAdjacent();
        for(size_t i = 0; i < adjacentVertex.size(); i++)
        {
            Vertex* nextAdjacent = adjacentVertex[i].first;                                                 // adjacent vertex
            unsigned int weight = adjacentVertex[i].second;                                                 // edge weight

            if(nextAdjacent->isVisited())                                                                   // continue if visited
                continue;

            unsigned int newCost = currentVertex->getCost() + weight;                                       // recompute costs/previous if there's a better path

            if(newCost < nextAdjacent->getCost())                                                           // add to priority queue if distance is now lower than previous path
            {
                nextAdjacent->setCost(newCost);
                nextAdjacent->setPrevious(currentVertex);
                pq.push(nextAdjacent);
            }
        }
    }

    std::cout << "Final shortest path from " << source_vertex_name << ":" << std::endl;
    for(Vertex* vertex : vertices) 
    {
        std::cout << "To " << vertex->getName() << ": ";
        if(vertex->getCost() == infinity) 
            std::cout << "No path exists!" << std::endl;
        else 
        {
            std::cout << "cost = " << vertex->getCost() << ", path = ";
            vertex->printFinalPath();
            std::cout << std::endl;
        }
    }

    // cleaning up memory
    for (Vertex* vertex : vertices) { delete vertex; }

    return EXIT_SUCCESS;
}
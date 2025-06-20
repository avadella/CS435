// IP Routing: Vertex Class - Vadella and Baker
#ifndef VERTEX_H
#define VERTEX_H

#include <sstream>
#include <string>
#include <vector>
#include <utility>                                                                          // for std::pair
#include <climits>                                                                          // for unit_max

const unsigned int infinity = UINT_MAX;

class Vertex
{
    private: 
        char name_;                                                                         // vertex name
        Vertex* previous_;                                                                  // tracks previous when computing algorithm
        unsigned int cost_;                                                                 // unsigned int to track cost during computation (represents current shortest known distance from source vertex)
        bool visited_;                                                                      // bool to track when vertex is added to N'
        std::vector<std::pair<Vertex*, unsigned int>> adjacent_;                            // vector of adjacent vertices (Vertex*) and edge weights (unsigned int)
    
    public: 
        Vertex(char n) {                                                                    // constructor 
            name_ = n; previous_ = nullptr; cost_ = infinity; visited_ = false; 
        }

        // getters
        char getName() { return name_; }
        Vertex* getPrevious() { return previous_; }
        unsigned int getCost() { return cost_; }
        bool isVisited() { return visited_; }
        std::vector<std::pair<Vertex*, unsigned int>> getAdjacent() { return adjacent_; }

        // setters
        void setPrevious(Vertex* previous) { previous_ = previous; }
        void setCost(unsigned int cost) { cost_ = cost; }
        void setVisited(bool visited) { visited_ = visited; }

        void addAdjacent(Vertex* vertex, unsigned int weight) {                              // method to add adjacent vertex with edge weight
            adjacent_.emplace_back(vertex, weight);
        }

        bool operator<(const Vertex& other) const {                                          // add operator< for priority queue
            return cost_ > other.cost_;
        }

        static Vertex* findVertex(const std::vector<Vertex*> vertices, char name) {         // static b/c operates on a class level, not instance level + searching through a collection of vertices instead of just one
            for(Vertex* v : vertices) {
                if(v->getName() == name) {
                    return v;
                }
            }
            return nullptr;
        }
        
        void printFinalPath() {
            if (previous_ != nullptr) {
                previous_->printFinalPath();
                std::cout << " -> ";
            }
            std::cout << name_;
        }
};

#endif
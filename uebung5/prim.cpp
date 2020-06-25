#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
#include <experimental/iterator>
#include <math.h>  
#include <climits>

// small test data (graph example from lecture slides)
const int N1 = 6;
const std::array<int, N1*N1> weights_table_1 {
    {
        -1,  3, -1, -1,  6,  5,
         3, -1,  1, -1, -1,  4,
        -1,  1, -1,  6, -1,  4,
        -1, -1,  6, -1,  8,  5,
         6, -1, -1,  8, -1,  2,
         5,  4,  4,  5,  2, -1
    }
};

// larger test data
// test data: distances between major German cities
//    vertices are cities
//    edges denote city connections
//    weights denote travel distances

const int N2 = 20;
const std::array<int, N2 * N2> weights_table_2 {
    {
        -1, 255, 504, 477, 424, 512, 477, 422, 453, 315, 165, 149, 249, 378, 471, 439, 452, 336, 479, 398,
        255,  -1, 612, 356, 393, 534, 338, 284, 308,  95, 377, 294, 132, 462, 321, 297, 320, 196, 370, 237,
        504, 612,  -1, 456, 304, 190, 486, 477, 493, 582, 359, 360, 488, 150, 503, 486, 470, 483, 433, 510,
        477, 356, 456,  -1, 152, 288,  34,  72,  57, 269, 474, 380, 249, 336,  56,  62,  37, 162,  25, 123,
        424, 393, 304, 152,  -1, 152, 182, 177, 190, 329, 371, 293, 261, 187, 200, 184, 167, 212, 131, 218,
        512, 534, 190, 288, 152,  -1, 322, 328, 335, 478, 412, 364, 401, 157, 342, 332, 311, 364, 264, 371,
        477, 338, 486,  34, 182, 322,  -1,  57,  30, 248, 485, 389, 240, 363,  23,  41,  26, 150,  59, 101,
        422, 284, 477,  72, 177, 328,  57,  -1,  32, 196, 439, 340, 182, 343,  49,  17,  36,  93,  90,  51,
        453, 308, 493,  57, 190, 335,  30,  32,  -1, 217, 470, 371, 212, 364,  18,  14,  24, 122,  81,  70,
        315,  95, 582, 269, 329, 478, 248, 196, 217,  -1, 405, 310, 100, 433, 229, 207, 231, 118, 285, 150,
        165, 377, 359, 474, 371, 412, 485, 439, 470, 405,  -1, 100, 312, 259, 487, 456, 460, 375, 467, 434,
        149, 294, 360, 380, 293, 364, 389, 340, 371, 310, 100,  -1, 214, 229, 389, 358, 363, 275, 375, 334,
        249, 132, 488, 249, 261, 401, 240, 182, 212, 100, 312, 214,  -1, 338, 229, 199, 217,  90, 258, 151,
        378, 462, 150, 336, 187, 157, 363, 343, 364, 433, 259, 229, 338,  -1, 377, 355, 343, 337, 318, 370,
        471, 321, 503,  56, 200, 342,  23,  49,  18, 229, 487, 389, 229, 377,  -1,  32,  33, 138,  81,  84,
        439, 297, 486,  62, 184, 332,  41,  17,  14, 207, 456, 358, 199, 355,  32,  -1,  26, 109,  84,  61,
        452, 320, 470,  37, 167, 311,  26,  36,  24, 231, 460, 363, 217, 343,  33,  26,  -1, 128,  58,  85,
        336, 196, 483, 162, 212, 364, 150,  93, 122, 118, 375, 275,  90, 337, 138, 109, 128,  -1, 175,  62,
        479, 370, 433,  25, 131, 264,  59,  90,  81, 285, 467, 375, 258, 318,  81,  84,  58, 175,  -1, 142,
        398, 237, 510, 123, 218, 371, 101,  51,  70, 150, 434, 334, 151, 370,  84,  61,  85,  62, 142,  -1
   }
};

struct Vertex {
    Vertex(const int i = 0) : index {i}, key {max_key}, parent_index {undef}, processed {false} {}

    int index;        // vertex identifier
    int key;          // temporary minimal weight (Prim algorithm)
    int parent_index; // temporary minimal distance neighboor vertex (Prim algorithm)
    int processed;    // flag used to mark vertices that are already included in V'

    static constexpr int max_key = std::numeric_limits<int>::max();
    static const int undef = -1;
};

struct Edge {
    Edge(int va, int vb, int w) : vi1 {va}, vi2 {vb}, weight {w} { }

    int vi1;
    int vi2;
    int weight;
};

struct Graph {
    int N;                    // number of vertices
    std::vector<Vertex> V;    // set of vertices
    std::vector<Edge> E;      // set of edges
    std::vector<Edge> MST;    // minimal spanning tree
    const int* weights_table; // weights given as distance matrix
};

int getWeight(Graph& G, int i, int j) // encapsulates access to (hard-coded) weight tables
{
    assert(i>= 0 && i < G.N); // check index i
    assert(j>= 0 && j < G.N); // check index j
    assert(G.weights_table[i + j * G.N] == G.weights_table[j + i * G.N]); // weights must be symmetric

    return G.weights_table[i + j * G.N];
}

// pretty vertex printing
std::ostream & operator<<(std::ostream& os, const Vertex& v) {
    os << static_cast<char>('a' + v.index); // a, b, c, ...
    return os;
}

// pretty edge printing
std::ostream & operator<<(std::ostream& os, const std::vector<Edge>& E) {
    os << "{";
    for (size_t i = 0, N = E.size(); i < N; ++i)
        os << (i > 0 ? "," : "") << "("
           << static_cast<char>('a' + E[i].vi1) << ","
           << static_cast<char>('a' + E[i].vi2) << ")";
    os << "}";
    return os;
}
bool operator==(const Edge e1, const Edge e2){
    if((e1.vi1 == e2.vi1) && (e1.vi2 == e2.vi2) && (e1.weight == e2.weight))
        return true;
    return false;
}
bool operator==(const Vertex v1, const Vertex v2){
    if(v1.index == v2.index)
        return true;
    return false;
}

// construct vertices and edges for a given graph
void createGraph(Graph& G) {
    // TODO 5.1a: clear V and E and insert all vertex objects and edge objects
    G.E.clear();
    G.V.clear();

    // - vertices are numbered (labeled) from 0 to N-1
    for(int i = 0; i < G.N; i++){
        G.V.push_back(Vertex(i));
    }

    for(int i = 0; i < G.N*G.N; i++){
        if(G.weights_table[i] > 0){
            // - edges are bidirectional, that is, edges are inserted only once between two vertices
            if(std::find(G.E.begin(), G.E.end(), Edge(i%G.N, i/G.N, getWeight(G, i%G.N, i/G.N))) == G.E.end()){
                G.E.push_back(Edge(i/G.N, i%G.N, getWeight(G, i/G.N, i%G.N)));
            }
        }
    }
}

// return added weights of a list of edges
int totalWeight(const std::vector<Edge>& E) {
    int weight = 0;
    for(int i = 0; i < E.size(); i++){
        weight += E[i].weight;
    }
    return weight;
}


Vertex findVertexWithLowestKey(std::vector<Vertex>& workingSet){
    Vertex smallestKeyVertex = workingSet[0];
    for(int i = 0; i < workingSet.size(); i++){
        if(workingSet[i].key < smallestKeyVertex.key)
            smallestKeyVertex = workingSet[i];
    }
    return smallestKeyVertex;
}

void prim(Graph& G) {
    G.MST.clear();
    
    G.V[0].key = 0; // arbitrarily defined start vertex, taken to V'

    std::vector<Vertex> secondVerticesVector;

    while(G.V.size() > 0){
        Vertex u = findVertexWithLowestKey(G.V);
        G.V.erase(std::remove(G.V.begin(), G.V.end(), u), G.V.end());
        secondVerticesVector.push_back(u);

        if(u.parent_index != -1){
            G.MST.push_back(Edge(u.index, u.parent_index, getWeight(G, u.index, u.parent_index)));
        }

        for(auto& currentEdge : G.V){
            int weight = getWeight(G, u.index, currentEdge.index);
            if(weight > 0 && weight < currentEdge.key){
                currentEdge.key = getWeight(G, u.index, currentEdge.index);
                currentEdge.parent_index = u.index;
            }
        }
    }

    // TODO 5.1c: implement prim algorithm
}

int main(int argc, char** argv) {
    // Example 1 (small)
    Graph G1;
    G1.N = N1;
    G1.weights_table = &weights_table_1[0];
    createGraph(G1);
    prim(G1);
    std::cout << G1.MST << ", total costs: " << totalWeight(G1.MST) << std::endl;

    // Example 2 (larger)
    Graph G2;
    G2.N = N2;
    G2.weights_table = &weights_table_2[0];
    createGraph(G2);
    prim(G2);
    std::cout << G2.MST << ", total costs: " << totalWeight(G2.MST) << std::endl;

    return 0;
}

#ifndef COLORING_PROBLEM_H
#define COLORING_PROBLEM_H

#include <string>
#include <vector>
#include <unordered_set>


struct Vertex {
    int sat_degree;
    int degree;
    int vertex;
};


//  Operator for comparing vertices in DSatur coloring algorithm
struct maxSat {
    bool operator()(const Vertex& a, const Vertex& b) const {
        return std::tie(a.sat_degree, a.degree, a.vertex) > std::tie(b.sat_degree, b.degree, b.vertex);
    }
};



class ColoringProblem {
    public:
        // Reads graph from file
        void ReadGraphFile(std::string filename);
        // Main method for coloring the graph
        void ColorTheGraph(std::string mode);
        // Checks if resulted coloring is correct   
        bool Check();

        // Returns the number of colors in the coloring
        inline int GetNumberOfColors() { return maxcolor; }
        // Prints color classes
        std::string PrintColors();

    private:
        // Gives a vertex a minimal color taking into account its neighbors
        void FindColor(int current_vertex, int& color, std::vector<bool>& used);

        // Colors a graph using DSatur method
        void DSaturColoring();
        // Colors a graph using "smallest vertex last with remove" ordering
        void SmallestLastWithRemoveOrdering();
        // Takes the best coloring of the previous two methods
        void CalculateBestColoring();

        inline const std::vector<int>& GetColors() { return colors; }

    private:
        std::vector<int> colors;
        int maxcolor = 1;
        std::vector<std::unordered_set<int>> neighbor_sets;
        int vertices_num;
};

#endif // COLORING_PROBLEM_H
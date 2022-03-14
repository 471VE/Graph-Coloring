#include "coloring_problem.h"

#include <algorithm>
#include <fstream>
#include <set>
#include <iostream>
#include <sstream>


void ColoringProblem::ReadGraphFile(std::string filename) {
    std::ifstream fin(filename);
    std::string line;
    int vertices = 0, edges = 0;
    while (std::getline(fin, line)) {
        if (line[0] == 'c')
            continue;

        std::stringstream line_input(line);
        char command;
        if (line[0] == 'p') {
            std::string type;
            line_input >> command >> type >> vertices >> edges;
            vertices_num = vertices;
            neighbor_sets.resize(vertices);
            colors.resize(vertices);
        } else {
            int start, finish;
            line_input >> command >> start >> finish;
            neighbor_sets[start - 1].insert(finish - 1);
            neighbor_sets[finish - 1].insert(start - 1);
        }
    }
}

void ColoringProblem::ColorTheGraph(std::string mode) {
    if (mode == "smallest_last") { SmallestLastWithRemoveOrdering(); }
    else if (mode == "dsatur") { DSaturColoring(); }
    else if (mode == "best") { CalculateBestColoring(); }
    else {
        std::cerr << "\nUnacceptable mode. Exiting...";
        exit(1);
    }
}


bool ColoringProblem::Check() {
    for (size_t i = 0; i < neighbor_sets.size(); ++i) {
        if (colors[i] == 0) {
            std::cout << "Vertex " << i + 1 << " is not colored\n";
            return false;
        }
        for (int neighbor : neighbor_sets[i]) {
            if (colors[neighbor] == colors[i]) {
                std::cout << "neighbor vertices " << i + 1 << ", " << neighbor + 1 <<  " have the same color\n";
                return false;
            }
        }
    }
    return true;
}


std::string ColoringProblem::PrintColors() {
    std::string result = "";
    bool single_begun = false;
    for (int color = 1; color < maxcolor + 1; ++color) {
        if (color > 1)
            result += ", ";
        result += "{";
        for (int vertex = 0; vertex < static_cast<int>(colors.size()); ++vertex) {
            if (colors[vertex] == color) {
                if (!single_begun) { single_begun = true; } 
                else { result += ", "; }                            
                result += std::to_string(vertex + 1);
            }
        }
        result += "}";
        single_begun = false;
    }
    return result;
}


void ColoringProblem::FindColor(int current_vertex, int& color, std::vector<bool>& used) {
    for (int neighbor: neighbor_sets[current_vertex])
        used[colors[neighbor]] = true;

    for (color = 1; color < static_cast<int>(used.size()); color++)
        if (used[color] == false)
            break;

    used.assign(used.size(), false);

    colors[current_vertex] = color;
    if (color > maxcolor)
        maxcolor = color;
}


void ColoringProblem::DSaturColoring() {
    int current_vertex, color;
    std::vector<bool> used(vertices_num, false);
    std::vector<int> degrees(vertices_num);
    std::vector<std::unordered_set<int>> neighbors_colors(vertices_num);
    std::set<Vertex, maxSat> queue;
    std::set<Vertex, maxSat>::iterator maxPtr;

    for (current_vertex = 0; current_vertex < vertices_num; current_vertex++) {
        colors[current_vertex] = 0;
        degrees[current_vertex] = static_cast<int>(neighbor_sets[current_vertex].size());
        neighbors_colors[current_vertex] = std::unordered_set<int>();
        queue.emplace(Vertex{0, degrees[current_vertex], current_vertex});
    }

    while (!queue.empty()) {
        maxPtr = queue.begin();
        current_vertex = (*maxPtr).vertex;
        queue.erase(maxPtr);

        FindColor(current_vertex, color, used);

        for (int neighbor: neighbor_sets[current_vertex]) {
            if (colors[neighbor] == 0) {
                queue.erase({int(neighbors_colors[neighbor].size()), degrees[neighbor], neighbor});
                neighbors_colors[neighbor].insert(color);
                --degrees[neighbor];
                queue.emplace(Vertex{int(neighbors_colors[neighbor].size()), degrees[neighbor], neighbor});
            }
        }
    }
}


void ColoringProblem::SmallestLastWithRemoveOrdering() {
    std::vector<int> degrees;
    degrees.reserve(neighbor_sets.size());
    for (const auto& vertex: neighbor_sets)
        degrees.push_back(static_cast<int>(vertex.size()));

    std::vector<int> vertices_sorted_by_degrees;
    vertices_sorted_by_degrees.reserve(neighbor_sets.size());
    for (int i = 0; i < static_cast<int>(neighbor_sets.size()); ++i)
        vertices_sorted_by_degrees.push_back(i);
    
    for (size_t i = 0; i < vertices_sorted_by_degrees.size() - 1; ++i) {
        std::sort(
            vertices_sorted_by_degrees.begin() + i, vertices_sorted_by_degrees.end(),
            [&degrees](const int& vertex_a, const int& vertex_b)
            { return degrees[vertex_a] < degrees[vertex_b]; });

        for (auto vertex: neighbor_sets[vertices_sorted_by_degrees[i]])
            --degrees[vertex];
    }

    int current_vertex, color;
    std::vector<bool> used(vertices_num, false);
    for (current_vertex = 0; current_vertex < vertices_num; current_vertex++) {
        colors[current_vertex] = 0;
    }
    for (int i = static_cast<int>(vertices_sorted_by_degrees.size()) - 1; i > -1; --i) {
        FindColor(vertices_sorted_by_degrees[i], color, used);
    }
}


void ColoringProblem::CalculateBestColoring() {
    DSaturColoring();
    auto colors_tmp = colors;
    auto maxcolor_tmp = maxcolor;

    maxcolor = 1;
    SmallestLastWithRemoveOrdering();
    if (maxcolor_tmp < maxcolor) {
        colors = colors_tmp;
        maxcolor = maxcolor_tmp;
    }
}
#include <iostream>
#include <string>
#include <time.h>
#include <filesystem>
#include <fstream>

#include "coloring_problem.h"


std::string mode = "best";

void parse_cmd_args(int argc, char** argv) {
    if (argc > 2) {
        std::cerr << "\nUnacceptable number of arguments. Exiting...";
        exit(1);
    }
    else if (argc == 2) { mode = argv[1]; }
    if (mode != "best" && mode != "dsatur" && mode != "smallest_last") {
        std::cerr << "\nUnacceptable mode. Exiting...";
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    parse_cmd_args(argc, argv);
    std::vector<std::string> files;
    for(auto& graph: std::filesystem::directory_iterator("graphs")) {
        if (!graph.is_directory()) {
            files.push_back(graph.path().string());
        }      
    }

    std::ofstream fout("coloring_" + mode + ".csv");
    fout << "Graph name; Number of colors; Coloring time (sec); Color classes\n";
    std::cout << "Graph name; Number of colors; Coloring time (sec)\n";

    for (std::string file : files) {
        ColoringProblem problem;
        problem.ReadGraphFile(file);
        clock_t start = clock();
        problem.ColorTheGraph(mode);
        if (!problem.Check()) {
            fout << "*** WARNING: incorrect coloring: ***\n";
            std::cout << "*** WARNING: incorrect coloring: ***\n";
        }
        double time = double(clock() - start) / 1000;
        fout << file << "; " << problem.GetNumberOfColors() << "; " << time << "; " << problem.PrintColors() << '\n';
        std::cout << file << "; " << problem.GetNumberOfColors() << "; " << time <<'\n';
    }
    fout.close();
    return 0;
}
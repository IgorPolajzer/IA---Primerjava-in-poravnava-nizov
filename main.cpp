#include <filesystem>
#include <iostream>
#include <vector>

#include "headers/Algorithm.h"
#include "headers/Util.h"

constexpr std::string OUTPUT_FOLDER = "results/";

void runAlgorithm(const std::string& modeFlag, const std::string& fileName) {
    std::vector<size_t> results;

    size_t pos = fileName.find('/');
    std::string outputFileName = fileName.substr(pos + 1);
    std::ofstream outputFile;

    auto start = std::chrono::high_resolution_clock::now();

    // Run algo

    auto stop = std::chrono::high_resolution_clock::now();
    const auto msDuration = duration_cast<std::chrono::milliseconds>(stop - start);
    const auto microsDuration = duration_cast<std::chrono::microseconds>(stop - start);

    Util::output(outputFile, "\nResult: ", true);
    Util::outputVector(outputFile, results, true);

    Util::output(
        outputFile,
        "\nExecution time: " +
        std::to_string(msDuration.count()) + " ms -> " +
        std::to_string(microsDuration.count()) + " us\n",
        true
    );
}

int main(const int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage: " << std::endl;
        std::cerr << "1.: " << argv[0] << " <dnk-file-path> [-n] [-m]" << std::endl;
        std::cerr << "2.: " << argv[0] << "[-t]" << std::endl;
        return 1;
    }

    if (argv[1] == "-t") {
        const std::vector<std::string> problemFiles = {
            "genom/G1.txt",
            "genom/G2.txt",
            "genom/G3.txt",
            "genom/G4.txt",
            "genom/G5.txt"
        };

        for (const auto& problemFile : problemFiles) {
            // run algo
        }
    }

    if (argc < 3) {
        std::cerr << "Usage: " << std::endl;
        std::cerr << "1.: " << argv[0] << " <dnk1-file-path> <dnk2-file-path> [-n] [-m]" << std::endl;
        std::cerr << "2.: " << argv[0] << "[-t]" << std::endl;
        return 1;
    }

    const std::string firstDnkPath = argv[1];
    const size_t n = std::stoi(argv[2]);

    const std::string secondDnkPath = argv[3];
    const size_t m = std::stoi(argv[4]);

    Algorithm::run_LCS(firstDnkPath, secondDnkPath, n, m);

    return 0;
}

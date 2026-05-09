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

    if (std::string(argv[1]) == "-t") {
        struct TestCase {
            std::string firstPath;
            size_t n;
            std::string secondPath;
            size_t m;
        };

        const std::vector<TestCase> problemFiles = {
            // DNK1 vs DNK2
            {"dnk/DNK1.txt", 10,  "dnk/DNK2.txt", 10},
            {"dnk/DNK1.txt", 20,  "dnk/DNK2.txt", 20},
            {"dnk/DNK1.txt", 30,  "dnk/DNK2.txt", 30},
            // DNK1 vs DNK3
            {"dnk/DNK1.txt", 15,  "dnk/DNK3.txt", 20},
            {"dnk/DNK1.txt", 15,  "dnk/DNK3.txt", 30},
            {"dnk/DNK1.txt", 35,  "dnk/DNK3.txt", 25},
            // DNK1 vs DNK4
            {"dnk/DNK1.txt", 30,  "dnk/DNK4.txt", 20},
            {"dnk/DNK1.txt", 10,  "dnk/DNK4.txt", 30},
            {"dnk/DNK1.txt", 13,  "dnk/DNK4.txt", 33},
            // DNK1 vs DNK5
            {"dnk/DNK1.txt", 10,  "dnk/DNK5.txt", 35},
            {"dnk/DNK1.txt", 22,  "dnk/DNK5.txt", 35},
            {"dnk/DNK1.txt", 35,  "dnk/DNK5.txt", 22},
            // DNK2 vs DNK3
            {"dnk/DNK2.txt", 40,  "dnk/DNK3.txt", 15},
            {"dnk/DNK2.txt", 24,  "dnk/DNK3.txt", 30},
            {"dnk/DNK2.txt", 9,   "dnk/DNK3.txt", 40},
            // DNK2 vs DNK4
            {"dnk/DNK2.txt", 33,  "dnk/DNK4.txt", 11},
            {"dnk/DNK2.txt", 40,  "dnk/DNK4.txt", 9},
            {"dnk/DNK2.txt", 36,  "dnk/DNK4.txt", 22},
            // DNK2 vs DNK5
            {"dnk/DNK2.txt", 13,  "dnk/DNK5.txt", 33},
            {"dnk/DNK2.txt", 25,  "dnk/DNK5.txt", 15},
            {"dnk/DNK2.txt", 36,  "dnk/DNK5.txt", 5},
            // DNK3 vs DNK4
            {"dnk/DNK3.txt", 28,  "dnk/DNK4.txt", 25},
            {"dnk/DNK3.txt", 11,  "dnk/DNK4.txt", 33},
            {"dnk/DNK3.txt", 39,  "dnk/DNK4.txt", 12},
            // DNK3 vs DNK5
            {"dnk/DNK3.txt", 10,  "dnk/DNK5.txt", 26},
        };

        for (const auto& tc : problemFiles) {
            Algorithm::run_LCS(tc.firstPath, tc.secondPath, tc.n, tc.m);
        }

        return 0;
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

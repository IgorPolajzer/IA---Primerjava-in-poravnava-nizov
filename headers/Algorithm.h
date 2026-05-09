//
// Created by igor on 5/9/26.
//

#ifndef IAK_PRIMERJAVA_IN_PORAVNAVA__NIZOV_ALGORITHM_H
#define IAK_PRIMERJAVA_IN_PORAVNAVA__NIZOV_ALGORITHM_H
#include <numeric>
#include <string>
#include <vector>

#include "Direction.h"
#include "Util.h"

namespace Algorithm {
    const std::string OUTPUT_FOLDER = "results/";

    inline void printLCS(const std::vector<std::vector<Direction> > &b, const std::string &v, size_t i, size_t j,
                         std::ofstream &outputFile) {
        if (i == 0 || j == 0) return;

        if (b[i][j] == Direction::DIAGONAL) {
            printLCS(b, v, i - 1, j - 1, outputFile);
            Util::output(outputFile, std::string(1, v[i - 1]) + " ", true);
        } else {
            if (b[i][j] == Direction::UP) {
                printLCS(b, v, i - 1, j, outputFile);
            } else {
                printLCS(b, v, i, j - 1, outputFile);
            }
        }
    }

    inline std::pair<size_t, std::vector<std::vector<Direction> > > LCS(std::string v, std::string w) {
        std::vector<std::vector<size_t> > s; // Intermediate distances.
        std::vector<std::vector<Direction> > b; // Moving directions.

        // Init s and b.
        for (size_t i = 0; i <= v.size(); i++) {
            s.emplace_back();
            b.emplace_back();
            for (size_t j = 0; j <= w.size(); j++) {
                s[i].push_back(0);
                b[i].push_back(Direction::UNKNOWN);
            }
        }

        for (size_t i = 1; i <= v.size(); i++) {
            for (size_t j = 1; j <= w.size(); j++) {
                size_t wj = s[i - 1][j - 1] + 1;
                size_t maxNeighbour = std::max(s[i][j - 1], s[i - 1][j]);

                s[i][j] = std::max(v[i - 1] == w[j - 1] ? wj : 0, maxNeighbour);

                // Set direction.
                Direction direction = Direction::UNKNOWN;

                if (s[i][j] == s[i - 1][j]) direction = Direction::UP;
                else if (s[i][j] == s[i][j - 1]) direction = Direction::LEFT;
                else if (s[i][j] == s[i - 1][j - 1] + 1) direction = Direction::DIAGONAL;

                b[i][j] = direction;
            }
        }

        return {s.back().back(), b};
    }

    inline void run_LCS(std::string firstDnkPath, std::string secondDnkPath, size_t n, size_t m) {
        std::filesystem::create_directories(OUTPUT_FOLDER);
        std::string outputPath = OUTPUT_FOLDER;

        size_t posOne = firstDnkPath.find('/');
        std::string firstDnkFileName = firstDnkPath.substr(posOne + 1);

        outputPath += firstDnkFileName;
        outputPath += "_";
        outputPath += std::to_string(n);

        size_t posTwo = firstDnkPath.find('/');
        std::string secondFileName = firstDnkPath.substr(posTwo + 1);

        outputPath += secondFileName;
        outputPath += "_";
        outputPath += std::to_string(m);
        outputPath += ".txt";

        std::ofstream outputFile(outputPath);

        auto firstDnk = Util::readFile(firstDnkPath);
        auto secondDnk = Util::readFile(secondDnkPath);

        auto v = firstDnk.substr(0, n);
        auto w = secondDnk.substr(0, m);

        std::pair<size_t, std::vector<std::vector<Direction>>> lcs;
        std::vector<long long> durations;

        for (size_t i = 0; i < 100; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            lcs = LCS(v, w);
            auto stop = std::chrono::high_resolution_clock::now();
            durations.push_back(duration_cast<std::chrono::microseconds>(stop - start).count());
        }

        long long avgMicros = std::accumulate(durations.begin(), durations.end(), 0LL) / 100;

        size_t d = n + m - 2 * lcs.first;

        Util::output(outputFile, "LCS = ", true);
        printLCS(lcs.second, v, n, m, outputFile);
        Util::output(outputFile, "\n|LCS| = " + std::to_string(d), true);

        Util::output(
            outputFile,
            "\nExecution time (avg 100 runs): " +
            std::to_string(avgMicros / 1000) + " ms -> " +
            std::to_string(avgMicros) + " us\n",
            true
        );
    }
}

#endif //IAK_PRIMERJAVA_IN_PORAVNAVA__NIZOV_ALGORITHM_H

//
// Created by igor on 5/9/26.
//

#ifndef IAK_PRIMERJAVA_IN_PORAVNAVA__NIZOV_ALGORITHM_H
#define IAK_PRIMERJAVA_IN_PORAVNAVA__NIZOV_ALGORITHM_H
#include <string>
#include <vector>

#include "Direction.h"
#include "Util.h"

namespace Algorithm {

    inline std::pair<size_t, std::vector<std::vector<Direction>>> LCS(std::string v, std::string w) {
        std::vector<std::vector<size_t>> s; // Intermediate distances.
        std::vector<std::vector<Direction>> b; // Moving directions.

        // Init s.
        /*for (size_t i = 0; i <= v.size(); i++) {
            s.emplace_back();

            if (i == 0) {
                for (size_t j = 0; j <= w.size(); j++) {
                    s[i].push_back(0);
                }
            } else {
                s[i].push_back(0);
            }
        }*/

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
                size_t wj =  s[i-1][j-1] + 1;
                size_t maxNeighbour = std::max(s[i][j-1], s[i-1][j]);

                s[i][j] = std::max(v[i - 1] == w[j - 1] ? wj : 0, maxNeighbour);

                // Set direction.
                Direction direction = Direction::UNKNOWN;

                if (s[i][j] == s[i-1][j]) direction = Direction::UP;
                else if (s[i][j] == s[i][j-1]) direction = Direction::LEFT;
                else if (s[i][j] == s[i-1][j-1]) direction = Direction::DIAGONAL;

                b[i][j] = direction;
            }
        }

        Util::print_grid(s, v, w);

        return { s.back().back(), b };
    }

    inline void run_LCS(std::string firstDnkPath, std::string secondDnkPath, size_t n, size_t m) {
        auto firstDnk = Util::readFile(firstDnkPath);
        auto secondDnk = Util::readFile(secondDnkPath);

        auto v = firstDnk.substr(0, n);
        auto w = secondDnk.substr(0, m);

        auto lcs = LCS(v, w);

        std::cout << lcs.first << std::endl;
    }
}

#endif //IAK_PRIMERJAVA_IN_PORAVNAVA__NIZOV_ALGORITHM_H

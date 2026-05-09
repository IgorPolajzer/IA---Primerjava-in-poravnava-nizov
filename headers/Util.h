//
// Created by igor on 5/5/26.
//

#ifndef IAK_PREUREDITEV_GENOMA_UTIL_H
#define IAK_PREUREDITEV_GENOMA_UTIL_H
#include <complex>
#include <fstream>
#include <iostream>

namespace Util {
    inline void output(std::ofstream &file, const std::string &msg, const bool print = true) {
        if (print) {
            std::cout << msg;
            if (file) file << msg;
        }
    }

    inline void outputVector(std::ofstream &file, const std::vector<size_t> &vec, const bool print = true) {
        for (auto el: vec) {
            output(file, std::to_string(el) + " ", print);
        }
    }

    inline std::string readFile(const std::string &fileName) {
        std::string stringFile;

        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return "";
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        stringFile = buffer.str();
        stringFile = stringFile.substr(0, stringFile.find_last_not_of(" \t\n\r") + 1);

        return stringFile;
    }

#pragma once

#include <cstddef>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

    /**
     * Prints a 2D vector<vector<size_t>> as a formatted grid, mirroring the
     * LCS / edit-distance DP table style from textbooks:
     *
     *   - Column indices + column sequence (w) printed above the grid.
     *   - Row indices + row sequence (v) printed to the left of each row.
     *
     * @param b      The matrix to print.
     * @param v      Row sequence (printed on the left side, one char per row).
     *               Pass "" to omit.
     * @param w      Column sequence (printed on the top, one char per column).
     *               Pass "" to omit.
     * @param label  Optional label printed above everything.
     * @param width  Column width for each cell (auto-detected if 0).
     */
    inline void print_grid(
        const std::vector<std::vector<size_t> > &b,
        const std::string &v = "",
        const std::string &w = "",
        const std::string &label = "",
        int width = 0) {
        if (b.empty()) {
            std::cout << "(empty matrix)\n";
            return;
        }

        // Auto-detect column width from the largest value.
        if (width == 0) {
            size_t max_val = 0;
            for (const auto &row: b)
                for (const auto &cell: row)
                    if (cell > max_val) max_val = cell;

            width = 1;
            size_t tmp = max_val;
            while (tmp >= 10) {
                tmp /= 10;
                ++width;
            }
            width += 1; // one space of padding
        }

        const size_t rows = b.size();
        const size_t cols = b[0].size();

        // How many digits the largest index needs.
        const int idx_digits = static_cast<int>(
            std::to_string(rows > cols ? rows - 1 : cols - 1).size());

        // Left margin = idx_digits + space + seq-char + space
        const int margin = idx_digits + 3;

        auto pad_margin = [&]() {
            std::cout << std::string(margin, ' ');
        };

        auto hr = [&]() {
            pad_margin();
            std::cout << '+';
            for (size_t c = 0; c < cols; ++c)
                std::cout << std::string(width, '-') << '+';
            std::cout << '\n';
        };

        if (!label.empty())
            std::cout << label << '\n';

        // ── Column index header ──────────────────────────────────────────────────
        // margin spaces put us at the '+' of the grid border; one more space lands
        // us at the start of the first cell's content — matching setw(width) below.
        std::cout << std::string(margin + 1, ' ');
        for (size_t c = 0; c < cols; ++c)
            std::cout << std::setw(width) << c << ' ';
        std::cout << '\n';

        // ── Column sequence header ───────────────────────────────────────────────
        if (!w.empty()) {
            std::cout << std::string(margin + 1, ' ');
            for (size_t c = 0; c < cols; ++c) {
                char ch = (c < w.size()) ? w[c] : ' ';
                int left = (width - 1) / 2;
                int right = width - 1 - left;
                std::cout << std::string(left, ' ') << ch
                        << std::string(right, ' ') << ' ';
            }
            std::cout << '\n';
        }

        // ── Rows ─────────────────────────────────────────────────────────────────
        hr();
        for (size_t r = 0; r < rows; ++r) {
            // Row index + row sequence character
            std::cout << std::setw(idx_digits) << r;
            char ch = (!v.empty() && r < v.size()) ? v[r] : ' ';
            std::cout << ' ' << ch << ' ';

            // Cells
            std::cout << '|';
            for (const auto &cell: b[r])
                std::cout << std::setw(width) << cell << '|';
            std::cout << '\n';
            hr();
        }
    }
}

#endif //IAK_PREUREDITEV_GENOMA_UTIL_H

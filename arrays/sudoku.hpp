#ifndef EOPI_ARRAYS_SUDOKU_HPP_
#define EOPI_ARRAYS_SUDOKU_HPP_

#include <cstdint>
#include <vector>

namespace eopi {
namespace arrays {

// check whether a given instance of a sudoku field is valid
inline bool is_valid_sudoku(
    std::vector<std::vector<std::int32_t>> const& field) {
    auto const check_row = [&](std::uint32_t const row) {
        std::uint32_t flags = 0;
        for (auto entry : field[row]) {
            if (entry && (flags & (1 << entry))) return false;

            flags |= (1 << entry);
        }
        return true;
    };

    auto const check_col = [&](std::uint32_t const col) {
        std::uint32_t flags = 0;
        for (std::uint32_t row = 0; row < 9; ++row) {
            auto const entry = field[row][col];
            if (entry && (flags & (1 << entry))) return false;

            flags |= (1 << entry);
        }
        return true;
    };

    for (std::uint32_t row_col = 0; row_col < 9; ++row_col) {
        if (!check_row(row_col)) return false;

        if (!check_col(row_col)) return false;
    }

    auto const check_box = [&](std::uint32_t x, std::uint32_t y) {
        auto const row_base = 3 * x;
        auto const col_base = 3 * y;

        std::uint32_t flags = 0;
        for (std::uint32_t row = row_base; row < row_base + 3; ++row) {
            for (std::uint32_t col = col_base; col < col_base + 3; ++col) {
                auto const entry = field[row][col];
                if (entry && (flags & (1 << entry))) return false;

                flags |= (1 << entry);
            }
        }
        return true;
    };

    for (std::uint32_t i = 0; i < 3; ++i)
        for (std::uint32_t j = 0; j < 3; ++j)
            if (!check_box(i, j)) return false;

    return true;
}

}  // namespace arrays
}  // namespace eopi

#endif  // EOPI_ARRAYS_SUDOKU_HPP_

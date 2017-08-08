#ifndef EOPI_ARRAYS_RANDOMS_HPP_
#define EOPI_ARRAYS_RANDOMS_HPP_

#include <algorithm>
#include <vector>

namespace eopi {
namespace arrays {

// check if given an array of advances (a_0, a_n), if it is possible to reach the end of the vector hopping from element to element
// 1,3,0,4,0,0,0 would allow jumping 1->3->4->end
// 1,2,0,0,3,0,0 would end at index 3 (zero based)
bool is_boardgame_winable(std::vector<std::uint32_t> const& board)
{
    if( board.empty() )
        return true;

    auto current_max = board.front();
    for( std::uint32_t i = 0; i <= current_max && i < board.size(); ++i )
        current_max = std::max(current_max,i+board[i]);

    return current_max + 1 >= board.size();
}

}  // namespace arrays
}  // namespace eopi

#endif  // EOPI_ARRAYS_RANDOMS_HPP_

#ifndef EOPI_ARRAYS_ALGORITHMS_HPP_
#define EOPI_ARRAYS_ALGORITHMS_HPP_

#include <algorithm>
#include <functional>
#include <iterator>

namespace eopi {
namespace arrays {

// three wya partition
// input: an array of values, comparable for less
// output and array with the elements less | equal | greater to the pivot element
// less needs to allow comp(pivot,*itr) and comp(*itr,pivot)
template<typename iterator_type, typename pivot_type, typename comparator_type>
void three_way_partition(const iterator_type begin, const iterator_type end, const pivot_type pivot, comparator_type less)
{
    static_assert(
        std::is_convertible<std::random_access_iterator_tag,
                         typename std::iterator_traits<iterator_type>::iterator_category>::value,
        "The iterators for three_way_partition need to be convertable to random access iterators.");

    auto smaller = begin, equal = begin, larger = end;
    while( equal != larger )
    {
        if( less(*equal,pivot) )
        {
            // element at equal is less than pivot
            std::swap(*smaller, *equal);
            ++smaller, ++equal;
        } else if( less(pivot,*equal) )
        {
            // element at *equal is larger and can be stored at the end
            --larger;
            std::swap(*equal,*larger);
        } else
        {
            // element is equal
            ++equal;
        }
    }
}

template<typename iterator_type, typename pivot_type>
void three_way_partition(const iterator_type begin, const iterator_type end, const pivot_type pivot)
{
    three_way_partition(begin,end,pivot,std::less<pivot_type>());
}

}  // namespace arrays
}  // namespace eopi

#endif //EOPI_ARRAYS_ALGORITHMS_HPP_

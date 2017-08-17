#ifndef EOPI_STRINGS_HPP_
#define EOPI_STRINGS_HPP_

#include <algorithm>
#include <string>

namespace eopi {
namespace strings {

void remove_and_replace(std::size_t input_size, std::string& result) {
    // remove 'b's
    std::size_t output_pos = 0;
    for (std::size_t i = 0; i < input_size; ++i) {
        if (result[i] != 'b') result[output_pos++] = result[i];
    }
    input_size = output_pos;
    // look at the next char
    output_pos = result.size() - 1;
    while (input_size--) {
        if (result[input_size] == 'a') {
            // add to 'd's
            result[output_pos--] = 'd';
            result[output_pos--] = 'd';
        }
    }
}

// check whether a given string is a palindrome
bool is_palindrom(std::string const& str) {
    auto itr = str.begin();
    auto ritr = str.rbegin();
    for (std::size_t i = 0; 2 * i < str.size(); ++i, ++itr, ++ritr)
        if (*itr != *ritr) return false;
    return true;
}

std::string reverse_words(std::string sentence)
{
    std::reverse(sentence.begin(), sentence.end());

    auto itr = sentence.begin();
    auto end = sentence.begin();
    while( end != sentence.end())
    {
        end = std::find(itr,sentence.end(),' ');
        std::reverse(itr,end);
        itr = end == sentence.end() ? end : end+1;
    }
    return sentence;
}

}  // namespace strings
}  // namespace eopi

#endif  // EOPI_STRINGS_HPP_

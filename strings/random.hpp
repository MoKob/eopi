#ifndef EOPI_STRINGS_RANDOM_HPP_
#define EOPI_STRINGS_RANDOM_HPP_

#include <algorithm>
#include <cstdint>
#include <string>

namespace eopi
{
    namespace strings
    {
        // compute the look and say sequence for a given repetition
        std::string look_and_say(std::uint32_t n)
        {
            std::string current = "1";
            while(--n)
            {
                std::string tmp = current;
                current = "";
                auto it = tmp.begin();
                while( it != tmp.end() )
                {
                    auto end = std::find_if(it,tmp.end(),[it](auto const c){ return c != *it; });
                    current += std::to_string(std::distance(it,end));
                    current += *it;
                    it = end;
                }
            }
            return current;
        }
    } // namespace strings
} // namespace eopi


#endif //EOPI_STRINGS_RANDOM_HPP_

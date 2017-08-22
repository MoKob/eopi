#include <iostream>
#include <string>

#include "algorithm.hpp"
#include "random.hpp"

using namespace std;

int main() {
    cout << "aba"
         << " is " << eopi::strings::is_palindrom("aba") << " palindromic?"
         << endl;
    std::string replace_and_result("abba");
    cout << "Replace and remove: " << replace_and_result << " ";
    eopi::strings::remove_and_replace(4, replace_and_result);
    cout << replace_and_result << std::endl;

    cout << "Reverse sentences: \""
         << eopi::strings::reverse_words("This is a senctence")
         << "\" Word: " << eopi::strings::reverse_words("Word") << endl;

    cout << "Phone Mnemonics: 1234" << endl;

    eopi::strings::print_mnemonics(123);

    std::cout << "Look and say:\n" << std::endl;
    std::cout << eopi::strings::look_and_say(1) << std::endl;
    std::cout << eopi::strings::look_and_say(2) << std::endl;
    std::cout << eopi::strings::look_and_say(3) << std::endl;
    std::cout << eopi::strings::look_and_say(4) << std::endl;
    std::cout << eopi::strings::look_and_say(5) << std::endl;
    std::cout << eopi::strings::look_and_say(6) << std::endl;
    std::cout << eopi::strings::look_and_say(7) << std::endl;

    std::cout << "Romans\n";
    std::cout << "\tIV:" << eopi::strings::from_roman("IV") << std::endl;
    std::cout << "\tXXXIV:" << eopi::strings::from_roman("XXXIV") << std::endl;
    std::cout << "\tCLIX:" << eopi::strings::from_roman("CLIX") << std::endl;

    std::cout << "All Ips for 19216811\n";
    eopi::strings::all_valid_ips("19216811");
    return 0;
}

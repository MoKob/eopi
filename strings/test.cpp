#include <iostream>
#include <string>
#include "algorithm.hpp"

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
    return 0;
}

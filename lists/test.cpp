#include "linked_list.hpp"

#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> const& data) {
    cout << "[vec]";
    for (auto d : data) cout << " " << d;
    cout << endl;
}

int main() {
    vector<int> odd = {1, 3, 5, 7, 9, 11, 13, 15};
    vector<int> even = {2, 4, 6, 8};

    cout << "Merging:\n";
    print(odd);
    print(even);
    cout << "Into:\n";
    auto merged_list =
        eopi::lists::algorithm::merge(eopi::lists::tool::from_vector(odd),
                                      eopi::lists::tool::from_vector(even));
    auto merged =  eopi::lists::tool::to_vector(merged_list);
    print(merged);

    auto reversed_list = eopi::lists::algorithm::reverse(merged_list);
    auto reversed = eopi::lists::tool::to_vector(reversed_list);
    cout << "Reversed:\n";
    print(reversed);
}

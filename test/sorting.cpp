#include <iostream>
#include <vector>

#include "sorting/algorithms.hpp"

using namespace std;

int main() {
  {
    // set intersection
    vector<int> lhs = {2, 3, 3, 5, 5, 6, 7, 7, 8, 12},
                rhs = {5, 5, 6, 8, 8, 9, 10, 10};
    auto intersect = eopi::sorting::algorithms::set_intersect(lhs, rhs);
    cout << "Intersection:";
    for (auto i : intersect)
      cout << " " << i;
    cout << endl;
  }
  {
    // inplace merge
    vector<int> lhs = {2, 3, 5, 6, 7, 8, 12}, rhs = {1, 4, 9, 10, 11};

    eopi::sorting::algorithms::semi_inplace_merge(lhs, rhs);
    cout << "Merged:";
    for (auto l : lhs)
      cout << " " << l;
    cout << endl;
  }
  {
    // optimal pair schedule
    vector<uint32_t> durations = {5, 1, 6, 2, 4, 4};
    auto schedule = eopi::sorting::algorithms::schedule(durations);
    cout << "Schedule:";
    for (auto s : schedule)
      cout << " (" << s.first << ", " << s.second << ")";
    cout << endl;
  }
  {
    struct object {
      typedef char key_type;
      key_type key() const { return c; }
      char c;
    };

    vector<object> objects;
    objects.push_back({'b'});
    objects.push_back({'a'});
    objects.push_back({'c'});
    objects.push_back({'b'});
    objects.push_back({'d'});
    objects.push_back({'a'});
    objects.push_back({'b'});
    objects.push_back({'d'});

    eopi::sorting::algorithms::counting_sort(objects);
    cout << "Sorted:";
    for (auto object : objects) {
      cout << " " << object.c;
    }
    cout << endl;
  }
}

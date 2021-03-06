#include "lists/linked_list.hpp"
#include "lists/postings.hpp"

#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

void print(vector<int> const &data) {
  cout << "[vec]";
  for (auto d : data)
    cout << " " << d;
  cout << endl;
}

using IntNode = eopi::lists::ListNode<int>;
using IntList = std::shared_ptr<IntNode>;

auto get_cyclic_list() {
  auto cyclic_list = std::make_shared<IntNode>(0, nullptr);
  auto cur = cyclic_list;

  for (int i = 1; i < 4; ++i) {
    cur->next = std::make_shared<IntNode>(i, nullptr);
    cur = cur->next;
  }

  auto cycle_start = cur;

  for (int i = 5; i < 17; ++i) {
    cur->next = std::make_shared<IntNode>(i, nullptr);
    cur = cur->next;
  }

  cur->next = cycle_start;

  return cyclic_list;
}

std::pair<IntList, IntList> get_common() {
  vector<int> odd = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25};
  vector<int> even = {2, 4, 6, 8, 10, 12, 14};

  auto odd_list = eopi::lists::tool::from_vector(odd);
  auto even_list = eopi::lists::tool::from_vector(even);

  // append the third node of the odd list to the even list
  auto third_odd = odd_list->next->next;
  auto last_even = even_list;
  while (last_even->next)
    last_even = last_even->next;
  last_even->next = third_odd;

  return std::make_pair(odd_list, even_list);
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
  auto merged = eopi::lists::tool::to_vector(merged_list);
  print(merged);

  auto reversed_list = eopi::lists::algorithm::reverse(merged_list);
  auto reversed = eopi::lists::tool::to_vector(reversed_list);
  cout << "Reversed:\n";
  print(reversed);

  cout << "Reversed is cyclic? "
       << eopi::lists::algorithm::is_cyclic(reversed_list) << endl;
  auto cyclic = get_cyclic_list();

  cout << "Can detect cycle: " << eopi::lists::algorithm::is_cyclic(cyclic)
       << endl;

  auto seventeen = eopi::lists::tool::from_vector(std::vector<int>{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17});

  auto batch_4 = eopi::lists::algorithm::reverse(seventeen, 4);

  cout << "Reversing list 0-17 in batches of 4:\n";
  auto batch_4_vec = eopi::lists::tool::to_vector(batch_4);
  print(batch_4_vec);

  auto common = get_common();
  cout << "The first common node of \n";
  print(eopi::lists::tool::to_vector(common.first));
  print(eopi::lists::tool::to_vector(common.second));
  cout << "Is: "
       << eopi::lists::algorithm::find_first_shared(common.first, common.second)
              ->data
       << "\n";

  cout << "Removing the 6th element from:\n";
  print(batch_4_vec);
  eopi::lists::algorithm::remove(eopi::lists::tool::get(batch_4, 6));
  print(eopi::lists::tool::to_vector(batch_4));

  vector<int> duplicates_vec = {0, 0, 0, 1, 2, 2, 2, 2, 2, 3, 4, 5, 5, 5};
  cout << "Duplicate Removal:\n";
  print(duplicates_vec);
  auto duplicates = eopi::lists::tool::from_vector(duplicates_vec);
  eopi::lists::algorithm::unique(duplicates);
  auto uniqued = eopi::lists::tool::to_vector(duplicates);
  cout << "After removal\n";
  print(uniqued);

  {
    vector<int> count_odd(21);
    vector<int> count_even(20);
    std::iota(count_odd.begin(), count_odd.end(), 0);
    std::iota(count_even.begin(), count_even.end(), 0);

    auto lodd = eopi::lists::tool::from_vector(count_odd);
    auto leven = eopi::lists::tool::from_vector(count_even);

    auto even_odd_odd = eopi::lists::algorithm::even_odd(lodd);
    auto even_odd_even = eopi::lists::algorithm::even_odd(leven);
    cout << "Even Odds:\n";
    print(eopi::lists::tool::to_vector(even_odd_odd));
    print(eopi::lists::tool::to_vector(even_odd_even));
  }

  {
    vector<int> count_odd(21);
    vector<int> count_even(20);
    std::iota(count_odd.begin(), count_odd.end(), 0);
    std::iota(count_even.begin(), count_even.end(), 0);

    auto lodd = eopi::lists::tool::from_vector(count_odd);
    auto leven = eopi::lists::tool::from_vector(count_even);

    auto even_odd_odd = eopi::lists::algorithm::zip(lodd);
    auto even_odd_even = eopi::lists::algorithm::zip(leven);
    cout << "Zip:\n";
    print(eopi::lists::tool::to_vector(even_odd_odd));
    print(eopi::lists::tool::to_vector(even_odd_even));
  }

  {
    vector<int> elems(5);
    std::iota(elems.begin(), elems.end(), 0);
    auto postings = eopi::lists::postings::tool::generate_random_posts(elems);
    eopi::lists::postings::tool::print_post(postings);
    auto copy = eopi::lists::postings::algorithm::copy(postings);
    cout << "Original and copy:\n";
    eopi::lists::postings::tool::print_post(postings);
    eopi::lists::postings::tool::print_post(copy);
  }
}

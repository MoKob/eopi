#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "arrays/variants.hpp"

using namespace std;

void test_addition() {
  int lhs = 123181, rhs = 9520051;
  std::cout << "Adding: " << std::bitset<32>(lhs) << " and "
            << std::bitset<32>(rhs) << "\n";
  std::cout << "Expecting:\n" << std::bitset<32>(lhs + rhs) << std::endl;

  auto const to_bitstring = [](auto const &val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
  };

  std::cout << "Got:\n"
            << eopi::array::add_bitstrings(to_bitstring(std::bitset<32>(lhs)),
                                           to_bitstring(std::bitset<32>(rhs)))
            << std::endl;
}

void test_trim() {
  std::cout << "Reasonable spaces in:\n";
  std::cout << "\"" << eopi::array::inplace_trim("   Hello    World!  ") << "\""
            << std::endl;
}

void test_mult_array() {
  auto print = [](auto const &data) {
    std::cout << "[data]";
    for (auto d : data)
      std::cout << " " << d;
    std::cout << std::endl;
  };
  std::vector<int> A = {-1, 2, 3, -4};
  print(A);
  print(eopi::array::mult_array(A));
}

int main() {
  test_addition();
  test_trim();
  test_mult_array();
  return 0;
}

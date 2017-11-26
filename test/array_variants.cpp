#include <bitset>
#include <iostream>
#include <sstream>
#include <string>

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

int main() {
  test_addition();
  return 0;
}

#include <iomanip>
#include <iostream>

#include <vector>

#include "algorithms.hpp"
#include "bigint.hpp"
#include "randoms.hpp"

using namespace std;


template<typename int_type>
void print(vector<int_type> const& vec)
{
    cout << "[vector]";
    for( auto e : vec )
        cout << " " << e;
    cout << endl;
}

int main() {
    vector<int> data = {1,2,4,1,1,3,4,3,3,4,2,3,1};

    cout << "Partitioning by pivot 3:\n";
    print(data);
    eopi::arrays::three_way_partition(data.begin(),data.end(),3);
    print(data);

    eopi::arrays::BigInt value("1234567891234567891234567890");
    cout << "Big value: " << value << endl;
    ++value;
    cout << "Big value incremented: " << value << endl;
    eopi::arrays::BigInt nine("999999999");
    cout << nine << "++ = " << ++nine << endl;
    eopi::arrays::BigInt minus("-1000000000");
    cout << minus << "++ = " << ++minus << endl;


    // boardgames:
    vector<std::uint32_t> winable = {1,3,0,0,4,0,0,0};
    vector<std::uint32_t> not_winable = {1,3,0,0,0,4,0,1};
    cout << "Winable: " << eopi::arrays::is_boardgame_winable(winable) << " Not Winable: " << eopi::arrays::is_boardgame_winable(not_winable) << endl;

    cout << "Removing 0 from:\n";
    print(winable);
    auto new_end = eopi::arrays::remove(winable.begin(),winable.end(),0);
    winable.erase(new_end,winable.end());
    print(winable);
    return 0;
}

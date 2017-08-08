#include <iomanip>
#include <iostream>

#include <vector>

#include "algorithms.hpp"
#include "bigint.hpp"

using namespace std;


void print(vector<int> const& vec)
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
    return 0;
}

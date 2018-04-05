
#include <iostream>

#include "rates.h"

using namespace std;
using namespace rr;

const unit
    mile    {"mile"},
    foot    {"foot"},
    hour    {"hour"},
    minute  {"minute"}
;
equiv<long> mtf {mile, 1L, foot, 5018L}; 



int main() {

    table<long> table;
    table.insert(pair<unit,equiv<long>>{mile, mtf});
    table.insert(pair<unit,equiv<long>>{mile, mtf});
    cout << "hello, world" << endl;
    return 0;
}



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

table<long> tab {{
    {{1, mile}, {5028, foot}},
    {{1, hour}, {60,   minute}}
}};


int main() {
    cout << "hello, world" << endl;
    cout << tab << endl;
    return 0;
}


//
// Created by Ryan Timmons on 3/16/18.
//

#include <utility>
#include <ostream>
#include <unordered_map>
#include <iostream>
#include <list>
#include "Tag.h"

using namespace std;


Tag::Tag(string name,
         unordered_map<string, string> mAttrs)
            :   mName(std::move(name)),
                mAttrs(std::move(mAttrs)),
                children(std::list<Tag>()) {  }

string Tag::get_name() {
    return this->mName;
}





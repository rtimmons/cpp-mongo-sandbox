//
// Created by Ryan Timmons on 3/16/18.
//

#include <utility>
#include <ostream>
#include <unordered_map>
#include <iostream>
#include "Tag.h"

using namespace std;


Tag::Tag(string mName,
        unordered_map<string, string> mAttrs,
        vector<Tag> children)
            :   mName(std::move(mName)),
                mAttrs(std::move(mAttrs)),
                children(std::move(children)) {}

string Tag::get_name() {
    return this->mName;
}





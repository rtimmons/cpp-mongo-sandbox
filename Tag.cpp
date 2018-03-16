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

Tag::Tag(Tag&& rhs)
:   mName{ move(rhs.mName) }
,   mAttrs{ move(rhs.mAttrs) }
,   children{ move(rhs.children) }
{
}

Tag &Tag::operator=(Tag &&rhs)
{
    this->mName = move(rhs.mName);
    this->mAttrs = move(rhs.mAttrs);
    this->children = move(rhs.children);
    return *this;
}



unordered_map<string, string>& Tag::get_attributes() {
    return this->mAttrs;
}

list<Tag>& Tag::get_children() {
    return this->children;
}

void Tag::add_child(Tag&& tag) {
    this->children.push_back(move(tag));
}
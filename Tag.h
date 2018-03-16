//
// Created by Ryan Timmons on 3/16/18.
//

#ifndef SANDBOX_TAG_H
#define SANDBOX_TAG_H

#include <vector>
#include <list>

using namespace std;

class Tag {
    string mName;
    unordered_map<string,string> mAttrs;
    list<Tag> children;
public:
    Tag(string name,
        unordered_map<string, string> mAttrs);
    unordered_map<string,string> get_attributes();
    string get_name();
    virtual ~Tag() = default;
    Tag(Tag&&) = default; // move
    list<Tag> get_children();
    Tag& operator=(Tag&&) = default;
    // copy ops deleted if lass declares move operation
    Tag(const Tag&) = default; // copy
    Tag& operator=(const Tag&) = default;
    friend ostream &operator<<(ostream &os, Tag tag);

    void add_child(Tag tag);
};


#endif //SANDBOX_TAG_H

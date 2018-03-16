//
// Created by Ryan Timmons on 3/16/18.
//

#ifndef SANDBOX_TAG_H
#define SANDBOX_TAG_H

#include <vector>

using namespace std;

class Tag {
    string mName;
    unordered_map<string,string> mAttrs;
    vector<Tag> children;
public:
    Tag(string mName,
        unordered_map<string, string> mAttrs,
        vector<Tag> children);
    unordered_map<string,string> & get_attributes();
    string get_name();
    virtual ~Tag() = default;
    Tag(Tag&&) = default; // move
    Tag& operator=(Tag&&) = default;
    // copy ops deleted if lass declares move operation
    Tag(const Tag&) = default; // copy
    Tag& operator=(const Tag&) = default;
    friend ostream &operator<<(ostream &os, Tag &tag);
};


#endif //SANDBOX_TAG_H

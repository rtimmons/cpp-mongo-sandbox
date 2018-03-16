//
// Created by Ryan Timmons on 3/16/18.
//

#ifndef SANDBOX_TAG_H
#define SANDBOX_TAG_H

#include <vector>
#include <list>
#include <memory>

using namespace std;

class Tag {
public:
    Tag(string name,
        unordered_map<string, string> mAttrs);
    unordered_map<string,string>& get_attributes();
    string get_name();
    virtual ~Tag() = default;
    Tag(Tag&&); // move
    unordered_map<string,unique_ptr<Tag>>& get_children();
    Tag& operator=(Tag&&);
    // copy ops deleted if lass declares move operation
    Tag(const Tag&) = default; // copy
    Tag& operator=(const Tag&) = default;
    friend ostream &operator<<(ostream &os, Tag& tag);

    void add_child(unique_ptr<Tag>&& tag);
private:
    string mName;
    unordered_map<string,string> mAttrs;
    unordered_map<string,std::unique_ptr<Tag>> children;
};


#endif //SANDBOX_TAG_H

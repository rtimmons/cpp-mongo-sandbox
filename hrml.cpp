#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <regex>

#include "Tag.h"

using namespace std;
//
//ostream &&operator<<(ostream &os, const unordered_map<string,string> &m){
//    return std::move(os);
//}
//
//ostream &&operator<<(ostream &os, const vector<Tag> &m){
//    return move(os);
//}



static const regex input_line{
    "^\\s*" // begin
    "<" // open bracket
    "(/)?" // 1: maybe close
    "([a-zA-Z0-9]+)" // 2: tag name
    "\\s*" // spaces
    "(" // attr groups
        "([a-zA-Z0-9]+)" // 3/5/6... attr name
        "\\s*" // space
        "=" // equal
        "\\s*" // space
        "\"([a-zA-Z0-9]+)\"" // attr value
        "\\s*" // spaces
    ")*" // any # of attr groups
    ">" // close bracket
    "\\s*$" // end
};

template<typename T>
ostream &operator<<(ostream &os, unordered_map<string,T> &m) {
    for(auto&& e : m) {
        os << "(" << e.first << "=>" << e.second << ")";
    }
    return os;
}

ostream &operator<<(ostream &os, unordered_map<string,string> &m) {
    for(auto&& e : m) {
        os << e.first << "=\"" << e.second << "\" ";
    }
    return os;
}

ostream &operator<<(ostream &os, Tag &tag) {
    os << "<";
    os << tag.get_name() << " ";
    os << tag.get_attributes();
    os << ">";
}

unordered_map<string, string> &Tag::get_attributes() {
    return this->mAttrs;
}




class Document {
    unordered_map<string,Tag> tags;
    stack<Tag> st;
public:
    Document(vector<string> &lines)
    : tags{ unordered_map<string,Tag>(20) },
      st{ stack<Tag>() }
    {
        for(const auto &line : lines) {
            smatch r;
            if (regex_match(line, r, input_line)) {
                std::unordered_map<string,string> attrs(20);
                bool close = r[1].length() == 1;
                string tag = r[2];
//                cout << "Line   " << line << " close " << close << endl;
//                cout << "   tag " << tag << endl;
                const long size = distance(r.begin(), r.end());
                for(int g=4; g<size; ++g) {
                    const string& name = r[g];
                    const string& val  = r[++g];
                    if (name.length() != 0) {
                        attrs[name] = val;
                    }
                }

                if (close) {
                    if (st.empty()) {
                        throw "Invalid closing (no opening)";
                    }
                    Tag top = st.top(); st.pop();
                    if (tag != top.get_name()) {
                        throw "Invalid closing closed " + top.get_name() + " with tag";
                    }

                    if (st.empty()) {
                        this->tags.insert({move(tag), move(top)});
                    }
                    continue;
                }

                Tag t{tag, std::move(attrs), vector<Tag>()};
                st.push(t);
            }
        }
    }

    friend ostream &operator<<(ostream &os, Document &document) {
        os << "tags: " << document.tags;
        return os;
    }
};


//            bool closing = false;
//            if ( line[0] != '<' ) {
//                throw "Invalid input " + line;
//            }
//            if ( line[1] == '/' ) {
//                closing = true;
//            }


void test() {
    vector<string> lines = {
            "<tag1 value = \"HelloWorld\">",
//            "<tag2 name = \"Name1\">",
//            "</tag2>",
            "</tag1>"
    };
    Document doc {lines};
    cout << doc;
}

int main() {
    test();
    return 0;
}


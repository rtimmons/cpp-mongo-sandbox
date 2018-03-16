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

ostream &operator<<(ostream &os, unordered_map<string,Tag>& m) {
    for(auto& e : m) {
        os << "(" << e.first;
        os << "=>";
        os.flush();
        os << e.second << ")";
    }
    return os;
}

ostream &operator<<(ostream &os, list<Tag>& m) {
    for(auto& e : m) {
        os << e << " ";
    }
    return os;
}

ostream &operator<<(ostream &os, unordered_map<string,string>& m) {
    for(auto& e : m) {
        os << e.first << "=\"" << e.second << "\" ";
    }
    return os;
}

ostream &operator<<(ostream &os, Tag& tag) {
    os << "<";
    os << tag.get_name() << " ";
    os << tag.get_attributes();
    os << ">";

    os << tag.get_children();
    os << "</" << tag.get_name() << ">";
    return os;
}




class Document {
    unordered_map<string,Tag> tags;
    stack<Tag> st;
public:
    explicit Document(vector<string>& lines)
    : tags{ unordered_map<string,Tag>(20) },
      st{ stack<Tag>() }
    {
        for(const auto& line : lines) {
            smatch r;
            if (regex_match(line, r, input_line)) {
                std::unordered_map<string,string> attrs(20);
                bool close = r[1].length() == 1;
                string tag = r[2];
                const long size = distance(r.begin(), r.end());
                for(int g=4; g<size; ++g) {
                    const string name = r[g];
                    const string val  = r[++g];
                    if (name.length() != 0) {
                        attrs[name] = val;
                    }
                }

                if (close) {
                    if (st.empty()) {
                        throw "Invalid closing (no opening)";
                    }
                    Tag top = move(st.top());
                    st.pop();
                    if (tag != top.get_name()) {
                        throw "Invalid closing closed " + top.get_name() + " with tag";
                    }

                    if (st.empty()) {
                        this->tags.insert({move(tag), move(top)});
                    }
                    else {
                        st.top().add_child(move(top));
                    }
                    continue;
                }

                Tag t{move(tag), move(attrs)};
                st.push(t);
            }
        }
    }

    unordered_map<string,Tag> &get_tags() {
        return this->tags;
    }
};

ostream &operator<<(ostream &os, Document& document) {
    cout.flush();
    os << "tags: " << document.get_tags();
    return os;
}


void test() {
    vector<string> lines = {
            "<tag1 value = \"HelloWorld\">",
            "<tag2 name = \"Name1\">",
            R"(<tag3 a = "A" b = "B">)",
            "</tag3>",
            "</tag2>",
            "</tag1>",
            "<other>",
            "</other>"
    };
    Document doc {lines};
    cout << doc;
}

int main() {
    test();
    return 0;
}


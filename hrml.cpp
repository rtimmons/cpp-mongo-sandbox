#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <regex>

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
        "\"([^\"]+)\"" // attr value
        "\\s*" // spaces
    ")*" // any # of attr groups
    ">" // close bracket
    "\\s*$" // end
};

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
    friend ostream &operator<<(ostream &, Tag&);
    void add_child(unique_ptr<Tag>&&);
private:
    string mName;
    unordered_map<string,string> mAttrs;
    unordered_map<string,std::unique_ptr<Tag>> children;
};


Tag::Tag(string name,
         unordered_map<string, string> mAttrs)
        :   mName(std::move(name)),
            mAttrs(std::move(mAttrs)),
            children(unordered_map<string,unique_ptr<Tag>>{}) {  }

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

unordered_map<string,unique_ptr<Tag>>& Tag::get_children() {
    return this->children;
}

void Tag::add_child(unique_ptr<Tag>&& child) {
    this->children[child->get_name()] = move(child);
}


class Document {
    unordered_map<string,unique_ptr<Tag>> tags;
    stack<unique_ptr<Tag>> st;
public:
    explicit Document(vector<string>& lines)
    : tags{ unordered_map<string,unique_ptr<Tag>>(20) },
      st{ stack<unique_ptr<Tag>>() }
    {
        for(const auto& line : lines) {
            smatch r;
            if (regex_match(line, r, input_line)) {
                std::unordered_map<string,string> attrs;
                bool close = r[1].length() == 1;
                string tag_name = r[2];
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
                        cout << "Invalid closing (no opening for tag " << tag_name << ")" << endl;
                        throw "inalid";
                    }
                    unique_ptr<Tag> top = move(st.top());
                    st.pop();
                    if (tag_name != top->get_name()) {
                        cout << "Invalid closing closed " + top->get_name() + " with tag " + tag_name;
                        throw "invalid";
                    }

                    if (st.empty()) {
                        this->tags[tag_name] = move(top);
                    }
                    else {
                        st.top()->add_child(move(top));
                    }
                    continue;
                }
                st.push( make_unique<Tag>(tag_name, attrs) );
            }
            else {
                cout << "Invalid line [" << line << "]" << endl;
            }
        }
    }

    string traverse(string const &path) {
        istringstream iss {path};
        Tag *child = nullptr;
        for(string token; getline(iss, token, '.'); ) {
            size_t tilde = token.find('~');
            string tagname = token.substr(0, tilde == string::npos ? token.length() : tilde);
            if ( child == nullptr ) {
                child = &*this->tags[tagname];
            } else {
                child = &*child->get_children()[tagname];
            }
            if ( child == nullptr ) {
                return "Not Found!";
            }
            if (tilde != string::npos) {
                string attr = token.substr(tilde+1);
                auto found = child->get_attributes().find(attr);
                return found == child->get_attributes().end() ? "Not Found!" : found->second;
            }
        }
        return "Not Found!";
    }

    unordered_map<string,unique_ptr<Tag>> &get_tags() {
        return this->tags;
    }
};



ostream &operator<<(ostream &os, unordered_map<string,Tag>& m) {
    for(auto& e : m) {
        os << "(" << e.first;
        os << "=>";
        os << e.second << ")";
    }
    return os;
}

ostream &operator<<(ostream &os, unordered_map<string,unique_ptr<Tag>>& m) {
    for(auto& e : m) {
        os << *e.second << " ";
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

ostream &operator<<(ostream &os, Document& document) {
    cout.flush();
    os << "tags: " << document.get_tags();
    return os;
}


void test() {
    vector<string> lines = {
//            R"(12 10)",
            R"(<a value = "GoodVal">)",
            R"(<b value = "BadVal" size = "10">)",
            R"(<c height = "auto">)",
            R"(<d size = "3">)",
            R"(<e strength = "200%">)",
            R"(<f a1 = "1" a2 = "2" a3 = "3">)",
            R"(</f>)",
            R"(</e>)",
            R"(</d>)",
            R"(</c>)",
            R"(</b>)",
            R"(</a>)",
//            R"(a.b.c.d.e.f~a1)",
//            R"(a.b.f~a1)",
//            R"(a.b~size)",
//            R"(a.b.c.d.e.f~a2)",
//            R"(a.b.c.d.e.f~a3)",
//            R"(a.c~height)",
//            R"(a.b.d.e~strength)",
//            R"(a.b.c.d.e~strength)",
//            R"(d~sze)",
//            R"(a.b.c.d~size)",
    };
    Document doc {lines};
    cout << doc;
    cout << endl;
    cout << doc.traverse("a.b.c.d.e.f~a1");
    cout << endl << endl;
    cout << doc.traverse("....");
    cout << doc.traverse("~~");
    cout << doc.traverse("tag1.tag2~name");
    cout << doc.traverse("tag1~oiaghih");
    cout << doc.traverse("tag1.tag2.tag3~b");
    cout << doc.traverse("tag1.tag2.tag3~d");
}

void run_input() {
    unsigned long nlines, nqueries;
    cin >> nlines >> nqueries;
    string ignore;
    getline(cin, ignore);
    std::vector<string> lines{};
    while(nlines-- > 0) {
        string line;
        getline(cin, line);
        lines.push_back(line);
    }
    Document doc {lines};

    std::vector<string> queries(nqueries);
    while(nqueries-- > 0) {
        string line;
        getline(cin, line);
        cout << doc.traverse(line) << endl;
    }
}

int main() {
//    run_input();
    test();
    return 0;
}

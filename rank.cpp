//
// Created by Ryan Timmons on 3/16/18.
//
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class BadLengthException : public exception {
    string error;
public:
    BadLengthException(int n_) {
        stringstream ss;
        ss << n_;
        error = std::move(ss.str());
    }
    const char * what () const throw ()
    {
        return error.c_str();
    }
};

bool checkUsername(string username) {
    bool isValid = true;
    int n = username.length();
    if(n < 5) {
        throw BadLengthException(n);
    }
    for(int i = 0; i < n-1; i++) {
        if(username[i] == 'w' && username[i+1] == 'w') {
            isValid = false;
        }
    }
    return isValid;
}

int main() {
//    int T; cin >> T;
    int T = 3;
    while(T--) {
        string username {"Me"};

//        cin >> username;
        try {
            bool isValid = checkUsername(username);
            if(isValid) {
                cout << "Valid" << '\n';
            } else {
                cout << "Invalid" << '\n';
            }
        } catch (BadLengthException e) {
            cout << "Too short: " << e.what() << '\n';
        }
    }
    return 0;
}

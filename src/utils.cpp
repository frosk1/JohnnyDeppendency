//
// Created by frosk on 09.06.17.
//
#include <string>
#include <iostream>
#include <sstream>
#include "utils.h"

vector<string> tokenizer(string sent, char delimiter) {
    vector<string> strings;
    istringstream f(sent);
    string s;
    while (getline(f, s, delimiter)) {
        strings.push_back(s);
    }

    for (string x : strings) cout << x << "*******";

    return strings;
}





//
// Created by frosk on 09.06.17.
//
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include "utils.h"


vector<string> tokenizer(string sent, char delimiter) {
    vector<string> strings;

    size_t pos = 0;
    string token;
    cout << sent << endl;
    while ((pos = sent.find(delimiter)) != std::string::npos) {
        token = sent.substr(0, pos);
        strings.push_back(token);
//        std::cout << token << std::endl;
        sent.erase(0, pos + 1);
    }
    for (string t: strings){
        cout << t << endl;
    }
    return strings;
}



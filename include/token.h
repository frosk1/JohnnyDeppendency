//
// Created by frosk on 09.06.17.
//

#include <iostream>
using namespace std;
#ifndef JOHNNYDEPPENDENCY_TOKEN_H
#define JOHNNYDEPPENDENCY_TOKEN_H

class Token {
public:
    int index, head;
public:
    string word, base, pos, type;
    Token();
    Token(int , string , string , string , int ,string );
};
#endif //JOHNNYDEPPENDENCY_TOKEN_H

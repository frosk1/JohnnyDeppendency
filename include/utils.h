//
// Created by frosk on 09.06.17.
//
#include <vector>
#include <token.h>
using namespace std;

#ifndef JOHNNYDEPPENDENCY_UTILS_H
#define JOHNNYDEPPENDENCY_UTILS_H

vector<string> tokenizer(string sent, char delimiter);
vector<Token> make_token(vector<vector<string>> sen_tokens);
vector<vector<Token>> init_conf(vector<Token> tokens);

#endif //JOHNNYDEPPENDENCY_UTILS_H

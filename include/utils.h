//
// Created by frosk on 09.06.17.
//
#include <vector>
#include <token.h>
#include "oracle.h"
#include "Multiperceptron.h"
#include "feature_ex.h"
using namespace std;

#ifndef JOHNNYDEPPENDENCY_UTILS_H
#define JOHNNYDEPPENDENCY_UTILS_H

vector<string> tokenizer(string sent, char delimiter);
vector<Token> make_token(vector<vector<string>> sen_tokens);
vector<vector<Token>> init_conf(vector<Token> tokens);

void print_parse(vector<vector<Token>> configuration, string action);

pair<int,int> train_perceptron(vector<vector<string>> sen_tokens,
           Multiperceptron& multiperceptron,
           string type,
           unordered_map<string,int>& feature_map);

pair<int, int> parse_dev(vector<vector<string>> sen_tokens,
                         Multiperceptron& multiperceptron,
                         string type,
                         unordered_map<string,int>& feature_map);

void dev_performance(string file_name,
                     Multiperceptron multiperceptron,
                     unordered_map<string, int> feature_map,
                     string type);


#endif //JOHNNYDEPPENDENCY_UTILS_H

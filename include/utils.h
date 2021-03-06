//
// Created by frosk on 09.06.17.
//
#include <vector>
#include <token.h>
#include "oracle.h"
#include "Multiperceptron.h"
#include "feature_ex.h"
#include <string>
#include <fstream>
#include <algorithm>
#include "sstream"

using namespace std;

#ifndef JOHNNYDEPPENDENCY_UTILS_H
#define JOHNNYDEPPENDENCY_UTILS_H

vector<string> tokenizer(string sent, char delimiter);
vector<Token> make_token(vector<vector<string>> sen_tokens);
vector<Token> make_token_blind(vector<vector<string>> sen_tokens);
vector<vector<Token>> init_conf(vector<Token> tokens);

void print_parse(vector<vector<Token>> configuration, string action);

unordered_map<string,string> config_parser(string cfg_file);

void parse_file(string in_file_name,
                string out_file_name,
                Multiperceptron multiperceptron,
                unordered_map<string, int> feature_map,
                string type);


vector<pair<Token,Token>> parse_blind_file(vector<vector<string>> sen_tokens,
                         Multiperceptron& multiperceptron,
                         string type,
                         unordered_map<string,int>& feature_map);

void train_model(string file_name, int max_iter,
                 Multiperceptron& multiperceptron,
                 unordered_map<string, int>& feature_map,
                 string type,
                 bool labeled);

pair<int,int> parse_train(vector<vector<string>> sen_tokens,
                               Multiperceptron& multiperceptron,
                               string type,
                               unordered_map<string,int>& feature_map,
                               bool labeled);

pair<int,int> parse_test(vector<vector<string>> sen_tokens,
                           Multiperceptron& multiperceptron,
                           string type,
                           unordered_map<string,int>& feature_map,
                           bool labeled);

void test_model(string file_name,
                Multiperceptron& multiperceptron,
                unordered_map<string, int>& feature_map,
                string type,
                bool labeled);

#endif //JOHNNYDEPPENDENCY_UTILS_H

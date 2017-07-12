//
// Created by Jean on 13.06.2017.
//
#include <string>
#include <vector>
#include "token.h"
#include <unordered_map>


#ifndef JOHNNYDEPPENDENCY_FEATURE_EX_H
#define JOHNNYDEPPENDENCY_FEATURE_EX_H


vector<string> feature_extraction(vector<vector<Token>> conf, vector<pair<Token,Token>> arc_set);

vector<int> feature_to_index(vector<string> feature_vector, unordered_map<string, int>& feature_map);

vector<int> feature_extraction_2(vector<vector<Token>> conf,
                                 vector<pair<Token,Token>> arc_set,
                                 unordered_map<string, int>& feature_map);
void fill_feature_vec(int index, string cur_feature, vector<int>& int_feature_vec, unordered_map<string, int>& feature_map);

#endif //JOHNNYDEPPENDENCY_FEATURE_EX_H

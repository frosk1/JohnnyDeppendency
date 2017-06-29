//
// Created by Jean on 13.06.2017.
//
#include <string>
#include <vector>
#include "token.h"
#include <unordered_map>


#ifndef JOHNNYDEPPENDENCY_FEATURE_EX_H
#define JOHNNYDEPPENDENCY_FEATURE_EX_H


vector<string> feature_extraction(vector<vector<Token>> conf, vector<tuple<Token,Token>> arc_set);

vector<int> feature_to_index(vector<string> feature_vector, unordered_map<string, int>& feature_map);

#endif //JOHNNYDEPPENDENCY_FEATURE_EX_H

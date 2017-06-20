//
// Created by Jean on 13.06.2017.
//
#include <string>
#include <vector>
#include "token.h"


#ifndef JOHNNYDEPPENDENCY_FEATURE_EX_H
#define JOHNNYDEPPENDENCY_FEATURE_EX_H


class feature_ex {

};
vector<string> feature_extraction(vector<vector<Token>> conf, vector<tuple<Token,Token>> arc_set);

#endif //JOHNNYDEPPENDENCY_FEATURE_EX_H

//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"
#include <string>
#include <vector>
#include "token.h"
#include "utils.h"
#include <tuple>

vector<string> feature_extraction(vector<vector<Token>> conf, vector<tuple<Token,Token>> arc_set){
    vector<Token> buffer = conf[1];
    vector<Token> stack = conf[0];

    vector<string> feature_vector;
    for ( Token token : stack ) {
        feature_vector.push_back("s" + to_string(token.index) + token.word);
        feature_vector.push_back("s" + to_string(token.index) + token.pos);
    }
    for ( Token token : buffer ) {
        feature_vector.push_back("b" + to_string(token.index) + token.word);
        feature_vector.push_back("b" + to_string(token.index) + token.pos);
    }

    for ( tuple<Token,Token> arc : arc_set){
        feature_vector.push_back(get<0>(arc).word + get<1>(arc).type + get<1>(arc).word);
        feature_vector.push_back(get<0>(arc).pos + get<1>(arc).type  + get<1>(arc).pos);
    }

    return feature_vector;
}
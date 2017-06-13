//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"
#include <string>
#include <vector>
#include "token.h"
#include "utils.h"

vector<string> feature_extraction(vector<vector<Token>> conf, vector<tuple<Token,Token>> arc_set){
    vector<Token> buffer = conf[0];
    vector<Token> stack = conf[1];

    vector<string> feature_vector;
    for ( Token token : stack ) {
        feature_vector.push_back("S_" + to_string(token.index) + "_"+ token.word);
        feature_vector.push_back("S_" + to_string(token.index) + "_"+ token.pos);
    }
    for ( Token token : buffer ) {
        feature_vector.push_back("B_" + to_string(token.index) + "_"+ token.word);
        feature_vector.push_back("B_" + to_string(token.index) + "_"+ token.pos);
    }
    
    for ( tuple<Token,Token> arc : arc_set){
        feature_vector.push_back(get<0>(arc).word + "_"+ get<1>(arc).type + "_" + get<1>(arc).word);
        feature_vector.push_back(get<0>(arc).pos + "_"+ get<1>(arc).type + "_" + get<1>(arc).pos);
    }

    return feature_vector;
}
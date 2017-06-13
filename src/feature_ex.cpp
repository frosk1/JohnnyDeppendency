//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"
#include <string>
#include <vector>
#include "token.h"
#include "utils.h"

vector<string> feature_extraction(vector<vector<Token>> conf) {
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

    return feature_vector;
}
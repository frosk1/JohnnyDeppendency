//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"
#include <string>
#include <vector>
#include "token.h"
#include "utils.h"
#include <tuple>

vector<string> feature_extraction(vector<vector<Token>> conf, vector<pair<Token,Token>> arc_set){
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

    for ( pair<Token,Token> arc : arc_set){
        feature_vector.push_back(arc.first.word + arc.second.type + get<1>(arc).word);
        feature_vector.push_back(arc.first.pos + arc.second.type  + get<1>(arc).pos);
    }

    return feature_vector;
}

vector<int> feature_to_index(vector<string> feature_vector, unordered_map<string, int>& feature_map){
    vector<int> int_feature_vec;
    for(string feature: feature_vector) {

        if (feature_map.count(feature) == 0){
            int cur_max_index = feature_map.size();
            feature_map[feature] = cur_max_index+1;
            int_feature_vec.push_back(feature_map[feature]);
        }
        else {
            int_feature_vec.push_back(feature_map[feature]);
        }
    }

    return int_feature_vec;
}




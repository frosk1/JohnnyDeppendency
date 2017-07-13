//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"

vector<string> feature_extraction(vector<vector<Token>> conf,
                                  vector<pair<Token,Token>> arc_set){

    vector<Token> buffer = conf[1];
    vector<Token> stack = conf[0];
    vector<string> feature_vector;

    for (int i = 0; i < 3; ++i) {
        if (stack.size()>i) {
            feature_vector.push_back("s" + to_string(stack[i].index) + stack[i].word);
            feature_vector.push_back("s" + to_string(stack[i].index) + stack[i].pos);
        }

        else if (buffer.size()>i) {
            feature_vector.push_back("b" + to_string(buffer[i].index) + buffer[i].word);
            feature_vector.push_back("b" + to_string(buffer[i].index) + buffer[i].pos);
        }

    }

//    for ( pair<Token,Token> arc : arc_set){
//        feature_vector.push_back(arc.first.word + arc.second.type + arc.second.word);
//        feature_vector.push_back(arc.first.pos + arc.second.type  + arc.second.pos);
//    }

    return feature_vector;
}

vector<int> feature_to_index(vector<string> feature_vector,
                             unordered_map<string, int>& feature_map){

    vector<int> int_feature_vec;
    for(string feature: feature_vector) {

        if (feature_map.count(feature) == 0){
            // feature_map.size()-1 to start with 0
            int cur_max_index = feature_map.size()-1;
            feature_map[feature] = cur_max_index+1;
            int_feature_vec.push_back(cur_max_index+1);
        }
        else {
            int_feature_vec.push_back(feature_map[feature]);
        }
    }

    return int_feature_vec;
}

//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"

vector<string> feature_extraction(vector<vector<Token>> conf,
                                  vector<pair<Token,Token>> arc_set){

    vector<Token> buffer = conf[1];
    vector<Token> stack = conf[0];
    vector<string> feature_vector;


    // Trigrams
    for (int i = 0; i < 1; ++i) {
        if (buffer.size() > i+2) {
            // N0pN1pN2p
            feature_vector.push_back("b" + to_string(i) + buffer[i].pos +
                                     "b" + to_string(i + 1) + buffer[i + 1].pos +
                                     "b" + to_string(i + 2) + buffer[i + 2].pos);
        }
        if (stack.size() > i && buffer.size()>i+1) {
            // S0pN0pN1p
            feature_vector.push_back("s" + to_string(i) + stack[i].pos +
                                     "b" + to_string(i) + buffer[i].pos+
                                     "b" + to_string(i+1) + buffer[i+1].pos);
        }
    }


    // Bigrams
    for (int i = 0; i < 1; ++i) {
        if (stack.size()>i) {
            // S0wpN0wp
            feature_vector.push_back("s" + to_string(i) + stack[i].word + stack[i].pos +
                                             "b" + to_string(i) + buffer[i].word + buffer[i].pos);
            // S0wpN0w
            feature_vector.push_back("s" + to_string(i) + stack[i].word + stack[i].pos +
                                             "b" + to_string(i) + buffer[i].word);
            // S0wN0w
            feature_vector.push_back("s" + to_string(i) + stack[i].word +
                                     "b" + to_string(i) + buffer[i].word + buffer[i].pos);
            // S0wpN0p
            feature_vector.push_back("s" + to_string(i) + stack[i].word + stack[i].pos +
                                     "b" + to_string(i) +  buffer[i].pos);
            // S0pN0wp
            feature_vector.push_back("s" + to_string(i) + stack[i].pos +
                                     "b" + to_string(i) + buffer[i].word + buffer[i].pos);
            // S0wN0w
            feature_vector.push_back("s" + to_string(i) + stack[i].word +
                                     "b" + to_string(i) + buffer[i].word);
            // S0pN0p
            feature_vector.push_back("s" + to_string(i) + stack[i].pos +
                                     "b" + to_string(i) + buffer[i].pos);
            // N0pN1p
            if (buffer.size()>i+1) {
                feature_vector.push_back("b" + to_string(i) + buffer[i].pos +
                                         "b" + to_string(i+1) + buffer[i + 1].pos);
            }
        }

    }

    // Unigrams
    for (int i = 0; i < 3; ++i) {
        if (stack.size()>i && i ==0) {
            feature_vector.push_back("s" + to_string(i) + stack[i].word);
            feature_vector.push_back("s" + to_string(i) + stack[i].pos);
            feature_vector.push_back("s" + to_string(i) + stack[i].word + stack[i].pos);
        }

        if (buffer.size()>i) {
            feature_vector.push_back("b" + to_string(i) + buffer[i].word);
            feature_vector.push_back("b" + to_string(i) + buffer[i].pos);
            feature_vector.push_back("b" + to_string(i) + buffer[i].word + buffer[i].pos);
        }

    }

    for ( pair<Token,Token> arc : arc_set){
        feature_vector.push_back(arc.first.word + arc.second.type + arc.second.word);
        feature_vector.push_back(arc.first.pos + arc.second.type  + arc.second.pos);
    }

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

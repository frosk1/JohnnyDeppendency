//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"

vector<string> feature_extraction(vector<vector<Token>> conf, vector<pair<Token,Token>> arc_set){
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


//    for ( Token token : stack ) {
//        feature_vector.push_back("s" + to_string(token.index) + token.word);
//        feature_vector.push_back("s" + to_string(token.index) + token.pos);
//    }
//    for ( Token token : buffer ) {
//        feature_vector.push_back("b" + to_string(token.index) + token.word);
//        feature_vector.push_back("b" + to_string(token.index) + token.pos);
//    }

//    for ( pair<Token,Token> arc : arc_set){
//        feature_vector.push_back(arc.first.word + arc.second.type + arc.second.word);
//        feature_vector.push_back(arc.first.pos + arc.second.type  + arc.second.pos);
//    }

    return feature_vector;
}

vector<int> feature_to_index(vector<string> feature_vector, unordered_map<string, int>& feature_map){
    vector<int> int_feature_vec;
    for(string feature: feature_vector) {

        if (feature_map.count(feature) == 0){
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


vector<int> feature_extraction_2(vector<vector<Token>> conf,
                                    vector<pair<Token,Token>> arc_set,
                                    unordered_map<string, int>& feature_map){

    vector<int> int_feature_vec;
    int_feature_vec.reserve(conf[0].size()+conf[1].size()+arc_set.size());
    int index = 0;

    for ( Token token : conf[0] ) {
        string cur_feature_1 = "s" + to_string(token.index) + token.word;
        string cur_feature_2 = "s" + to_string(token.index) + token.pos;
        fill_feature_vec(index, cur_feature_1,int_feature_vec, feature_map);
        fill_feature_vec(index, cur_feature_2,int_feature_vec, feature_map);
        index++;

    }
    for ( Token token : conf[1] ) {
        string cur_feature_1 = "b" + to_string(token.index) + token.word;
        string cur_feature_2 = "b" + to_string(token.index) + token.pos;
        fill_feature_vec(index, cur_feature_1,int_feature_vec, feature_map);
        fill_feature_vec(index, cur_feature_2,int_feature_vec, feature_map);
        index++;
    }

    for ( pair<Token,Token> arc : arc_set){
        string cur_feature_1 = arc.first.word + arc.second.type + arc.second.word;
        string cur_feature_2 = arc.first.pos + arc.second.type  + arc.second.pos;
        fill_feature_vec(index, cur_feature_1,int_feature_vec, feature_map);
        fill_feature_vec(index, cur_feature_2,int_feature_vec, feature_map);
        index++;
    }

    return int_feature_vec;
}

void fill_feature_vec(int index, string cur_feature, vector<int>& int_feature_vec, unordered_map<string, int>& feature_map){

    if (feature_map.count(cur_feature) == 0){
        int cur_max_index = feature_map.size();
        feature_map[cur_feature] = cur_max_index+1;
        int_feature_vec[index] = cur_max_index+1;
    }
    else {
        int_feature_vec[index] = feature_map[cur_feature];
        }
}

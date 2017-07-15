//
// Created by Jean on 13.06.2017.
//

#include "feature_ex.h"


pair<Token,Token> get_ld_rd(Token input_token,
                                vector<pair<Token, Token>> arc_set){

        int max_right = input_token.index;
        int max_left = input_token.index;
        Token ld;
        Token rd;
        for(pair<Token,Token> p : arc_set){
            if (p.first.word == input_token.word){
                if (p.second.index > p.first.index && p.second.index > max_right){
                    rd = p.second;
                    max_right = p.second.index;
                }
                else if (p.second.index< p.first.index && p.second.index < max_left){
                    ld = p.second;
                    max_left = p.second.index;
                }
            }
        }
        return make_pair(ld,rd);
    };

vector<string> feature_extraction(vector<vector<Token>> conf,
                                  vector<pair<Token,Token>> arc_set){

    vector<Token> buffer = conf[1];
    vector<Token> stack = conf[0];
    vector<string> feature_vector;


    // Trigrams
        if (buffer.size() >= 3) {
            // B0pB1pB2p
            feature_vector.push_back("b0" +  buffer[0].pos +
                                     "b1" +  buffer[1].pos +
                                     "b2" +  buffer[2].pos);
        }
        if (stack.size() > 0 && buffer.size() >= 2) {
            // S0pB0pB1p
            feature_vector.push_back("s0" + stack.back().pos +
                                     "b0" + buffer[0].pos+
                                     "b1" + buffer[1].pos);
        }


        // Trigrams with ld and rd
        if (stack.size() > 0) {

            pair<Token, Token> s_ld_rd = get_ld_rd(stack.back(), arc_set);
            Token ld_s0 = s_ld_rd.first;
            Token rd_s0 = s_ld_rd.second;

            pair<Token, Token> b_ld_rd = get_ld_rd(buffer[0], arc_set);
            Token ld_b0 = b_ld_rd.first;




            // as Root is the init value of default Token constructor
            // it used in this case to determine if a left/right dependent
            // has been found, if Root is ld or rd, it means ld and rd
            // has been initialized empty and there is no ld/rd !!!
            if (ld_s0.word != "Root") {
                // S0pS0lpB0p;
                feature_vector.push_back("s0"  + stack.back().pos +
                                         "s0"  + ld_s0.pos +
                                         "b0"  + buffer[0].pos);
            }
            if (rd_s0.word != "Root") {
                // S0pS0rpB0p
                feature_vector.push_back("s0" + stack.back().pos +
                                         "s0" + rd_s0.pos +
                                         "b0" + buffer[0].pos);
            }
            if (ld_b0.word != "Root") {
                // S0pN0pB0lp
                feature_vector.push_back("s0" +  stack.back().pos +
                                         "b0" +  buffer[0].pos +
                                         "b0" +  ld_b0.pos);
            }
    }


    // Bigrams
    if (stack.size()>0) {
        // S0wpB0wp
        feature_vector.push_back("s0" + stack.back().word + stack.back().pos +
                                 "b0" + buffer[0].word + buffer[0].pos);
        // S0wpB0w
        feature_vector.push_back("s0" + stack.back().word + stack.back().pos +
                                 "b0" + buffer[0].word);
        // S0wpB0p
        feature_vector.push_back("s0" + stack.back().word + stack.back().pos +
                                 "b0" + buffer[0].pos);
        // S0pB0wp
        feature_vector.push_back("s0" + stack.back().pos +
                                 "b0" + buffer[0].word + buffer[0].pos);
        // S0wB0w
        feature_vector.push_back("s0" + stack.back().word +
                                 "b0" + buffer[0].word);
        // S0pB0p
        feature_vector.push_back("s0" + stack.back().pos +
                                 "b0" + buffer[0].pos);
    }
    if (buffer.size()>=2) {
            // B0pB1p
            feature_vector.push_back("b0" + buffer[0].pos +
                                     "b1" + buffer[1].pos);
        }


    // Unigrams
    if (stack.size()>0) {
        feature_vector.push_back("s0" + stack.back().word);
        feature_vector.push_back("s0" + stack.back().pos);
        feature_vector.push_back("s0" + stack.back().word + stack.back().pos);
        }

    for (int i = 0; i < 3; ++i) {
        if (buffer.size()>i) {
            feature_vector.push_back("b" + to_string(i) + buffer[i].word);
            feature_vector.push_back("b" + to_string(i) + buffer[i].pos);
            feature_vector.push_back("b" + to_string(i) + buffer[i].word + buffer[i].pos);
        }
        else{
            break;
        }

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

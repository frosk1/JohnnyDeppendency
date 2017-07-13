#include <iostream>
#include <fstream>
#include "utils.h"
#include <chrono>
#include <unordered_set>
using namespace chrono;


int main() {
    high_resolution_clock ::time_point start = high_resolution_clock::now();


    string line;
    int c = 0;
    int f = 0;
    int sen_c = 0;
    vector<vector<string>> sen_tokens;
    vector<vector<string>> sen_tokens_dev;
    string type = "standard";
    vector<string> classnames {"shift","RA","LA"};
    Multiperceptron multiperceptron(classnames);
    unordered_map<std::string,int> feature_map;
    vector<pair<Token,Token>> pred_parse_tree;
    vector<pair<Token,Token>> gold_parse_tree;
    int corr = 0;
    int overall = 0;


    int max_iter = 1;

    for (int i = 0; i < max_iter; ++i) {
        corr = 0;
        overall = 0;
        cout << "...Epoch-" << i << "..." << endl;

//        ifstream myfile ("/home/frosk/data/english/train/wsj_train.conll06");
        ifstream myfile ("../resource/wsj_train.first-1k.conll06");
        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                if (line != "") {
                    c++;
                    vector<string> tokens = tokenizer(line, '\t');
                    sen_tokens.push_back(tokens);
                }
                else {
                    pair<int,int> result = train_perceptron(sen_tokens, multiperceptron, type, feature_map);
                    corr += result.first;
                    overall += result.second;

                    sen_tokens.clear();

                    // sentence finished
                    cout << "finished sentence: " << sen_c << endl;
                    sen_c++;
                    c = 1;

                }

                f++;
            }

            // EPOCH finished
            cout << "train correct: " << corr  << "/" << overall << endl;
        }
        else {
            cout << "Unable to open train file";
        }

        myfile.close();
    }
    dev_performance("..resource/wsj_dev.conll06.gold", multiperceptron, feature_map, type) ;




    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count();
    cout << "time: " << duration/1000000 << "s; ";
    cout << (float)(duration/1000000)/(float)60 << "m";
    return 0;
}
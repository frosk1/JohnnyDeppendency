#include <iostream>
#include <fstream>
#include "utils.h"
#include "oracle.h"
#include "Multiperceptron.h"
#include "feature_ex.h"
#include <chrono>
using namespace chrono;


int main() {
    high_resolution_clock ::time_point start = high_resolution_clock::now();


    string line;
    bool oracle_bool = true;
    int c = 0;
    int f = 0;
    int sen_c = 0;
//    ifstream myfile ("../resource/wsj_train.first-1k.conll06");
    vector<vector<string>> sen_tokens;
    string type = "standard";
    vector<string> classnames {"shift","RA","LA"};
    Multiperceptron multiperceptron(classnames);
    unordered_map<std::string,int> feature_map;
    vector<pair<Token,Token>> parse_tree;
    int corr = 0;
    int overall = 0;


    int max_iter = 10;

    for (int i = 0; i < max_iter; ++i) {
        cout << "...Epoch-" << i << "..." << endl;

        ifstream myfile ("../resource/wsj_train.first-1k.conll06");
        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                if (line != "") {
                    c++;
                    vector<string> tokens = tokenizer(line, '\t');
                    sen_tokens.push_back(tokens);
                }
                else {

                    corr += train(sen_tokens, multiperceptron, type, feature_map);
//                    parse_tree = predict(sen_tokens, multiperceptron, type, feature_map);
                    sen_tokens.clear();

//                    cout << "finished sentence: " << sen_c << endl;
                    sen_c++;
                    c = 1;

                }

                f++;
            }

            // EPOCH finished
            cout << "correct: " << corr << "/" << overall <<endl;
            corr = 0;
            overall = 0;
        }
        else {
            cout << "Unable to open file";
        }

        myfile.close();
    }



    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count();
    cout << "time: " << duration/1000000 << "s; ";
    cout << (float)(duration/1000000)/(float)60 << "m";
    return 0;
}
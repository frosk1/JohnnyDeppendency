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
                    vector<Token> tokens = make_token(sen_tokens);
                    vector<vector<Token>> configuration = init_conf(tokens);
                    vector<pair<Token, Token>> arc_set;


//                  while buffer is not emtpy
                    while (configuration[1].size() > 0) {

                        if (oracle_bool) {

                            string action = oracle(configuration, arc_set, type);
                            vector<string> s_feature_vector = feature_extraction(configuration, arc_set);
                            vector<int> feature_vector = feature_to_index(s_feature_vector, feature_map);
                            string pred = multiperceptron.train(feature_vector, action);

//                            cout << "gold: " << action << " pred: " << pred << endl;
                            if (action == pred){ corr ++;}
                            overall++;
//                            print_parse(configuration,action);

                            configuration = parser(configuration, action, type);

                        } else {
                            cout << "using perceptrion";


                        }

                    }


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
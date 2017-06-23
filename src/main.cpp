#include <iostream>
#include <fstream>
#include "utils.h"
#include "oracle.h"
#include "Multiperceptron.h"
#include "feature_ex.h"
#include <unordered_map>

int main() {

    string line;
    bool oracle_bool = true;
    int c = 0;
    int f = 0;
    int sen_c = 0;
    bool not_sent_end = true;
    ifstream myfile ("../resource/wsj_dev.conll06.gold");
    vector<vector<string>> sen_tokens;
    string type = "standard";
    vector<string> classnames {"shift","RA","LA"};
    Multiperceptron multiperceptron(classnames);
    unordered_map<std::string,int> feature_map;

    int correct = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line))
        {
            if (line!= ""){

                c++;
                vector<string> tokens = tokenizer(line, '\t');
                sen_tokens.push_back(tokens);
            }

            else {
                vector<Token> tokens = make_token(sen_tokens);
//              conf =  [[t0] [t1,t2,t3,t4,t5]]
                vector<vector<Token>> configuration = init_conf(tokens);
                vector<tuple<Token,Token>> arc_set;

//                  while buffer is not emtpy
                    while (configuration[1].size() > 0){

                        if (oracle_bool){

                            tuple<string,vector<tuple<Token,Token>>> oracle_result = oracle(configuration,
                                                                                        arc_set, type);

                            string action;
                            action = get<0>(oracle_result);
                            arc_set = get<1>(oracle_result);

                            vector<string> s_feature_vector = feature_extraction(configuration, arc_set);
                            vector<int> feature_vector = feature_to_index(s_feature_vector, feature_map);

                            string pred = multiperceptron.train(feature_vector,action);
                            cout << action << ":::" << pred << endl;
//                            if (pred == action){
//                                correct++;
//                            }
//                            cout << correct << endl;

//                            cout << "STACK:" << endl;
//                            for (Token t: configuration[0]){
//                                cout << t.word << " ";
//                            }
//                            cout << "\nBuffer:" << endl;
//                            for (Token t: configuration[1]){
//                                cout << t.word << " ";
//                            }
//                            cout << endl<< "+++++++"+action +"+++++++" << endl;

                            configuration = parser(configuration, action, type);

                        }

                        else {
                            cout << "using perceptrion";



                        }

                    }


                sen_tokens.clear();
                cout << "finished sentence: " << sen_c << endl;
                sen_c++;
                c = 1;

            }

            f ++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";





    return 0;
}
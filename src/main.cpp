#include <iostream>
#include <fstream>
#include "utils.h"
#include "oracle.h"
#include "Multiperceptron.h"
#include "feature_ex.h"

int main() {

    string line;
    bool oracle_bool = true;
    int c = 0;
    int f = 0;
    bool not_sent_end = true;
    ifstream myfile ("../resource/wsj_dev.conll06.gold");
    vector<vector<string>> sen_tokens;
    string type = "standard";
    vector<string> classnames {"shift","RA","LA"};
    if (myfile.is_open())
    {
        while ( getline (myfile,line)  && f < 700 )
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
                Multiperceptron multiperceptron(classnames);

//                  while buffer is not emtpy
                    while (configuration[1].size() > 0){

                        if (oracle_bool){

//                          action, arc_set = Oracle(conf)
                            tuple<string,vector<tuple<Token,Token>>> oracle_result = oracle(configuration,
                                                                                        arc_set, type);

                            string action;
                            action = get<0>(oracle_result);
                            arc_set = get<1>(oracle_result);

                            vector<string> featue_vector = feature_extraction(configuration, arc_set);



                            multiperceptron.train(featue_vector,action);

                            cout << "STACK:" << endl;
                            for (Token t: configuration[0]){
                                cout << t.word << " ";
                            }
                            cout << "\nBuffer:" << endl;
                            for (Token t: configuration[1]){
                                cout << t.word << " ";
                            }
                            cout << endl<< "+++++++"+action +"+++++++" << endl;

//                          feat_vec = make_feat_vec(conf)
//                          # X, y
//                          train_perc(feat_vec, action)
//                          conf = parser(action)
                            configuration = parser(configuration, action, type);
                            int s = 0;

                        }

                        else {
                            cout << "using perceptrion";



                        }
                    }


                sen_tokens.clear();
                c = 1;

            }
            f ++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}
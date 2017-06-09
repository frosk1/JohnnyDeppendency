#include <iostream>
#include <fstream>
#include "utils.h"
#include "oracle.h"

int main() {
    string line;
    bool oracle_bool = true;
    int c = 0;
    int f = 0;
    bool not_sent_end = true;
    ifstream myfile ("../resource/wsj_dev.conll06.gold");
    vector<vector<string>> sen_tokens;
    string type = "standard";
    if (myfile.is_open())
    {
        while ( getline (myfile,line) && f < 26 )
        {
            cout << "C:"<< c << endl;
            if (line!= ""){

                c++;
                vector<string> tokens = tokenizer(line, '\t');
                sen_tokens.push_back(tokens);
            }

            else {
                vector<Token> tokens = make_token(sen_tokens);
//              conf =  [[t0] [t1,t2,t3,t4,t5]]
                vector<vector<Token>> configuration = init_conf(tokens);
                vector<tuple<int,int>> arc_set;

//                  while buffer is not emtpy
                    while (configuration[1].size() > 0){

                        if (oracle_bool){

//                          action, arc_set = Oracle(conf)
                            tuple<string,vector<tuple<int,int>>> oracle_result = oracle(configuration,
                                                                                        arc_set, type);
                            string action;
                            action = get<0>(oracle_result);
                            arc_set = get<1>(oracle_result);


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
//    class token:
//    ind = 1
//    term= "Ms."
//    term2 = "ms."
//    pos = "NNP"
//    pos2 = ""
//    head = 2
//    type = "NMOD"
    /*
     *
     * [[string1, string2, string3],
     *  [string1, string2, string3,
     *  .....]
     */
//
//
//    def parse(sent, Oracle=True, Classfi=False):
//    if Oracle && not Classfi:
//    tokens = create_tokens(sent)
//# tokens = [t0,t1,t2,t3,t4,t5]
//    conf = init(tokens)
//# [[t0] [t1,t2,t3,t4,t5]]
//
//    while buffer not empty:
//# oracle_bool has extract feat method
//    feat_vec, action = Oracle(conf)
//# X, y
//    train_perc(feat_vec, action)
//    conf = parser(action)
//    elif Classfi && not Oracle:
//    tokens = create_tokens(sent)
//# tokens = [t0,t1,t2,t3,t4,t5]
//    conf = init(tokens)
//# [[t0] [t1,t2,t3,t4,t5]]
//    while buffer not empty:
//    feat_vec = extrac_feat(conf)
//    action = pred_perc(feat_vec)
//    conf = parser(action)
//
//    tree = construct_tree(tokens)
//
//    return tree
//
//
//    def construct_tree(tokens):
//    arcs = [(1,2),(2,3),(,4,5),...]
//    return arcs
//
//
//    main:
//
//#train
//    sentences = read_in conll
//    for sen in sentences:
//    parse(sent, Oracle=True)
//# test
//    sentences = read_in test_conll
//            trees = []
//    for sen in sentences:
//    tree = parse(sent,Classfi=True)
//
//    return 0;
}
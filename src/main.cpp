#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "utils.h"
using namespace std;

int main() {
    string line;
    int c = 0;
    int f = 0;
    bool not_sent_end = true;
    ifstream myfile ("/home/frosk/dev/wsj_dev.conll06.gold");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) && f < 30 )
        {
            cout << "C:"<< c << endl;
//            cout << line<< endl;
            if (line!= ""){
                c++;
                vector<string> tokens = tokenizer(line, '\t');
            }
            else {
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
//# oracle has extract feat method
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
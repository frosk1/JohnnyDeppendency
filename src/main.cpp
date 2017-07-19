#include <iostream>
#include "utils.h"
#include <chrono>
#include "parser_config.h"
#include <algorithm>
using namespace chrono;


int main() {
    high_resolution_clock ::time_point start = high_resolution_clock::now();

    vector<string> clabelded_s = init_classnames_labeled("en","standard");

//    string eager= "eager";
//    vector<string> eager_classnames {"reduce","shift","RA","LA"};
    string standard = "standard";
//    vector<string> standard_classnames {"shift","RA","LA"};

    string train_all = "/home/frosk/data/english/train/wsj_train.conll06";
    string train_1k =  "../resource/wsj_train.first-1k.conll06";
    string dev_blind = "../resource/wsj_dev.conll06.blind";
    string dev_gold = "../resource/wsj_dev.conll06.gold";



    Multiperceptron multiperceptron(clabelded_s);
    unordered_map<string,int> feature_map;


    int max_iter = 1;

    train_model(train_all, max_iter, multiperceptron, feature_map, standard);

//    parse_file(dev_blind,"test_out.txt", multiperceptron, feature_map, standard);
    test_model(dev_gold, multiperceptron, feature_map, standard);



    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count();
    cout << "time: " << duration/1000000 << "s; ";
    cout << (float)(duration/1000000)/(float)60 << "m";
    return 0;
}
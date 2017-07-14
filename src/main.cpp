#include <iostream>
#include <fstream>
#include "utils.h"
#include <chrono>
using namespace chrono;


int main() {
    high_resolution_clock ::time_point start = high_resolution_clock::now();


//    string type = "eager";
//    vector<string> classnames {"reduce","shift","RA","LA"};
    string type = "standard";
    vector<string> classnames {"shift","RA","LA"};

    Multiperceptron multiperceptron(classnames);
    unordered_map<string,int> feature_map;

    string train_all = "/home/frosk/data/english/train/wsj_train.conll06";
    string train_1k =  "../resource/wsj_train.first-1k.conll06";
    string dev_gold = "../resource/wsj_dev.conll06.gold";

    int max_iter = 4;

    train_model(train_1k, max_iter, multiperceptron, feature_map, type);

    dev_performance(dev_gold, multiperceptron, feature_map, type) ;




    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count();
    cout << "time: " << duration/1000000 << "s; ";
    cout << (float)(duration/1000000)/(float)60 << "m";
    return 0;
}
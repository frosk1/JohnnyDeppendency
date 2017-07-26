#include <iostream>
#include "utils.h"
#include <chrono>
#include "parser_config.h"
using namespace chrono;


int main() {
    high_resolution_clock ::time_point start = high_resolution_clock::now();

    vector<string> clabelded_s = init_classnames_labeled("de","standard");

//    string eager= "eager";
//    vector<string> eager_classnames {"reduce","shift","RA","LA"};
    string standard = "standard";
//    vector<string> standard_classnames {"shift","RA","LA"};

    string train_all = "/home/frosk/data/english/train/wsj_train.conll06";
//    string train_all = "/home/users0/wesslijn/dependency-parsing/data/english/train/wsj_train.conll06";
    string train_all_ger = "/home/frosk/data/german/train/tiger-2.2.train.conll06";
//    string train_all_ger = "/home/users0/wesslijn/dependency-parsing/data/german/train/tiger-2.2.train.conll06";

//    string train_all_only_p = "/home/frosk/data/english/train/wsj_train.only-projective.conll06";
    string train_1k =  "../resource/wsj_train.first-1k.conll06";
    string train_1k_ger = "/home/frosk/data/german/train/tiger-2.2.train.first-1k.conll06";
//    string train_5k_ger = "/home/frosk/data/german/train/tiger-2.2.train.first-5k.conll06";
    string train_5k_ger = "/home/users0/wesslijn/dependency-parsing/data/german/train/tiger-2.2.train.first-5k.conll06";

//    string train_1k_only_proj =  "../resource/wsj_train.only-projective.first-1k.conll06";
    string dev_blind = "../resource/wsj_dev.conll06.blind";
    string dev_gold = "../resource/wsj_dev.conll06.gold";
    string dev_blind_ger = "/home/frosk/data/german/dev/tiger-2.2.dev.conll06.blind";
    string dev_gold_ger = "/home/frosk/data/german/dev/tiger-2.2.dev.conll06.gold";

    string test = "../resource/wsj_test.conll06.blind";
//    string test = "/home/users0/wesslijn/dependency-parsing/data/english/test/wsj_test.conll06.blind";
//    string test_ger = "/home/frosk/data/german/test/tiger-2.2.test.conll06.blind";
//    string test_ger = "/home/users0/wesslijn/dependency-parsing/data/german/test/tiger-2.2.test.conll06.blind";


    bool labeled = true;



    Multiperceptron multiperceptron(clabelded_s);
//    Multiperceptron multiperceptron(clabelded_s);
    unordered_map<string,int> feature_map;


    int max_iter = 2;

    train_model(train_all_ger, max_iter, multiperceptron, feature_map, standard, labeled);

    // unlabeled, method knows if labeled or unlabeled from the model classes
    parse_file(dev_blind_ger,"de_labeled_standard_dev_final.txt", multiperceptron, feature_map, standard);
//    parse_file(dev_blind_ger,"de_unlabeled_standard_dev.txt", multiperceptron, feature_map, standard);

   // labeled, method knows if labeled or unlabeled from the model classes
//    parse_file(test,"en_labeled_standard.txt", multiperceptron, feature_map, eager);


//     test_model(dev_gold, multiperceptron, feature_map, standard, labeled);




    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count();
    cout << "time: " << duration/1000000 << "s; ";
    cout << (float)(duration/1000000)/(float)60 << "m";
    return 0;
}

//
// Created by frosk on 13.06.17.
//

#include "Multiperceptron.h"
#include <iostream>
#include <unordered_map>
//class Multiperceptron {
//public:
//    vector<string> classnames;
//    unordered_map<string,Perceptron> perceptrons;
//
//    Multiperceptron(vector<string> classnames);
//    void train(vector<string> feature_vector);
//    void learn_2(vector<string> feature_vector);
//
//private:
//    void initperceptron();
//};

Multiperceptron::Multiperceptron(vector<string> inclassnames) {
    classnames = inclassnames;
    initperceptron();
}

void Multiperceptron::initperceptron() {
   for (string name: classnames){
       Perceptron perceptron(name);
       perceptrons.emplace(name, perceptron);
   }
}

string Multiperceptron::train(vector<int> feature_vector, string gold_label) {
    string best_label = this->best_perceptron(feature_vector);

    if (best_label != gold_label){
        perceptrons[best_label].subtract(feature_vector);
        perceptrons[gold_label].add(feature_vector);
    }
    return best_label;
}


string Multiperceptron::best_perceptron(vector<int> feature_vector) {
    string any_perceptron = classnames[0];

    double best_score = perceptrons[any_perceptron].score(feature_vector);
    string best_label = perceptrons[any_perceptron].label;

    for (string percectron_name: classnames ) {
        if (percectron_name != any_perceptron){

            int cur_score = perceptrons[percectron_name].score(feature_vector);

            if (cur_score > best_score) {
                best_score = cur_score;
                best_label = perceptrons[percectron_name].label;
                }
            }
    }


    return best_label;

}















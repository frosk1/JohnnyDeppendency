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

void Multiperceptron::train(vector<string> feature_vector, string label) {
    learn_2(feature_vector, label);
}

void Multiperceptron::learn_2(vector<string> feature_vector, string label) {
    string best_label = best_perceptron(feature_vector);
    if (best_label != label){
        perceptrons[best_label].subtract(feature_vector);
        perceptrons[label].add(feature_vector);
    }
}

string Multiperceptron::best_perceptron(vector<string> feature_vector) {
    string any_perceptron;
    for (auto it = perceptrons.begin(); it != perceptrons.end(); ++it ) {
        any_perceptron = it->first;
    }

    double best_score = perceptrons[any_perceptron].score(feature_vector);
    string best_label = perceptrons[any_perceptron].label;

    for (auto it = perceptrons.begin(); it != perceptrons.end(); ++it ) {
        Perceptron cur_perceptron = it->second;
        double cur_score = cur_perceptron.score(feature_vector);

        if (cur_score > best_score) {
            best_score = cur_score;
            best_label = cur_perceptron.label;
        }
    }

    return best_label;

}















//
// Created by frosk on 13.06.17.
//

#include "perceptron.h"
#include <vector>
#include <unordered_map>
using namespace std;
#ifndef JOHNNYDEPPENDENCY_MULTIPERCEPTRON_H
#define JOHNNYDEPPENDENCY_MULTIPERCEPTRON_H


class Multiperceptron {
public:
    vector<string> classnames;
    unordered_map<string,Perceptron> perceptrons;

    Multiperceptron(vector<string> classnames);
    string train(vector<int> feature_vector, string label);
    string learn_2(vector<int> feature_vector, string label);
    string best_perceptron(vector<int> feature_vector);

private:
    void initperceptron();
};


#endif //JOHNNYDEPPENDENCY_MULTIPERCEPTRON_H

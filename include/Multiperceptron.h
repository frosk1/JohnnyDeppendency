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
    void train(vector<string> feature_vector);
    void learn_2(vector<string> feature_vector);

private:
    void initperceptron();
};


#endif //JOHNNYDEPPENDENCY_MULTIPERCEPTRON_H
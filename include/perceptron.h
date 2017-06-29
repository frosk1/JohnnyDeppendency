//
// Created by frosk on 13.06.17.
//
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;
#ifndef JOHNNYDEPPENDENCY_PERCEPTRON_H
#define JOHNNYDEPPENDENCY_PERCEPTRON_H


class Perceptron {
public:
    map<int, int> weightVector;
    string label;
    Perceptron(string label);
    Perceptron();
    void initialize(int feature);
    void add(vector<int> feature_vector);
    void subtract(vector<int> feature_vector);
    double score(vector<int> feature_vector);

};


#endif //JOHNNYDEPPENDENCY_PERCEPTRON_H

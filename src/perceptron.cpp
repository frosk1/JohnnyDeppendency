//
// Created by frosk on 13.06.17.
//

#include "perceptron.h"

Perceptron::Perceptron(string inlabel) {
    label = inlabel;
}

void Perceptron::initialize(string feature) {
 weightVector.emplace(feature, 0);
}

void Perceptron::add(vector<string> feature_vector) {
   for (string feature: feature_vector){
       double value = weightVector[feature];
       weightVector.emplace(feature, value +=1);
   }
}

void Perceptron::subtract(vector<string> feature_vector){
   for (string feature: feature_vector){
       double value = weightVector[feature];
       weightVector.emplace(feature, value -=1);
   }
}

double Perceptron::score(vector<string> feature_vector) {
    double sum = 0.0;
    for (string feature: feature_vector){
        if (!weightVector.count(feature)){
            initialize(feature);
            sum += weightVector[feature];
        }
        else {
            sum += weightVector[feature];
        }
    }
    return sum;
}

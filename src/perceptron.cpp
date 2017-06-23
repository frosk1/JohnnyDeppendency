//
// Created by frosk on 13.06.17.
//

#include "perceptron.h"
#include <iostream>

Perceptron::Perceptron(string inlabel) {
    label = inlabel;
}

Perceptron::Perceptron(){
}


void Perceptron::initialize(int feature) {
    weightVector.emplace(feature, 0);
}

void Perceptron::add(vector<int> feature_vector) {
   for (int feature: feature_vector){
       double value = weightVector[feature];
       weightVector[feature] = value +1;
   }
}

void Perceptron::subtract(vector<int> feature_vector){
   for (int feature: feature_vector){
       double value = weightVector[feature];
       weightVector[feature] = value-1;
   }
}

double Perceptron::score(vector<int> feature_vector) {
     double sum = 0.0;
//    double sum;

    for (int feature: feature_vector){
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

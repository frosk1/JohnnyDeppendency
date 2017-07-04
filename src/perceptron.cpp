//
// Created by frosk on 13.06.17.
//

#include "perceptron.h"
#include <iostream>

Perceptron::Perceptron(string inlabel) {
    label = inlabel;
    for (int i = 0; i < 70000; ++i) {
        weightVector.push_back(0);

    }
}

Perceptron::Perceptron(){
}


void Perceptron::initialize(int feature) {
//    weightVector.emplace(feature, 0);
}

void Perceptron::add(vector<int> feature_vector) {
   for (int feature: feature_vector){
//       double value = weightVector[feature];
//       weightVector[feature] = value +1;
       weightVector[feature]++;
   }
}

void Perceptron::subtract(vector<int> feature_vector){
   for (int feature: feature_vector){
//       double value = weightVector[feature];
//       weightVector[feature] = value-1;
       weightVector[feature]--;
   }
}

double Perceptron::score(vector<int> feature_vector) {
     int sum = 0;
//    double sum;

//    for (int feature: feature_vector){
//        if (!weightVector.count(feature)){
//            initialize(feature);
//            sum += weightVector[feature];
//        }
//        else {
//            sum += weightVector[feature];
//        }
//    }
    for (int feature: feature_vector){
        if (feature > weightVector.size()){
            int dif = feature-weightVector.size();
            for (int i = 0; i < dif; ++i) {
                weightVector.push_back(0);
            }
        }
        else {
            sum += weightVector[feature];
        }
    }
    return sum;
}

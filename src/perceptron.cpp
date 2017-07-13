//
// Created by frosk on 13.06.17.
//

#include "perceptron.h"

Perceptron::Perceptron(string inlabel) {
    label = inlabel;
    weightVector.resize(1000);
}

Perceptron::Perceptron(){
}


void Perceptron::add(vector<int> feature_vector) {
   for (int feature: feature_vector){
       weightVector[feature]++;
   }
}

void Perceptron::subtract(vector<int> feature_vector){
   for (int feature: feature_vector){
       weightVector[feature]--;
   }
}

double Perceptron::score(vector<int> feature_vector) {
     int sum = 0;
    for (int feature: feature_vector) {

        if (feature >= weightVector.size()) {
            weightVector.resize(weightVector.size() + 1);
        } else {
            sum += weightVector[feature];
        }
    }
    return sum;
}

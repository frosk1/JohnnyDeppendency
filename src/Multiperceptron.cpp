//
// Created by frosk on 13.06.17.
//

#include "Multiperceptron.h"

Multiperceptron::Multiperceptron(vector<string> inclassnames) {
    classnames = inclassnames;
    initperceptron();
}

void Multiperceptron::initperceptron() {
   for (string name: classnames){
       Perceptron perceptron(name);
       perceptrons[name] = perceptron;
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

//    cout << "....................................." << endl;
    double best_score = perceptrons[any_perceptron].score(feature_vector);
    string best_label = perceptrons[any_perceptron].label;
//    cout << best_label << "::" << best_score << endl;

    for (string percectron_name: classnames ) {
        if (percectron_name != any_perceptron){

            int cur_score = perceptrons[percectron_name].score(feature_vector);
//            cout << perceptrons[percectron_name].label << ":: " << cur_score << endl;

            if (cur_score > best_score) {
                best_score = cur_score;
                best_label = perceptrons[percectron_name].label;
                }
            }
    }


//    cout << "best: " << best_label << endl;
//    cout << "....................................." << endl;
    return best_label;

}















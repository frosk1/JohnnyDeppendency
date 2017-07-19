#include <string>
#include "utils.h"
#include <fstream>
#include <algorithm>


vector<string> tokenizer(string sent, char delimiter) {
    vector<string> tokens;

    size_t pos = 0;
    string token;
    while ((pos = sent.find(delimiter)) != std::string::npos) {
        token = sent.substr(0, pos);
        tokens.push_back(token);
        sent.erase(0, pos + 1);
    }
    return tokens;
}

vector<Token> make_token(vector<vector<string>> sen_tokens){
    vector<Token> tokens;
    tokens.reserve(sen_tokens.size());
    for (vector<string> token : sen_tokens){

        Token t(stoi(token[0]), token[1], token[2],
                token[3], stoi(token[6]), token[7]);
        tokens.push_back(t);
    }

    return tokens;

}

vector<Token> make_token_blind(vector<vector<string>> sen_tokens){
    vector<Token> tokens;
    tokens.reserve(sen_tokens.size());
    for (vector<string> token : sen_tokens){

        Token t(stoi(token[0]), token[1],
                token[2], token[3]);
        tokens.push_back(t);
    }

    return tokens;

}

vector<vector<Token>> init_conf(vector<Token> tokens){
    vector<vector<Token>> configuration;
//    configuration.reserve(2);
    Token root;
    vector<Token> stack {root};
//    stack.reserve(tokens.size());

    configuration.push_back(stack);
    configuration.push_back(tokens);

    return configuration;
}


void print_parse(vector<vector<Token>> configuration, string action){
    cout << "STACK" << endl;
    for (Token t : configuration[0]) cout << t.word << " ";
    cout << endl;
    cout << "Buffer" << endl;
    for (Token t : configuration[1]) cout << t.word << " ";
    cout << endl;
    cout << "ACTION " << action << endl;
}

pair<int,int> parse_train(vector<vector<string>> sen_tokens,
            Multiperceptron& multiperceptron,
            string type,
            unordered_map<string,int>& feature_map){

    vector<Token> tokens = make_token(sen_tokens);
    vector<vector<Token>> configuration = init_conf(tokens);
    vector<pair<Token, Token>> arc_set;
    int corr = 0;
    int overall =0;

//     while buffer is not emtpy
   while (configuration[1].size() > 0) {

        vector<string> s_feature_vector = feature_extraction(configuration, arc_set);
        vector<int> feature_vector = feature_to_index(s_feature_vector, feature_map);

        string gold_label= oracle(configuration, arc_set, type);
        string pred = multiperceptron.train(feature_vector, gold_label);

        configuration = parser(configuration, gold_label, arc_set, type);

        if (gold_label == pred){ corr ++;}
        overall++;
    }
    return make_pair(corr,overall);
}

vector<pair<Token,Token>> parse_blind_file(vector<vector<string>> sen_tokens,
            Multiperceptron& multiperceptron,
            string type,
            unordered_map<string,int>& feature_map){

    vector<Token> tokens = make_token_blind(sen_tokens);
    vector<vector<Token>> configuration = init_conf(tokens);
    vector<pair<Token, Token>> arc_set;
    int corr = 0;
    int all = 0;

//     while buffer is not emtpy
   while (configuration[1].size() > 0) {

        vector<string> s_feature_vector = feature_extraction(configuration, arc_set);
        vector<int> feature_vector = feature_to_index(s_feature_vector, feature_map);

        string gold_label = multiperceptron.best_perceptron(feature_vector);

//        string pred = oracle(configuration, arc_set, type);

//       if (pred==action) {corr++;}
//       all++;

        configuration = parser(configuration, gold_label, arc_set, type);
    }

    return arc_set;
}

void train_model(string file_name, int max_iter,
                 Multiperceptron& multiperceptron,
                 unordered_map<string, int>& feature_map,
                 string type) {

    int corr = 0;
    int overall = 0;
    vector<vector<string>> sen_tokens;

    string line;
    int sen_c = 0;

    for (int i = 0; i < max_iter; ++i) {
        corr = 0;
        overall = 0;
        cout << "...Epoch-" << i << "..." << endl;
        ifstream myfile (file_name);

        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                if (line != "") {
                    vector<string> tokens = tokenizer(line, '\t');
                    sen_tokens.push_back(tokens);
                }
                else {
                    pair<int,int> result = parse_train(sen_tokens, multiperceptron, type, feature_map);
                    corr += result.first;
                    overall += result.second;

                    // sentence finished
                    // cout << "finished sentence: " << sen_c << endl;
                    sen_tokens.clear();
                    sen_c++;
                }
            }
            // EPOCH finished
            cout << "train acc: " << (float)corr/(float)overall << endl;
            cout << "overall datapoints: " << (float) overall << endl;
            sen_c = 0;
        }
        else {
            cout << "Unable to open train file";
        }
        myfile.close();
    }
    cout << "Finished Training with: " << max_iter << " Epochs" << endl;
}


void parse_file(string in_file_name,
                string out_file_name,
                Multiperceptron multiperceptron,
                unordered_map<string, int> feature_map,
                string type) {

    vector<vector<string>> sen_tokens_dev;

    string line2;
    ifstream devfile(in_file_name);
    ofstream out_file;
    out_file.open (out_file_name);
//    out_file << "Writing this to a file.\n";

    if (devfile.is_open()) {
        while (getline(devfile, line2)) {
            if (line2 != "") {
                vector<string> tokens = tokenizer(line2, '\t');
                sen_tokens_dev.push_back(tokens);
            }
            else {
                vector<pair<Token,Token>> arc_set = parse_blind_file(sen_tokens_dev, multiperceptron, type, feature_map);
                vector<Token> dependents;
                for (pair<Token,Token> p : arc_set) dependents.push_back(p.second);
                sort(dependents.begin(),dependents.end());
                for (Token t : dependents) {
                    string cur_line = to_string(t.index) + "\t" + t.word + "\t" + t.base
                                      + "\t" + t.pos + "\t" + "_" + "\t" + "_" + "\t" +
                                      to_string(t.head) + "\t" + t.type + "\t" + "_" +
                                      "\t" + "_" + "\n";
                    out_file << (cur_line);
                }
                out_file << ("\n");
                sen_tokens_dev.clear();
            }
        }
    }
    else {
        cout << "Unable to open dev file: " << in_file_name << endl;
    }
}

pair<int,int> parse_test(vector<vector<string>> sen_tokens,
            Multiperceptron& multiperceptron,
            string type,
            unordered_map<string,int>& feature_map){

    vector<Token> tokens = make_token(sen_tokens);
    vector<vector<Token>> configuration = init_conf(tokens);
    vector<pair<Token, Token>> arc_set;
    int corr = 0;
    int all = 0;

//     while buffer is not emtpy
   while (configuration[1].size() > 0) {

        vector<string> s_feature_vector = feature_extraction(configuration, arc_set);
        vector<int> feature_vector = feature_to_index(s_feature_vector, feature_map);

        string pred = multiperceptron.best_perceptron(feature_vector);

        string gold_label = oracle(configuration, arc_set, type);

       if (pred == gold_label) corr++;
       all++;

        configuration = parser(configuration, gold_label, arc_set, type);
    }

    return make_pair(corr,all);
}

void test_model(string file_name,
                 Multiperceptron& multiperceptron,
                 unordered_map<string, int>& feature_map,
                 string type) {

    int corr = 0;
    int overall = 0;
    vector<vector<string>> sen_tokens;

    string line;
    corr = 0;
    overall = 0;
    ifstream myfile (file_name);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line != "") {
                vector<string> tokens = tokenizer(line, '\t');
                sen_tokens.push_back(tokens);
            }
            else {
                pair<int,int> result = parse_test(sen_tokens, multiperceptron, type, feature_map);
                corr += result.first;
                overall += result.second;

                sen_tokens.clear();
            }
        }
        // Testing finished
        cout << "test acc: " << (float)corr/(float)overall << endl;
        cout << "overall datapoints: " << (float) overall << endl;
    }
    else {
        cout << "Unable to open train file";
    }
    myfile.close();
    cout << "Finished testing" << endl;
}
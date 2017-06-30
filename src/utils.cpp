#include <string>
#include "utils.h"


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

vector<vector<Token>> init_conf(vector<Token> tokens){
    vector<vector<Token>> configuration;
    configuration.reserve(2);
    Token root;
    vector<Token> stack {root};
    stack.reserve(tokens.size());

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

int train(vector<vector<string>> sen_tokens,
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

        string action = oracle(configuration, arc_set, type);
        string pred = multiperceptron.train(feature_vector, action);


        configuration = parser(configuration, action, type);
        if (action == pred){ corr ++;}
        overall++;
    }
    return corr;
}

vector<pair<Token, Token>> predict(vector<vector<string>> sen_tokens,
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

        string action = multiperceptron.best_perceptron(feature_vector);
        configuration = parser(configuration, action, type);
    }

    return arc_set;
}


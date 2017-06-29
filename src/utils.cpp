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




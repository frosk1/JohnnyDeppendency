//
// Created by frosk on 09.06.17.
//
#include "oracle.h"
#include <typeinfo>


bool hasallchildren(int cur_token_ind, vector<Token> buffer, string type){
    if(type == "standard") {
        // standard: start by 1 to skip buffer front
        for (int i=1; i < buffer.size(); ++i) {
            if (cur_token_ind == buffer[i].head) {
                return false;
            }
        }
        return true;
    }
    else {
        // eager: start by 0 to get all buffer elements
        for (int i=0; i < buffer.size(); ++i) {
            if (cur_token_ind == buffer[i].head) {
                return false;
            }
        }
        return true;
    }
}


bool hashead(int stack_top_ind, vector<pair<Token,Token>> arc_set){
    for (pair<Token,Token> arc : arc_set){
       if (stack_top_ind == arc.second.index){
          return true;
       }
    }
    return false;
}


bool stackisnotroot(Token top_stack){
    if (top_stack.word == "Root"){
        return false;
    }
    else{
        return true;
    }

}

string standard_action(
        vector<vector<Token>> configuration,
        string type)
{

    vector<Token> stack = configuration[0];

    if (stack.size() == 0){
        return "shift";
    }

    vector<Token> buffer = configuration[1];
    Token stack_top = stack.back();
    Token buffer_front = buffer[0];
    int stack_top_head = stack_top.head;
    int stack_top_ind = stack_top.index;
    int buffer_front_head = buffer_front.head;
    int buffer_front_ind = buffer_front.index;


    if (stack_top_head == buffer_front_ind && stackisnotroot(stack_top)) {
//        return "LA";
        return "LA"+stack_top.type;

    } else if (buffer_front_head == stack_top_ind &&  hasallchildren(buffer_front_ind, buffer, type)) {
//        return "RA";
        return "RA"+buffer_front.type;

    } else {

        return "shift";
    }
}

string eager_action(
        vector<vector<Token>> configuration,
        vector<pair<Token,Token>>& arc_set,
        string type)
{

    vector<Token> stack = configuration[0];
    vector<Token> buffer = configuration[1];
    Token stack_top = stack.back();
    Token buffer_front = buffer[0];
    int stack_top_head = stack_top.head;
    int stack_top_ind = stack_top.index;
    int buffer_front_head = buffer_front.head;
    int buffer_front_ind = buffer_front.index;


    if (stack_top_head == buffer_front_ind && stackisnotroot(stack_top)) {
//        return "LA";
        return "LA"+stack_top.type;
    }
    else if (buffer_front_head == stack_top_ind) {
//        return "RA";
        return "RA"+buffer_front.type;
    }
    else if( hashead(stack_top_ind, arc_set) && hasallchildren(stack_top_ind, buffer, type)){
            return "reduce";
        }
    else {
        return "shift";
    }
}


string oracle(vector<vector<Token>> configuration,
              vector<pair<Token,Token>>& arc_set,
              string type){

    if (type == "standard") {
        return standard_action(configuration, type);
    }
    else {
        return eager_action(configuration, arc_set, type);
    }
}

vector<vector<Token>> parser(
        vector<vector<Token>> configuration,
        string gold_label,
        vector<pair<Token,Token>>& arc_set,
        string type) {

    vector<Token> stack = configuration[0];
    vector<Token> buffer = configuration[1];
    string action;

    if(gold_label.compare("shift") != 0) {
        action = gold_label.substr(0, 2);
        }
    else{
        action = gold_label;
        }



   if (type == "standard") {
       if (action == "LA") {

           // Set the arc_label and index within the arc_set
           // only when testing, parsing a blind file
            if (stack.back().type.empty()){
                stack.back().type = gold_label.substr(2,gold_label.size());
                stack.back().head = buffer[0].index;
            }

           arc_set.push_back( pair<Token,Token> (buffer[0], stack.back()));
           //      pop top most token on the stack
           stack.pop_back();
       }
       else if (action == "RA") {

           // Set the arc_label and index within the arc_set
           // only when testing, parsing a blind file
           if (buffer[0].type.empty()){
               buffer[0].type = gold_label.substr(2,gold_label.size());
               buffer[0].head = stack.back().index;
           }
           arc_set.push_back( pair<Token,Token> (stack.back(), buffer[0]));
//           move top stack to front buffer; deleting front buffer with assignment
           buffer[0] = stack.back();
           stack.pop_back();
       }
       else {
//           move front of buffer to top of stack; no stack deletion, but buffer front deletion
           stack.push_back(buffer[0]);
           buffer.erase(buffer.begin());
       }
   }

   else if (type == "eager") {

       if (action == "LA" || action == "reduce") {
           if (action == "LA") {
               arc_set.push_back( pair<Token,Token> (buffer[0], stack.back()));
           }
           //      pop top most token on the stack
           stack.pop_back();
       }
       else if (action == "RA" || action == "shift") {
           if(action == "RA"){
               arc_set.push_back( pair<Token,Token> (stack.back(), buffer[0]));
           }
//           move front of buffer to top of stack; no stack deletion, but buffer front deletion
           stack.push_back(buffer[0]);
           buffer.erase(buffer.begin());
       }
   }

    configuration[0] = stack;
    configuration[1] = buffer;
    return configuration;
}

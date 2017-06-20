//
// Created by frosk on 09.06.17.
//
#include "oracle.h"



bool hasallchildren(int cur_token_ind, vector<Token> buffer){
    for (int i = 1; i < buffer.size(); ++i) {
        if (cur_token_ind == buffer[i].head) {
            cout << cur_token_ind << endl;
            cout << buffer[i].head << endl;
            return false;
        }
    }
    return true;
}

bool hashead(int stack_top_ind, vector<tuple<Token,Token>> arc_set){
    for (tuple<Token,Token> arc : arc_set){
       if (stack_top_ind == get<1>(arc).index){
          return true;
       }
        else{
           return false;
       }
    }
}

tuple<string,vector<tuple<Token,Token>>> standard_action(
        vector<vector<Token>> configuration,
        vector<tuple<Token,Token>> arc_set )
{
    vector<Token> stack = configuration[0];
    vector<Token> buffer = configuration[1];
    Token stack_top = stack.back();
    Token buffer_front = buffer[0];
    int stack_top_head = stack_top.head;
    int stack_top_ind = stack_top.index;
    int buffer_front_head = buffer_front.head;
    int buffer_front_ind = buffer_front.index;


    if (stack_top_head == buffer_front_ind) {
        arc_set.push_back( tuple<Token,Token> (buffer_front, stack_top));

        tuple<string, vector<tuple<Token,Token>>> action ("LA", arc_set);
        return action;
    } else if (buffer_front_head == stack_top_ind &&  hasallchildren(buffer_front_ind, buffer)) {
        arc_set.push_back( tuple<Token,Token> (stack_top, buffer_front));

        tuple<string, vector<tuple<Token,Token>>> action ("RA", arc_set);
        return action;
    } else {

        tuple<string, vector<tuple<Token,Token>>> action ("shift", arc_set);
        return action;
    }
}

tuple<string,vector<tuple<Token,Token>>> eager_action(
        vector<vector<Token>> configuration,
        vector<tuple<Token,Token>> arc_set)
{

    vector<Token> stack = configuration[0];
    vector<Token> buffer = configuration[1];
    Token stack_top = stack.back();
    Token buffer_front = buffer[0];
    int stack_top_head = stack_top.head;
    int stack_top_ind = stack_top.index;
    int buffer_front_head = buffer_front.head;
    int buffer_front_ind = buffer_front.index;


    if (stack_top_head == buffer_front_ind) {
        arc_set.push_back( tuple<Token,Token> (buffer_front, stack_top));

        tuple<string, vector<tuple<Token,Token>>> action ("LA", arc_set);
        return action;
    }
    else if (buffer_front_head == stack_top_ind) {
        arc_set.push_back( tuple<Token,Token> (stack_top, buffer_front));

        tuple<string, vector<tuple<Token,Token>>> action ("RA", arc_set);
        return action;
    }
    else if( hashead(stack_top_ind, arc_set) && hasallchildren(stack_top_ind, buffer)){
            tuple<string, vector<tuple<Token,Token>>> action ("reduce", arc_set);
            return action;
        }
    else {
        tuple<string, vector<tuple<Token,Token>>> action ("shift", arc_set);
        return action;
    }
}


tuple<string,vector<tuple<Token,Token>>> oracle(vector<vector<Token>> configuration,
                                            vector<tuple<Token,Token>> arc_set ,
                                            string type){

    if (type == "standard") {
        return standard_action(configuration, arc_set);
    }
    else {
        return eager_action(configuration, arc_set);
    }
}

vector<vector<Token>> parser(
        vector<vector<Token>> configuration,
        string action,
        string type) {

    vector<Token> stack = configuration[0];
    vector<Token> buffer = configuration[1];


    Token stack_top = stack.back();
    Token buffer_front = buffer[0];
    int dummy;


   if (type == "standard") {
       if (action == "LA") {
           //      pop top most token on the stack
           stack.pop_back();
       }
       else if (action == "RA") {
//           move top stack to front buffer; deleting front buffer with assignment
          buffer_front = stack_top;
           stack.pop_back();
       }
       else {
//           move front of buffer to top of stack; no stack deletion, but buffer front deletion
           stack.push_back(buffer_front);
           buffer.erase(buffer.begin());
       }
   }

   else if (type == "eager") {

       if (action == "LA" || action == "reduce") {
           //      pop top most token on the stack
           stack.pop_back();
       }
       else if (action == "RA" || action == "shift") {
//           move front of buffer to top of stack; no stack deletion, but buffer front deletion
           stack.push_back(buffer_front);
           buffer.erase(buffer.begin());
       }
   }

    configuration[0] = stack;
    configuration[1] = buffer;
    return configuration;
}

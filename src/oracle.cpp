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

bool hashead(int stack_top_ind, vector<tuple<int,int>> arc_set){
    for (tuple<int,int> arc : arc_set){
       if (stack_top_ind == get<1>(arc)){
          return true;
       }
        else{
           return false;
       }
    }
}

tuple<string,vector<tuple<int,int>>> standard_action(
        vector<vector<Token>> configuration,
        vector<tuple<int,int>> arc_set )
{
    vector<Token> buffer = configuration[1];
    int stack_top_head = configuration[0].back().head;
    int stack_top_ind = configuration[0].back().index;
    int buffer_front_head = configuration[1][0].head;
    int buffer_front_ind = configuration[1][0].index;


    if (stack_top_head == buffer_front_ind) {
        arc_set.push_back( tuple<int,int> (buffer_front_ind, stack_top_ind));

        tuple<string, vector<tuple<int,int>>> action ("LA", arc_set);
        return action;
    } else if (buffer_front_head == stack_top_ind &&  hasallchildren(buffer_front_ind, buffer)) {
        arc_set.push_back( tuple<int,int> (stack_top_ind, buffer_front_ind));

        tuple<string, vector<tuple<int,int>>> action ("RA", arc_set);
        return action;
    } else {

        tuple<string, vector<tuple<int,int>>> action ("shift", arc_set);
        return action;
    }
}

tuple<string,vector<tuple<int,int>>> eager_action(
        vector<vector<Token>> configuration,
        vector<tuple<int,int>> arc_set)
{

    vector<Token> buffer = configuration[1];
    int stack_top_head = configuration[0].back().head;
    int stack_top_ind = configuration[0].back().index;
    int buffer_front_head = configuration[1][0].head;
    int buffer_front_ind = configuration[1][0].index;


    if (stack_top_head == buffer_front_ind) {
        arc_set.push_back( tuple<int,int> (buffer_front_ind, stack_top_ind));

        tuple<string, vector<tuple<int,int>>> action ("LA", arc_set);
        return action;
    }
    else if (buffer_front_head == stack_top_ind) {
        arc_set.push_back( tuple<int,int> (stack_top_ind, buffer_front_ind));

        tuple<string, vector<tuple<int,int>>> action ("RA", arc_set);
        return action;
    }
    else if( hashead(stack_top_ind, arc_set) && hasallchildren(stack_top_ind, buffer)){
            tuple<string, vector<tuple<int,int>>> action ("reduce", arc_set);
            return action;
        }
    else {
        tuple<string, vector<tuple<int,int>>> action ("shift", arc_set);
        return action;
    }
}


tuple<string,vector<tuple<int,int>>> oracle(vector<vector<Token>> configuration,
                                            vector<tuple<int,int>> arc_set ,
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

   if (type == "standard") {
       if (action == "LA") {
           //      pop top most token on the stack
           configuration[0].pop_back();
       }
       else if (action == "RA") {
//           move top stack to front buffer; deleting front buffer with assignment
          configuration[1][0] = configuration[0].back();
           configuration[0].pop_back();
       }
       else {
//           move front of buffer to top of stack; no stack deletion, but buffer front deletion
           configuration[0].push_back(configuration[1][0]);
           configuration[1].erase(configuration[1].begin());
       }
   }

   else if (type == "eager") {

       if (action == "LA" || action == "reduce") {
           //      pop top most token on the stack
           configuration[0].pop_back();
       }
       else if (action == "RA" || action == "shift") {
//           move front of buffer to top of stack; no stack deletion, but buffer front deletion
           configuration[0].push_back(configuration[1][0]);
           configuration[1].erase(configuration[1].begin());
       }
   }

    return configuration;
}

//
// Created by frosk on 09.06.17.
//

#include "oracle.h"
tuple<string,vector<tuple<int,int>>> standard_action(
        vector<vector<Token>> configuration,
        vector<tuple<int,int>> arc_set )
{
    int stack_top_head = configuration[0][-1].head;
    int stack_top_ind = configuration[0][-1].index;
    int buffer_front_head = configuration[1][0].head;
    int buffer_front_ind = configuration[1][0].index;


    if (stack_top_head == buffer_front_ind) {
        arc_set.push_back( tuple<int,int> (buffer_front_ind, stack_top_ind));

        tuple<string, vector<tuple<int,int>>> action ("LA", arc_set);
        return action;
    } else if (buffer_front_head == stack_top_ind) {
        arc_set.push_back( tuple<int,int> (stack_top_ind, buffer_front_ind));

        tuple<string, vector<tuple<int,int>>> action ("RA", arc_set);
        return action;
    } else {

        tuple<string, vector<tuple<int,int>>> action ("shift", arc_set);
        return action;
    }
}

bool hasallchildren(int stack_top_ind, vector<Token> buffer){
   for (Token t : buffer){
       if (stack_top_ind == t.head){
           return true;
       }
       else{
           return false;
       }
   }

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


tuple<string,vector<tuple<int,int>>> eager_action(
        vector<vector<Token>> configuration,
        vector<tuple<int,int>> arc_set)
{

    vector<Token> buffer = configuration[1];
    int stack_top_head = configuration[0][-1].head;
    int stack_top_ind = configuration[0][-1].index;
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
                                            string type="eager"){

    if (type == "standard") {
        return standard_action(configuration, arc_set);
    }
    else {
        return eager_action(configuration, arc_set);
    }
}


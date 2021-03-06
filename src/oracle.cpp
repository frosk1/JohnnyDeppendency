//
// Created by frosk on 09.06.17.
//
#include "oracle.h"


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
        string parse_type,
        bool labeled)
{

    vector<Token> stack = configuration[0];

    if (stack.size() == 0){
//        cout << "0 shift" << endl;
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
        if (labeled) {
            return "LA"+stack_top.type;
        }
        else {
            return "LA";
        }

    } else if (buffer_front_head == stack_top_ind &&  hasallchildren(buffer_front_ind, buffer, parse_type)) {
        if (labeled) {
            return "RA"+buffer_front.type;
        }
        else {
            return "RA";
        }

    } else if (buffer.size()>1){
//        cout << "buf_sizeinfunc:"<<  buffer.size() << endl;
//        cout << "yep_shift" << endl;

        return "shift";
    }
//    else {
////        cout << "nothing trifft zu" << endl;
//    }

}

string eager_action(
        vector<vector<Token>> configuration,
        vector<pair<Token,Token>>& arc_set,
        string parse_type,
        bool labeled)

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
        if (labeled){
            return "LA"+stack_top.type;
        }
        else {
            return "LA";
        }
    }
    else if (buffer_front_head == stack_top_ind) {
        if (labeled){
            return "RA"+buffer_front.type;
        }
        else {
            return "RA";
        }
    }
    else if( hashead(stack_top_ind, arc_set) && hasallchildren(stack_top_ind, buffer, parse_type)){
            return "reduce";
        }
    else {
        return "shift";
    }
}


string oracle(vector<vector<Token>> configuration,
              vector<pair<Token,Token>>& arc_set,
              string parse_type,
              bool labeled){

    if (parse_type == "standard") {
        return standard_action(configuration, parse_type, labeled);
    }
    else {
        return eager_action(configuration, arc_set, parse_type, labeled);
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

    if(gold_label.compare("shift") != 0 && gold_label.compare("reduce") != 0) {
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

           arc_set.push_back(make_pair(buffer[0], stack.back()));
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
           arc_set.push_back( make_pair(stack.back(), buffer[0]));

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

               if (stack.back().type.empty()){
                    stack.back().type = gold_label.substr(2,gold_label.size());
                    stack.back().head = buffer[0].index;
                }

               arc_set.push_back( make_pair(buffer[0], stack.back()));
           }
           //      pop top most token on the stack
           stack.pop_back();
       }
       else if (action == "RA" || action == "shift") {
           if(action == "RA"){

               if (buffer[0].type.empty()){
                    buffer[0].type = gold_label.substr(2,gold_label.size());
                    buffer[0].head = stack.back().index;
                }

               arc_set.push_back( make_pair(stack.back(), buffer[0]));
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

//
// Created by frosk on 09.06.17.
//

#include <vector>
#include <token.h>
#include <tuple>
using namespace std;
#ifndef JOHNNYDEPPENDENCY_ORACLE_H
#define JOHNNYDEPPENDENCY_ORACLE_H

string oracle(vector<vector<Token>> configuration,
              vector<pair<Token,Token>>& arc_set,
              string type);

vector<vector<Token>> parser(vector<vector<Token>> configuration,
                             string action,
                             vector<pair<Token,Token>>& arc_set,
                             string type);
#endif //JOHNNYDEPPENDENCY_ORACLE_H

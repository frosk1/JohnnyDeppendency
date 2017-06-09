//
// Created by frosk on 09.06.17.
//

#include <vector>
#include <token.h>
#include <tuple>
using namespace std;
#ifndef JOHNNYDEPPENDENCY_ORACLE_H
#define JOHNNYDEPPENDENCY_ORACLE_H

tuple<string,vector<tuple<int,int>>> oracle(vector<vector<Token>> configuration,
                                            vector<tuple<int,int>> arc_set ,
                                            string type="eager");
#endif //JOHNNYDEPPENDENCY_ORACLE_H

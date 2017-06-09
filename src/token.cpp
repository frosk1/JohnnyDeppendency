//
// Created by Jean on 09.06.2017.
//

#include <iostream>
#include <vector>
#include <string>
#include "../include/token.h"

using namespace std;

/*class token:
1     ind = 1
2     term= "Ms."
3     term2 = "ms."
4     pos = "NNP"
5     pos2 = ""
6     head = 2
7     type = "NMOD"*/

class Token {
public: int index, head;
public: string word, base, pos, pos2, type;
public:
    Token() {};
    Token(int indexparam, string wordparam, string baseparam, string posparam, string pos2param, int headparam,
          string typeparam) {index = indexparam, word = wordparam, base = baseparam, pos = posparam, pos2 = pos2param,
                             head = headparam, type = typeparam;};
};

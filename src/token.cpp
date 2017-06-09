//
// Created by Jean on 09.06.2017.
//

#include "token.h"

/*class token:
1     ind = 1
2     term= "Ms."
3     term2 = "ms."
4     pos = "NNP"
5     pos2 = ""
6     head = 2
7     type = "NMOD"*/

Token::Token () {
        index = 0;
        word = "Root";
        base = "root";
        pos = "root";
    };

Token::Token (int indexparam, string wordparam, string baseparam,
                string posparam, int headparam, string typeparam){

                        index = indexparam, word = wordparam,
                        base = baseparam, pos = posparam,
                        head = headparam, type = typeparam;};


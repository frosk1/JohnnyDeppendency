#include "parser_config.h"
#include "iostream"
using namespace std;
vector<string> universal_deplabel = {"acl","advcl","advmod","amod","appos",
                                     "aux","case","cc","ccomp","clf","compound",
                                     "conj","cop","csubj","dep","det","discourse",
                                     "dislocated","expl","fixed","flat",
                                     "goeswith","iobj","list","mark","nmod",
                                     "nsubj","nummod","obj","obl","orphan",
                                     "parataxis","punct","reparandum","root",
                                     "vocative","xcomp"};

vector<string> english_deplabel = {
"ADV", "AMOD", "APPO", "CONJ", "COORD",
"DEP", "EXTR", "GAP", "GAP-SBJ", "IM",
"INTJ", "LGS", "NMOD", "OBJ", "OPRD",
"P", "PMOD", "PRN", "PRT", "QMOD",
"ROOT", "SBJ", "SUB", "VC"};


vector<string> german_deplabel = {
"--", "AC", "ADC", "AG", "AMS",
"APP", "AVC", "CC", "CD", "CJ",
"CM", "CP", "CVC", "DA", "DM",
"EP", "JU", "MNR", "MO", "NG",
"NK", "NMC", "OA", "OA2", "OC",
"OG", "OP", "PAR", "PD", "PG",
"PH", "PM", "PNC", "RC", "RE",
"RS", "SB", "SBP", "SP", "SVP",
"UC", "VO"};


vector<string> init_classnames_labeled(string lang, string parse_type){

    vector<string> labels;

    if (lang=="de"){
       labels = german_deplabel;
    }
    else {
        labels = english_deplabel;

    }

    vector<string> l_classnames;
    if (parse_type=="standard") {
        for (string label: labels) {
            l_classnames.push_back("RA"+label);
            l_classnames.push_back("LA"+label);
        }
        l_classnames.push_back("shift");
    }
    else if (parse_type == "eager"){
        for (string label: labels) {
            l_classnames.push_back("RA"+label);
            l_classnames.push_back("LA"+label);
        }
        l_classnames.push_back("shift");
        l_classnames.push_back("reduce");
    }
    else {
        cout << "not valid type: "<< parse_type << endl;
    }
    return l_classnames;
}


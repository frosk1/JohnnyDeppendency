#include <iostream>
#include "utils.h"
#include <chrono>
#include "fstream"
#include "parser_config.h"
#include <unistd.h>
using namespace chrono;


int main(int argc, char* argv[]) {
    high_resolution_clock ::time_point start = high_resolution_clock::now();

    int c;
    unordered_map<string,string> cfg;
    while ((c = getopt (argc, argv, "c")) != -1) {
        switch (c) {

            case 'c':
                cfg = config_parser(argv[2]);
                break;

            default:
                cout << "Non valid option: "  << argv[1] << endl;
                cout << "Use -c path_to_cfg_file !" << endl;
                abort();
        }

    }


    string type;
    bool labeled;
    vector<string> classnames;
    int max_iter = stoi (cfg["max_iter"]);


    if (cfg["parse_out"]=="labeled"){
        labeled=true;
    }
    else if (cfg["parse_out"]=="unlabeled"){
        labeled=false;
    }

    if (cfg["parse_type"]=="standard" && labeled){
        classnames = init_classnames_labeled(cfg["parse_lang"], cfg["parse_type"]);

    }
    else if (cfg["parse_type"]=="standard" && !labeled){
        classnames = {"shift","RA","LA"};
    }

    else if (cfg["parse_type"]=="eager" && labeled){
        classnames = init_classnames_labeled(cfg["parse_lang"], cfg["parse_type"]);

    }
    else if (cfg["parse_type"]=="eager" && !labeled){
        classnames = {"reduce","shift","RA","LA"};
    }


    cout << "++++ Johnny Dependency ++++" << endl;
    cout << "LANG:\t" << cfg["parse_lang"] << endl;
    cout << "OUT:\t" << cfg["parse_out"] << endl;
    cout << "TYPE:\t" << cfg["parse_type"] << endl;
    cout << "Iter:\t" << cfg["max_iter"] << endl << endl;
    cout << "Train_File: " << cfg["train_file"] << endl;
    cout << "Test_File: " << cfg["test_file"] << endl;
    cout << endl << "### Start Training ###" << endl;


    Multiperceptron multiperceptron(classnames);
    unordered_map<string,int> feature_map;

    string outfile = cfg["parse_lang"] + "_" + cfg["parse_out"] + "_" + cfg["parse_type"] + ".txt";

    train_model(cfg["train_file"], max_iter, multiperceptron, feature_map, cfg["parse_type"], labeled);
    parse_file(cfg["test_file"], outfile, multiperceptron, feature_map, cfg["parse_type"]);



    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( end - start ).count();
    cout << "time: " << duration/1000000 << "s; ";
    cout << (float)(duration/1000000)/(float)60 << "m";
    return 0;
}

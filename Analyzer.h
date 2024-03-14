#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Client.h>
#include <iostream>
#include <fstream>
using namespace std;

class Analyzer {
    private:
        string ping_results;
        string short_iperf_results;
        string long_iperf_results;
    public:
        Analyzer(string ping_file, string short_file, string long_file);
        bool analyze(uint8_t OP_CODE);
        bool ping_test();
        bool iperf_test(string file_name);
};


#endif
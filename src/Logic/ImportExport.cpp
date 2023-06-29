#include "Calculator.h"
#include "ImportExport.h"



using namespace std;

ImportExport::ImportExport(Calculator* calculator) {
    calc = calculator;
}

void ImportExport::importMemory(const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(infile, line)) {
        calc->executeCommand(line);
    }
}

void ImportExport::exportMemory(const string &filename) {
    ofstream outfile(filename);
    if (!outfile) {
        throw runtime_error("Cannot open file: " + filename);
    }

    for (const auto &var : calc->getVariables()) {
        outfile << var.first << " = " << var.second->toString() << endl;
    }
}
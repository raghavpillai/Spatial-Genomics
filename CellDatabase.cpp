#include <iostream>
#include <string>
#include <sstream>
#include "CellDatabase.h"
#include "CellData.h"
#include <fstream>
#include <vector>

using std::cout;
using std::string;
using std::fstream;
using std::ofstream;
using std::endl;

// Default constructor/destructor. Modify them if you need to.
CellDatabase::CellDatabase() {}
CellDatabase::~CellDatabase() {}


void CellDatabase::loadData(const string& filename)  {
    std::string line;
    std::ifstream inFile(filename);

    if ( inFile.is_open() ){
        while ( getline (inFile,line) ){
            std::stringstream ss(line); // stringstream because lazy
            std::vector<std::string> v; // should switch to array

            while ( ss.good() ) {
                std::string substr;
                getline(ss, substr, ','); // break by comma
                v.push_back(substr); // push into vector for easy 1,2,3
            }

            if ( v.at(0) != "fov" ) { // If not first line
                CellData curr; // ID, fov,volume,center_x,center_y,min_x,max_x,min_y,max_y
                curr.id = stof(v.at(0));
                curr.fov = stof(v.at(1));
                curr.volume = stof(v.at(2));
                curr.center_x = stof(v.at(3));
                curr.center_y = stof(v.at(4));
                curr.min_x = stof(v.at(5));
                curr.min_y = stof(v.at(6));
                curr.max_x = stof(v.at(7));
                curr.max_y = stof(v.at(8));
                std::cout << "New node: " << curr.id << std::endl;
            }
        }
    } else {
        std::cout << "Error, unable to open" << std::endl;
    }
}

// Do not modify
void CellDatabase::outputData(const string& filename) {
    ofstream dataout("sorted." + filename);

    if (!dataout.is_open()) {
        cout << "Error: Unable to open " << filename << endl;
        exit(1);
    }
    dataout << records.print();
}

void CellDatabase::performQuery(const string& filename) {
    // Implement this function
}

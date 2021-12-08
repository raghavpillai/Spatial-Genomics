#include <iostream>
#include <string>
#include <sstream>
#include "CellDatabase.h"
#include "CellData.h"
#include "LinkedList.h"
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

            if ( v.at(1) != "fov" ) { // If not first line
                CellData curr; // ID, fov,volume,center_x,center_y,min_x,max_x,min_y,max_y
                curr.id = v.at(0);
                curr.fov = stoi(v.at(1));
                curr.volume = stod(v.at(2));
                curr.center_x = stod(v.at(3));
                curr.center_y = stod(v.at(4));
                curr.min_x = stod(v.at(5));
                curr.min_y = stod(v.at(6));
                curr.max_x = stod(v.at(7));
                curr.max_y = stod(v.at(8));
                records.insert(curr.id, curr.fov, curr.volume, curr.center_x, curr.center_y, curr.min_x, curr.min_y, curr.max_x, curr.max_y);
                //std::cout << "New node: " << curr.id << std::endl;
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
    std::string line;
    std::ifstream inFile(filename);
    std::ofstream outFile("queries.data");

    if ( inFile.is_open() && outFile.is_open() ){
        while ( getline (inFile,line) ){
            std::stringstream ss(line);
            std::vector<std::string> v;

            while ( ss.good() ) {
                std::string substr;
                getline(ss, substr, ' '); // break by space
                v.push_back(substr); 
            }

            if ( v.at(0) == "AVG" ) { 
                double ret = this->records.average( stoi(v.at(1)) );
                outFile << "AVG " << v.at(1) << ": " << std::to_string(ret) << "\n";
            }else if ( v.at(0) == "VAR" ) { 
                double ret = this->records.variance( stoi(v.at(1)) );
                outFile << "VAR " << v.at(1) << ": " << std::to_string(ret) << "\n";
            }else if ( v.at(0) == "COUNT" ) { 
                double ret = this->records.countN( stoi(v.at(1)) );
                outFile << "COUNT " << v.at(1) << ": " << std::to_string(ret) << "\n";
            }else if ( v.at(0) == "OUTLIER" ) { 
                std::string out = this->records.outliers( stoi(v.at(1)),stoi(v.at(2)),stoi(v.at(3)) );
                outFile << "OUTLIER " << v.at(1) << " " << v.at(2) << " " << v.at(3) << ": " << out << "\n";
            }
        }
    } else {
        std::cout << "Error, unable to open" << std::endl;
    }
}

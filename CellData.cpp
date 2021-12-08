/*
 * CellData.h
 *
 *  Created on: Nov 9, 2021
 *      Author: student
 */

#include <iostream>
#include <string>
#include "CellData.h"

using std::cout;
using std::string;

CellData::CellData() {
    this->id = "-1";
    this->fov = -1;
    this->volume = -1;
    this->center_x = -1;
    this->center_y = -1;
    this->min_x = -1;
    this->max_x = -1;
    this->min_y = -1;
    this->max_y = -1;
} //initialize everything

CellData::CellData(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y){
    this->id = id;
    this->fov = fov;
    this->volume = volume;
    this->center_x = center_x;
    this->center_y = center_y;
    this->min_x = min_x;
    this->max_x = max_x;
    this->min_y = min_y;
    this->max_y = max_y;
} //initialize everything


CellData::~CellData() {} // You should not need to implement this

bool CellData::operator<(const CellData& b) {
	if(this->fov < b.fov) {
        return true;
    }else if(this->fov == b.fov && this->id < b.id) {
        return true;
    }
    return false;
}

bool CellData::operator==(const CellData& b) {
    if(this == &b) {
        return true;
    }
    return false;
}


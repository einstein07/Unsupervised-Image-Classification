/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: root07
 *
 * Created on 26 March 2020, 19:33
 */
#include "clusterer.h"
#include <cstdlib>

using namespace MKHSIN035;
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    KMeansClusterer obj;
    obj.readDataSet("Gradient_Numbers_PPMS/");
    obj.imageFeature(4);
    return 0;
}


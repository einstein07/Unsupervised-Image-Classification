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
    //get the location of the folder that contains the images to be clustered
    string dataset = argv[1];
    string outputfile;
    int k = 10;
    int bin = 1;
    if(argc > 2)
        outputfile = argv[2];
    else
        outputfile = NULL;
    if(argc > 3)
        k = atoi(argv[3]);
    if(argc > 4)
        bin = atoi(argv[4]);
    KMeansClusterer obj(k);
    obj.readDataSet(dataset);
    obj.imageFeature(bin);
    obj.kmeans();
    if(outputfile == NULL)
        cout<<obj;
    else{
        
    }
    return 0;
}


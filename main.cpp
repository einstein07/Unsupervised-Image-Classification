/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 19:33
 */
#include "image.h"
#include "cluster.h"
#include "kmeansclusterer.h"
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
    bool color = false;
    int k = 10;
    int bin = 1;
    if(argc > 2)
        outputfile = argv[2];
    else
        outputfile = "";
    if(argc > 3)
        k = atoi(argv[3]);
    if(argc > 4)
        bin = atoi(argv[4]);
    if(argc > 5)
        color = true;
    cout<<"Main k: "<<k<<endl;
    KMeansClusterer obj(k, color, bin);
    Image im(dataset);
    string file = dataset+"eight_10.ppm";
    cout<<"File name: "<<file<<endl;
    im.read(file);
    im.createFeature(bin, true);
    //obj.readDataSet();
    //obj.createFeature();
//    obj.kmeansclustering();
//    const KMeansClusterer oj = obj;
//    if(outputfile == "")
//        cout<<oj;
//    else{
//        ofstream file(outputfile);
//        file<<oj;
//    }
    return 0;
}


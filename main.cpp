/* 
 * File:   main.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 19:33
 */
#include "image.h"
#include "kmeansclusterer.h"
#include <cstdlib>
#include <dirent.h>

using namespace MKHSIN035;
using namespace std;

/*
 * Driver file 
 */
int main(int argc, char** argv) {
    
    
    //get the location of the folder that contains the images to be clustered
    string dataset = argv[1];
    string outputfile;
    bool color = false;
    int k = 10;
    int bin = 1;
    bool advanced = false;
    if(argc > 2)
        outputfile = argv[2];
    else
        outputfile = "";
    if(argc > 3)
        k = atoi(argv[3]);
    if(argc > 4)
        bin = atoi(argv[4]);
    if(argc > 5){
        if(argv[5] == "color")
            color = true;
    }
    if(argc > 6)
        advanced = true;
    
    
    int n = 0;//Number of files in directory
    int c = 0; //counter
    DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);
    //Compute number of files
    while((dir = readdir(d)) != NULL){
        if(!strcmp(dir->d_name, ".")||!strcmp(dir->d_name,"..")){}
        else
            n++;
    }
    rewinddir(d);
    char* files[n];
    //put in file names in array
    while((dir = readdir(d)) != NULL){
        if(!strcmp(dir->d_name, ".")||!strcmp(dir->d_name,"..")){}
        else{
            files[c] = (char*) malloc (strlen(dir->d_name)+1);
            strncpy(files[c], dir->d_name, strlen(dir->d_name));
            c++;
        }
    }
    rewinddir(d);
//    for(int i = 0; i < n; i++){
//        cout<<files[i]<<" ";
//    }
    
    KMeansClusterer obj(k);
    for(int i = 0; i < n; i++){
        Image im(dataset, color);
        im.read(files[i]);
        if(advanced)
            im.SobelEdgeDetector();
        else
            im.createFeature(bin);
        obj.images.push_back(im);
    }
  
    obj.kmeansclustering();
    const KMeansClusterer oj = obj;
    if(outputfile == "")
        cout<<oj;
    else{
        ofstream file(outputfile);
        file<<oj;
    }
    return 0;
}


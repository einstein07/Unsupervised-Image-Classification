

/* 
 * File:   clusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 22:05
 */

#include "clusterer.h"
using namespace MKHSIN035;
using namespace std;

/*
 * Default Constructor definition
 */
MKHSIN035::KMeansClusterer::KMeansClusterer(){}
/*
 * Destructor definition
 */
MKHSIN035::KMeansClusterer::~KMeansClusterer(){}

void KMeansClusterer::readDataSet(string folder){
    string extension = ".ppm";
    string filename;
    ifstream dataset;
    images = new unsigned char* [100];
    int counter = 0;
    for (int i = 0; i < 10; i++){
        for(int j = 1; j <=10; j++ ){
            filename = folder+filenames[i]+to_string(j)+extension;
            
            dataset.open(filename, ios::binary|ios::ate); 
            streampos begin,end;
            
            if(dataset.is_open()){
                end = dataset.tellg();
                string dim;
                string line;

                //Take pointer back to the beginning of the file
                dataset.seekg(0, ios::beg);

                while(getline(dataset, line)){
                    if(line == "255"){
                        begin = dataset.tellg();
                    }
                }
                images[counter] = new unsigned char[end-begin];
                char buf[end-begin];
                unsigned char val [end-begin];
                dataset.read(buf, (end-begin));
                memcpy(&val, buf, sizeof(val));
                images[counter] = val; 
                            
                cout<<"Done reading: "<<filename<<endl;

            }
            else{
                cout<<"Could not open file "<<filename<<endl;
            }
            dataset.close();
            counter++;
        }
    }
    
}

ostream& operator<<(std::ostream& os, const KMeansClusterer& kt){
    
}


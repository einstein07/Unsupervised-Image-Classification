

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
                images[counter] = new unsigned char[(end-begin)+1];
                char buf[end-begin];
                unsigned char val [end-begin];
                dataset.read(buf, (end-begin));
                memcpy(&val, buf, sizeof(val));
                //Store the size first
                images[counter][0] = (end-begin);
                for (int k = 1; k <= ((end-begin)+1); k++){
                    images[counter][k] = val[k-1];
                    //cout<<+images[counter][k]<<" ";
                }
                 
                cout<<endl;            
                cout<<"Image "<<i<<" length: "<< (end-begin)<<endl;

            }
            else{
                cout<<"Could not open file "<<filename<<endl;
            }
            dataset.close();
            counter++;
        }
    }
    
}

void MKHSIN035::KMeansClusterer::imageFeature(int bin){
    //feature = new int* [100];
    
    int Lbound = 0;
    int Ubound = bin;
    
    
    for(int i = 0; i < 100; i++){
        cout<<"Size of image "<<(i+1)<<": "<<+images[i][0]<<endl;
        int entries = images[i][0]/bin;
        vector <int> features(entries,0);

        for (int k = 0; k < entries; k++){
            for (int j = 0; j <= images[i][0]; j++){
                if (images[i][j] >= Lbound && images[i][j] < Ubound){
                    features[k]++;
                }

            }
                  
            Lbound += bin;
            Ubound += bin;

        }
                    
        cout<<"Done creating feature for image: "<<i<<". Num of entries: "<<entries<<endl;

        feature.push_back(features);
        
    }
}

ostream& operator<<(std::ostream& os, const KMeansClusterer& kt){
    
}


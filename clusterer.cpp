

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
 * Default Constructor definition for Image class
 */
MKHSIN035::Image::Image(std::string name):filename(name){}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::Image::~Image(){}
/*
 * Default Constructor definition for KMeansClusterer
 */
MKHSIN035::KMeansClusterer::KMeansClusterer(){}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::KMeansClusterer::~KMeansClusterer(){}

/*
 * setintensitylen definition
 */
void MKHSIN035::Image::setintensitylen(int len){intensitylen = len;}

/*
 * setfeaturelen definition
 */
void MKHSIN035::Image::setfeaturelen(int len){featurelen = len;}

/*
 * getintensitylen definition
 */
int MKHSIN035::Image::getintensitylen(){return intensitylen;}

/*
 * getintensitylen definition
 */
int MKHSIN035::Image::getfeaturelen(){return featurelen;}

/*
 * getfilename definition
 */
string MKHSIN035::Image::getfilename(){return filename;}

void KMeansClusterer::readDataSet(string folder){
    string extension = ".ppm";
    string filename;
    ifstream dataset;
    //images = new unsigned char* [100];
    int counter = 0;
    for (int i = 0; i < 10; i++){
        for(int j = 1; j <=10; j++ ){
            filename = folder+filenames[i]+to_string(j)+extension;
            Image obj(filename);
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
                obj.setintensitylen(end-begin);
                obj.intensity = new unsigned char[(obj.getintensitylen())];
                char buf[obj.getintensitylen()];
                unsigned char val [obj.getintensitylen()];
                dataset.read(buf, obj.getintensitylen());
                memcpy(&val, buf, sizeof(val));
                obj.intensity = val;
                //Add image to collection of images
                images.push_back(obj);
                
                

            }
            else{
                cout<<"Could not open file "<<filename<<endl;
            }
            dataset.close();
            counter++;
        }
    }
    
    for(int i = 0; i < images.size(); i++){
                                        
        cout<<"\nDone reading image "<<images[i].getfilename()<<endl;            

        for (int j = 0; j < images[i].getintensitylen(); j++){
            cout<<+images[i].intensity[j]<<" ";            

        }

    }
    
}

void MKHSIN035::KMeansClusterer::imageFeature(int bin){
//    //feature = new int* [100];
//    
//    int Lbound = 0;
//    int Ubound = bin;
//    
//    
//    for(int i = 0; i < 100; i++){
////        cout<<"Size of image "<<(i+1)<<": "<<+images[i][0]<<endl;
////        int entries = images[i][0]/bin;
////        vector <int> features(entries,0);
//
//        for (int k = 0; k < entries; k++){
//            for (int j = 0; j <= images[i][0]; j++){
//                if (images[i][j] >= Lbound && images[i][j] < Ubound){
//                    features[k]++;
//                }
//
//            }
//                  
//            Lbound += bin;
//            Ubound += bin;
//
//        }
//                    
//        cout<<"Done creating feature for image: "<<i<<". Num of entries: "<<entries<<endl;
//
//        feature.push_back(features);
        
//    }
}

ostream& operator<<(std::ostream& os, const KMeansClusterer& kt){
    
}


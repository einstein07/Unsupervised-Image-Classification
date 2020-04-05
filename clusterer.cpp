

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
void MKHSIN035::Image::setgreyscalelen(int len){greyscalelen = len;}

/*
 * setfeaturelen definition
 */
void MKHSIN035::Image::setfeaturelen(int len){featurelen = len;}

/*
 * getintensitylen definition
 */
int MKHSIN035::Image::getgreyscalelen(){return greyscalelen;}

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
                obj.setgreyscalelen(((end-begin)/3));
                obj.greyscale = new unsigned char[(obj.getgreyscalelen())];
                char buf[end-begin];
                unsigned char val [end-begin];
                dataset.read(buf, end-begin);
                memcpy(&val, buf, sizeof(val));
                
                int count = 0;
                for (int c = 0; c < obj.getgreyscalelen(); c++){
                    obj.greyscale[c] = 0.21*val[count] + 0.72*val[count+1] + 0.07*val[count+2];
                    count += 3;
                }
                
                //obj.intensity = val;
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
                                        
        cout<<"\nDone reading image "<<images[i].getfilename()<<"\nSize: "<<images[i].getgreyscalelen()<<endl;            

        for (int j = 0; j < images[i].getgreyscalelen(); j++){
            cout<<+images[i].greyscale[j]<<" ";            

        }

    }
    
}

void MKHSIN035::KMeansClusterer::imageFeature(int bin){
    int featurelen = 256/bin;
    
    
    
   
    for(int i = 0; i < images.size(); i++){
        images[i].feature = new int[featurelen];
        images[i].setfeaturelen(featurelen);
        int Lbound = 0;
        int Ubound = bin;
    
        for (int a = 0; a < images[i].getfeaturelen(); a++){
            images[i].feature[a] = 0;
        }

        
        

        for (int k = 0; k < images[i].getfeaturelen(); k++){
            for (int j = 0; j <= images[i].getgreyscalelen(); j++){
                if (Lbound <= images[i].greyscale[j]  && images[i].greyscale[j] < Ubound){
                    images[i].feature[k]++;
                }

            }
               
            Lbound += bin;
            Ubound += bin;

        }
                    
        //cout<<"Done creating feature for image: "<<i<<endl;

        
    }
    
    for(int i = 0; i < images.size(); i++){
                                        
        cout<<"Image "<<images[i].getfilename()<<" Feature length: "<<images[i].getfeaturelen()<<endl;            

        for (int j = 0; j < images[i].getfeaturelen(); j++){
            cout<<images[i].feature[j]<<" ";            

        }

    }
}

ostream& operator<<(std::ostream& os, const KMeansClusterer& kt){
    
}


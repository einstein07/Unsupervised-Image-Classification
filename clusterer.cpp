

/* 
 * File:   clusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 22:05
 */

#include "clusterer.h"
using namespace MKHSIN035;
using namespace std;
MKHSIN035::KMeansClusterer::KMeansClusterer(){}
void KMeansClusterer::readDataSet(){
    string filename = "Gradient_Numbers_PPMS/eight_1.ppm";
    //Open the file in binary mode
    //Position the pointer at the end of the file
    ifstream dataset(filename, ios::binary|ios::ate); 
    streampos begin,end;

    if(dataset.is_open()){
        end = dataset.tellg();
        int Nrows, Ncols;
        string dim;
        string line;
                
        //Take pointer back to the beginning of the file
        dataset.seekg(0, ios::beg);
        
        while(getline(dataset, line)){
            if(line == "255"){
                
                begin = dataset.tellg();
            
                
            }

        }
        KMeansClusterer::image = new unsigned char[end - begin];
        char buf[end-begin];
        unsigned char val [end-begin];
        dataset.read(buf, (end-begin));
        memcpy(&val, buf, sizeof(val));
        image = val;    
        for(int i = 0;  i < end-begin; i++){
            cout<<+image[i]<<" ";

        }
        
        cout<<" Done"<<endl;
        
        dataset.close();

    }
    else{
        cout<<"Could not open file "<<filename<<endl;
    }
}

ostream& operator<<(std::ostream& os, const KMeansClusterer& kt){
    
}


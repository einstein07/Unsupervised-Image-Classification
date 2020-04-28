#include "image.h"
using namespace MKHSIN035;
using namespace std;
//------------------------------------------------------------------------------
//                      Class Image member functions definitions
//------------------------------------------------------------------------------

/*
 * Default Constructor definition for Image class
 */
MKHSIN035::Image::Image(std::string name):filename(name), cluster_id(0){}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::Image::~Image(){}

void Image::createGreyScale(){
    this->greyscale = new unsigned char[(this->data_len/3)];
    int count = 0;
    for (int c = 0; c < this->greyscale_len; c++){
        greyscale[c] = 0.21*imageDataSet[count] + 0.72*imageDataSet[count+1] + 0.07*imageDataSet[count+2];
        count += 3;
    }
}

        
void Image::createFeature(int bin, bool color){
 
    if(color){
        int feature_size = (256/bin)*3;




        feature = new int[feature_size];
        setfeaturelen(feature_size);
        int Lbound = 0;
        int Ubound = bin;

        for (int a = 0; a < feature_size; a++){
            feature[a] = 0;
        }




        for (int k = 0; k < feature_size; k+=3){
            for (int j = 0; j <= data_len; j+=3){
                if (Lbound <= imageDataSet[j]  && imageDataSet[j] < Ubound){
                    feature[k]++;
                }
                if (Lbound <= imageDataSet[j+1]  && imageDataSet[j+1] < Ubound){
                    feature[k+1]++;
                }
                if (Lbound <= imageDataSet[j+2]  && imageDataSet[j+2] < Ubound){
                    feature[k+2]++;
                }

            }

            Lbound += bin;
            Ubound += bin;

        }

    }
    else{
        
        int feature_size = 256/bin;

        feature = new int[feature_size];
        setfeaturelen(feature_size);
        int Lbound = 0;
        int Ubound = bin;

        //Initialize feature array with zeros
        for (int a = 0; a < feature_size; a++){
            feature[a] = 0;
        }


        for (int k = 0; k < feature_size; k++){
            for (int j = 0; j <= greyscale_len; j++){
                if (Lbound <= greyscale[j]  && greyscale[j] < Ubound){
                    feature[k]++;
                }

            }

            Lbound += bin;
            Ubound += bin;

        }


    }

    
   
}


/*
 * setfeaturelen(int) definition
 */
void MKHSIN035::Image::setfeaturelen(int len){featurelen = len;}

/*
 * setgreyscalelen(int) definition
 */
void MKHSIN035::Image::setgreyscalelen(int len){greyscale_len = len;}

/*
 * 
 */
void MKHSIN035::Image::setImageDataSetlen(int len){data_len = len;}


/*
 * setClusterId(int) method definition 
 */
void MKHSIN035::Image::setClusterId(int cluster_id){this->cluster_id = cluster_id;}

/*
 * getfilename definition
 */
string MKHSIN035::Image::getfilename()const{return filename;}

/*
 * getgreyscalelen() definition
 */
int MKHSIN035::Image::getgreyscalelen()const{return greyscalelen;}

/*
 *getRGBlen() definition         
 */
int MKHSIN035::Image::getImageDataSetlen()const{return rgb_len;}        

/*
 * getfeaturelen() definition
 */
int MKHSIN035::Image::getfeaturelen()const{return featurelen;}


/*
 * getClusterId() definition
 */
int MKHSIN035::Image::getClusterId()const{return this->cluster_id;}

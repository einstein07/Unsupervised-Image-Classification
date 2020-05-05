/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 28 April 2020, 20:35
 */

#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstring>
#include <ctime>
#include <cfloat>
#include <math.h>
#include <algorithm>
namespace MKHSIN035{
class Image{
    
    private:
    
        std::string filename;
        int greyscale_len;
        int data_len;
        int featurelen;
        int cluster_id;
        double min_dist;
        friend class KMeansClusterer;
    
    public:
        //Stores intensity values for each pixel
        
        unsigned char* imageDataSet; //RGB
        unsigned char* greyscale; //In grey scale format
        int* feature;
        
        /*
         * Big Six
         */
        //Default constructor
        Image();
        //Constructor
        Image(std::string name);
        //Destructor
        ~Image();
        //Move constructor
        Image(Image&& rhs);
        //Copy constructor
        Image(const Image& rhs);
        //Assignment op
        Image& operator=(const Image& rhs);
        //Move assignment op
        Image& operator=(Image&& rhs);
        
        bool read(std::string folder);
        
        void createGreyScale();
        
        void createFeature(int bin, bool color);
        
        double distance(Image i, bool color);

        /*
         * Sets length of feature array 
         */
        void setfeaturelen(int len);
        /*
         * Sets the length of the intensity array 
         */
        void setgreyscalelen(int len);
        
        /*
         * Sets length of rgb array
         */
        void setImageDataSetlen(int len);
        
        /*
         * Sets cluster id for this image
         */
        void setClusterId(int cluster_id);
        /*
         * Returns filename of image
         */
        std::string getfilename()const;
        
        /*
         * Returns length of intensity array
         */
        int getgreyscalelen()const;
        
        /*
         * Returns length of RGB array
         */
        int getImageDataSetlen()const;        
        
        /*
         * Returns length of feature array
         */
        int getfeaturelen()const;
               
        /*
         * Returns cluster id for this image
         */
        int getClusterId()const;
        
    };
    

}
#endif /* IMAGE_H */


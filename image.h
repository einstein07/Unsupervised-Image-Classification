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
    
        std::string folder;
        bool color;
        std::string filename;
        int greyscale_len;
        int data_len;
        int featurelen;
        int cluster_id;
        double min_dist;
        int Nrows, Ncols;
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
        Image(std::string folder, bool color);
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
        
        bool read(std::string filename);
        
        void createGreyScale();
        
        void createFeature(int bin);
        
        void SobelEdgeDetector();
        
        double distance(Image i);

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


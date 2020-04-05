

/* 
 * File:   clusterer.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 26 March 2020, 22:05
 */

#ifndef CLUSTERER_H
#define CLUSTERER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstring>


namespace MKHSIN035{
    class Image{
    private:
        std::string filename;
        int intensitylen;
        int featurelen;
        friend class KMeansClusterer;
    public:
        //Stores intensity values for each pixel
        unsigned char* intensity;
        int* feature;
        Image(std::string name);
        ~Image();
        /*
         * Sets the length of the feature array 
         */
        void setfeaturelen(int len);
        /*
         * Sets the length of the intensity array 
         */
        void setintensitylen(int len);
        /*
         * Returns filename of image
         */
        std::string getfilename();
        
        /*
         * Returns the length of the intensity array
         */
        int getintensitylen();
        
        /*
         * Returns the length of the feature array
         */
        int getfeaturelen();
    };
    class KMeansClusterer{
    public:
        std::string filenames [10] = {"zero_", "one_", "two_", "three_", "four_", "five_", "six_", "seven_", "eight_", "nine_"}; 
        std::vector<Image> images;
        /*
         * Default constructor
         */
        KMeansClusterer();
        /*
         * Destructor
         */
        ~KMeansClusterer();
        /*
         * This method reads the color images. 
         * Each color image is then converted into greyscale image i.e. a single
         * value per pixel.
         */
        void readDataSet(std::string folder);
        
        /*
         * This method uses a histogram to create an image feature for each image
         */
        void imageFeature(int bin);
    };
    std::ostream& operator<<(std::ostream& os, const KMeansClusterer& kt);


}

#endif /* CLUSTERER_H */


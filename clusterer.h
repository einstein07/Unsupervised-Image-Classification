

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
    class KMeansClusterer{
    public:
        std::string filenames [10] = {"zero_", "one_", "two_", "three_", "four_", "five_", "six_", "seven_", "eight_", "nine_"}; 
        unsigned char** images;
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
    };
    std::ostream& operator<<(std::ostream& os, const KMeansClusterer& kt);


}

#endif /* CLUSTERER_H */


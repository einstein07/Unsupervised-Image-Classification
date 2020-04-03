

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
        unsigned char* image;
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
        void readDataSet();
    };
    std::ostream& operator<<(std::ostream& os, const KMeansClusterer& kt);


}

#endif /* CLUSTERER_H */


#include "image.h"
using namespace MKHSIN035;
using namespace std;
//------------------------------------------------------------------------------
//                      Class Image member functions definitions
//------------------------------------------------------------------------------

/*
 * Default Constructor definition for Image class
 */
MKHSIN035::Image::Image():folder(""),filename(""), cluster_id(-1), min_dist(DBL_MAX), featurelen(-1), data_len(-1){}
/*
 * @params name: filename of image
 */
MKHSIN035::Image::Image(std::string folder, bool color):color(color),folder(folder), cluster_id(-1), min_dist(DBL_MAX), featurelen(-1), data_len(-1) {}

/*
 * Destructor definition for KMeansClusterer
 */
MKHSIN035::Image::~Image(){}

/*
 * The copy constructor.
 * Constructs by copying another object
 * @params constant l-value ref to object of same type
 */
MKHSIN035::Image::Image(const Image& rhs): color(rhs.color),folder(rhs.folder),filename(rhs.filename), 
        cluster_id(rhs.cluster_id), min_dist(rhs.min_dist), data_len(rhs.data_len), greyscale_len(rhs.greyscale_len), featurelen(rhs.featurelen),
        imageDataSet(rhs.imageDataSet), greyscale(rhs.greyscale), feature(rhs.feature){
    
}

/*
 * The move constructor
 * Constructs by moving resources from one object to another object
 * @params r-value ref to object of same type
 */
MKHSIN035::Image::Image(Image&& rhs){
    if(this != &rhs){
        this->color = std::move(rhs.color);
        this->folder = std::move(rhs.folder);
        this->filename = std::move(rhs.filename);
        this->cluster_id = rhs.cluster_id;
        this->min_dist = rhs.min_dist;
        this->data_len = rhs.data_len;
        this->greyscale_len = rhs.greyscale_len;
        this->featurelen = rhs.featurelen;
        this->imageDataSet = rhs.imageDataSet;
        this->greyscale = rhs.greyscale;
        this->feature = rhs.feature;
        
        //Leave rhs in destructable state
        //int "move" copies anyway so set all ints to defaults
        rhs.cluster_id = -1;
        rhs.min_dist = DBL_MAX;
        rhs.data_len = -1;
        rhs.featurelen = -1;
        rhs.greyscale_len = -1;
    }
       
}

/*
 * Copy assignment operator
 * Copies content of one object to another
 * 
 * @params Constant l-value ref to class type
 */

Image& Image::operator=(const Image& rhs){
    if(this!=&rhs){
        this->color = rhs.color;
        this->folder = rhs.folder;
        this->filename = rhs.filename;
        this->cluster_id = rhs.cluster_id;
        this->min_dist = rhs.min_dist;
        this->data_len = rhs.data_len;
        this->greyscale_len = rhs.greyscale_len;
        this->featurelen = rhs.featurelen;
        this->imageDataSet = rhs.imageDataSet;
        this->greyscale = rhs.greyscale;
        this->feature = rhs.feature;
    }
    return *this;
}

/*
 * Move Assignment op
 * 
 */
Image& Image::operator=(Image&& rhs){
    if(this != &rhs){
        this->color = std::move(rhs.color);
        this->folder = std::move(rhs.folder);
        this->filename = std::move(rhs.filename);
        this->cluster_id = rhs.cluster_id;
        this->min_dist = rhs.min_dist;
        this->data_len = rhs.data_len;
        this->greyscale_len = rhs.greyscale_len;
        this->featurelen = rhs.featurelen;
        this->imageDataSet = rhs.imageDataSet;
        this->greyscale = rhs.greyscale;
        this->feature = rhs.feature;
        
        //Leave rhs in destructable state
        //int "move" copies anyway so set all ints to defaults
        rhs.cluster_id = -1;
        rhs.min_dist = DBL_MAX;
        rhs.data_len = -1;
        rhs.featurelen = -1;
        rhs.greyscale_len = -1;
    }
} 

bool Image::read(string filename){
    
    string extension = ".ppm";         
    string name = filename+extension;
    this->filename = name;
    name = this->folder+name;
    ifstream dataset(name.c_str(), ios::binary);

    if(!dataset){
        cout<<"Could not open "<<name<<endl;
        return false;
    }
    else{
        string line = "";
        string size;
        while(getline(dataset, line)){
            if(line == "255")
                break;
            size = line;
        }
        std::string::size_type sz;   // alias of size_t
        int Nrows = stoi(size, &sz);
        int Ncols = stoi (size.substr(sz));
            
        int counter = 0;
        data_len = Nrows*Ncols*3;
        imageDataSet = new unsigned char[data_len];
        unsigned char value;
        char buf[sizeof(unsigned char)];
        while(dataset.read(buf,sizeof(buf))){
            memcpy(&value, buf, sizeof(value));
            imageDataSet[counter] = value;
            counter++;

        }
        
        if(!color)
            createGreyScale();
    }

            
}

void Image::createGreyScale(){
    int count = 0;
    this->greyscale_len = ceil(this->data_len/3.0);
    this->greyscale = new unsigned char[greyscale_len];
    for (int c = 0; c < this->greyscale_len; c++){
      
        greyscale[c] = 0.21*imageDataSet[count] + 0.72*imageDataSet[count+1] + 0.07*imageDataSet[count+2];
        count += 3;
    }
    
}

        
void Image::createFeature(int bin){
 
    if(color){
        int feature_size = ceil((256.0/bin))*3;
        feature = new int[feature_size];
        setfeaturelen(feature_size);
        int Lbound = 0;
        int Ubound = bin;
        for (int a = 0; a < feature_size; a++){
            feature[a] = 0;
        }
        for (int k = 0; k < feature_size; k+=3){
            for (int j = 0; j <= data_len; j+=3){
                if (Lbound <= imageDataSet[j] && imageDataSet[j] < Ubound){
                        feature[k] += 1;
                    
                }
                
                if (Lbound <= imageDataSet[j+1] && imageDataSet[j+1] < Ubound){
                        feature[k+1] += 1;
                }
                
                if (Lbound <= imageDataSet[j+2] && imageDataSet[j+2] < Ubound){
                        feature[k+2] += 1;
                }
            }
            Lbound += bin;
            Ubound += bin;
        }

       
    }
    else{
        int feature_size = ceil((256.0/bin));
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

double Image::distance(Image image){
    double sum = 0.0;           
//    if(color){
//        for(int i = 0; i < data_len; i++){
//            sum += pow(feature[i] - image.feature[i], 2);
//
//        }
//    }
//    else{
        for(int i = 0; i < featurelen; i++){
            sum += pow(this->feature[i] - image.feature[i], 2);
            
        }
   // }
    return sum;
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
int MKHSIN035::Image::getgreyscalelen()const{return greyscale_len;}

/*
 *getRGBlen() definition         
 */
int MKHSIN035::Image::getImageDataSetlen()const{return data_len;}        

/*
 * getfeaturelen() definition
 */
int MKHSIN035::Image::getfeaturelen()const{return featurelen;}

/*
 * getClusterId() definition
 */
int MKHSIN035::Image::getClusterId()const{return this->cluster_id;}

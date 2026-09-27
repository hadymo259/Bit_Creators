#include<iostream>
using namespace std;
#include "Image_Class.h"

int main(){
    string filename;
    cout<<"enter the image filename to rotate it: ";
    cin>>filename;
    Image img(filename);

    int w = img.width;
    int h = img.height;
    cout << "Loaded image: " << w << " x " << h << endl; // debug line

    int rotatedegree;
    cout<<"enter the clockwise degree to rotate the image: ";
    cin>>rotatedegree;

    if(rotatedegree == 90){
        Image rotated(h, w);
        for(int y = 0; y < w; y++)
            for(int x = 0; x < h; x++)
                for(int c = 0; c < 3; c++)
                    rotated.setPixel(x, y, c, img.getPixel(y, h-1-x, c));
        rotated.saveImage("rotated_" + filename);
    }
    else if(rotatedegree == 180){
        Image rotated(w, h);
        for(int y = 0; y < h; y++)
            for(int x = 0; x < w; x++)
                for(int c = 0; c < 3; c++)
                    rotated.setPixel(x, y, c, img.getPixel(w-1-x, h-1-y, c));
        rotated.saveImage("rotated_" + filename);
    }
    else if(rotatedegree == 270){
        Image rotated(h, w);
        for(int y = 0; y < w; y++)
            for(int x = 0; x < h; x++)
                for(int c = 0; c < 3; c++)
                    rotated.setPixel(x, y, c, img.getPixel(w-1-y, x, c));
        rotated.saveImage("rotated_" + filename);
    }
    else{
        cout<<"only 90, 180, or 270 supported"<<endl;
    }

    return 0;
}
#include<iostream>
using namespace std;
#include "Image_Class.h"

int main(){
    string filename;
    cout<<"enter the image filename for edge detection: ";
    cin>>filename;
    Image img(filename);

    int w = img.width;
    int h = img.height;
    Image edges(w, h);

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){

            // last column has no pixel to its right, so just leave it white
            if(x == w-1){
                edges.setPixel(x, y, 0, 255);
                edges.setPixel(x, y, 1, 255);
                edges.setPixel(x, y, 2, 255);
                continue;
            }

            // brightness of this pixel (average of R, G, B)
            int here = (img.getPixel(x, y, 0) + img.getPixel(x, y, 1) + img.getPixel(x, y, 2)) / 3;

            // brightness of the pixel to its right
            int right = (img.getPixel(x+1, y, 0) + img.getPixel(x+1, y, 1) + img.getPixel(x+1, y, 2)) / 3;

            // how much brightness changes between the two
            int difference = here - right;
            if(difference < 0) difference = -difference;

            // invert it: big difference = edge (dark), small difference = flat area (bright)
            int value = 255 - difference;

            edges.setPixel(x, y, 0, value);
            edges.setPixel(x, y, 1, value);
            edges.setPixel(x, y, 2, value);
        }
    }

    edges.saveImage("edges_" + filename);
    cout << "Saved as edges_" << filename << endl;

    return 0;
}
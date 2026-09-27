#include<iostream>
using namespace std;
#include "Image_Class.h"

int main(){
    string filename;
    cout<<"enter the image filename for the TV filter: ";
    cin>>filename;
    Image img(filename);

    int w = img.width;
    int h = img.height;
    Image tv(w, h);

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            for(int c = 0; c < 3; c++){

                int value = img.getPixel(x, y, c);

                // scan lines: darken every other row like an old TV screen
                if(y % 2 == 0){
                    value = value / 2;
                }

                tv.setPixel(x, y, c, value);
            }
        }
    }

    tv.saveImage("tv_" + filename);
    cout << "Saved as tv_" << filename << endl;

    return 0;
}
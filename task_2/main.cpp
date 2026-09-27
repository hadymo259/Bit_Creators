#include<iostream>
using namespace std;
#include "Image_Class.h"
int main(){
    string filename;
    cout<<"enter the image filename to turn it to grayscale: ";
    cin>>filename;
    Image img(filename);
    for(int i = 0 ; i<img.width;i++){
        for(int j =0 ; j<img.height;j++){
            unsigned int average = 0;
            for(int c = 0 ; c<3;c++){
                average+= img(i,j,c);
            }
            average/=3;
            img(i,j,0)=average;
            img(i,j,1)=average;
            img(i,j,2)=average;
        }
    }
    cout<<"enter the filename to store the new image and specify extension .jpg, .bmp, .png, .tga: ";
    cin>>filename;
    img.saveImage(filename);
    return 0;
}
/*
 FCAI – CS213: OOP Programming – Assignment 1
 Team Name: Bit Creators
 Section: 25 - 26
 
 Team Members & Assigned Filters:
 ---------------------------------------------
 1. Adam | ID: 20250076
    - Filter 01: Grayscale Conversion
    - Filter 05: Flip Image
    - Filter 09: Merge Images
    - Filter 13: Sunlight Filter

 2. Malak | ID: 20250658
    - Filter 02: Black and White
    - Filter 06: Rotate Image
    - Filter 10: Detect Image Edges
    - Filter 14: Old TV Filter

 3. Nariman | ID: 20250697
    - Filter 03: Invert Image
    - Filter 07: Darken and Lighten Image
    - Filter 11: Crop Images
    - Filter 15: Purple Filter

 4. Hady | ID: 20251467
    - Filter 04: Adding a Frame to the Picture
    - Filter 08: Resizing Images
    - Filter 12: Blur Images
    - Filter 16: Infrared Filter
    - Made the menu,load,save and exit fun
 ----------------------------------------------
*/
#include <iostream>
#include "Image_Class.h"

using namespace std;

void frame(Image& img)
{
    int r = 0, g = 0, b = 0, ch, thinkness;
    cout << "Choose color (1. Red | 2. Green | 3. Blue): ";
    cin >> ch;
    if (ch == 1) { r = 255; g = 0;   b = 0;   }
    else if (ch == 2) { r = 0;   g = 255; b = 0;   }
    else if (ch == 3) { r = 0;   g = 0;   b = 255; }
    cout << "write the thinkness you want : ";
    cin >> thinkness;
    int newwidth = img.width + (2 * thinkness);
    int newheight = img.height + (2 * thinkness);
    Image newimg(newwidth, newheight);
    for (int i = 0; i < newwidth; i++)
    {
        for (int j = 0; j < newheight; j++)
        {
            newimg(i, j, 0) = r;
            newimg(i, j, 1) = g;
            newimg(i, j, 2) = b;
        }
    }
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                newimg(i + thinkness, j + thinkness, k) = img(i, j, k);
            }
        }
    }
    img = newimg;
}
void Resizing(Image& img)
{
    int newwidth,newhight;
    cout<<"write new width for image : ";
    cin>>newwidth;
    cout<<"write new hight for image : ";
    cin>>newhight;
    float x= (float)img.width / newwidth;
    float y= (float)img.height / newhight;
    Image newimg(newwidth,newhight);
    for(int i=0;i<newwidth;i++)
    {
        for(int j=0;j<newhight;j++)
        {
            int newi=i*x;
            int newj=j*y;
            for(int k=0;k<3;k++)
            {
                newimg(i,j,k)=img(newi,newj,k);
            }
        }
    }
    img=newimg;
}
void infraredFilter(Image& img)
{
    for(int i=0;i<img.width;i++)
    {
        for(int j=0;j<img.height;j++)
        {
            int r=img(i,j,0);
            int g=img(i,j,1);
            int b=img(i,j,2);
            int avg =(r+g+b)/3;
            int inv=255-avg;
            img(i,j,0)=255;
            img(i,j,1)=inv;
            img(i,j,2)=inv;
        }
    }
}
void Blur(Image& img)
{
    int radius;
    cout << "Enter blur level ( 5 for normal, 10-15 for heavy blur ): ";
    cin >> radius;
    Image newImg(img.width, img.height);
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;
            for (int dx = -radius; dx <= radius; dx++)
            {
                for (int dy = -radius; dy <= radius; dy++)
                {
                    int ni = i + dx;
                    int nj = j + dy;
                    if (ni >= 0 && ni < img.width && nj >= 0 && nj < img.height)
                    {
                        sumR += img(ni, nj, 0);
                        sumG += img(ni, nj, 1);
                        sumB += img(ni, nj, 2);
                        count++;
                    }
                }
            }
            newImg(i, j, 0) = sumR / count;
            newImg(i, j, 1) = sumG / count;
            newImg(i, j, 2) = sumB / count;
        }
    }
    img = newImg;
}
void grayscale (Image& img)
{
    for(int i = 0 ; i<img.width;i++){
        for(int j =0 ; j<img.height;j++){
            int average = 0;
            for(int k= 0 ; k<3 ;k++){
                average+= img(i,j,k);
            }
            average/=3;
            img(i,j,0)=average;
            img(i,j,1)=average;
            img(i,j,2)=average;
        }
    }
}
void rotate (Image& img,string filename,string newname)
{
    int w = img.width;
    int h = img.height;
    cout << "Loaded image: " << w << " x " << h << endl;

    int rotatedegree;
    cout<<"enter the clockwise degree to rotate the image: ";
    cin>>rotatedegree;

    if(rotatedegree == 90){
        Image rotated(h, w);
        for(int y = 0; y < w; y++)
            for(int x = 0; x < h; x++)
                for(int c = 0; c < 3; c++)
                    rotated.setPixel(x, y, c, img.getPixel(y, h-1-x, c));
        img = rotated;
    }
    else if(rotatedegree == 180){
        Image rotated(w, h);
        for(int y = 0; y < h; y++)
            for(int x = 0; x < w; x++)
                for(int c = 0; c < 3; c++)
                    rotated.setPixel(x, y, c, img.getPixel(w-1-x, h-1-y, c));
        img = rotated;
    }
    else if(rotatedegree == 270){
        Image rotated(h, w);
        for(int y = 0; y < w; y++)
            for(int x = 0; x < h; x++)
                for(int c = 0; c < 3; c++)
                    rotated.setPixel(x, y, c, img.getPixel(w-1-y, x, c));
        img = rotated;
    }
    else{
        cout<<"only 90, 180, or 270 supported"<<endl;
    }
}
void edge_detection(Image& img)
{
    int w = img.width;
    int h = img.height;
    Image edges(w, h);

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){

            if(x == w-1){
                edges.setPixel(x, y, 0, 255);
                edges.setPixel(x, y, 1, 255);
                edges.setPixel(x, y, 2, 255);
                continue;
            }
            int here = (img.getPixel(x, y, 0) + img.getPixel(x, y, 1) + img.getPixel(x, y, 2)) / 3;

            int right = (img.getPixel(x+1, y, 0) + img.getPixel(x+1, y, 1) + img.getPixel(x+1, y, 2)) / 3;

            int difference = here - right;
            if(difference < 0) difference = -difference;

            int value = 255 - difference;

            edges.setPixel(x, y, 0, value);
            edges.setPixel(x, y, 1, value);
            edges.setPixel(x, y, 2, value);
        }
    }
    img=edges;
}
void TV (Image& img)
{
    int w = img.width;
    int h = img.height;
    Image tv(w, h);

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            for(int c = 0; c < 3; c++){

                int value = img.getPixel(x, y, c);

                if(y % 2 == 0){
                    value = value / 2;
                }

                tv.setPixel(x, y, c, value);
            }
        }
    }
    img=tv;
}
void invertImage(Image& image) {
    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            for (int color = 0; color < 3; color++) {
                int currentPixel = image.getPixel(col, row, color);
                int invertedPixel = 255 - currentPixel;
                image.setPixel(col, row, color, invertedPixel);
            }
        }
    }
}
void lightenImage(Image& image) {
    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            for (int color = 0; color < 3; color++) {
                int currentPixel = image.getPixel(col, row, color);
                int newPixel = currentPixel + 50; 

                if (newPixel > 255) newPixel = 255; 

                image.setPixel(col, row, color, newPixel);
            }
        }
    }
}

void darkenImage(Image& image) {
    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            for (int color = 0; color < 3; color++) {
                int currentPixel = image.getPixel(col, row, color);
                int newPixel = currentPixel - 50; 

                if (newPixel < 0) newPixel = 0; 

                image.setPixel(col, row, color, newPixel);
            }
        }
    }
}

int main()
{
    string nameimg, newname;
    Image img;
    
    cout << "write your name img with extension .jpg, .bmp, .png, .tga : ";
    cin >> nameimg;
    cout << "\nwrite your new output image name with extension .jpg, .bmp, .png, .tga:  : ";
    cin >> newname;
    img.loadNewImage(nameimg);
    int x;
    bool valid = false;
    do {
        cout << "\nTo Resizing filter choose num 1\n";
        cout << "To Add Frame choose num 2\n";
        cout << "To Infrared filter choose num 3\n";
        cout << "To Blur filter choose num 4\n";
        cout << "To Grayscale filter choose num 5\n";
        cout << "To Rotate filter choose num 6\n";
        cout << "To Edge detection filter choose num 7\n";
        cout << "To TV filter choose num 8\n";
        cout << "To Invert filter choose num 9\n";
        cout << "To Lighten filter choose num 10\n";
        cout << "To Darken filter choose num 11\n";
        cout << "To Exit choose num 0\n";
        cout << "Enter choice: ";
        cin >> x;

        if (x == 0) {
            cout << "Exiting program. Goodbye!\n";
            return 0;
        }
        else if (x == 1) {
            Resizing(img);
            valid = true;
        } 
        else if (x == 2) {
            frame(img);
            valid = true;
        } 
        else if (x == 3) {
            infraredFilter(img);
            valid = true;
        } 
        else if (x == 4) {
            Blur(img);
            valid = true;
        } 
        else if (x == 5) {
            grayscale(img);
            valid = true;
        } 
        else if (x == 6) {
            rotate(img,nameimg,newname);
            valid = true;
        } 
        else if (x == 7) {
            edge_detection(img);
            valid = true;
        } 
        else if (x == 8) {
            TV(img);
            valid = true;
        } 
        else if (x == 9){
            invertImage(img);
            valid = true;
        }
        else if (x ==10){
            lightenImage(img);
            valid = true;
        }
        else if (x == 11){
            darkenImage(img);
            valid = true;
        }
        else {
            cout << "\nInvalid choice! Please try again.\n";
        }
    } while (!valid);

    if(img.saveImage(newname))
    {
        cout << "\nDone! Image saved successfully.\n";
    }
    return 0;
}
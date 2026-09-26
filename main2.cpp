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

int main()
{
    string nameimg, newname;
    Image img;
    
    cout << "write your name img : ";
    cin >> nameimg;
    cout << "\nwrite your new output image name : ";
    cin >> newname;
    img.loadNewImage(nameimg);
    int x;
    bool valid = false;
    do {
        cout << "\nto Resizing filter choose num 1\n";
        cout << "to frame filter choose num 2\n";
        cout << "to infrared filter choose num 3\n";
        cout << "Enter choice: ";
        cin >> x;

        if (x == 1) {
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
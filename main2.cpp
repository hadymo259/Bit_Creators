/*
 FCAI – CS213: OOP Programming – Assignment 1
 Team Name: Bit Creators
 Section: 29 - 30
 
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
    - Filter 17: Skew Filter(Bonus)
    - Filter 18: Oil painting Filter(Bonus)
    - Made the menu,load,save and exit fun
 ----------------------------------------------
*/
#include <iostream>
#include <cmath>
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
void rotate (Image& img)
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
    int ch;
    cout<<"\nTo lighten image choose num 1\n";
    cout<<"To Darken image choose num 2\n";
    cout<<"Enter your choose : ";
    cin>>ch;
    if(ch==1)
    {
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
    }else if(ch==2)
    {
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
    
}
void blackandwhite(Image& img)
{
    for(int i=0;i<img.width;i++)
    {
        for(int j=0;j<img.height;j++)
        {
            int avg=0;
            for(int k=0;k<3;k++)
            {
                avg+=img(i,j,k);
            }
            avg/=3;
            if(avg>127)
            {
                img(i,j,0)=255;
                img(i,j,1)=255;
                img(i,j,2)=255;
            }else{
                img(i,j,0)=0;
                img(i,j,1)=0;
                img(i,j,2)=0;
            }
        }
    }
}
void flip(Image& img)
{
    int choice;
    cout << "1. Horizontal Flip\n";
    cout << "2. Vertical Flip\n";
    cout << "Choose: ";

    if (!(cin >> choice) || (choice != 1 && choice != 2))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice.\n";
        return;
    }

    if (choice == 1)
    {
        for (int i = 0; i < img.width / 2; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    swap(img(i, j, k), img(img.width - 1 - i, j, k));
                }
            }
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height / 2; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    swap(img(i, j, k), img(i, img.height - 1 - j, k));
                }
            }
        }
    }
}
void oilPainting(Image& img)
{
    int radius;
    
    do
    {
        cout << "\nEnter oil painting level ";
        cout << "(2-3 for normal, 4-6 for strong, 7-10 for very strong): ";
        cin >> radius;

        if (radius < 2 || radius > 10)
        {
            cout << "Invalid level! Please enter a number from 2 to 10.\n";
        }

    } while (radius < 2 || radius > 10);

    int width = img.width;
    int height = img.height;

    Image newimg(width, height);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int count[256] = {0};

            int sumR[256] = {0};
            int sumG[256] = {0};
            int sumB[256] = {0};

            for (int dx = -radius; dx <= radius; dx++)
            {
                for (int dy = -radius; dy <= radius; dy++)
                {
                    int x = i + dx;
                    int y = j + dy;

                    if (x < 0)
                        x = 0;

                    if (x >= width)
                        x = width - 1;

                    if (y < 0)
                        y = 0;

                    if (y >= height)
                        y = height - 1;

                    int r = img(x, y, 0);
                    int g = img(x, y, 1);
                    int b = img(x, y, 2);

                    int intensity = (r + g + b) / 3;

                    count[intensity]++;

                    sumR[intensity] += r;
                    sumG[intensity] += g;
                    sumB[intensity] += b;
                }
            }

            int maxIntensity = 0;

            for (int k = 1; k < 256; k++)
            {
                if (count[k] > count[maxIntensity])
                {
                    maxIntensity = k;
                }
            }

            newimg(i, j, 0) =
                sumR[maxIntensity] / count[maxIntensity];

            newimg(i, j, 1) =
                sumG[maxIntensity] / count[maxIntensity];

            newimg(i, j, 2) =
                sumB[maxIntensity] / count[maxIntensity];
        }
    }

    img = newimg;
}
void skew(Image& img)
{
    double angle;

    cout << "\nEnter skew angle in degrees: ";
    cin >> angle;

    int width = img.width;
    int height = img.height;

    double radians = angle * 3.14159265 / 180.0;

    int shift = (int)((height - 1) * tan(radians));

    int newWidth = width + abs(shift);

    Image newimg(newWidth, height);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int newX = i - (int)(j * tan(radians)) + shift;

            if (newX >= 0 && newX < newWidth)
            {
                newimg(newX, j, 0) = img(i, j, 0);
                newimg(newX, j, 1) = img(i, j, 1);
                newimg(newX, j, 2) = img(i, j, 2);
            }
        }
    }

    img = newimg;
}
void cropImage(Image& image) 
{
    int x, y, w, h;
    cout << "Enter x, y, width, height: ";
    cin >> x >> y >> w >> h;


    if (x < 0 || y < 0 || x + w > image.width || y + h > image.height) {
        cout << "Error: Out of bounds!\n";
        return;
    }

    Image output(w, h);

    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            for (int c = 0; c < 3; c++) {
                output(col, row, c) = image(x + col, y + row, c);
            }
        }
    }

    image = output;
}
void purpleFilter(Image& image) 
{
    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {

            int r = image.getPixel(col, row, 0) + 40;
            int b = image.getPixel(col, row, 2) + 40;

            if (r > 255) r = 255;
            if (b > 255) b = 255;

            image.setPixel(col, row, 0, r);
            image.setPixel(col, row, 2, b);
        }
    }
}

bool validExtension(string name)
{
    int pos = name.find_last_of('.');

    if (pos == -1)
        return false;

    string ext = name.substr(pos);

    if (ext == ".jpg" ||
        ext == ".jpeg" ||
        ext == ".png" ||
        ext == ".bmp" ||
        ext == ".tga")
    {
        return true;
    }

    return false;
}

bool loadImage(Image& image, string& imageName)
{
    string name;

    while (true)
    {
        cout << "\nEnter image name with extension .jpg, .bmp, .png, .tga : ";
        cin >> name;

        if (!validExtension(name))
        {
            cout << "Invalid extension! Try again.\n";
            continue;
        }

        image.loadNewImage(name);
        imageName = name;

        cout << "Image loaded successfully!\n\n";

        return true;
    }
}
bool saveImage(Image& image, string& imageName)
{
    int choice;

    cout << "\n1. Save with same name\n";
    cout << "2. Save with new name\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        if (image.saveImage(imageName))
        {
            cout << "Image saved successfully!\n\n";
            return true;
        }

        cout << "Failed to save image!\n";
        return false;
    }

    else if (choice == 2)
    {
        string name;

        while (true)
        {
            cout << "\nEnter new image name with extension .jpg, .bmp, .png, .tga : ";
            cin >> name;

            if (!validExtension(name))
            {
                cout << "Invalid extension! Try again.\n";
                continue;
            }

            if (image.saveImage(name))
            {
                imageName = name;

                cout << "Image saved successfully!\n";
                return true;
            }

            cout << "Failed to save image!\n";
            return false;
        }
    }

    else
    {
        cout << "Invalid choice!\n";
        return false;
    }
}
void showMenu()
{
    cout << "==== Choose a Filter ====\n";
    cout << "1. Grayscale Filter\n";
    cout << "2. Black and White Filter\n";
    cout << "3. Invert Filter\n";
    cout << "4. Add Frame Filter\n";
    cout << "5. Flip Filter\n";
    cout << "6. Rotate Filter\n";
    cout << "7. Lighten / Darken Filter\n";
    cout << "8. Resize Filter\n";
    cout << "10. Edge Detection Filter\n";
    cout << "11. Crop Image Filter\n";
    cout << "12. Blur Filter\n";
    cout << "14. TV Filter\n";
    cout << "15. Purple Image Filter\n";
    cout << "16. Infrared Filter\n";
    cout << "17. Skew Filter\n";
    cout << "18. Oil Painting Filter\n";
    cout << "19. Save Image\n";
    cout << "20. Load New Image\n";
    cout << "21. Undo last Filter\n";
    cout << "22. Clear all Filters\n";
    cout << "0. Exit\n";
    
    cout << "====================================\n";
}
void clear(Image& image, Image& originalImage)
{
    image = originalImage;

    cout << "\nAll filters have been cleared!\n";
}

int main()
{
    Image image;
    Image originalImage;
    Image oldImage;
 
    string imageName;

    bool loaded = false;

    while (!loaded)
    {
        loaded = loadImage(image, imageName);
        if (!loaded)
        {
            cout << "Please try again.\n";
        }
    }
    originalImage = image;
    while (true)
    {
        showMenu();

        int choice;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0)
        {
            char answer;

            cout << "\nDo you want to save before exit? (y/n): ";
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {
                saveImage(image, imageName);
            }

            cout << "\nGoodbye!\n";
            break;
        }
        else if (choice == 1)
        {
            oldImage = image;
            grayscale(image);
        }
        else if (choice == 2)
        {
            oldImage = image;
            blackandwhite(image);
        }
        else if (choice == 3)
        {
            oldImage = image;
            invertImage(image);
        }
        else if (choice == 4)
        {
            oldImage = image;
            frame(image);
        }
        else if (choice == 5)
        {
            oldImage = image;
            flip(image);
        }
        else if (choice == 6)
        {
            oldImage = image;
            rotate(image);
        }
        else if (choice == 7)
        {
            oldImage = image;
            lightenImage(image);
        }
        else if (choice == 8)
        {
            oldImage = image;
            Resizing(image);
        }
        else if (choice == 10)
        {
            oldImage = image;
            edge_detection(image);
        }
        else if (choice == 11)
        {
            oldImage = image;
            cropImage(image);
        }
        else if (choice == 12)
        {
            oldImage = image;
            Blur(image);
        }
        else if (choice == 14)
        {
            oldImage = image;
            TV(image);
        }
        else if (choice == 15)
        {
            oldImage = image;
            purpleFilter(image);
        }
        else if (choice == 16)
        {
            oldImage = image;
            infraredFilter(image);
        }
        else if (choice == 17)
        {
            oldImage = image;
            skew(image);
        }
        else if (choice == 18)
        {
            oldImage = image;
            oilPainting(image);
        }
        else if (choice == 19)
        {
            saveImage(image, imageName);
        }
        else if (choice == 20)
        {
            char answer;

            cout << "\nDo you want to save the current image before loading a new one? (y/n): ";
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {
                saveImage(image, imageName);
            }

            loadImage(image, imageName);
            originalImage = image;
        }
        else if(choice == 21)
        {
            image = oldImage;
            cout << "Undo done successfully!\n";
        }
        else if(choice == 22)
        {
            clear(image, originalImage);
        }
        else
        {
            cout << "\nInvalid choice! Please try again.\n";
        }
    }
    return 0;
}
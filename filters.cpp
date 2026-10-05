#include "filters.h"
#include <algorithm>
using namespace std;

void mergeImages(Image &img1, Image img2)
{
    try
    {
        int width = min(img1.width, img2.width);
        int height = min(img1.height, img2.height);
        Image mergeImages(width, height);
        {
            for (int w = 0; w < width; w++)
            {
                for (int h = 0; h < height; h++)
                {
                    int red1 = img1.getPixel(w, h, 0);
                    int red2 = img2.getPixel(w, h, 0);

                    int green1 = img1.getPixel(w, h, 1);
                    int green2 = img2.getPixel(w, h, 1);

                    int blue1 = img1.getPixel(w, h, 2);
                    int blue2 = img2.getPixel(w, h, 2);

                    int newRed = (int)(red1 + red2) / 2;
                    int newGreen = (int)(green1 + green2) / 2;
                    int newBlue = (int)(blue1 + blue2) / 2;

                    mergeImages.setPixel(w, h, 0, newRed);
                    mergeImages.setPixel(w, h, 1, newGreen);
                    mergeImages.setPixel(w, h, 2, newBlue);
                }
            }
        }
        img1 = mergeImages;
    }
    catch (const exception &y)
    {
        cerr << "ERROR!!!" << y.what();
    }
}

void grayscale(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0; 

            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k); 
            }

            avg /= 3; 


            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}




void flipImage(Image &image)
{
    short choice;

    cout << "Press 1 for vertical flip\n";
    cout << "Press 2 for horizontal flip\n";
    cin >> choice;
    
    switch (choice)
    {
    case 1:
    {
        for(int i = 0; i < image.width/2;i++){
            for(int j = 0; j <image.height;j++){
                for(int k = 0; k <3; k++){
                    unsigned char temp = image(i,j,k);
                    image(i,j,k) = image(image.width-i-1,j,k);
                    image(image.width-i-1,j,k) = temp;
                }
            }
        }
    };
    break;
    
    case 2:
    {
        for (int j = 0; j < image.height / 2; j++)
        {
            for (int i = 0; i < image.width; i++)
            {
                for (int k = 0; k < 3; k++)
                {
                    unsigned char temp = image(i, j, k);
                    image(i,j,k) = image(i,image.height-j-1,k);
                    image(i,image.height-1-j,k) = temp;
                }
            }
        }
    }

    }
}



void blackAndWhite(Image& image) {
    for(int y = 0; y < image.height; ++y) {
        for(int x = 0; x < image.width; ++x) {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int avg = (r + g + b) / 3;
            if(avg < 128) {
                image.setPixel(x, y, 0, 0);
                image.setPixel(x, y , 1, 0);
                image.setPixel(x, y, 2, 0);
            } else {
                image.setPixel(x, y, 0, 255);
                image.setPixel(x, y , 1, 255);
                image.setPixel(x, y, 2, 255);
            }
        }
    }
}

void rotateImage(Image& image, int angle) {
    int height = image.height;
    int width = image.width;
    int newWidth = width, newHeight = height;

    if(angle == 0) return;
    if(angle == 90 || angle == 270) {newWidth = height; newHeight = width;}
    else if(angle == 180) {newWidth= width; newHeight = height;}
    else return;

    Image temp(newWidth, newHeight);

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            int newX, newY;
            if(angle == 90 ) {newX = height - 1 - y; newY = x;}
            if(angle == 180) {newX = width - 1 - x; newY = height - 1 - y;}
            if(angle == 270) {newX = y; newY = width - 1 - x;}     
            
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            temp.setPixel(newX, newY, 0, r);
            temp.setPixel(newX, newY, 1, g);
            temp.setPixel(newX, newY, 2, b);
        }
    }

    image = temp;
}

void detectEdges(Image& image) {
    int height = image.height, width = image.width;
    Image temp(width, height);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int red = image.getPixel(x, y, 0), green = image.getPixel(x, y, 1), blue = image.getPixel(x, y, 2);
            int nextXRed   = x < width - 1  ? image.getPixel(x + 1, y, 0) : image.getPixel(x - 1, y, 0);
            int nextXGreen = x < width - 1  ? image.getPixel(x + 1, y, 1) : image.getPixel(x - 1, y, 1);
            int nextXBlue  = x < width - 1  ? image.getPixel(x + 1, y, 2) : image.getPixel(x - 1, y, 2);
            int nextYRed   = y < height - 1 ? image.getPixel(x, y + 1, 0) : image.getPixel(x, y - 1, 0);
            int nextYGreen = y < height - 1 ? image.getPixel(x, y + 1, 1) : image.getPixel(x, y - 1, 1);
            int nextYBlue  = y < height - 1 ? image.getPixel(x, y + 1, 2) : image.getPixel(x, y - 1, 2);
            
            int currentAvg = (red + green + blue) / 3;
            int nextXAvg   = (nextXRed + nextXGreen + nextXBlue) / 3;
            int nextYAvg   = (nextYRed + nextYGreen + nextYBlue) / 3;

            int val = 255;
            if(abs(currentAvg - nextXAvg) > 75 || abs(currentAvg - nextYAvg) > 75) val = 0;

            temp.setPixel(x, y, 0, val);
            temp.setPixel(x, y, 1, val);
            temp.setPixel(x, y, 2, val);
        }
    }
    image = temp;
}

// void detectEdges(Image& image) {
//     int height = image.height, width = image.width;
//     Image temp(width, height);
//     blackAndWhite(image);
//     for(int y = 0; y < height; ++y) {
//         for(int x = 0; x < width; ++x) {
//             int val = 255;
//             int current = image.getPixel(x, y, 0);
//             int nextX = x < width - 1 ? image.getPixel(x + 1, y, 0) : image.getPixel(x - 1, y, 0);
//             int nextY = y < height -1 ? image.getPixel(x, y + 1, 0) : image.getPixel(x, y - 1, 0);
//             if(current != nextX || current != nextY) val = 0;
                    
//             temp.setPixel(x, y, 0, val);
//             temp.setPixel(x, y, 1, val);
//             temp.setPixel(x, y, 2, val);
//         }
//     }
//     image = temp;
// }

void oilPainting(Image& image) {
    int height = image.height, width = image.width;
    Image temp(width, height);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int intensity, levels = 30, bucket, radius = 2;
            int count[256] = {0}, sumR[256] = {0}, sumG[256] = {0}, sumB[256] = {0};
            
            for(int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = min(max(x + dx, 0), width - 1);
                    int ny = min(max(y + dy, 0), height - 1);
                    int r = image.getPixel(nx, ny, 0);
                    int g = image.getPixel(nx, ny, 1);
                    int b = image.getPixel(nx, ny, 2);
                    intensity = (r + g + b) / 3;
                    bucket = intensity * (levels - 1) / 255;
                    count[bucket]++  ;
                    sumR[bucket] += r;
                    sumG[bucket] += g;
                    sumB[bucket] += b; 
                }
            }
            int best = 0;
            for(int i = 0; i < levels; i++) { if(count[i] > count[best]) best = i; }
            temp.setPixel(x, y, 0, sumR[best]/count[best]);
            temp.setPixel(x, y, 1, sumG[best]/count[best]);
            temp.setPixel(x, y, 2, sumB[best]/count[best]);
        }
    }
    image = temp;
}
// void oilPainting(Image& image) {
//     int height = image.height, width = image.width;
//     Image temp(width, height);

//     int radius = 2;
//     int levels = 30;
//     int strength = 70;

//     for(int y = 0; y < height; y++) {
//         for(int x = 0; x < width; x++) {
//             int count[256] = {0}, sumR[256] = {0}, sumG[256] = {0}, sumB[256] = {0};

//             for(int dy = -radius; dy <= radius; dy++) {
//                 for(int dx = -radius; dx <= radius; dx++) {
                    
//                     if(dx * dx + dy * dy > radius * radius)  continue;

//                     int nx = min(max(x + dx, 0), width - 1);
//                     int ny = min(max(y + dy, 0), height - 1);
//                     int r = image.getPixel(nx, ny, 0);
//                     int g = image.getPixel(nx, ny, 1);
//                     int b = image.getPixel(nx, ny, 2);
//                     int bucket = ((r + g + b) / 3) * (levels - 1) / 255;
//                     count[bucket]++;
//                     sumR[bucket] += r;
//                     sumG[bucket] += g;
//                     sumB[bucket] += b;
//                 }
//             }

//             int best = 0;
//             for(int i = 1; i < levels; i++) {
//                 if(count[i] > count[best]) best = i;
//             }

//             int origR = image.getPixel(x, y, 0);
//             int origG = image.getPixel(x, y, 1);
//             int origB = image.getPixel(x, y, 2);

//             temp.setPixel(x, y, 0, (sumR[best] / count[best] * strength + origR * (100 - strength)) / 100);
//             temp.setPixel(x, y, 1, (sumG[best] / count[best] * strength + origG * (100 - strength)) / 100);
//             temp.setPixel(x, y, 2, (sumB[best] / count[best] * strength + origB * (100 - strength)) / 100);
//         }
//     }
//     image = temp;
// }

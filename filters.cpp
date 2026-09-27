#include "filters.h"

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
    blackAndWhite(image);
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            int val = 255;
            int current = image.getPixel(x, y, 0);
            int nextX = x < width - 1 ? image.getPixel(x + 1, y, 0) : image.getPixel(x - 1, y, 0);
            int nextY = y < height -1 ? image.getPixel(x, y + 1, 0) : image.getPixel(x, y - 1, 0);
            if(current != nextX || current != nextY) val = 0;
                    
            temp.setPixel(x, y, 0, val);
            temp.setPixel(x, y, 1, val);
            temp.setPixel(x, y, 2, val);
        }
    }
    image = temp;
}
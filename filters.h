#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"

void grayscale(Image& image);
void blackAndWhite(Image& image);
void invertImage(Image& image);
void addFrame(Image& image);
void flipImage(Image& image);
void rotateImage(Image& image, int angle);
void darkenImage(Image& image);
void lightenImage(Image& image);
void resizeImage(Image& image, int newWidth, int newHeight);
void mergeImages(Image& image, const Image& secondImage);
void detectEdges(Image& image);
void cropImage(Image& image, int startX, int startY, int width, int height);
void blurImage(Image& image);
void sunlightFilter(Image& image);
void tvFilter(Image& image);
void purpleFilter(Image& image);
void infraredFilter(Image& image);
void skewImage(Image& image);
void oilPainting(Image& image);

#endif
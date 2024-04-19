/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    // Complete your implementation below
    referenceimg = inputimg;
    brightamount = b_amount;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    unsigned int x = p.x % (referenceimg.width() / 2) * 2;
    unsigned int y = p.y % (referenceimg.height() / 2) * 2;

    RGBAPixel* original = referenceimg.getPixel(x, y);
    RGBAPixel* east = referenceimg.getPixel(x + 1, y);
    RGBAPixel* south = referenceimg.getPixel(x, y + 1);
    RGBAPixel* southeast = referenceimg.getPixel(x + 1, y + 1);

    return calcPixel(original, east, south, southeast);
}

/**
 * Add your private QuarterColorPicker function implementations below
 */

RGBAPixel QuarterColorPicker::calcPixel(RGBAPixel* original, RGBAPixel* east, RGBAPixel* south, RGBAPixel* southeast) {
    // RGBAPixel out = RGBAPixel();
    // out.r = std::min((unsigned char)(((original->r + right->r) / 2.0 + down->r) / 2) + brightamount, 255);
    // out.g = std::min((unsigned char)(((original->g + right->g) / 2.0 + down->g) / 2) + brightamount, 255);
    // out.b = std::min((unsigned char)(((original->b + right->b) / 2.0 + down->b) / 2) + brightamount, 255);
    RGBAPixel avg1 = avgPixel(*original, *east);
    RGBAPixel avg2 = avgPixel(*south, *southeast);
    RGBAPixel out = avgPixel(avg1, avg2);
    out.r = std::min(out.r + brightamount, 255);
    out.g = std::min(out.g + brightamount, 255);
    out.b = std::min(out.b + brightamount, 255);
    return out;
}

RGBAPixel QuarterColorPicker::avgPixel(RGBAPixel p1, RGBAPixel p2) {
    RGBAPixel out = RGBAPixel();
    out.r = (p1.r + p2.r) / 2;
    out.g = (p1.g + p2.g) / 2;
    out.b = (p1.b + p2.b) / 2;
    return out;
}

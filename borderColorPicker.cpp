/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include <cmath>
#include "borderColorPicker.h"

/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
{
    // Complete your implementation below
	borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
}

/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    if (img.getPixel(p.x, p.y)->distanceTo(seedcolor) > tolerance)  // return original color if not in fill area
        return *img.getPixel(p.x, p.y);

    for (unsigned int dx = 0; dx <= (borderwidth * 2); dx++) {
        for (unsigned int dy = 0; dy <= (borderwidth * 2); dy++) {
            int x = p.x + dx - borderwidth;
            int y = p.y + dy - borderwidth;

            unsigned int distancesquares = (dx - borderwidth) * (dx - borderwidth) + (dy - borderwidth) * (dy - borderwidth);
            if (distancesquares > borderwidth * borderwidth)
                continue;

            if (x < 0 || x >= (int) img.width() || y < 0 || y >= (int) img.height() || img.getPixel(x, y)->distanceTo(seedcolor) > tolerance)
                return bordercolor;
        }
    }

    return *img.getPixel(p.x, p.y);
}

/**
 * Add your private BorderColorPicker function implementations below
 */

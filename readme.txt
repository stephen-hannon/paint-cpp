P1: Stephen Hannon (shannon3)
P2: Julius Boateng (jboateng)

This project takes an image file as a command line argument and
displays it, allowing the user to draw over it with different colors
using the mouse. Files must be in the PPM format, which allows for easy
reading and storing of pixels. This can represent any 24-bit color, but for
performance reasons the program only displays each pixel's closest 8-bit
color. Using the second command line argument, the program can save the
modified image into a new file. If only one argument is given, the original
file is overwritten on save.

Example usage (two sample PPM images are provided):
./paint background1.ppm
./paint ramzi.ppm out.ppm


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])

{
        // Define file pointer and variables
        FILE *file;
        int BytesPerPixel;
        int Width=500;
        int Height=750;
        int Size=256;
        // Check for proper syntax
        if (argc < 3){
                cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
                cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
                return 0;
        }

        // Check if image is grayscale or color
        if (argc < 4){
                BytesPerPixel = 1; // default is grey image
        }
        else {
                BytesPerPixel = atoi(argv[3]);
                // Check if size is specified
                if (argc >= 5){
                        Size = atoi(argv[4]);
                }
        }

        // Allocate image data array
        unsigned char Imagedata[Width][Height][1];


        // Read image (filename specified by first argument) into image data matrix
         if (!(file=fopen(argv[1],"rb"))) {
                cout << "Cannot open file: " << argv[1] <<endl;
                exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Width*Height*1, file);
        fclose(file);

        ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	for (int i = 1; i < (Width-1); i++)
    	    {
       	     for (int j = 1; j < (Height-1); j++)
        	{
			if(float(Imagedata[i][j][0])>=0.0 && float(Imagedata[i][j][0])<128.00)
				Imagedata[i][j][0]=(unsigned char)0;
			else
			        Imagedata[i][j][0]=(unsigned char)255;
		}
	    }


        // Write image data (filename specified by second argument) from image data matrix

        if (!(file=fopen(argv[2],"wb"))) {
                cout << "Cannot open file: " << argv[2] << endl;
                exit(1);
        }
        fwrite(Imagedata, sizeof(unsigned char), Width*Height*1, file);
        fclose(file);

        return 0;
}



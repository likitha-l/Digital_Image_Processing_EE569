// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:        The code assumes that the image is of size 256 x 256 and is in the
//                      RAW format. You will need to make corresponding changes to
//                      accommodate images of different sizes and/or types

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
        int Width=320;
        int Height=320;
        int Size=256;
        // Check for proper syntax
        if (argc < 4){
                cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
                cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
                return 0;
        }

        // Check if image is grayscale or color
        if (argc < 5){
                BytesPerPixel = 1; // default is grey image
        }
        else {
                BytesPerPixel = atoi(argv[4]);
                // Check if size is specified
                if (argc >= 6){
                        Size = atoi(argv[5]);
                }
        }


        // Allocate image data array
        unsigned char Imagedata[Width][Height][BytesPerPixel];
        //Allocate original image data array
        unsigned char OriginalImage[Width][Height][BytesPerPixel];

        // Read image (filename specified by first argument) into image data matrix
         if (!(file=fopen(argv[1],"rb"))) {
                cout << "Cannot open file: " << argv[1] <<endl;
                exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
        fclose(file);


        // Read image (filename specified by second argument) into original image matrix
         if (!(file=fopen(argv[2],"rb"))) {
                cout << "Cannot open file: " << argv[2] <<endl;
                exit(1);
        }
        fread(OriginalImage, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
        fclose(file);

        ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
        float mask[3][3]={{1/9.0,1/9.0,1/9.0},{1/9.0,1/9.0,1/9.0},{1/9.0,1/9.0,1/9.0}};
      //  float mask[4][4]={{1/16.0,1/16.0,1/16.0,1/16.0},{1/16.0,1/16.0,1/16.0,1/16.0},{1/16.0,1/16.0,1/16.0,1/16.0},{1/16.0,1/16.0,1/16.0,1/16.0}};
      // float mask[5][5]={{1/25.0,1/25.0,1/25.0,1/25.0,1/25.0},{1/25.0,1/25.0,1/25.0,1/25.0,1/25.0},{1/25.0,1/25.0,1/25.0,1/25.0,1/25.0},{1/25.0,1/25.0,1/25.0,1/25.0,1/25.0},{1/25.0,1/25.0,1/25.0,1/25.0,1/25.0}};
        float sum;
        float a;
        float mse=0.0;
        float error;
        float psnr;
        float norm_mse;

        unsigned char temp[Width][Height][1];


   for (int i = 1; i < (Width-1); i++)
    {
        for (int j = 1; j < (Height-1); j++)
        {
            sum=0.0;

            for (int u = -1; u <= 1; u++)
            {
                for (int v = -1; v <= 1; v++)
                {
                    a=(float)Imagedata[i+u][j+v][0];
                    sum= sum + a* (mask[u+1][v+1]);
                }
            }

            sum=ceil(sum);
            if(sum<0)
                sum=0;
            if(sum>255)
                sum=255;
            temp[i][j][0]=(unsigned char)sum;

        }
    }


	//Calculating PSNR
    for(int i=1;i<(Width-1);i++){
        for(int j=1;j<(Height-1);j++){
            error=(float)temp[i][j][0]-(float)OriginalImage[i][j][0];
            mse=mse+pow(error,2);
        }
    }

    norm_mse=mse/(Width*Height);
    psnr=10*log10(pow(255,2)/norm_mse);
    cout<<"PSNR: "<<psnr<<endl;

        // Write image data (filename specified by third argument) from image data matrix

        if (!(file=fopen(argv[3],"wb"))) {
                cout << "Cannot open file: " << argv[3] << endl;
                exit(1);
        }
        fwrite(temp, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
        fclose(file);

        return 0;
}





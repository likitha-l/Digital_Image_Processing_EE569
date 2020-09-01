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
        int Width=321;
        int Height=481;
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
        unsigned char Imagedata[Width][Height][3];
        unsigned char Grayscale[Width][Height][1];
        unsigned char GradientxImage[Width][Height][1];
        unsigned char GradientyImage[Width][Height][1];
	unsigned char GradientMag[Width][Height][1];
	unsigned char BinaryImage[Width][Height][1];


        // Read image (filename specified by first argument) into image data matrix
         if (!(file=fopen(argv[1],"rb"))) {
                cout << "Cannot open file: " << argv[1] <<endl;
                exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Width*Height*3, file);
        fclose(file);

        ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	float gradientx[3][3]={{1.0,0.0,-1.0},{2.0,0.0,-2.0},{1.0,0.0,-1.0}};     
	float gradienty[3][3]={{1.0,2.0,1.0},{0.0,0.0,0.0},{-1.0,-2.0,-1.0}};
        float sum1;
	float sum2;
        float a;
	float c;
	int count=0;
	int count1=0;
 
        for(int i=0;i<Width;i++){
            for(int j=0;j<Height;j++){
                    Grayscale[i][j][0]=0.2989*Imagedata[i][j][0]+0.5870*Imagedata[i][j][1]+0.1140*Imagedata[i][j][2];
            }
        }

	for (int i = 1; i < (Width-1); i++)
        {
            for (int j = 1; j < (Height-1); j++)
            {
                sum1=0.0;
		sum2=0.0;

                for (int u = -1; u <= 1; u++)
                {
                    for (int v = -1; v <= 1; v++)
                    {
                        a=(float)Grayscale[i+u][j+v][0];
                        sum1= sum1 + a* (gradientx[u+1][v+1]);
			sum2= sum2 + a* (gradienty[u+1][v+1]);
                    }
                }

		sum1=ceil(sum1);
		if(sum1<0)
                sum1=0;
                if(sum1>255)
                sum1=255;
                GradientxImage[i][j][0]=(unsigned char)sum1;
		sum2=ceil(sum2);
               if(sum2<0){
                  count1++;
		  sum2=0;}
                if(sum2>255)
                    count++;
                GradientyImage[i][j][0]=(unsigned char)sum2;
		c=sqrt(pow(sum1,2)+pow(sum2,2));
		GradientMag[i][j][0]=(unsigned char)c;


            }
        }


	for (int i = 1; i < (Width-1); i++)
    	    {
       	     for (int j = 1; j < (Height-1); j++)
        	{
			if(float(GradientMag[i][j][0])>=0.0 && float(GradientMag[i][j][0])<128.00)
				BinaryImage[i][j][0]=(unsigned char)0;
			else
			        BinaryImage[i][j][0]=(unsigned char)255;
		}
	    }

        // Write image data (filename specified by second argument) from image data matrix

        if (!(file=fopen(argv[2],"wb"))) {
                cout << "Cannot open file: " << argv[2] << endl;
                exit(1);
        }
        fwrite(BinaryImage, sizeof(unsigned char), Width*Height*1, file);
        fclose(file);

        return 0;
}


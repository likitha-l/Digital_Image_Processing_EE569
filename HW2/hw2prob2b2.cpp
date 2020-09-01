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
        unsigned char Imagedatacpy[Width][Height][1];
	unsigned char OutputImage[Width][Height][1];


        // Read image (filename specified by first argument) into image data matrix
         if (!(file=fopen(argv[1],"rb"))) {
                cout << "Cannot open file: " << argv[1] <<endl;
                exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Width*Height*1, file);
        fclose(file);

        ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
        int b[Width][Height];
       // float h[5][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,7/48.0,5/48.0},{3/48.0,5/48.0,7/48.0,5/48.0,3/48.0},{1/48.0,3/48.0,5/48.0,3/48.0,1/48.0}};
       //float hflip[5][5]={{0,0,0,0,0},{0,0,0,0,0},{5/48.0,7/48.0,0,0,0},{3/48.0,5/48.0,7/48.0,5/48.0,3/48.0},{1/48.0,3/48.0,5/48.0,3/48.0,1/48.0}};
        float h[5][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,8/42.0,4/42.0},{2/42.0,4/42.0,8/42.0,4/42.0,2/42.0},{1/42.0,2/42.0,4/42.0,2/42.0,1/42.0}};
        float hflip[5][5]={{0,0,0,0,0},{0,0,0,0,0},{4/42.0,8/42.0,0,0,0},{2/42.0,4/42.0,8/42.0,4/42.0,2/42.0},{1/42.0,2/42.0,4/42.0,2/42.0,1/42.0}};
	float e;
	float data;
	float data1;

	    for (int i = 1; i < (Width-1); i++)
        	{
       	     for (int j = 1; j < (Height-1); j++)
        	{
        	    Imagedatacpy[i][j][0]=Imagedata[i][j][0];
	        }
	    }

        for (int i = 1; i < (Width-1); i++)
        {
            if(i%2==0){
       	     for (int j = 1; j < (Height-1); j++)
        	{
		    if(Imagedatacpy[i][j][0]>128.00){
			b[i][j]=255;}
		    else{
			 b[i][j]=0;
			}
        	    e=(float)Imagedatacpy[i][j][0]-b[i][j];

                for (int u = -2; u <= 2; u++)
                    {
                    for (int v = -2; v <= 2; v++)
                        {
                            if((i+u)<0 || (j+v)<0 ||((i+u)>(Width-1))||((j+u)>(Height-1)) ){
                                continue;
                            }
			     data1=((float)Imagedatacpy[i+u][j+v][0]+h[u+2][v+2]*e);
			     Imagedatacpy[i+u][j+v][0]=(unsigned char)(data1);
                        }
                    }
        	}
        }
        if(i%2!=0){
       	     for (int j1 =Height; j1 >=0; j1--)
        	{
		  if(float(Imagedatacpy[i][j1][0])>128.00)
			b[i][j1]=255;
		  else
               		 b[i][j1]=0;
        	    e=(float)Imagedatacpy[i][j1][0]-b[i][j1];
                for (int u = -2; u <= 2; u++)
                    {
                    for (int v = -2; v <= 2; v++)
                        {
                            if((i+u)<0 || (j1+v)<0 || ((i+u)>(Width-1))||((j1+u)>(Height-1))){
                                continue;
                            }
			     data=((float)Imagedatacpy[i+u][j1+v][0]+hflip[u+2][v+2]*e);
			     Imagedatacpy[i+u][j1+v][0]=(unsigned char)(data);    
                        }
                    }
        	}
        }
        }

  for (int i = 1; i <(Width-1) ; i++)
        {
       	   for (int j=1; j < (Height-1); j++)
        	{
                if(float(Imagedatacpy[i][j][0])>128.00)
	        	OutputImage[i][j][0]=(unsigned char)255;
	        else
                        OutputImage[i][j][0]=(unsigned char)0;
		}
	}




        // Write image data (filename specified by second argument) from image data matrix

        if (!(file=fopen(argv[2],"wb"))) {
                cout << "Cannot open file: " << argv[2] << endl;
                exit(1);
        }
        fwrite(OutputImage, sizeof(unsigned char), Width*Height*1, file);
        fclose(file);

        return 0;
}





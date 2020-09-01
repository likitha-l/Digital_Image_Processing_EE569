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
        int Width=480;
        int Height=640;
        int Size=256;
        // Check for proper syntax
        if (argc < 3){
                cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
                cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
                return 0;
        }



        // Allocate image data array
        unsigned char Imagedata[Width][Height][3];
        unsigned char Imagedatacpy[Width][Height][3];
	unsigned char OutputImage[Width][Height][3];


        // Read image (filename specified by first argument) into image data matrix
         if (!(file=fopen(argv[1],"rb"))) {
                cout << "Cannot open file: " << argv[1] <<endl;
                exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Width*Height*3, file);
        fclose(file);

        ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
        float h[3][3]={{0,0,0},{0,0,7/16.0},{3/16.0,5/16.0,1/16.0}};
        float hflip[3][3]={{0,0,0},{7/16.0,0,0},{1/16.0,5/16.0,3/16.0}};
        float e1,e2,e3,e4,e5,e6;

	    for (int i = 1; i < (Width-1); i++)
        	{
       	     for (int j = 1; j < (Height-1); j++)
        	{
        	    Imagedatacpy[i][j][0]=255-Imagedata[i][j][0];
        	    Imagedatacpy[i][j][1]=255-Imagedata[i][j][1];
        	    Imagedatacpy[i][j][2]=255-Imagedata[i][j][2];
	        }
	    }

        for (int i = 1; i < (Width-1); i++)
        {
            if(i%2==0){
       	     for (int j = 1; j < (Height-1); j++)
        	{

        	    e1=(float)Imagedatacpy[i][j][0]-((Imagedatacpy[i][j][0]>128.00)?255:0);
                e2=(float)Imagedatacpy[i][j][1]-((Imagedatacpy[i][j][1]>128.00)?255:0);
                e3=(float)Imagedatacpy[i][j][2]-((Imagedatacpy[i][j][2]>128.00)?255:0);

                for (int u = -1; u <= 1; u++)
                    {
                    for (int v = -1; v <= 1; v++)
                        {
                            if((i+u)<0 || (j+v)<0 ||((i+u)>(Width-1))||((j+u)>(Height-1)) ){
                                continue;
                            }
			     Imagedatacpy[i+u][j+v][0]=(unsigned char)(((float)Imagedatacpy[i+u][j+v][0]+h[u+1][v+1]*e1));
			     Imagedatacpy[i+u][j+v][1]=(unsigned char)(((float)Imagedatacpy[i+u][j+v][1]+h[u+1][v+1]*e2));
			     Imagedatacpy[i+u][j+v][2]=(unsigned char)(((float)Imagedatacpy[i+u][j+v][2]+h[u+1][v+1]*e3));
                        }
                    }
        	}
        }
        if(i%2!=0){
       	     for (int j1 =Height-1; j1 >=1; j1--)
        	{

                e4=(float)Imagedatacpy[i][j1][0]-((Imagedatacpy[i][j1][0]>128.00)?255:0);
                e5=(float)Imagedatacpy[i][j1][1]-((Imagedatacpy[i][j1][1]>128.00)?255:0);
                e6=(float)Imagedatacpy[i][j1][2]-((Imagedatacpy[i][j1][2]>128.00)?255:0);

                for (int u = -1; u <= 1; u++)
                    {
                    for (int v = -1; v <= 1; v++)
                        {
                            if((i+u)<0 || (j1+v)<0 || ((i+u)>(Width-1))||((j1+u)>(Height-1))){
                                continue;
                            }
			     Imagedatacpy[i+u][j1+v][0]=(unsigned char)(((float)Imagedatacpy[i+u][j1+v][0]+hflip[u+1][v+1]*e4));
			     Imagedatacpy[i+u][j1+v][1]=(unsigned char)(((float)Imagedatacpy[i+u][j1+v][1]+hflip[u+1][v+1]*e5));
			     Imagedatacpy[i+u][j1+v][2]=(unsigned char)(((float)Imagedatacpy[i+u][j1+v][2]+hflip[u+1][v+1]*e6));			     
                        }
                    }
        	}
        }
        }

  for (int i = 1; i <(Width-1) ; i++)
        {
       	   for (int j=1; j < (Height-1); j++)
        	{
	       		OutputImage[i][j][0]=255-(unsigned char)((Imagedatacpy[i][j][0]>128.00)?255:0);
	                OutputImage[i][j][1]=255-(unsigned char)((Imagedatacpy[i][j][1]>128.00)?255:0);
			OutputImage[i][j][2]=255-(unsigned char)((Imagedatacpy[i][j][2]>128.00)?255:0);

		}
	}




        // Write image data (filename specified by second argument) from image data matrix

        if (!(file=fopen(argv[2],"wb"))) {
                cout << "Cannot open file: " << argv[2] << endl;
                exit(1);
        }
        fwrite(OutputImage, sizeof(unsigned char), Width*Height*3, file);
        fclose(file);

        return 0;
}






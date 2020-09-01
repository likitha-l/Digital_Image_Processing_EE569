#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <random>
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
	int N=2;
	int I[2][2]={{1,2},{3,0}};
    //change the index matrix
	//int I[4][4]={{5,9,6,10},{13,1,14,2},{7,11,4,8},{15,3,12,0}};
	//int I[8][8]={{ 21,    37,    25,    41,    22,    38,    26,    42},
//    {53,     5,    57,     9,    54,     6,    58,    10},
//    {29,    45,    17,    33,    30,    46,    18,    34},
//    {61,    13,    49,     1,    62,    14,    50,     2},
//    {23,    39,    27,    43,    20,    36,    24,    40},
//    {55,     7,    59,    11,    52,     4,    56,     8},
//    {31,    47,    19,    35,    28,    44,    16,    32},
//    {63,    15,    51,     3,    60,    12,    48,     0}}; 
	float threshold[N][N];
	int count=0;
	int indexi;
	int indexj;


   	for (int i = 0; i < (N); i++)
    	{
      	for (int j = 0; j < (N); j++)
        	{
    		threshold[i][j] =((I[i][j]+0.5)/pow(N,2))*255;
		}
        }


	for (int i = 0; i < (Width); i++)
        {
       	     for (int j = 0; j < (Height); j++)
        	{
			indexi=i%N;
			indexj=j%N;
    			if(float(Imagedata[i][j][0])<=threshold[indexi][indexj])
				Imagedata[i][j][0]=(unsigned char)0;
			else
			        Imagedata[i][j][0]=(unsigned char)255;
		     }
	    }

	for (int i = 1; i < (N); i++)
    	    {
       	     for (int j = 1; j < (N); j++)
        	{
			if(threshold[i][j]>0){
                           count++;}
		}
	    }

	cout<<"Count"<<count<<endl;
        // Write image data (filename specified by second argument) from image data matrix

        if (!(file=fopen(argv[2],"wb"))) {
                cout << "Cannot open file: " << argv[2] << endl;
                exit(1);
        }
        fwrite(Imagedata, sizeof(unsigned char), Width*Height*1, file);
        fclose(file);

        return 0;
}





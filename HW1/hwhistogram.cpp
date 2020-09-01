#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<cmath>
#include<fstream>
#include<string>
using namespace std;

ofstream outputFile;

ofstream fs;
std::string filename = "histogramresults.csv";


int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Width=400;
	int Height=560;
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
	BytesPerPixel=3;
	// Allocate image data array
	unsigned char Imagedata[Width][Height][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

float freq[256][3]; //histogram value for each channel
float prob[256][3];
float cumprob[256][3];
unsigned char temp[Width][Height][3];
for(int i=0;i<=255;i++){
		for(int j=0;j<3;j++){
                freq[i][j]=0;
                prob[i][j]=0.0;
                cumprob[i][j]=0.0;

		}
}
    for(int i=0;i<Width;i++){
		for(int j=0;j<Height;j++){
                freq[int(Imagedata[i][j][0])][0]=freq[int(Imagedata[i][j][0])][0]+1;
                freq[int(Imagedata[i][j][1])][1]=freq[int(Imagedata[i][j][1])][1]+1;
                freq[int(Imagedata[i][j][2])][2]=freq[int(Imagedata[i][j][2])][2]+1;
		}
    }

        for(int i=0;i<=255;i++){
            prob[i][0]=freq[i][0]*(1.0/(Width*Height));
            prob[i][1]=freq[i][1]*(1.0/(Width*Height));
            prob[i][2]=freq[i][2]*(1.0/(Width*Height));
            if(i==0){
                cumprob[i][0]=prob[i][0];
                cumprob[i][1]=prob[i][1];
                cumprob[i][2]=prob[i][2];
            }
            else{
            cumprob[i][0]=(cumprob[i-1][0]+prob[i][0]);
            cumprob[i][1]=(cumprob[i-1][1]+prob[i][1]);
            cumprob[i][2]=(cumprob[i-1][2]+prob[i][2]);
            }

        }

        for(int i=0;i<Width;i++){
            for(int j=0;j<Height;j++){
                temp[i][j][0]=(unsigned char)(floor(cumprob[int(Imagedata[i][j][0])][0]*255));
                temp[i][j][1]=(unsigned char)(floor(cumprob[int(Imagedata[i][j][1])][1]*255));
                temp[i][j][2]=(unsigned char)(floor(cumprob[int(Imagedata[i][j][2])][2]*255));
            }
        }

outputFile.open("histogramresults.csv");

 for(int c=0;c<256;c++){
outputFile << c<< "," << freq[c][0] <<","<<freq[c][1]<<","<<freq[c][2]<<std::endl;
 }
outputFile.close();

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(temp, sizeof(unsigned char), Width*Height*3, file);
	fclose(file);



	return 0;
}




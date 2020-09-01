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
        int Width=532;
        int Height=600;
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
        unsigned char Imagedata[Width][Height][BytesPerPixel];

        // Read image (filename specified by first argument) into image data matrix
         if (!(file=fopen(argv[1],"rb"))) {
                cout << "Cannot open file: " << argv[1] <<endl;
                exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
        fclose(file);

        ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
        //float mask1[3][3]={{0.0,1/2.0,0.0},{0.0,0.0,0.0},{0.0,1/2.0,0.0}};
        //float mask2[3][3]={{0.0,0.0,0.0},{1/2.0,0.0,1/2.0},{0.0,0.0,0.0}};
        //float mask3[3][3]={{0.0,1/4.0,0.0},{1/4.0,0.0,1/4.0},{0.0,1/4.0,0.0}};
        //float mask4[3][3]={{1/4.0,0.0,1/4.0},{0.0,0.0,0.0},{1/4.0,0.0,1/4.0}};
        float mask1[5][5]={{0.0,0.0,-1/8.0,0.0,0.0},{0.0,0.0,1/4.0,0.0,0.0},{-1/8.0,1/4.0,1/2.0,1/4.0,-1/8.0},{0.0,0.0,1/4.0,0.0,0.0},{0.0,0.0,-1/8.0,0.0,0.0}};
        float mask2[5][5]={{0.0,0.0,1/16.0,0.0,0.0},{0.0,-1/8.0,0.0,-1/8.0,0.0},{-1/8.0,1/2.0,5/8.0,1/2.0,-1/8.0},{0.0,-1/8.0,0.0,-1/8.0,0.0},{0.0,0.0,1/16.0,0.0,0.0}};
        float mask3[5][5]={{0.0,0.0,-1/8.0,0.0,0.0},{0.0,-1/8.0,1/2.0,-1/8.0,0.0},{1/16.0,0.0,5/8.0,0.0,1/16.0},{0.0,-1/8.0,1/2.0,-1/8.0,0.0},{0.0,0.0,-1/8.0,0.0,0.0}};
        float mask4[5][5]={{0.0,0.0,-3/16.0,0.0,0.0},{0.0,1/4.0,0.0,1/4.0,0.0},{-3/16.0,0.0,6/8.0,0.0,-3/16.0},{0.0,1/4.0,0.0,1/4.0,0.0},{0.0,0.0,-3/16.0,0.0,0.0}};

        float sum1,sum2,sum3,sum4;
        float a;
        unsigned char temp[Width][Height][3];


   for (int i = 2; i < (Width-2); i++)
    {
        for (int j = 2; j < (Height-2); j++)
        {
            sum1=0.0;
            sum2=0.0;
            sum3=0.0;
            sum4=0.0;

            
            for (int u = -2; u <= 2; u++)
            {
                for (int v = -2; v <=2; v++)
                {
                    a=(float)Imagedata[i+u][j+v][0];
                    sum1= sum1 + a* (mask1[u+2][v+2]);     
                    sum2= sum2 + a* (mask2[u+2][v+2]);
                    sum3= sum3 + a* (mask3[u+2][v+2]);   
                    sum4= sum4 + a* (mask4[u+2][v+2]);   

                }
            }

            sum1=ceil(sum1);
	    sum2=ceil(sum2);
	    sum3=ceil(sum3);
            sum4=ceil(sum4);

    if(sum1<0)
        sum1=0;
    if(sum1>255)
        sum1=255;
    if(sum2<0)
        sum2=0;
    if(sum2>255)
        sum2=255;
    if(sum3<0)
        sum3=0;
    if(sum3>255)
        sum3=255;
    if(sum4<0)
        sum4=0;
    if(sum4>255)
        sum4=255;

            if((i%2==0)&&(j%2==0))
            {
                temp[i][j][0]=(unsigned char)sum2;
                temp[i][j][1]=Imagedata[i][j][0];
                temp[i][j][2]=(unsigned char)sum3;
            }

            if((i%2==0)&&(j%2!=0))
            {
                temp[i][j][0]=Imagedata[i][j][0];
                temp[i][j][1]=(unsigned char)sum1;
                temp[i][j][2]=(unsigned char)sum4;
            }

            if((i%2!=0)&&(j%2!=0))
            {
                temp[i][j][0]=(unsigned char)sum3;
                temp[i][j][1]=Imagedata[i][j][0];
                temp[i][j][2]=(unsigned char)sum2;
            }

            if((i%2!=0)&&(j%2==0))
            {
                temp[i][j][0]=(unsigned char)sum4;
                temp[i][j][1]=(unsigned char)sum1;
                temp[i][j][2]=Imagedata[i][j][0];
            }


            

        }
    }


	cout<<"Input Image"<<endl;
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			cout<<(float)Imagedata[i][j][0]<<" ";
		}
		cout<<endl;
	}

	cout<<"Output Image"<<endl;
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			cout<<(float)temp[i][j][1]<<" ";
		}
		cout<<endl;
	}
        // Write image data (filename specified by second argument) from image data matrix

        if (!(file=fopen(argv[2],"wb"))) {
                cout << "Cannot open file: " << argv[2] << endl;
                exit(1);
        }
        fwrite(temp, sizeof(unsigned char), Width*Height*3, file);
        fclose(file);

        return 0;
}


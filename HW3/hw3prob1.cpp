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
        int Width=512;
        int Height=512;
        // Check for proper syntax
        if (argc < 3){
                cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
                cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
                return 0;
        }



        // Allocate image data array
        unsigned char Imagedata[Width][Height][3];
        unsigned char OutputImage[Width][Height][3];
	unsigned char ReverseImage[Width][Height][3];
	float u1,v1,xcart,ycart,ucart,vcart,yreverse,xreverse;
	int u,v,a,b;


        // Read image (filename specified by first argument) into image data matrix
         if (!(file=fopen(argv[1],"rb"))) {
                cout << "Cannot open file: " << argv[1] <<endl;
                exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Width*Height*3, file);
        fclose(file);

        ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	for(int x=0;x<Width;x++){
            for(int y=0;y<Height;y++){
		    //cout<<"w"<<(Width/2);
		    //cout<<(x-Width/2)<<endl;
                    //cout<<"xcart"<<((x-Width/2)/(Width/2))<<endl;
                    xcart=(float)(x-(Width/2-1))/(float)((Width/2-1));
		    ycart=(float)((Width-y-1)-(Width/2-1))/(float)(Width/2-1);
		    //cout<<"x "<<x<<"y "<<y<<endl;
		    //cout<<xcart<<" "<<ycart<<endl;
                    u1=xcart*sqrt(1-0.5*pow(ycart,2));
		    v1=ycart*sqrt(1-0.5*pow(xcart,2));
		    //cout<<u1<<" "<<v1<<endl;
		    u=round(u1*(Width/2-1)+(Width/2-1));
		    v=round(Width-(v1*(Width/2-1)+(Width/2-1)));
		    //cout<<u<<" "<<v<<endl;
		    OutputImage[u][v][0]=Imagedata[x][y][0];
		    OutputImage[u][v][1]=Imagedata[x][y][1];
		    OutputImage[u][v][2]=Imagedata[x][y][2];
		    xreverse=0.5*(sqrt(2+pow(u1,2)-pow(v1,2)+2*sqrt(2)*u1))-0.5*(sqrt(2+pow(u1,2)-pow(v1,2)-2*sqrt(2)*u1));
                    yreverse=0.5*(sqrt(2-pow(u1,2)+pow(v1,2)+2*sqrt(2)*v1))-0.5*(sqrt(2-pow(u1,2)+pow(v1,2)-2*sqrt(2)*v1));
                    a=round(xreverse*((Width/2)-1)+(Width/2)-1);
                    b=round(Width-1-(yreverse*(Width/2-1)+(Width/2-1)));
		    ReverseImage[a][b][0]=OutputImage[u][v][0];
                    ReverseImage[a][b][1]=OutputImage[u][v][1];
                    ReverseImage[a][b][2]=OutputImage[u][v][2];
            }
        }

	//int x,y;
	 // for(int u=0;u<Width;u++){
          //  for(int v=0;v<Height;v++){
         //           ucart=(float)(u-Width/2)/(float)(Width/2);
         //           vcart=(float)((Width-v)-Width/2)/(float)(Width/2);
//		    //cout<<u<<"U"<<" "<<v<<"V";
//		    //cout<<ucart<<" "<<vcart<<endl;
//		    if((pow(ucart,2)+pow(vcart,2))<=1){
//		    //cout<<u<<"U"<<" "<<v<<"V";
 //                   //cout<<ucart<<" "<<vcart<<endl;
//                    xcart=0.5*(sqrt(2+pow(ucart,2)-pow(vcart,2)+2*sqrt(2)*ucart))-0.5*(sqrt(2+pow(ucart,2)-pow(vcart,2)-2*sqrt(2)*vcart));
//                    ycart=0.5*(sqrt(2-pow(ucart,2)+pow(vcart,2)+2*sqrt(2)*vcart))-0.5*(sqrt(2-pow(ucart,2)+pow(vcart,2)-2*sqrt(2)*vcart));
		    //cout<<xcart<<" "<<ycart<<endl;
//                    x=ceil(xcart*(Width/2)+Width/2);
//                    y=ceil(Width-(ycart*(Width/2)+Width/2));
//                    ReverseImage[x][y][0]=OutputImage[u][v][0];
//                    ReverseImage[x][y][1]=OutputImage[u][v][1];
//                    ReverseImage[x][y][2]=OutputImage[u][v][2];
//		    }
//            }
//        }

        // Write image data (filename specified by second argument) from image data matrix

        if (!(file=fopen(argv[2],"wb"))) {
                cout << "Cannot open file: " << argv[2] << endl;
                exit(1);
        }
        fwrite(ReverseImage, sizeof(unsigned char), Width*Height*3, file);
        fclose(file);

        return 0;

	if (!(file=fopen(argv[3],"wb"))) {
                cout << "Cannot open file: " << argv[3] << endl;
                exit(1);
        }
        fwrite(ReverseImage, sizeof(unsigned char), Width*Height*3, file);
        fclose(file);

        return 0;
}



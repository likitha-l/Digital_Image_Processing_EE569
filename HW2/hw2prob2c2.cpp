#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int getNearestVertex(int mbvq,float R,float G,float B){
    //cout<<"R"<<R<<"G"<<G<<"B"<<B<<endl;
    int vertex;
    //No.1 for CMYW
    if (mbvq == 1){
        vertex = 8;
        if (B < 0.5){
            if (B <= R){
                if (B <= G){
                    vertex = 7;
    }
    }
    }
        if (G < 0.5){
            if (G <= B){
                if (G <= R){
                    vertex = 5;
        }
        }
        }
        if (R < 0.5){
            if (R <= B){
                if (R <= G){
                    vertex = 6;
        }
        }
        }
    }


//No.2 for MYGC
    if (mbvq == 2){
        vertex = 5;
        if (G >= B){
            if (R >= B){
                if (R >= 0.5)
                    vertex = 7;
                else
                    vertex = 4;
    }
    }

        if (G >= R){
            if (B >= R){
                if (B >= 0.5)
                    vertex = 6;
                else
                    vertex = 4;
        }
        }

    }


//No.3 for RGMY
    if (mbvq == 3){
        if (B > 0.5){
            if (R > 0.5){
                if (B >= G)
                    vertex = 5;
                else
                    vertex = 7;
            }
            else{
                if (G > B + R)
                    vertex = 4;
                else
                    vertex = 5;
                }
        }
        else{
            if (R >= 0.5){
                if (G >= 0.5)
                    vertex = 7;
                else
                    vertex = 3;
                }
            else{
                if (R >= G)
                    vertex = 3;
                else
                    vertex = 4;
                }
        }
    }


//No.4 for KRGB
    if (mbvq == 4){
        vertex = 1;
        if (B > 0.5){
            if (B >= R){
                if (B >= G){
                    vertex = 2;
                }
            }
        }
        if (G > 0.5){
            if (G >= B){
                if (G >= R){
                    vertex = 4;
                }
            }
        }
        if (R > 0.5){
            if (R >= B){
                if (R >= G){
                    vertex = 3;
                }
            }
        }
    }


//No.5 for RGBM
    if (mbvq == 5){
        vertex = 4;
        if (R > G){
            if (R >= B){
                if (B < 0.5)
                    vertex = 3;
                else
                    vertex = 5;
            }
        }
        if (B > G){
            if (B >= R){
                if (R < 0.5)
                    vertex = 2;
                else
                    vertex = 5;
            }
        }
}


//No.6 for CMGB
    if (mbvq == 6){
        if (B > 0.5){
            if ( R > 0.5){
                if (G >= R)
                    vertex = 6;
                else
                    vertex = 5;
                }
            else{
                if (G > 0.5)
                    vertex = 6;
                else
                    vertex = 2;
                }
        }
        else{
            if ( R > 0.5){
                if (R - G + B >= 0.5)
                    vertex = 5;
                else
                    vertex = 4;
                }
            else{
                if (G >= B)
                    vertex = 4;
                else
                    vertex = 2;
                }
            }
        }

return vertex;
}

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
        float R,G,B;
        int b1,b2,b3;
        int mbvq;
        int vertex;


	    for (int i = 1; i < (Width-1); i++)
        	{
       	     for (int j = 1; j < (Height-1); j++)
        	{
        	    Imagedatacpy[i][j][0]=Imagedata[i][j][0];
        	    Imagedatacpy[i][j][1]=Imagedata[i][j][1];
        	    Imagedatacpy[i][j][2]=Imagedata[i][j][2];
	        }
	    }

        for (int i = 1; i < (Width-1); i++)
        {
            if(i%2==0){
       	     for (int j = 1; j < (Height-1); j++)
        	{

                R=(float)Imagedatacpy[i][j][0];
                G=(float)Imagedatacpy[i][j][1];
                B=(float)Imagedatacpy[i][j][2];


                if((R+G)>255){
                    if((G+B)>255){
                        if((R+G+B)>510)
                            mbvq=1;
                        else
                            mbvq=2;
                    }
                    else
                        mbvq=3;
                }
                else{
                    if(!((G+B)>255)){
                        if(!((R+G+B)>255))
                            mbvq=4;
                        else
                            mbvq=5;
                    }
                    else
                        mbvq=6;
                }

                vertex=getNearestVertex(mbvq,R/255.0,G/255.0,B/255.0);

                if(vertex=1){
                    b1=0;
                    b2=0;
                    b3=0;}
                if(vertex=2){
                    b1=0;
                    b2=0;
                    b3=255;}
                if(vertex=3){
                    b1=255;
                    b2=0;
                    b3=0;}
                if(vertex=4){
                    b1=0;
                    b2=255;
                    b3=0;}
                if(vertex=5){
                    b1=255;
                    b2=0;
                    b3=255;}
                if(vertex=6){
                    b1=0;
                    b2=255;
                    b3=255;}
                if(vertex=7){
                    b1=255;
                    b2=255;
                    b3=0;}
                if(vertex=8){
                    b1=255;
                    b2=255;
                    b3=255;}



        	    e1=(float)Imagedatacpy[i][j][0]-(b1);
                e2=(float)Imagedatacpy[i][j][1]-(b2);
                e3=(float)Imagedatacpy[i][j][2]-(b3);

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

                R=(float)Imagedatacpy[i][j1][0];
                G=(float)Imagedatacpy[i][j1][1];
                B=(float)Imagedatacpy[i][j1][2];


                if((R+G)>255){
                    if((G+B)>255){
                        if((R+G+B)>510)
                            mbvq=1;
                        else
                            mbvq=2;
                    }
                    else
                        mbvq=3;
                }
                else{
                    if(!((G+B)>255)){
                        if(!((R+G+B)>255))
                            mbvq=4;
                        else
                            mbvq=5;
                    }
                    else
                        mbvq=6;
                }

                vertex=getNearestVertex(mbvq,R/255.0,G/255.0,B/255.0);

                if(vertex=1){
                    b1=0;
                    b2=0;
                    b3=0;}
                if(vertex=2){
                    b1=0;
                    b2=0;
                    b3=255;}
                if(vertex=3){
                    b1=255;
                    b2=0;
                    b3=0;}
                if(vertex=4){
                    b1=0;
                    b2=255;
                    b3=0;}
                if(vertex=5){
                    b1=255;
                    b2=0;
                    b3=255;}
                if(vertex=6){
                    b1=0;
                    b2=255;
                    b3=255;}
                if(vertex=7){
                    b1=255;
                    b2=255;
                    b3=0;}
                if(vertex=8){
                    b1=255;
                    b2=255;
                    b3=255;}


                e4=(float)Imagedatacpy[i][j1][0]-(b1);
                e5=(float)Imagedatacpy[i][j1][1]-(b2);
                e6=(float)Imagedatacpy[i][j1][2]-(b3);

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


		
                R=(float)Imagedatacpy[i][j][0];
                G=(float)Imagedatacpy[i][j][1];
                B=(float)Imagedatacpy[i][j][2];


                if((R+G)>255){
                    if((G+B)>255){
                        if((R+G+B)>510)
                            mbvq=1;
                        else
                            mbvq=2;
                    }
                    else
                        mbvq=3;
                }
                else{
                    if(!((G+B)>255)){
                        if(!((R+G+B)>255))
                            mbvq=4;
                        else
                            mbvq=5;
                    }
                    else
                        mbvq=6;
                }

                vertex=getNearestVertex(mbvq,R/255.0,G/255.0,B/255.0);

                if(vertex=1){
                    b1=0;
                    b2=0;
                    b3=0;}
                if(vertex=2){
                    b1=0;
                    b2=0;
                    b3=255;}
                if(vertex=3){
                    b1=255;
                    b2=0;
                    b3=0;}
                if(vertex=4){
                    b1=0;
                    b2=255;
                    b3=0;}
                if(vertex=5){
                    b1=255;
                    b2=0;
                    b3=255;}
                if(vertex=6){
                    b1=0;
                    b2=255;
                    b3=255;}
                if(vertex=7){
                    b1=255;
                    b2=255;
                    b3=0;}
                if(vertex=8){
                    b1=255;
                    b2=255;
                    b3=255;}
            OutputImage[i][j][0]=(unsigned char)(255-Imagedatacpy[i][j][0]);
            OutputImage[i][j][1]=(unsigned char)(255-Imagedatacpy[i][j][1]);
	    OutputImage[i][j][2]=(unsigned char)(255-Imagedatacpy[i][j][2]);

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







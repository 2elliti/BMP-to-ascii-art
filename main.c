#include <stdio.h>
#include <stdlib.h>

#define BRIGHTFACTOR 25
#define MAXVALUE 255
#define BLACK 0
#define WHITE 255
#define THRESHOLD 128


char *get_ascii(char ch){
	int temp = ch % 10; 
    static char retch;
    
    switch(temp) {
        case 0: retch = '?'; break;  // Lightest
        case 1: retch = '@'; break;
        case 2: retch = '%'; break;
        case 3: retch = '#'; break;
        case 4: retch = '+'; break;
        case 5: retch = ','; break;
        case 6: retch = '='; break;
        case 7: retch = '-'; break;
        case 8: retch = ':'; break;
        case 9: retch = '.'; break;  // Darkest
        default: retch = '.';
    }

    return &retch;
}


void print_usage(char *file){
	fprintf(stderr,"Error: %s < File_Path >\n",file);
	exit(1);
}



int main(int argc,char *argv[]){

	if(argc != 2){
		print_usage(argv[0]);
	}


	FILE *file = fopen(argv[1],"rb");

	if(file == NULL){
		fprintf(stderr,"Error: Can't open file stream\n");
		exit(1);
	}

	unsigned char *header = (unsigned char *)malloc(sizeof(char)*54);
	unsigned char *colorTable = (unsigned char *)malloc(sizeof(char)*1024);

	if(fread(header,1,54,file) != 54){
		fprintf(stderr,"Error: Can't read header file\n");
		exit(1);
	}
	
	unsigned int width = *(unsigned int *)(header+18);
	unsigned int height = *(unsigned int *)(header+22);
	unsigned short int bitdepth = *(unsigned short int *)(header+28);


	printf("width = %d ; height = %d ; bitdepth = %d \n",width,height,bitdepth);



	if(bitdepth <= 8){
		if(fread(colorTable,1,1024,file) != 1024){
			fprintf(stderr,"Error: Can't read Color Table\n");
			exit(1);
		}
	}
	else{
		printf("Color Table not found\n");
	}
	
	unsigned char *buffer = (unsigned char *)malloc(width * height);

	if(fread(buffer,1,width*height,file) != width*height){
		fprintf(stderr, "Error: Cant read pixel data.\n");
		exit(1);
	}

	
	// /*------------------- FOR NEGATIVE IMAGE----------------------*/

	// char *negative_data = malloc(height*width);

	// for(int i=0;i<height;i++){
	// 	for(int j=0;j<width;j++){
	// 		negative_data[width*i + j] = 255 - buffer[width*i +j];
	// 	}
	// }


	// /*-------------------- FOR BRIGHTNESS ----------------------------*/
	
	// char *bright_data = malloc(height * width);
	// for(int i=0;i<height;i++){
	// 	for(int j=0;j<width;j++){
	// 		int temp;
	// 		temp = buffer[width*i + j] + BRIGHTFACTOR;
	// 		bright_data[width*i + j] = (temp > MAXVALUE)? MAXVALUE : temp;

	// 	}
	// }
	

	// /*-------------------- BLACK AND WHITE ----------------------------*/

	// char *bandw_data = malloc(height*width);

	// for(int i =0;i<height*width;i++){
	// 	bandw_data[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;
	// }

	



//	FILE *new_file = fopen("blackAndWhiteImage.bmp","wb");


//	if(fwrite(header,1,54,new_file) != 54){
//		fprintf(stderr,"Error: error while writing header.\n");
//		exit(1);
//	}
	// if(fwrite(colorTable,1,1024,new_file) != 1024){
	// 	fprintf(stderr,"Error: error while writing Color Table.\n");
	// 	exit(1);
	// }
	// if(fwrite(bandw_data,1,width*height,new_file) != width*height){
	// 	fprintf(stderr,"Error: error while writing pixel data.\n");
	// 	exit(1);
	// }




	for(int i=height-1;i>=0;i--){
			for(int j=width-1;j>=0;j--){
				char df =  *(get_ascii(buffer[width*i + j]));
				printf("%c",df);

		}
		putchar('\n');
	}

	putchar('\n');


	// free(bandw_data);
	// free(bright_data);
	// free(negative_data);
	free(header);
	free(colorTable);
	free(buffer);
	// fclose(new_file);

	fclose(file);

}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <ao/ao.h>
#include <mpg123.h>

#define BITS 8

int bntr;
int cekpause = 0;
char namalagu[256];
int stop = 0;
char temp[256];
char listlagu[256][256];
int nomor;
int i = 0;

static const char *dirpath = "/home/thalutn5/";
//static const char *dirpath = "/home/thalutn5/FPSISOP/";

void *play(){

    while(1){
        
        while(wait(bntr) > 0);
        strcpy(temp, dirpath);
        strcat(temp, namalagu);

        if(strlen(namalagu) > 0){

            mpg123_handle *mh;
            unsigned char *buffer;
            size_t buffer_size;
            size_t done;
            int err;

            int driver;
            ao_device *dev;

            ao_sample_format format;
            int channels, encoding;            
            long rate;

            // if(argc < 2)
                //   exit(0);

            /* initializations */
            ao_initialize();
            driver = ao_default_driver_id();
            mpg123_init();
            mh = mpg123_new(NULL, &err);
            buffer_size = mpg123_outblock(mh);
            buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

            /* open the file and get the decoding format */
            mpg123_open(mh, temp);
            mpg123_getformat(mh, &rate, &channels, &encoding);

            /* set the output format and open the output device */
            format.bits = mpg123_encsize(encoding) * BITS;
            format.rate = rate;
            format.channels = channels;
            format.byte_format = AO_FMT_NATIVE;
            format.matrix = 0;
            dev = ao_open_live(driver, &format, NULL);

            /* decode and play */
            stop = 0;
            while(1){                
                if(cekpause == 0){
                    if(mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK){
                        ao_play(dev, buffer, done);
                        //printf("katakata\n\n\n\n\n");
                    }
                    else{ 
                        break;
                    }
                }
                if(stop == 1){
                    break;
                }       
            }
            /* clean up */
            free(buffer);
            ao_close(dev);
            mpg123_close(mh);
            mpg123_delete(mh);
            mpg123_exit();
            ao_shutdown();
        }
    }
}

int list(){
    DIR *dir;
	struct dirent *ent;

	dir = opendir(dirpath);
	if (dir == NULL){
		return;
    }

	while ((ent = readdir(dir)) != NULL) {
        if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 && strstr(ent->d_name,".mp3")){
		    printf("%s\n", ent->d_name);
        }
    }
    closedir(dir);
}
int list2(){
    DIR *dir;
	struct dirent *ent;

	dir = opendir(dirpath);
	if (dir == NULL){
		return;
    }

	while ((ent = readdir(dir)) != NULL) {
        if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 && strstr(ent->d_name, ".mp3")){
		    strcpy(listlagu[i], ent->d_name);
            //printf("%s\n",listlagu[i]);
            i++;
            //printf("ini i %d\n", i);

        }
    }
    closedir(dir);
}
void next(){
    nomor = nomor + 1;
    //printf("%d\n", nomor);
    //printf("adasd %d\n", i);
    if(nomor > i - 1 ){
        nomor = 0;
    }
    strcpy(namalagu, listlagu[nomor]);
}
void prev(){
    nomor = nomor - 1;
    //printf("%d\n", nomor);
    if(nomor < 0){
        nomor = i - 1 ;
    }
    strcpy(namalagu, listlagu[nomor]);
}
int indeks(char gulagu[256]){
    DIR *dir;
	struct dirent *ent;
    int indexes = 0;

	dir = opendir(dirpath);
	if (dir == NULL){
        //return;
		printf("error\n");
    }

	while ((ent = readdir(dir)) != NULL) {
        if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 && strstr(ent->d_name, ".mp3")) {  
            if(strcmp(gulagu, ent->d_name) == 0){
                return indexes;
            }
            indexes++;
        }	    
    }
    closedir(dir);
    return -1;
}

int main(){
    char inputan[256];
    printf("Music Player\n");
    printf("1. play (namalagu)\n");
    printf("2. next\n");
    printf("3. pause\n");
    printf("4. resume\n");
    printf("5. prev\n");
    printf("6. list\n");
    pthread_t thread1, thread2, thread3, thread4, thread5;
    //pthread_create(&thread1, NULL, play, NULL);
    //pthread_join(thread1, NULL);
    //pthread_create(&thread2, NULL, next, NULL);
    ////pthread_join(thread2, NULL);
    //pthread_create(&thread3, NULL, pause, NULL);
    //pthread_join(thread3, NULL);
    //pthread_create(&thread4, NULL, prev, NULL);
    //pthread_join(thread4, NULL);
    //pthread_create(&thread5, NULL, list, NULL);
    //pthread_join(thread5, NULL);
    pthread_create(&thread1, NULL, play, &namalagu);
    list2();
    while(1){
        
        printf("Fitur yang diinginkan  : ");
        scanf("%s", inputan);
        if(strcmp(inputan,"resume") == 0 && cekpause == 1)
        { 
            cekpause = 0;
            //printf("katakata222\n\n\n\n\n");
        }
        else if(strcmp(inputan, "play") == 0){
            //if(cekpause==1)
            //{cekpause=0;}
            stop = 1;
            scanf("%s", namalagu); 
            nomor = indeks(namalagu);
            //pthread_create(&thread1, NULL, play, &namalagu);
        }
        else if(strcmp(inputan, "next")==0){
            stop = 1;
            next();
        }
        else if(strcmp(inputan, "pause")==0){
            cekpause = 1;
        }
        else if(strcmp(inputan, "prev")==0){
            stop = 1;
            prev();
        
        }
        else if(strcmp(inputan, "list")==0){
            int hasil = list();
        }
        
    }
}

# FP_SISOP19_F11
Buatlah sebuah music player dengan bahasa C yang memiliki fitur play nama_lagu, pause, next, prev, list lagu. Selain music player juga terdapat FUSE untuk mengumpulkan semua jenis file yang berekstensi .mp3 kedalam FUSE yang tersebar pada direktori /home/user. Ketika FUSE dijalankan, direktori hasil FUSE hanya berisi file .mp3 tanpa ada direktori lain di dalamnya. Asal file tersebut bisa tersebar dari berbagai folder dan subfolder. program mp3 mengarah ke FUSE untuk memutar musik.
Note: playlist bisa banyak, link mp3player

Jawab :
- Untuk mengerjakan soal ini terdapat 2 file, yaitu fpsisop.c yang berisikan file mp3 playernya dan fuse.c yang bersikan fusenya.
- Didalam fpsisop.c berisi berbagai macam fitur mp3 player seperti play, pause, resume, next dan prev.
- Untuk menjalankan sebuah lagu menggunakan script seperti dibawah ini

      else if(strcmp(inputan, "play") == 0){
            //if(cekpause==1)
            //{cekpause=0;}
            stop = 1; //berguna untuk memberhentikan lagu sebelumnya
            scanf("%s", namalagu); //memasukkan nama lagunya
            nomor = indeks(namalagu); //mencari indks dari sebuah lagu agr bisa menggunakan fitur next dan prev
            //pthread_create(&thread1, NULL, play, &namalagu);
        }
     
- Untuk menjalankan fitur pause maka kita menggunakan script seperti dibawah ini

      else if(strcmp(inputan, "pause")==0){
            cekpause = 1;
        }
      
    dimana variabel cekpause merupakan variabel global yang akan menghentikan sebuah looping pada fungsi play
    
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

- Sedangkan untuk fitur resume kita mengganti variabel cekpause menjadi angka 1

       if(strcmp(inputan,"resume") == 0 && cekpause == 1)
            { 
                cekpause = 0;
                //printf("katakata222\n\n\n\n\n");
            }
           
 - Untuk fitur next kami menggunakan script seperti dibawah ini

        else if(strcmp(inputan, "next")==0){
                stop = 1; //berguna untuk memberhentikan lagu sebelumnya
                next(); //memanggil fungsi next
            }
       
     dimana isi dari fungsi next adalah 
     
         void next(){
        nomor = nomor + 1; //menaikkan indeks dari sebuah lagu sehingga akan memulai lagu berikutnya
        //printf("%d\n", nomor);
        //printf("adasd %d\n", i);
        if(nomor > i - 1 ){ jika indeks nomornya melebihi jumlah lagu yang ada makanya akan memulai dari lagu pertama lagi
            nomor = 0;
        }
        strcpy(namalagu, listlagu[nomor]); //mempasing lagunya
    }
   
  - Untuk fitur prev kami menggunakan script seperti dibawah ini
  
        else if(strcmp(inputan, "prev")==0){
                stop = 1; //berguna untuk memberhentikan lagu sebelumnya
                prev(); //memanggil fungsi prev

            }
           
         dimana isi dari fungsi prev adalah
         
          void prev(){
          nomor = nomor - 1;  //mengurangu indeks dari sebuah lagu sehingga akan memulai lagu berikutnya
          //printf("%d\n", nomor);
          if(nomor < 0){
              nomor = i - 1 ;//jika indeks nomornya melebihi jumlah lagu yang ada makanya akan memulai dari lagu pertama lagi
          }
          strcpy(namalagu, listlagu[nomor]);  //mempasing lagunya
      }
    

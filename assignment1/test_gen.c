#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

int main(int argc, char *argv){

  create_power_tests();

}

char* create_dir(unsigned int i, char* dir_path);

write_text(FILE* file, char body, unsigned long size){

  int k = 0;
  
  for(k; k<size; k++)
    {
      putc(body, file);
    }
}

write_pattern(FILE* file, char body, char end, unsigned long size){

  int k = 0;
  
  for(k; k<size-1; k++)
    {
      putc(body, file);
    }

  putc(end, file);
}


create_power_tests(){
  int total_count = 0;
  int pat_len;
  int k, l;
  unsigned long desired_length;
  int pat_length[20];

  // 10^2
  pat_length[0]= 2;
  pat_length[1]= 4;
  pat_length[2]= 5;
  pat_length[3]= 10;
  
  // 10^4
  pat_length[4]= 5;
  pat_length[5]= 10;
  pat_length[6]= 20;
  pat_length[7]= 50;

  // 10^6
  pat_length[8]= 10;
  pat_length[9]= 20;
  pat_length[12]= 50;
  pat_length[11]= 100;

  // 10^8
  pat_length[12]= 100;
  pat_length[13]= 200;
  pat_length[14]= 500;
  pat_length[15]= 1000;

  // 10^10
  pat_length[16]= 1000;
  pat_length[17]= 2000;
  pat_length[18]= 5000;
  pat_length[19]= 10000;

  //calculate how many characters per text/pattern
  for(k = 2; k <= 10; k += 2)
    {
      desired_length = pow(10,k);
      // printf("Desired Len: %lu\nPattern Len: %d\nText Len: %d\n", desired_length, l, m);
      for(l = 0; l < 4; l++)
	{
	  pat_len = pat_length[total_count];
	  create_test(total_count, pat_len, desired_length/pat_len);
	  total_count++;
	}
    }
}

create_test(int test_num, unsigned long pat_len, unsigned long text_len){
  char* dir_name;
  char text_file_path[200];
  char pat_file_path[200];
  FILE* text_file;
  FILE* pattern_file;
    
  dir_name = (char*) malloc (100);
  dir_name = create_dir(test_num, dir_name);

  sprintf (text_file_path, "%s/text.txt", dir_name);
  sprintf (pat_file_path, "%s/pattern.txt", dir_name);

  text_file = fopen(text_file_path, "w+");
  pattern_file = fopen(pat_file_path, "w+");

  write_text(text_file, 'A', text_len);
  write_pattern(pattern_file, 'A', 'B', pat_len);

  fclose(text_file);
  fclose(pattern_file);
}

char* create_dir(unsigned int i, char * dir_path){

#ifdef DOS
  sprintf (dir_path, "inputs\\test%u\\", i);
#else
  sprintf (dir_path, "inputs/test%u/", i);
#endif 

  mode_t process_mask = umask(0);
  int result_code = mkdir(dir_path, S_IRWXU);
  umask(process_mask);

  return dir_path;

}

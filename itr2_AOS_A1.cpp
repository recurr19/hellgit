#include <iostream>

#include <unistd.h>

#include <fcntl.h>

#include <errno.h>

#include <math.h>

using namespace std;
extern int errno;
void write_helper();
int string_int_helper();
int main(int argc, char * argv[])
{
    cout << "the number of arguments are " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }
    // file to read from
    int fd_read = open(argv[2], O_RDWR);
    //error handling remaining
    // file to write into
    int fd_write = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    off_t buff_size = lseek(fd_read, 0, SEEK_END);
    lseek(fd_read, 0, SEEK_SET); //reseting the file_offset to the begining
    cout << "the size of the file is: " << buff_size << endl;

    // FLAG 0
    cout<<* (argv[4] + 0)<<endl;
    if ( * (argv[4] + 0) == '0') {
        cout << "got flag 0" << endl;
        //get the block size;
        int i = 0;
        while ( * (argv[5] + i) != '\0') {
            i++;
        }
        int num_digits_block = i;
        int block_size = 0;
        for (int k = 0; k < num_digits_block; k++) {
            block_size = block_size + ( * (argv[5] + k) - '0') * pow(10, num_digits_block - k - 1);
        }
        cout << "the block size :" << block_size << endl;
        // reversing block by block

        //int itr_block = block_size - 1;
        //------------------------------------------
        lseek(fd_read, 0, SEEK_SET);
        int size_file = buff_size;
        if (size_file >= block_size) {
            int num_blocks = buff_size / block_size;
            int rem_num_ele = buff_size % block_size;
            int prev = 0;
            for (int i = 0; i < num_blocks; i++) {
                char * read_buff = (char * ) malloc(block_size);
                read(fd_read, read_buff, block_size);
                char * to_write = (char * ) malloc(block_size);
                for (int k = 0; k < block_size; k++) {
                    to_write[k] = '\0';
                }
                for (int t = 0; t < block_size; t++) {
                    to_write[t] = read_buff[block_size - 1 - t];
                }
                write(fd_write, to_write, block_size);

                prev = prev + block_size;
                lseek(fd_read, prev, SEEK_SET);

                free(read_buff);
                free(to_write);
            }
            if (rem_num_ele > 0) {
                char * read_buff_rem = (char * ) malloc(rem_num_ele);
                read(fd_read, read_buff_rem, rem_num_ele);
                char * to_write_rem = (char * ) malloc(rem_num_ele);
                for (int k = 0; k < rem_num_ele; k++) {
                    to_write_rem[k] = '\0';
                }
                for (int t = 0; t < rem_num_ele; t++) {
                    to_write_rem[t] = read_buff_rem[rem_num_ele - 1 - t];
                }
                write(fd_write, to_write_rem, rem_num_ele);
                free(read_buff_rem);
                free(to_write_rem);

            }

        } else {
            //reverse the entire file
        }
        off_t curr_file_offset_write = lseek(fd_write, 0, SEEK_CUR);
        cout << "curr_file_offset_write " << curr_file_offset_write << endl;
        close(fd_write);
        close(fd_read);



    }
    if ( * (argv[4] + 0) == '1') {
        // reverse the entire file
        
        cout << "Size of the file " << buff_size << endl;
        /*
        int file_chunk = buff_size/500;//0.2% of the file //ask this question
        int chunk_size;
        if(file_chunk==0){
            chunk_size = 1;
        }else{
            int power_2 = (int)(log((double)file_chunk)/log(2.0));
            chunk_size = pow(2,power_2);
        }
        */
        int chunk_size = 5;//hardcoded
        int number_chunks = buff_size / chunk_size;
        int left_elements = buff_size % chunk_size;
        lseek(fd_read, 0, SEEK_SET);
        lseek(fd_write, 0, SEEK_SET);
        if (left_elements > 0) {
            char * read_buff = (char * ) malloc(left_elements);
            char * to_write = (char * ) malloc(left_elements);
            int last_ele_off = number_chunks * chunk_size;
            lseek(fd_read, last_ele_off, SEEK_SET);
            read(fd_read, read_buff, left_elements);
            int i = 0;
            while (i < left_elements) {
                to_write[i] = read_buff[left_elements - 1 - i];
                i++;
            }
            write(fd_write, to_write, left_elements);
            free(read_buff);
            free(to_write);
            lseek(fd_read,0,SEEK_SET);
        }
        int ind = number_chunks-1;
        while(ind>=0){
            char * read_buff = (char * ) malloc(chunk_size);
            char * to_write = (char * ) malloc(chunk_size);
            int offset = ind*chunk_size;
            lseek(fd_read,offset,SEEK_SET);
            read(fd_read,read_buff,chunk_size);
            int i=0;
            while(i<chunk_size){
                to_write[i]=read_buff[chunk_size-1-i];
                i++;
            }
            write(fd_write, to_write, chunk_size);
            free(read_buff);
            free(to_write);
            lseek(fd_read,0,SEEK_SET);
            ind--;
        }
        off_t curr_file_offset_write = lseek(fd_write, 0, SEEK_CUR);
        cout << "curr_file_offset_write " << curr_file_offset_write << endl;
        close(fd_write);
        close(fd_read);


    }
    if ( * (argv[4] + 0) == '2'){
        //reverse the file from 0 to start-1
        //reverse the file from end+1 to end of file
        int start=2; // <-- get from arguments // convert from 
        int end;//<-- get from arguments
        //reverse the file from 0 to start-1
        int chunk_size = 2;//hardcoded
        int number_chunks = start / chunk_size;
        int left_elements = start % chunk_size;
        lseek(fd_read, 0, SEEK_SET);
        lseek(fd_write, 0, SEEK_SET);
        if (left_elements > 0) {
            char * read_buff = (char * ) malloc(left_elements);
            char * to_write = (char * ) malloc(left_elements);
            int last_ele_off = number_chunks * chunk_size;
            lseek(fd_read, last_ele_off, SEEK_SET);
            read(fd_read, read_buff, left_elements);
            int i = 0;
            while (i < left_elements) {
                to_write[i] = read_buff[left_elements - 1 - i];
                i++;
            }
            write(fd_write, to_write, left_elements);
            free(read_buff);
            free(to_write);
            lseek(fd_read,0,SEEK_SET);
        }
        int ind = number_chunks-1;
        while(ind>=0){
            char * read_buff = (char * ) malloc(chunk_size);
            char * to_write = (char * ) malloc(chunk_size);
            int offset = ind*chunk_size;
            lseek(fd_read,offset,SEEK_SET);
            read(fd_read,read_buff,chunk_size);
            int i=0;
            while(i<chunk_size){
                to_write[i]=read_buff[chunk_size-1-i];
                i++;
            }
            write(fd_write, to_write, chunk_size);
            free(read_buff);
            free(to_write);
            lseek(fd_read,0,SEEK_SET);
            ind--;
        }
        lseek(fd_read,start-1,SEEK_SET);
        off_t curr_file_offset_write = lseek(fd_write, 0, SEEK_CUR);
        cout << "curr_file_offset_write " << curr_file_offset_write << endl;
        close(fd_write);
        close(fd_read);
        
        
        
    }



    return 0;
}
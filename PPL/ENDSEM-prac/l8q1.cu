#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#define MAX_SENTENCE_LEN 1024
#define MAX_WORD_LEN 64
#include<string.h>

__global__ void FindMatchingWord(char * d_sen, char * d_word, int * d_count, int sen_len, int word_len){
    int tid=threadIdx.x;
    while(tid<sen_len){
        int i=0;
        while(d_sen[i+tid]==d_word[i] && i<word_len){
            i++;
        }
        if(i==word_len){
            atomicAdd(d_count,1);
            tid+=word_len;
        }else
            tid++;
    }
}

int main(){
    char sen[MAX_SENTENCE_LEN]="what is up what is up";
    char word[MAX_WORD_LEN]="what";
    int word_len,sen_len;
    int count=0;

    char * d_sen, *d_word;
    int *d_count;

    sen_len=strlen(sen);
    word_len=strlen(word);

    cudaMalloc((void**)&d_sen,sen_len*sizeof(char));
    cudaMalloc((void**)&d_word,word_len*sizeof(char));
    cudaMalloc((void**)&d_count,sizeof(int));

    cudaMemcpy(d_sen,sen, sen_len*sizeof(char),cudaMemcpyHostToDevice);
    cudaMemcpy(d_word,word, word_len*sizeof(char),cudaMemcpyHostToDevice);

    int blockSize = 1;
    int gridSize = 1;
    FindMatchingWord<<<gridSize,blockSize>>>( d_sen, d_word, d_count,sen_len,word_len);

    cudaMemcpy(&count,d_count, sizeof(int),cudaMemcpyDeviceToHost);

    printf("\n the word was repeated %d times\n",count);

    cudaFree(d_sen);
    cudaFree(d_word);
    cudaFree(d_count);

    return 0;
}
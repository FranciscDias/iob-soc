#include <stdio.h>
#include <stdlib.h>

#define ZERO    0000001 
#define UM      1001111
#define DOIS    0010010
#define TRES    0000110
#define QUATRO  1001100
#define CINCO   0100100
#define SEIS    0100000
#define SETE    0001111
#define OITO    0000000
#define NOVE    0000100


void Dec_to_Bin(int num){
    int BinaryNum[10], i=0, l=0;

    for ( ; num > 0; ){
        BinaryNum[i++] = num % 2;
        num /= 2; 
    }
    for (int j = i-1; j>=0 ; j--){
        printf("%d", BinaryNum[j]);
    }
}

void Detect_Number(int num, int BinaryNum[]){
    
  int cathode, cat;

  uint16_t anode;

    switch (num)
    {
    case 1000 <= num:
        cathode = num / 1000;
        anode = 0'b00000111;
    //    gpio_set_output_enable(); //Ativar pin do anodo A4 ou 0111
    //    gpio_set(1);
        
        break;
    case 100 <= num:
        cathode = (num % 1000)/100;
        anode = 1024;
    //    gpio_set_output_enable(); //Ativar pin do anodo A3 ou 1011
    //    gpio_set(1);
        
        break;
    case 10 <= num:
        cathode = ((num % 1000)%100)/10;
        cat = 512;
    //    gpio_set_output_enable(); //Ativar pin do anodo A2 ou 1101
    //    gpio_set(1);
        break;
    case 0 <= num:
        cathode = ((num % 1000)% 100)%10;
        cat = 256;
    //    gpio_set_output_enable(); //Ativar pin do anodo A1 ou 1110
    //    gpio_set(1);
        break;
    default:
        //todos os leds a 0 ou desativados
        break;
    }
}

int main(void){
    int num;

    printf("Number: ");
    scanf("%d", &num);
    Dec_to_Bin(num);
}

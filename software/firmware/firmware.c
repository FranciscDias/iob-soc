#include <stdio.h>
#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "iob-gpio.h"
#include "printf.h"

char *send_string = "Sending this string as a file to console.\n"
                    "The file is then requested back from console.\n"
                    "The sent file is compared to the received file to confirm " 
                    "correct file transfer via UART using console.\n"
                    "Generating the file in the firmware creates an uniform "
                    "file transfer between pc-emul, simulation and fpga without"
                    " adding extra targets for file generation.\n";

// copy src to dst
// return number of copied chars (excluding '\0')
int string_copy(char *dst, char *src) {
    if (dst == NULL || src == NULL) {
        return -1;
    }
    int cnt = 0;
    while(src[cnt] != 0){
        dst[cnt] = src[cnt];
        cnt++;
    }
    dst[cnt] = '\0';
    return cnt;
}

// 0: same string
// otherwise: different
int compare_str(char *str1, char *str2, int str_size) {
    int c = 0;
    while(c < str_size) {
        if (str1[c] != str2[c]){
            return str1[c] - str2[c];
        }
        c++;
    }
    return 0;
}


void Detect_Number(int num, int vetor[]){

  int cathode[4], teste;

  uint32_t anode;

  for(int i=0; i<4; i++){
  cathode[i]=0;
  }

  cathode[0] = num/1000;
  cathode[1] = (num%1000)/100;
  cathode[2] = ((num%1000)%100)/10;
  cathode[3] = ((num%1000)%100)%10;
  
  if(1000 <= num && num <= 9999)
  {
    anode = 0b00000000000000000000000000000000;
    vetor[0] = anode|cathode[0];
    anode = 0b00000000000000000000000000000000;
    printf("vetor 0 = %d\n", vetor[0]);
    anode = 0b00001000000000000000000000000000;
    vetor[1] = anode|cathode[1];
    anode = 0b00000000000000000000000000000000;
    printf("vetor 1 = %d\n", vetor[1]);
    anode = 0b00001100000000000000000000000000;
    vetor[2] = anode|cathode[2];
    anode = 0b00000000000000000000000000000000;
    printf("vetor 2 = %d\n", vetor[2]);
    anode = 0b00001110000000000000000000000000;
    vetor[3] = anode|cathode[3];
    anode = 0b00000000000000000000000000000000;
    printf("vetor 3 = %d\n", vetor[3]);
    return;
  }
  if(100 <= num && num <= 999){
    anode = 0b00001000000000000000000000000000;
    vetor[1] = anode|cathode[1];
    anode = 0b00001100000000000000000000000000;
    vetor[2] = anode|cathode[2];
    anode = 0b00001110000000000000000000000000;
    vetor[3] = anode|cathode[3];
    return;
  }
  if(10 <= num && num <= 99){
    anode = 0b00001100000000000000000000000000;
    teste = anode|cathode[1];
    return;
  }
  if(0 <= num && num <= 9){
    anode = 0b00001110000000000000000000000000;
    teste = anode|cathode[1];
    return;
  }
  else{
    teste = 0b00001111000000000000000000000000;
    return;
  }
  
}

int main()
{

  int valor, vetor[4];

  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  gpio_init(GPIO_BASE);

  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats
  printf("Value of Pi = %f\n\n", 3.1415);

//  scanf("%d", &valor);
	valor = 2190;

  Detect_Number(valor, vetor);
 
  gpio_set_output_enable(valor);

  gpio_set(1);

  printf("valor ==== %d%d%d%d\n", vetor[0], vetor[1], vetor[2], vetor[3]);


  uart_finish();
}

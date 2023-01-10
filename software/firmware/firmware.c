#include <stdio.h>
#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "iob-gpio.h"
#include "printf.h"
#include "sensor.c"

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


int Detect_Number(int num){

  int cathode[4], global, anode1, anode2, anode3, anode4, num1, num2, num3, num4, value;
  //1- numero mais a esquerda... 4- numero mais a direita

  anode1 = 0b0000;
  anode2 = 0b1000;
  anode3 = 0b1100;
  anode4 = 0b1110;
  cathode[0] = num/1000;
  cathode[1] = (num%1000)/100;
  cathode[2] = ((num%1000)%100)/10;
  cathode[3] = ((num%1000)%100)%10;

  printf("before ==============> %d%d%d%d\n", cathode[0], cathode[1], cathode[2], cathode[3]);

  for(int i=0; i<4; i++){
    if(cathode[i]==0)
       cathode[i] = 1;
    if(cathode[i]==1)
      cathode[i] = 79;
    if(cathode[i]==2)
      cathode[i] = 18;
    if(cathode[i]==3)
      cathode[i] = 6;
    if(cathode[i]==4)
      cathode[i] = 76;
    if(cathode[i]==5)
      cathode[i] = 36;
    if(cathode[i]==6)
      cathode[i] = 32;
    if(cathode[i]==7)
      cathode[i] = 15;
    if(cathode[i]==8)
      cathode[i] = 0;
    if(cathode[i]==9)
      cathode[i] = 4;
  }

  printf("Valor=============> %d%d%d%d\n", cathode[0], cathode[1], cathode[2], cathode[3]);

  global = cathode[0] << 24 | cathode[1] << 16 | cathode[2] << 8 | cathode[3];

  printf("global variable=======>%d\n", global);
  /* if(cathode1 != 0){
    num1 = num1 | anode1;
    num1 = num1 << 26;
    num1 = num1 | cathode1;
  }
  else
    num1 = 0;
  if(cathode2 != 0){
    num2 = num2 | anode2;
    num2 = num2 << 18;
    num2 = num2 | cathode2;
  }
  else
    num2 = 0;
  if(cathode3 != 0){
    num3 = num3 | anode3;
    num3 = num3 << 10;
    num3 = num3 | cathode3;
  }
  else
    num3 = 0;
  if(cathode4 != 0){
    num4 = num4 | anode4;
    num4 = num4 << 4;
    num4 = num4 | cathode4;
  }
  else
    num4 = 0;
  printf("chomi  %d \n", num1);
  printf("chomi  %d \n", num2);
  printf("chomi  %d \n", num3);
  printf("chomi  %d \n", num4);

  value = value | num1;
  value = value << 8;
  value = value | num2;
  value = value << 8;
  value = value | num3;
  value = value << 8;
  value = value | num4;*/
}

int main()
{
  int valor, value;

  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  gpio_init(GPIO_BASE);

  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats
  printf("Value of Pi = %f\n\n", 3.1415);


	valor = 5482;

  value =  Detect_Number(valor);
 
  gpio_set_output_enable(valor);

  gpio_set(1);

  printf("valor ==== %d\n", value);

  uart_finish();
}

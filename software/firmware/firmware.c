#include <stdio.h>
#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "iob-gpio.h"
#include "printf.h"

static int* pointer_cathode = (int*)0x00000000000024a;
static int* pointer_anode = (int*)0x000000000000254;

static uint32_t anode[4];

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

  int cathode[4], global_cathode;
  //1- numero mais a esquerda... 4- numero mais a direita
  
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

  global_cathode = cathode[0] << 24 | cathode[1] << 16 | cathode[2] << 8 | cathode[3];

  gpio_set_cathode_output(global_cathode);

  printf("global variable=======>%d", global_cathode);

  return global_cathode;
}

void pin_decoder(int counter){
  int pin, cathode = 0, anode = 0;

  int cathode_c = *pointer_cathode;
  int anode_c = *pointer_anode;

  cathode = cathode_c;
  anode = anode_c;
  
  cathode << 8*(3-counter);
  cathode >> 8*3;

  pin = anode | cathode;

  printf("\nANODE =================> %d", anode);
  printf("\nCATHODE ==============> %d\n", cathode);
  printf("PIN DECODE ===========> %d\n", pin);
}

int main()
{

  int valor, value, counter=0, pin=0;

  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  gpio_init(GPIO_BASE);

  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats
  printf("Value of Pi = %f\n\n", 3.1415);

  anode[0] = anode[0] | 0b0111 << 8;
  anode[1] = anode[1] | 0b1011 << 8;
  anode[2] = anode[2] | 0b1101 << 8;
  anode[3] = anode[3] | 0b1110 << 8;

  printf("\nfunciona ==============> %d\n", anode[0]);
  
  gpio_set_anode_output(anode[counter]);

  //while(1)
	valor = 5482;

  value =  Detect_Number(valor);

  pin_decoder(counter);
 
  gpio_set_output_enable(valor);

  gpio_set(1);

  printf("valor ==== %d\n", value);

  counter += 1;
  if(counter==4)
    counter = 0;

  uart_finish();
}

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


int Detect_Number(int num){

  int cathode1, cathode2, cathode3, cathode4, teste;

  uint16_t anode;
  cathode1 = num/1000;
  cathode2 = (num%1000)/100;
  cathode3 = ((num%1000)%100)/10;
  cathode4 = ((num%1000)%100)%10;
  
  if(1000 <= num <= 9999)
  {
    anode = 0b0000000000000000;
    teste = anode;
    //return teste;
  }
  if(100 <= num <= 999){
    anode = 0b0000100000000000;
    //return anode;
  }
  if(10 <= num <= 99){
    anode = 0b0000110000000000;
  }
  if(0 <= num <= 9){
    anode = 0b0000111000000000;
  }
  else{
    anode = 0b0000111100000000;
  }
  
}

int main()
{

  int valor;

  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  gpio_init(GPIO_BASE);

  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats
  printf("Value of Pi = %f\n\n", 3.1415);

//  scanf("%d", &valor);
	valor = 2190;

  valor =  Detect_Number(valor);
 
  gpio_set_output_enable(valor);

  gpio_set(1);

  printf("valor ==== %d\n", valor);


  uart_finish();
}

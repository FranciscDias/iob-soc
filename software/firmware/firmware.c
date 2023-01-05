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

<<<<<<< HEAD
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
  
=======
  int cathode1, cathode2, cathode3, cathode4, anode1, anode2, anode3, anode4, num1, num2, num3, num4, value;
  //1- numero mais a esquerda... 4- numero mais a direita

  anode1 = 0b0000;
  anode2 = 0b1000;
  anode3 = 0b1100;
  anode4 = 0b1110;
  cathode1 = num/1000;
  cathode2 = (num%1000)/100;
  cathode3 = ((num%1000)%100)/10;
  cathode4 = ((num%1000)%100)%10;
  
  if(cathode1 != 0){
    num1 = num1 | anode1;
    num1 = num1 << 4;
    num1 = num1 | cathode1;
  }
  else
    num1 = 0;
  if(cathode2 != 0){
    num2 = num2 | anode2;
    num2 = num2 << 4;
    num2 = num2 | cathode2;
  }
  else
    num2 = 0;
  if(cathode3 != 0){
    num3 = num3 | anode3;
    num3 = num3 << 4;
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
  value = value | num4;
  return value;
>>>>>>> f65ed0f845a37fc71a19a59afa610f08207be75f
}

int main()
{

<<<<<<< HEAD
  int valor, vetor[4];
=======
  int valor, value;
>>>>>>> f65ed0f845a37fc71a19a59afa610f08207be75f

  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  gpio_init(GPIO_BASE);

  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats
  printf("Value of Pi = %f\n\n", 3.1415);

//  scanf("%d", &valor);
	valor = 5482;

<<<<<<< HEAD
  Detect_Number(valor, vetor);
=======
  value =  Detect_Number(valor);
>>>>>>> f65ed0f845a37fc71a19a59afa610f08207be75f
 
  gpio_set_output_enable(valor);

  gpio_set(1);

<<<<<<< HEAD
  printf("valor ==== %d%d%d%d\n", vetor[0], vetor[1], vetor[2], vetor[3]);

=======
  printf("valor ==== %d\n", value);
>>>>>>> f65ed0f845a37fc71a19a59afa610f08207be75f

  uart_finish();
}

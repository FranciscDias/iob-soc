#include <stdio.h>
#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "iob-gpio.h"
#include "iob-timer.h"
#include "printf.h"
//#include "sensor.h"

//static int* pointer_cathode = (int*)0x00000000000024a;
//static int* pointer_anode = (int*)0x000000000000254;

static uint8_t anode[4];

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


int trig(void){
  unsigned long long elapsed, elapsed_end, time;
  unsigned int elapsedu;
  unsigned int elapsed_aux = 0;
  int get_jump = 0, distance = 0;
  
  elapsed = timer_get_count();
  
  elapsedu = timer_time_us();

  gpio_set_jump_output(1);
  
  while(elapsed_aux < 10){
    elapsed_aux = elapsedu - timer_time_us();
    }
  gpio_set_jump_output(0);
  
  //elapsed = timer_get_count();
  elapsed = timer_time_us();
  get_jump = gpio_jump_get();
  
  while(get_jump != 1){
    printf("get_jum === %d \n", get_jump);
    get_jump = gpio_jump_get();
  }
  while(get_jump == 1){
    get_jump = gpio_jump_get();
    printf("jump\n");
  }
  // elapsed_end = timer_get_count();
  elapsed_end = timer_time_us();
  time = elapsed_end - elapsed;

  distance = time/58;
  distance = distance/2;
  printf("Time1  ============> %lld \n", time);
  printf("Elapsed  ============> %lld \n", elapsed);
  printf("Elapsed_end  ============> %lld  \n", elapsed_end);
  return distance;

}

int Detect_Number(int num){

  int cathode[4], global_cathode;
  //1- numero mais a esquerda... 4- numero mais a direita
  
  cathode[0] = num/1000;
  cathode[1] = (num%1000)/100;
  cathode[2] = ((num%1000)%100)/10;
  cathode[3] = ((num%1000)%100)%10;

//  printf("before ==============> %d%d%d%d\n", cathode[0], cathode[1], cathode[2], cathode[3]);

  for(int i=0; i<4; i++){
    if(cathode[i]==0)//1
       cathode[i] = 64;
    else if(cathode[i]==1)//79-158
      cathode[i] = 121;
    else if(cathode[i]==2)//18-36
      cathode[i] = 36;
    else if(cathode[i]==3)//6-12
      cathode[i] = 48;
    else if(cathode[i]==4)//76-152
      cathode[i] = 25;
    else if(cathode[i]==5)//36-72
      cathode[i] = 18;
    else if(cathode[i]==6)//32-64
      cathode[i] = 2;
    else if(cathode[i]==7)//15-30
      cathode[i] = 120;
    else if(cathode[i]==8)
      cathode[i] = 0;
    else  if(cathode[i]==9)//4-8
      cathode[i] = 16;
  }

  //printf("Valor=============> %d%d%d%d\n", cathode[0], cathode[1], cathode[2], cathode[3]);

  global_cathode = cathode[0] << 24 | cathode[1] << 16 | cathode[2] << 8 | cathode[3];

  //printf("global variable=======>%d\n", global_cathode);

  return global_cathode;
}

int pin_decoder(int anode, int cathode,  int counter){
  int pin;

//  printf("\nbefore ===================> %d", cathode);
  
  cathode = cathode << 8*counter;
  cathode = cathode >> 8*3;

  // pin = anode | cathode;
  
//  printf("\nANODE =================> %d", anode);
//  printf("\nCATHODE ==============> %d\n", cathode);
//  printf("PIN DECODE ===========> %d\n", pin);
  return cathode;
}

int main()
{  
  int valor, value, counter=0, pin=0, button=0, get_jump = 0, distance = 0;
  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  //gpio init
  gpio_init(GPIO_BASE);

  //timer init
  timer_init(TIMER_BASE);
  
  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats
  printf("Value of Pi = %f\n\n", 3.1415);
  /*
  anode[3] = anode[3] | 0b1000 << 8;
  anode[2] = anode[2] | 0b0100 << 8;
  anode[1] = anode[1] | 0b0010 << 8;
  anode[0] = anode[0] | 0b0001 << 8;
*/

  anode[0] |= 0b0111;
  anode[1] |= 0b1011;
  anode[2] |= 0b1101;
  anode[3] |= 0b1110;
  

//  printf("\nfunciona ==============> %d\n", anode[0]);



   distance =  trig();
   printf("Distance  ============> %d \n", distance);
   // valor = 5789;

   value =  Detect_Number(distance);

   while(counter < 5){

      
     //  trig();
     //gpio_set(1);

     // printf("get_jump ==========> %d \n", get_jump);
     
      pin = pin_decoder(anode[counter], value, counter);

      // pin = pin - counter;
      
      gpio_set_anode_output(anode[counter]);

      // gpio_set(1);
    
      gpio_set_output_enable(pin);

      // gpio_set(1);

      //printf("valor ==== %d\n", pin);

      counter += 1;
      if(counter==4){
        counter = 0;
	//	valor  = valor - 1;
	//	value =  Detect_Number(valor);
      }

      if((button = gpio_button_get())==1)
	break;
    }
    // counter = 0;
    /*
    gpio_set_anode_output(15);
    gpio_set(1);
    gpio_set_output_enable(36);
    gpio_set(1);
    gpio_set_anode_output(0);
    gpio_set(1);*/
    
  uart_finish();

  return 0;
}

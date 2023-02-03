#include <stdio.h>
#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "iob-gpio.h"
#include "iob-timer.h"
#include "printf.h"

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
  
  elapsedu = timer_time_us();

  gpio_set_jump_output(1);
  
  while(elapsed_aux < 10){
    elapsed_aux = elapsedu - timer_time_us();
    }
  gpio_set_jump_output(0);
  
  elapsed = timer_time_us();
  get_jump = gpio_jump_get();
  
  while(get_jump != 1){
    get_jump = gpio_jump_get();
  }
  while(get_jump == 1){
    get_jump = gpio_jump_get();
  }
  
  elapsed_end = timer_time_us();
  time = elapsed_end - elapsed;

  distance = time/58;
  distance = distance/2;
  return distance;
}

int Detect_Number(int num){

  int cathode[4], global_cathode;
  //1- numero mais a esquerda... 4- numero mais a direita
  
  cathode[0] = num/1000;
  cathode[1] = (num%1000)/100;
  cathode[2] = ((num%1000)%100)/10;
  cathode[3] = ((num%1000)%100)%10;

  for(int i=0; i<4; i++){
    if(cathode[i]==0)
       cathode[i] = 192;
    else if(cathode[i]==1)
      cathode[i] = 249;
    else if(cathode[i]==2)
      cathode[i] = 164;
    else if(cathode[i]==3)
      cathode[i] = 176;
    else if(cathode[i]==4)
      cathode[i] = 153;
    else if(cathode[i]==5)
      cathode[i] = 146;
    else if(cathode[i]==6)
      cathode[i] = 130;
    else if(cathode[i]==7)
      cathode[i] = 248;
    else if(cathode[i]==8)
      cathode[i] = 128;
    else  if(cathode[i]==9)
      cathode[i] = 144;
  }

  global_cathode = cathode[0] << 24 | cathode[1] << 16 | cathode[2] << 8 | cathode[3];

  return global_cathode;
}

int pin_decoder(int anode, int cathode,  int counter){
  int pin;
  
  cathode = cathode << 8*counter;
  cathode = cathode >> 8*3;
  return cathode;
  
}

int on_off(int var){
  int pin = 0, i=0;

  if(var==1){
    while(gpio_button1_get()==0){
      for(i=0; i<2; i++){
	gpio_set_anode_output(15);
	gpio_set_output_enable(255);
	gpio_set(1);
	switch(i){
        case 0:
          pin = 192;
	  break;
        case 1:
	  pin = 200;
	  break;
	}
	gpio_set_anode_output(anode[i]);
	gpio_set_output_enable(pin);
	gpio_set(1);
      }
    }
  }
    if(var==0){
      for(i=0; i<3; i++){
	gpio_set_anode_output(15);
	gpio_set_output_enable(255);
	gpio_set(1);
	switch(i){
        case 0:
          pin = 192;
	  break;
	case 1:
	  pin = 142;
	  break;
	case 2:
	  pin = 142;
	  break;  
	}
	gpio_set_anode_output(anode[i]);
	gpio_set_output_enable(pin);
	gpio_set(1);
      }       
    }
  return 1;
}

void off(void){
  int pin = 0, i=0;
  unsigned int elapsed_s_before = 0, elapsed_s_after = 0, time = 0;
  
  elapsed_s_before = timer_time_s();
  while(time < 3){
    for(i=0; i<2; i++){
      gpio_set_anode_output(15);
      gpio_set_output_enable(255);
      gpio_set(1);
      switch(i){
        case 0:
          pin = 192;
	  break;
        case 1:
	  pin = 142;
	  break;
	  //case 2:
	  //pin = 142;
	  //break;
      }
      gpio_set_anode_output(anode[i]);
      gpio_set_output_enable(pin);
      gpio_set(1);
    }
    elapsed_s_after = timer_time_s();
    time = elapsed_s_after - elapsed_s_before;

    printf("TIME  ============> %d \n", time);
  }
  gpio_set_anode_output(15);
  gpio_set_output_enable(255);
  gpio_set(1);
}


int main()
{  
  int valor, value, counter=0, count=0,  pin=0, button1=0, button2=0, get_jump = 0, distance = 0, on_var = 1;
  unsigned int elapsed_s_before = 0, elapsed_s_after = 0, time = 0;
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

  anode[0] |= 0b0111;
  anode[1] |= 0b1011;
  anode[2] |= 0b1101;
  anode[3] |= 0b1110;

  
  while(gpio_switch_get()==1){
    if(on_var==1){
      button1=on_off(1);
      on_var=0;
    }
    if((button1 = gpio_button1_get())==1){
      distance =  trig();
      printf("Distance  ============> %d \n", distance);
      value =  Detect_Number(distance);
      if(100 <= distance && distance<1000)
	count = 1;
      else if(10 <= distance &&  distance<100)
	count = 2;
      else if(distance<10)
	count = 3;
      else
	count = 0;
      while(counter < 5){
        gpio_set_anode_output(15);
	gpio_set_output_enable(255);
	gpio_set(1);
     
	pin = pin_decoder(anode[counter], value, counter);
	
        gpio_set_anode_output(anode[counter]);
      
        gpio_set_output_enable(pin);
	gpio_set(1);

        counter += 1;
	
        if(counter==4){
	    counter = count;
	}
	
        if((button2 = gpio_button2_get())==1 || gpio_switch_get()==0)
	  break;  
      }
    }
  }  
  gpio_set_anode_output(15);
  gpio_set_output_enable(255);
  gpio_set(1);  

  elapsed_s_before = timer_time_s();
  while(time < 3){
    on_off(0);
    printf("ANtes ============> %d \n", time);
    elapsed_s_after = timer_time_s();
    time = elapsed_s_after - elapsed_s_before;
    printf("TIME  ============> %d \n", time);
  }

  gpio_set_anode_output(15);
  gpio_set_output_enable(255);
  gpio_set(1);
  uart_finish();

  return 0;
}


`timescale 1ns / 1ps
`include "system.vh"

module top_system(
	          input        clk,
	          input        reset,

	          //uart
	          output       uart_txd,
	          input        uart_rxd,
		  //gpio
		  input        JUMP_IN,
		  input        BTN_1,
		  input        BTN_2,
		  input        SWITCH,       
		  output       JUMP_OUT,
		  output [7:0] PIN,
		  output [3:0] AN
		  );

   //
   // RESET MANAGEMENT
   //

   //system reset

   wire                         sys_rst;

   reg [15:0] 			rst_cnt;
   reg                          sys_rst_int;

   always @(posedge clk, posedge reset)
     if(reset) begin
        sys_rst_int <= 1'b0;
        rst_cnt <= 16'hFFFF;
     end else begin
        if(rst_cnt != 16'h0)
          rst_cnt <= rst_cnt - 1'b1;
        sys_rst_int <= (rst_cnt != 16'h0);
     end

   assign sys_rst = sys_rst_int;

   //
   // SYSTEM
   //
   system system
     (
      .clk           (clk),
      .rst           (sys_rst),
      .trap          (trap),

      //UART
      .uart_txd      (uart_txd),
      .uart_rxd      (uart_rxd),
      .uart_rts      (),
      .uart_cts      (1'b1),

      //GPIO
      .JUMP_IN       (JUMP_IN),
      .JUMP_OUT      (JUMP_OUT),
      .BTN_1         (BTN_1),
      .BTN_2         (BTN_2),
      .PIN           (PIN),
      .AN            (AN),
      .SWITCH        (SWITCH)
      );

endmodule

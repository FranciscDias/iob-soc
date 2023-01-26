# ----------------------------------------------------------------------------
#     _____
#    /     \
#   /____   \____
#  / \===\   \==/
# /___\===\___\/  AVNET Design Resource Center
#      \======/         www.em.avnet.com/drc
#       \====/
# ----------------------------------------------------------------------------
#
#  Disclaimer:
#     Avnet, Inc. makes no warranty for the use of this code or design.
#     This code is provided  "As Is". Avnet, Inc assumes no responsibility for
#     any errors, which may appear in this code, nor does it make a commitment
#     to update the information contained herein. Avnet, Inc specifically
#     disclaims any implied warranties of fitness for a particular purpose.
#                      Copyright(c) 2009 Avnet, Inc.
#                              All rights reserved.
#
# ----------------------------------------------------------------------------

## System Clock
set_property PACKAGE_PIN W5 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]

# System Reset
set_property PACKAGE_PIN T17 [get_ports reset]
set_property IOSTANDARD LVCMOS33 [get_ports reset]

create_clock -period 10.000 [get_ports clk]

## USB-UART Interface
set_property PACKAGE_PIN B18 [get_ports uart_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_rxd]
set_property PACKAGE_PIN A18 [get_ports uart_txd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_txd]




#7 segment display
#Bank = 34, Pin name = , Sch name = CA
set_property PACKAGE_PIN W7 [get_ports {PIN[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[7]}]
#Bank = 34, Pin name = , Sch name = CB
set_property PACKAGE_PIN W6 [get_ports {PIN[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[6]}]
#Bank = 34, Pin name = , Sch name = CC
set_property PACKAGE_PIN U8 [get_ports {PIN[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[5]}]
#Bank = 34, Pin name = , Sch name = CD
set_property PACKAGE_PIN V8 [get_ports {PIN[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[4]}]
#Bank = 34, Pin name = , Sch name = CE
set_property PACKAGE_PIN U5 [get_ports {PIN[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[3]}]
#Bank = 34, Pin name = , Sch name = CF
set_property PACKAGE_PIN V5 [get_ports {PIN[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[2]}]
#Bank = 34, Pin name = , Sch name = CG
set_property PACKAGE_PIN U7 [get_ports {PIN[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[1]}]
#Bank = 34, Pin name = , Sch name = DP
set_property PACKAGE_PIN V7 [get_ports {PIN[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PIN[0]}]


#Bank = 34, Pin name = , Sch name = AN0
set_property PACKAGE_PIN U2 [get_ports {AN[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {AN[0]}]
#Bank = 34, Pin name = , Sch name = AN1
set_property PACKAGE_PIN U4 [get_ports {AN[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {AN[1]}]
#Bank = 34, Pin name = , Sch name = AN2
set_property PACKAGE_PIN V4 [get_ports {AN[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {AN[2]}]
#Bank = 34, Pin name = , Sch name = AN3
set_property PACKAGE_PIN W4 [get_ports {AN[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {AN[3]}]

#Buttons
#Bank = 14, Pin name = , Sch name = BTNC
#set_property PACKAGE_PIN U18 [get_ports {BTN[4]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {BTN[4]}]
#Bank = 14, Pin name = , Sch name = BTNU
#set_property PACKAGE_PIN T18 [get_ports {BTN[0]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {BTN[0]}]
#Bank = 14, Pin name = , Sch name = BTNL
#set_property PACKAGE_PIN W19 [get_ports {BTN[1]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {BTN[1]}]
#Bank = 14, Pin name = , Sch name = BTNR
#set_property PACKAGE_PIN T17 [get_ports {BTN[2]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {BTN[2]}]
#Bank = 14, Pin name = , Sch name = BTND
#set_property PACKAGE_PIN U17 [get_ports {BTN[3]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {BTN[3]}]


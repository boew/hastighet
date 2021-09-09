
Example project for the IAR LPC-P213X evaluation board, the project
is configured for the J-Link JTAG interface.
Load the workspace file Lpc213x_demo.eww in the IAR Embedded Workbench to start.

The project contains two configurations.
Debug RAM - downloads the code to RAM
Debug flash - downloads the code to flash

Button functions
B1 - next
B2 - select

Press B1 until you get the "Adc measure" menu, turn the
potentiometer knob to show the rotation on the display.

Terminal settings:

UART1
Communication speed: 9600 bps
Number of data bits:    8
Number of stop bits:    1
Parity:              none

UART2
Communication speed: 9600 bps
Number of data bits:    8
Number of stop bits:    1
Parity:              none


Jumper settings:
Set PWM/DAC to DAC.
Set Ext/J-Link to Ext.

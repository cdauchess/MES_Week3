# MES Week 3 - Make Blinky

## Questions

### What are the hardware registers that cause the LED to turn on and off?
For the RP2040 the registers for the GPIO output control are SIO:GPIO_OUT[25]

### What registers can you read to find the state of the button?
The GPIO input for my button can be found in register SIO:GPIO_IN[15]

### Can you read the register directly and see the button change in a debugger or by printing the values of the memory at the register address?
Yes

## Button Bounce
Below is a screen shot from my logic analyzer of the button bounce from my button
 ![Bounce Button](/images/Button_Bounce.png)

## Prerequisites

This assumes that 
1. You have already installed OpenOCD with picoprobe, according to the steps in [Getting Started](https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf), Appendix A
2. Your VSCode has already been configured according to the steps [here](https://shawnhymel.com/2096/how-to-set-up-raspberry-pi-pico-c-c-toolchain-on-windows-with-vs-code/)
3. You have installed the picoprobe uf2 to one Pico, and it is connected to the other Pico with the correct wiring (refer again to Appendix A).



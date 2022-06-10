This timer is configured differently from the default system clock (4Mhz MSI).
The system clock is reconfigured to first select HSI as the clock source. HSI
runs at 16Mhz. HSI is then configured through the PLL to output 80Mhz. Thus, 
the clock source is now PLLCLK which runs on the APB2 bus the timer is connected
to. This 80Mhz will be used as the frequency for PWM.

Comment out the System_Clock_Init() function in main to see the default 4Mhz 
frequency and notice the difference.

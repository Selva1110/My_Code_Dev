Example Code: XMC1300_SPI_Master_Loopback

Description of example project
==============================
This example sends a SPI frame on each alternate (receive) interrupt. Initialize P0.0 which connected to an on-board LED as output pin.Initialize P1.1 (SEL pin), P1.2 (TX, RX pin) and P1.4 (CLK)for SPI communication with loopback Next, Initialize clock
and USIC channel 1. Followed by create a receive start interrupt handler to toggle LED and send a SPI frame. Generate the first alternate (receive) interrupt.

Hardware Setup
===============
XMC1300 Bootkit (No satellite board required)

How to test the application
============================
a. Import the project
b. Compile and flash the application to the device
c. Observed the LED P0.0 toggles
d. Observe the SPI signals on an oscilloscope.



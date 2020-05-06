Example Code: XMC1300_CCU4_PWM_Duty_Cycle


Description of example project
==============================
This example uses the compare match to generate a PWM signal. The compare match interrupt will alternate the duty cycle of the output signal between 33.3% and 66.6% by changing the compare match value.
This will generate a PWM signal of 1Hz with 33.3% and 66.6% alternating duty cycle at P0.0.

Hardware Setup
===============
XMC1300 Bootkit (No satellite board required)


How to test the application
============================
a. Import the project
b. Compile and flash the application to the device
c. Measure the output pin P0.0 with an oscilloscope to check PWM waveform
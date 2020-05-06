Example Code: XMC1300_CCU4_Capture_PWM

Description of example project
==============================
This example uses the CCU4 capture mode to measure the frequency and duty cycle of an external incoming PWM pulse signal. P0.0 is configured to generate a PWM signal of 50 kHz and 33% duty cycle.
P0.1 is used to detect the incoming PWM signal. The CCU40 interrupt request is used to measure the frequency and duty cycle of the signal.

Hardware Setup
===============
XMC1300 Bootkit (No satellite board required)

How to test the application
============================
a. Import the project
b. Compile and flash the application to the device
c. Apply PWM pulse signal from P0.0 to P0.1 using a jumper wire
d. Read frequency (variable capturefrequency) and duty cycle (variable captureduty) values in the CCU40_2_IRQHandler() routine.
MOTOR CONTROL BLOCK COMMUTATION WITH HALL SENSOR MIDDLEWARE
===========================================================
Motor control block commutation with hall sensor using ATBLDCLV reference kit and Atmel SAMC21/SAMD21 MCU. 

Interface Feature
-----------------

* Peripheral initialization
* Sending/receipt ADP data package
* Update of commutation on Hall events

Dependencies
------------
* An instance of the TCC0 used for PWM generation and ADP middleware for communication with UI
* An instance of the SPI Master Sync interface driver must be passed to ADP
  when ADP initialized.

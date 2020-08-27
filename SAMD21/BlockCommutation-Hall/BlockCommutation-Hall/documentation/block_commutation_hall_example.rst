MOTOR CONTROL BLOCK COMMUTATION WITH HALL SENSOR APPLICATION
============================================================
This application demonstrates Block Commutation with hall sensor implementation for control of a BLDC Motor(LDO 42BL02402-0026B-002) using an Atmel SAMD21/SAMC21 MCU and the Atmel ATBLDCLV kit with 24V input supply.

Features
--------
* Peripheral initialization
* Block commutation algorithm implementation
* Interfacing with Atmel Data Visualizer tool

SUPPORTED EVALUATION KIT
------------------------
* ATBLDCLV kit with ATSAMD21MOTOR/ATSAMC21MOTOR MCU card and LDO 42BL02402-0026B-002 motor

Interface Settings
------------------
* Connect a micro-USB to the EDBG port on the ATBLDCLV kit and a USB port on the PC
* Connect the 24V power supply to the kit using the cord supplied with the kit
* Install Atmel Data Visualizer tool from Atmel Gallery (URL: https://gallery.atmel.com/Products/Details/2f6059f5-9200-4028-87e1-ba3964e0acc2) on the PC.

Running the Demo
----------------
1. Press **Save Configuration** and save the .atzip file.
2. Import .atzip file into Atmel Studio 7, File->Import->Atmel Start Project.
3. Build and flash into supported evaluation board.
4. Start Atmel Data Visualizer on the PC and click "Connect" button on the "DGI Control Panel"
5. This should load a dashboard for motor control in the tool.
6. Once all the UI components are loaded, set the speed in the "Speed Ref (RPM)" text box and press return key.
7. Click the "Start" button to spin the motor.
8. Vary the speed by changing the value in "Speed Ref (RPM)" textbox.
9. To change spinning direction, ensure that the motor is in "Stop" state and then select the appropriate radio button for "Direction".
10. Click "Start" to spin the motor.

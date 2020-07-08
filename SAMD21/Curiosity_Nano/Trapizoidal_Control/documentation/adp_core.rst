Atmel Data Protocol
===================

Atmel Data Protocol (ADP) is used for data wrapping, the ADP data package can be
decoded in Data Visualizer. It supports data transfer in both directions.
In addition, the MCU side can send a configuration packet that
describes what modules should be opened in DV and how to connect them.

Interface Feature
-----------------

* Initialization
* Sending/receipt ADP data package

Dependencies
------------
* An instance of the SPI Master Sync interface driver must be passed to ADP
  when ADP initialized.

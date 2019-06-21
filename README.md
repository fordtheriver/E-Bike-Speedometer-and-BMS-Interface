# E-Bike-Speedometer-and-BMS-Interface

**Updated 6/21/19** Completed REV3

This repository includes information needed to built a display to output relevant information for an electric bicycle. Speed, mileage, power, current, pack voltage and individual cell voltages are some of the values that this system can output. The five components in this system include an Arduino Nano, 20x4 LCD screen, a JBDTools-based Battery Management System, DC/DC converter and a Hall-Effect Sensor. This repository includes the necessary Arduino files, a custom Arduino shield PCB designed in EAGLE and various information about the components required to build this system.

My ebike uses the Cyclone 3000 ebike kit. The throttle/ignition has a built in switch on the B+ line. My system draws power from the B+ after this switch so that if the switch opens, the system turns off. I recommend configuring your system this way so that it only draws power when the bike is on.

Here is a brief list describing the necessary high level components for this system.

1. Arduino Nano. REV4 will embed the ATmega328P micrcoprocessor on the board to significantly reduce system size and weight. 

2. [20x4 LCD Display with I2C.](https://www.ebay.com/sch/i.html?_from=R40&_trksid=m570.l1313&_nkw=20x4+i2c+lcd+&_sacat=0). The I2C communication bus drastically reduces the number of wires going to the LCD and the \#include <LiquidCrystal_I2C.h> library seamlessly integrates the I2C protocol into your arduino. 

3. JBDTools Compatible BMS: Here is a [link](https://www.aliexpress.com/item/15S-Li-ion-Battery-Intelligent-Smart-BMS-with-Bluetooth-function-and-PC-software-UART-communication-PCB/32876909159.html?spm=a2g0s.13010208.99999999.263.70483c00UKdgf7) to the one I purchased.  . Make sure the BMS you buy is compatible with JBDTools software. My arduino script uses the communication protocol used by the JBDTools software. This protocol can be found in an excel file call JBDTools Communication Protol at the homepage of this repository. [Simat](https://github.com/simat/BatteryMonitor/wiki/Generic-Chinese-Bluetooth-BMS-communication-protocol) also has a great description of it as well. 

4. DC/DC Converter. The linear voltage regulator on [this](https://www.aliexpress.com/item/15S-Li-ion-Battery-Intelligent-Smart-BMS-with-Bluetooth-function-and-PC-software-UART-communication-PCB/32876909159.html?spm=a2g0s.13010208.99999999.263.70483c00UKdgf7) type of BMS is not designed to handle high amounts of current. REV3 of this project includes [this](https://www.mouser.com/ProductDetail/MEAN-WELL/SKM15C-12?qs=erfQA2AIGbWiXI5iTXq5SA%3D%3D) DC/DC converter to provide 12V at a max of 1.25A to the system.

5. [Hall effect sensor.](https://www.adafruit.com/product/158). This type of sensor send a HIGH pulse whenever a significant magnetic field acts upon it.

6. Connectors. [Housing](https://www.mouser.com/ProductDetail/Molex/70543-0001?qs=sGAEpiMZZMtVoztFdqDXOwZ%252B3K3gi96X). [Plug](https://www.mouser.com/ProductDetail/Molex/50-57-9402?qs=%2Fha2pyFaduiLH0020kLaRTyvVPMd9o3wI7LfZqK7vYk%3D). [Crimp Pin](https://www.mouser.com/ProductDetail/Molex/16-02-0086-Cut-Strip?qs=sGAEpiMZZMs%252BGHln7q6pm%252Bv5BXf4QdrTI%252BpAylNNmmH%2F60rOt1UzkQ%3D%3D)

7. EAGLE PCB design software. I used [OSHPark](https://oshpark.com/) to manufacture the PCB and had no issues. 

# High Level System Requirements:

1. Input Voltage Range: 36 - 72 Volts
2. Max Power Output at 12V: 1.25 Amps



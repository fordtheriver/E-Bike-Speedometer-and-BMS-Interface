# E-Bike-Speedometer-and-BMS-Interface

**Updated 4/23/19**

This repository includes information needed to built a display to output relevant information for an electric bicycle. Speed, mileage, power, current, pack voltage and individual cell voltages are some of the values that this system can output. The five components in this system include an Arduino Nano, 20x4 LCD screen, a JBDTools-based Battery Management System, DC/DC converter and a Hall-Effect Sensor. This repository includes the necessary Arduino files, a custom Arduino shield PCB designed in EAGLE and various information about the components required to build this system.

Although I attached my code and eagle files, this is not a "plug-and-play" type project where I walk you through each step. I'm happy to answer questions or provide support but you will have to do a significant amount of reading yourself to implement this project. Successful completion of the project means you've learned serial communication, PCB design, Arduino programming and general embedded computing techniques. 

Here is a brief list describing the necessary high level components for this system.

1. Arduino Nano. 

2. [20x4 LCD Display with I2C.](https://www.ebay.com/sch/i.html?_from=R40&_trksid=m570.l1313&_nkw=20x4+i2c+lcd+&_sacat=0). The I2C communication bus drastically reduces the number of wires going to the LCD and the \#include <LiquidCrystal_I2C.h> library seamlessly integrates the I2C protocol into your arduino. 

3. JBDTools Compatible BMS: Here is a [link](https://www.aliexpress.com/item/15S-Li-ion-Battery-Intelligent-Smart-BMS-with-Bluetooth-function-and-PC-software-UART-communication-PCB/32876909159.html?spm=a2g0s.13010208.99999999.263.70483c00UKdgf7) to the one I purchased.  . Make sure the BMS you buy is compatible with JBDTools software. My arduino script uses the communication protocol used by the JBDTools software. This protocol can be found in an excel file call JBDTools Communication Protol at the homepage of this repository. [Simat](https://github.com/simat/BatteryMonitor/wiki/Generic-Chinese-Bluetooth-BMS-communication-protocol) also has a great description of it as well. 

4. DC/DC Converter. The linear voltage regulator on [this](https://www.aliexpress.com/item/15S-Li-ion-Battery-Intelligent-Smart-BMS-with-Bluetooth-function-and-PC-software-UART-communication-PCB/32876909159.html?spm=a2g0s.13010208.99999999.263.70483c00UKdgf7) type of BMS is not designed to handle high amounts of current. The bluetooth module that comes with the BMS draws about 120 uA of current while the Arduino/LCD display draws about 60mA, which causes the LVR to get quite hot. I'm currently modifying the design to include [this](https://octopart.com/click/track?country=US&ct=offers&ppid=82218729&sid=2401&sig=0046b1c&vpid=423139082) DC/DC converter to power the Arduino. 

5. [Hall effect sensor.](https://www.adafruit.com/product/158). This type of sensor send a HIGH pulse whenever a significant magnetic field acts upon it.


6. EAGLE PCB design software. I used [OSHPark](https://oshpark.com/) to manufacture the PCB and had no issues. 

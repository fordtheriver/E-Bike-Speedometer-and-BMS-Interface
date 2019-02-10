# E-Bike-Speedometer-and-BMS-Interface
This repository includes information needed to built a small Electronics Control Units for an electric bicycle. The four components in this system include an Arduino Nano, 20x4 LCD screen, a Chinese made Battery Management System and a Hall-Effect Sensor. This repository includes the necessary Arduino files, a custom Arduino shield PCB design in Eagle and various information about the components required to build this system.

Although I attached my code and eagle files, this is not a "plug-and-play" type project where I walk you through each step. I'm happy to answer questions or provide support but you will have to do a significant amount of reading yourself to implement this project. 

Here is a brief list describing the necessary high level components for this system.

1. Arduino Nano. I

2. Generic Chinese BMS: Here is a [link](https://www.aliexpress.com/item/15S-Li-ion-Battery-Intelligent-Smart-BMS-with-Bluetooth-function-and-PC-software-UART-communication-PCB/32876909159.html?spm=a2g0s.13010208.99999999.263.70483c00UKdgf7) to the one I purchased.  . Make sure the BMS you buy is compatible with JBDTools software. My arduino script uses the communication protocol used by the JBDTools software. This protocol can be found in an excel file call JBDTools Communication Protol. [Simat](https://github.com/simat/BatteryMonitor/wiki/Generic-Chinese-Bluetooth-BMS-communication-protocol) also has a great description of it as well. 

3. [Hall effect sensor.](https://www.adafruit.com/product/158). This type of sensor send a HIGH pulse whenever a significant magnetic field acts up it.

4. [20x4 LCD Display with I2C.](https://www.ebay.com/sch/i.html?_from=R40&_trksid=m570.l1313&_nkw=20x4+i2c+lcd+&_sacat=0). The I2C communication bus drastically reduces the number of wires going to the LCD and the \#include <LiquidCrystal_I2C.h> library seamlessly integrates the I2C protocol into your arduino. 

5. EAGLE PCB design software. I used [OSHPark](https://oshpark.com/) to manufacture the PCB and it worked out great.

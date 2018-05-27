## DO IT YOURSELF!

# Moto Alarm Project (Linkit One version)

##### LOCATE YOUR MOTORCYCLE 24 HOURS A DAY AND 365 DAYS A YEAR

[Moto Alarm Project website](https://motoalarm-project.com "Moto Alarm Project")

#### PROJECT FUNCTIONALITIES (For iOS and Android apps):

- You can see the position of your motorcycle at all times.
- You can see the last update date of your motorcycle's position.
- If your motorcycle is moving, speed in meters per second.
- You can activate and deactivate the service via bluetooth.
- You can see the battery status of the device.
- You can activate and deactivate the service through sms from the application.
- If your motorcycle starts to move, you will receive an alert by SMS of the change of position of the motorcycle and the speed.
- You can ask him to send you an SMS or chat to see the status of the battery.
- You can ask for the position of the motorcycle and you will receive an SMS.
- You can also ask how it is and it will send you temperature, humidity and whether it is raining or not ;)

#### PROJECT FUNCTIONALITIES (For macOS app):

- You can see the position of your motorcycle at all times.
- You can see the last update date of your motorcycle's position.
- If your motorcycle is moving, speed in meters per second.
- You can see the battery status of the device.

#### UPDATE TIMES (For iOS and Android apps):

- With the service deactivated, the status of the battery is sent every <b>24 hours</b>.
- With the service activated, if the motorcycle with Grove - 6-Axis Accelerometer & Gyroscope sensor module detects movement, it is sent every <b>2 minutes</b>.
- From the mobile application, you can change the default update time (2 minutes) and adapt it to your needs, but the Grove - 6-Axis Accelerometer & Gyroscope sensor module will activate the services if necessary and save battery ;)

### DOWNLOAD iOS VERSION:

[Moto Alarm Project iOS version](https://itunes.apple.com/us/app/moto-alarm-project/id1313229312?l=es&ls=1&mt=8 "Moto Alarm Project iOS version")

![MacDown Screenshot](Resources/iPhone_X_1.png)
![MacDown Screenshot](Resources/iPhone_X_2.png)
![MacDown Screenshot](Resources/iPhone_X_3.png)
![MacDown Screenshot](Resources/iPhone_X_4.png)
![MacDown Screenshot](Resources/iPhone_X_5.png)
![MacDown Screenshot](Resources/iPhone_X_6.png)

### DOWNLOAD macOS VERSION:

I'm developing this version :)

### DOWNLOAD ANDROID VERSION:

I'm developing this version :)

### WHAT IS ARDUINO?

Arduino is an open-source electronics platform based on easy-to-use hardware and software. It's intended for anyone making interactive projects.

This is the manufacturer's website:

[Arduino website](https://www.arduino.cc "Arduino")

To program for Arduino, you need to download the Integrated development environment (IDE):

[Arduino software website](https://www.arduino.cc/en/Main/Software "Arduino Software")

### LINKIT ONE BOARD

For this project, I found an Arduino board that integrated all the modules I needed and had a good price: Linkit One.

The LinkIt ONE development board is an open source, high-performance board for prototyping Wearables and IoT devices. It's based on the world's leading SoC for Wearables, MediaTek Aster (MT2502) combined with high-performance Wi-Fi (MT5931) and GPS (MT3332) chipsets to provide you with access to all the features of MediaTek LinkIt. It also provides similar pin-out features to Arduino boards, making it easy for you to connect to various sensors, peripherals, and Arduino shields.

![MacDown Screenshot](Resources/LinkitOne_1.png)
![MacDown Screenshot](Resources/LinkitOne_2.png)
![MacDown Screenshot](Resources/LinkitOne_3.png)

This is the manufacturer's website:

[SeedStudio website](https://www.seeedstudio.com "SeedStudio")

In order to use this board with the Arduino IDE, you need to follow some steps:

[Linkit One Guide website](https://docs.labs.mediatek.com/resource/linkit-one/en "SeedStudio")

### GROVE - 6-AXIS ACCELEROMETER & GYROSCOPE

Grove - 6-Axis Accelerometer & Gyroscope is a cost-effective Grove sensor integrated with a 3-axis digital accelerometer and a 3-axis digital gyroscope.

With a serious low power consumption digital chip LSM6DS3 and power supply regulator inside, it features high sensitivity, green tech and low noise interference. It can be configured to different sensitivity levels of acceleration and different angular rate measurement range. Provided with detailed SDK, it can make the prototyping process quicker and easier.

This product can be used for different applications for tilt, motion, and tap sensing, such as robotics, IoT devices and consumer electronic devices.

This module is used to send movement alert by SMS and not consume battery sending data if they are not necessary to the server.

[Grove - 6-Axis Accelerometer & Gyroscope for Linkit One](https://www.seeedstudio.com/Grove-6-Axis-Accelerometer%26Gyroscope-p-2606.html "Grove - 6-Axis Accelerometer & Gyroscope for Linkit One")

![MacDown Screenshot](Resources/Grove.jpg)

### INSTRUCTIONS

You have to add a SIM card in your Linkit One with the PIN code deactivated in order to use the GPRS connection, in addition, I use a card with SMS to be able to communicate with the motorcycle, as well as over the Internet, by normal SMS.

I use FreedomPop SIM, it is free with:

- 200 mb for data
- 300 SMS
- 100 minutes for call

[FreedomPop website](https://es.freedompop.com/es?experience=organic.default "FreedomPop")

It is also necessary to add a <b>micro sd card</b> to your Linkit One, since your user data that is sent by bluetooth to the board, is stored so you can restart the device remotely. This data is updated when you activate the service again using the bluetooth. This is important :)

Once you have everything configured in the Arduino IDE to use your new Linkit One board, you can already clone this repository on your computer and access the MotoAlarmProject folder and open the <b>MotoAlarmProject.ino</b> file.

You need to download and install two libraries that are used in the project in the Arduino IDE:

[ArduinoJson in GitHub](https://github.com/bblanchon/ArduinoJson "ArduinoJson")

[elapsedMillis in GitHub](https://github.com/pfeerick/elapsedMillis "elapsedMillis")

[MPU6050 in GitHub](https://github.com/jarzebski/Arduino-MPU6050 "MPU6050")

[OTAUpdate in GitHub](https://github.com/ArtCC/OTAUpdate "OTAUpdate")

<b>All the data that your Linkit One needs is sent by bluetooth from the iOS or Android application.</b>

If you change the default name for your device (MotoAlarmProject) for the bluetooth connection, you have to restart your Linkit One later.

For your Linkit One to send you SMS you have to add your phone in your profile in the iOS or Android application and it will be sent by bluetooth when you activate the service.

You can now upload the code to your Linkit One!

### BOX FOR LINKIT ONE AND BATTERY WITH 6000mAh (Battery size: 19x54x54mm)

If you have a 3D printer or know someone who has it, here are the .stl files to print that I designed for the project:

![MacDown Screenshot](Resources/Box_6000_1.jpg)
![MacDown Screenshot](Resources/Box_6000_2.jpg)
![MacDown Screenshot](Resources/Box_6000_3.jpg)
![MacDown Screenshot](Resources/Box_6000_4.jpg)
![MacDown Screenshot](Resources/Box_6000_5.jpg)

[STL files in Thingeverse.com by me](https://www.thingiverse.com/thing:2859090 "STL files")

### BATTERY WITH 6000mAh

![MacDown Screenshot](Resources/Battery6000.jpg)

[Battery in 'BricoGeek' shop](http://tienda.bricogeek.com/baterias-lipo/418-bateria-lipo-6000mah-37v.html)

### INSTALLING IN YOUR MOTORBIKE

I have changed the original battery with 1000mAh for a battery with 6000mAh, so it lasts a lot longer without charging.

I added a usb charger to the battery in my motorcycle but in positive, that means that when I turn off the motorcycle it has no current, it only charges the powerbank when the motorcycle is on.

### DO YOU CAN'T THE DEVICE? ASK FOR MY HELP!

Don't worry, write me to my email and I can build it for you at the price of materials and shipping :)

### LEGAL CONDITIONS

General regulation of data protection and terms of use:

- This application needs a user registration through his email and a password.
- All the data that can be requested in the user's profile, such as: name, surname, address, telephone, etc., are optional and therefore, are not needed for the normal use of the application.
- This application is used to, by means of a device that the user constructs and places on his motorcycle, to locate it at any time by sending his location to his user account.
- The last coordinates of the motorcycle are stored in the server and no history of them is saved.
- The user has at his disposal a button in the settings of the application to delete his account and all the data associated with it.
- This application does not use analytics and does not transfer user data to third parties, nor does it exploit usage data for its benefit.
- The developer of this project is not responsible under any circumstances, that the position of the vehicle is not registered correctly.

### LICENSE

This project is free and use <b>CC BY-NC-SA</b>.

This license lets others remix, tweak, and build upon your work without for commercial purposes, as long as they credit you and license their new creations under the identical terms.

### THANK YOU

Nothing else, if you want to improve the Linkit One code, do not hesitate to share it with me. For any question you have, you can write me to my email in the iOS application.

Thank you very much! I hope you like it!


##### ArtCC 2017++

## DO IT YOURSELF!

# Moto Alarm Project (Linkit One version)

##### LOCATE YOUR MOTORCYCLE 24 HOURS A DAY AND 365 DAYS A YEAR

[Moto Alarm Project Website](https://motoalarm-project.com "Moto Alarm Project")

#### PROJECT FUNCTIONALITIES (From macOS, iOS or Android apps):

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

#### UPDATE TIMES:

- With the service deactivated, battery status is sent every <b>60 minutes</b>.
- With the service activated, all data is sent every <b>30 minutes</b>, but if the motorcycle detects movement, it is sent every <b>30 seconds</b>.
- From the mobile application you can change the default update time and adapt it to your needs.

### DOWNLOAD iOS VERSION:

[Moto Alarm Project iOS version](https://itunes.apple.com/us/app/moto-alarm-project/id1313229312?l=es&ls=1&mt=8 "Moto Alarm Project iOS version")

![MacDown Screenshot](Resources/iPhone_1.png)
![MacDown Screenshot](Resources/iPhone_2.png)
![MacDown Screenshot](Resources/iPhone_3.png)
![MacDown Screenshot](Resources/iPhone_4.png)
![MacDown Screenshot](Resources/iPhone_5.png)
![MacDown Screenshot](Resources/iPhone_6.png)

### DOWNLOAD macOS VERSION:

I am developing this version :)

### DOWNLOAD ANDROID VERSION:

I am developing this version :)

### WHAT IS ARDUINO?

Arduino is an open-source electronics platform based on easy-to-use hardware and software. It's intended for anyone making interactive projects.

This is the manufacturer's website:

[Arduino Website](https://www.arduino.cc "Arduino")

To program for Arduino, you need to download the Integrated development environment (IDE):

[Arduino Sofware Website](https://www.arduino.cc/en/Main/Software "Arduino Software")

### LINKIT ONE BOARD

For this project, I found an Arduino board that integrated all the modules I needed and had a good price: Linkit One.

The LinkIt ONE development board is an open source, high-performance board for prototyping Wearables and IoT devices. It's based on the world's leading SoC for Wearables, MediaTek Aster (MT2502) combined with high-performance Wi-Fi (MT5931) and GPS (MT3332) chipsets to provide you with access to all the features of MediaTek LinkIt. It also provides similar pin-out features to Arduino boards, making it easy for you to connect to various sensors, peripherals, and Arduino shields.

![MacDown Screenshot](Resources/LinkitOne_1.png)
![MacDown Screenshot](Resources/LinkitOne_2.png)
![MacDown Screenshot](Resources/LinkitOne_3.png)

This is the manufacturer's website:

[SeedStudio Website](https://www.seeedstudio.com "SeedStudio")

In order to use this board with the Arduino IDE, you need to follow some steps:

[Linkit One Guide Website](https://docs.labs.mediatek.com/resource/linkit-one/en "SeedStudio")

### INSTRUCTIONS

You have to add a SIM card in your Linkit One with the PIN code deactivated in order to use the GPRS connection, in addition, I use a card with SMS to be able to communicate with the motorcycle, as well as over the Internet, by normal SMS.

I use FreedomPop SIM, it is free with:

- 200 mb for data
- 300 SMS
- 100 minutes for call

[FreedomPop Website](https://es.freedompop.com/es?experience=organic.default "FreedomPop")

Once you have everything configured in the Arduino IDE to use your new Linkit One board, you can already clone this repository on your computer and access the MotoAlarmProject folder and open the <b>MotoAlarmProject.ino</b> file.

You need to download and install two libraries that are used in the project in the Arduino IDE:

[ArduinoJson in GitHub](https://github.com/bblanchon/ArduinoJson "ArduinoJson")

[elapsedMillis in GitHub](https://github.com/pfeerick/elapsedMillis "elapsedMillis")

The only class in which you need to add your data is in the <b>PublicConstants.h</b> class.

![MacDown Screenshot](Resources/ArduinoIDE.png)

Your configuration data is in this class, but you only need to add the following:

- The name of the device to connect by bluetooth with the iOS application. If you do not modify it in the application or in the device code, it will be 'MotoAlarmProject'.

```
// Device name
static char deviceNameForBluetooth[] = "MotoAlarmProject";
```

- To configure internet access from your Linkit One with your SIM card, you must add your operator's configuration. In my case, the APN property is orangeworld and the username and password are empty.

```
// APN
static char apnName[] = "apnName";
static char apnUser[] = "";
static char apnPassword[] = "";
```

- To receive SMS from your Linkit One, add your phone number in userPhone property.
- Once you download the app for iOS (iPhone and iPad) and register as a user, you must put your registration email and your password in the userMail and userPassword properties respectively, so that your Linkit One can get a session token and do requests sending the data to the server. Also, look at your user id in the application profile and put it in the userId property.

```
// User
static char* userPhone = "+34600000000";
static String userMail = "\"mail@mail.com\"";
static String userPassword = "\"userPassword\"";
static String userId = "userId";
```

You can now upload the code to your Linkit One!

### BOX FOR LINKIT ONE AND BATTERY WITH 4000mAh (Battery size: 7x100x70mm)

If you have a 3D printer or know someone who has it, here are the .stl files to print that I designed for the project:

![MacDown Screenshot](Resources/Box_4000_1.jpg)
![MacDown Screenshot](Resources/Box_4000_2.jpg)
![MacDown Screenshot](Resources/Box_4000_3.jpg)
![MacDown Screenshot](Resources/Box_4000_4.jpg)
![MacDown Screenshot](Resources/Box_4000_5.jpg)
![MacDown Screenshot](Resources/Box_4000_6.jpg)

[STL files in Thingeverse.com by me](https://www.thingiverse.com/thing:2835547 "STL files")

### BOX FOR LINKIT ONE AND BATTERY WITH 6000mAh (Battery size: 19x54x54mm)

If you have a 3D printer or know someone who has it, here are the .stl files to print that I designed for the project:

![MacDown Screenshot](Resources/Box_6000_1.jpg)
![MacDown Screenshot](Resources/Box_6000_2.jpg)
![MacDown Screenshot](Resources/Box_6000_3.jpg)
![MacDown Screenshot](Resources/Box_6000_6.jpg)
![MacDown Screenshot](Resources/Box_6000_5.jpg)
![MacDown Screenshot](Resources/Box_6000_4.jpg)

[STL files in Thingeverse.com by me](https://www.thingiverse.com/thing:2859090 "STL files")

### BATTERY WITH 4000mAh (EXAMPLE)

![MacDown Screenshot](Resources/Battery4000.jpg)

[Battery in 'Electrónica Embajadores' shop](https://www.electronicaembajadores.com/es/Productos/Detalle/BA1A3740/baterias-pilas-y-cargadores/baterias-de-polimero-de-litio/bateria-de-polimero-litio-3-7v-4000ma)

![MacDown Screenshot](Resources/Conector.jpg)

[Connector in 'Electrónica Embajadores' shop](https://www.electronicaembajadores.com/es/Productos/Detalle/CTK02HA02/conectores/conectores-poste-polarizado/conector-poste-2-00mm-hembra-aerea-2-contactos)

![MacDown Screenshot](Resources/Terminal.jpg)

[Terminal in 'Electrónica Embajadores' shop](https://www.electronicaembajadores.com/es/Productos/Detalle/CTK02TT/conectores/conectores-poste-polarizado/terminal-para-conector-poste-2-00mm-hembra)

### BATTERY WITH 6000mAh (EXAMPLE)

![MacDown Screenshot](Resources/Battery6000.jpg)

[Battery in 'BricoGeek' shop](http://tienda.bricogeek.com/baterias-lipo/418-bateria-lipo-6000mah-37v.html)

### INSTALLING IN YOUR MOTORBIKE

I have changed the original battery with 1000mAh for a battery with 6000mAh, so it lasts a lot longer without charging.

I added a usb charger to the battery in my motorcycle but in positive, that means that when I turn off the motorcycle it has no current, it only charges the powerbank when the motorcycle is on.

### DO YOU CAN'T THE DEVICE? ASK FOR MY HELP!

Don't worry, write me to my email and I can build it for you at the price of materials and shipping :)

### LICENSE

This project is free and use CC BY-SA.

![MacDown Screenshot](https://licensebuttons.net/l/by-sa/3.0/88x31.png)

This license lets others remix, tweak, and build upon your work even for commercial purposes, as long as they credit you and license their new creations under the identical terms. This license is often compared to “copyleft” free and open source software licenses. All new works based on yours will carry the same license, so any derivatives will also allow commercial use. This is the license used by Wikipedia, and is recommended for materials that would benefit from incorporating content from Wikipedia and similarly licensed projects.

[View License Deed](https://creativecommons.org/licenses/by-nd/4.0) | [View Legal Code](https://creativecommons.org/licenses/by-nd/4.0/legalcode)

### THANK YOU

Nothing else, if you want to improve the Linkit One code, do not hesitate to share it with me. For any question you have, you can write me to my email in the iOS application.

Thank you very much! I hope you like it!


##### ArtCC 2017++

# WiFi-Messagebox

Full project video can be found at: https://www.youtube.com/watch?v=rMLxC14VNs4

![WiFi Message Box](https://github.com/EngineeringDads/WiFi-Messagebox/blob/main/Thumbnail.jpg?raw=true")

# :love_letter: WiFi Message Box :love_letter:

Modified version of the alcohol shot gun. It's a game inspired by the traditional russian roulette, with a slight kink. The game uses an arduino nano to select a random player/s in a game where an alcohol shot in loaded. When it is the selected players turn, a piezo buzzer indicates that player is receiving the shot, before a servo motor pulls the trigger of the gun. The game is capped at a maximum of 15 players and must have more than one player to proceed.

Inspired by the amazon Lovebox, this is a custom made version designed to fulfil your lovers needs. This project uses an arduino programmed Weimos D1 mini with an ESP8266 to send messages through wifi. When your github gist is updated, the ESP8266 will detect the change in the line 'id' and trigger the servo motor that the love heart is connected to. The servo motor will then spin, until the message is read, which is detected by a photoresistor. The ESP8266 will scan the github every minute.

<img src="https://raw.githubusercontent.com/EngineeringDads/WiFi-Messagebox/main/Lovebox%20video_Moment.jpg" width="350" height="200"> <img src="https://raw.githubusercontent.com/EngineeringDads/WiFi-Messagebox/main/Hi.JPG" width="350" height="200">

## Materials

1. Weimos D1 mini
2. Photoresistor
3. Servo Motor
4. 10k resistor
5. PCB
6. OLED Display
7. Box for components (3D Printed)
8. Mini-usb cable
9. Male and Female header sockets

## Composition

Below is the schematic of the electronic components. The photoresister was programmed to detect light above a threshold of 300, which would update the arduino's memory as '1', unitl a new line id is received. All components were soldered to a PCB, and then wired using male and female header sockets. The components could have been directly soldered to the board, although since my PCB's were the perfect size for the box and i could 3D print around them, it made for a snug fit. The servo motor peaked through a whole in the box, where the loveheart was attached using the servo attachments (see STL files)

<img src="https://raw.githubusercontent.com/EngineeringDads/WiFi-Messagebox/main/Circuit.png" width="700" height="400">

## How it works

To program the game, we used the Arduino IDE. The LCD screen menu and selections were characterised by a 'count' for the number of times a button was selected. Different combinations of these selections dictated which menu was to be viewed, and how many players and shots per game. The select button was then used to send a character off to an analog seed, which would set the number of players and shots.

To program the game, i used the Arduino IDE. The OLED screen was programmed to display both text and binary images. A binary converted can be found here: https://www.dcode.fr/binary-image. The messages were sent using a private 'gist'. In the private gist, you will notice 3 lines. The first is a number, the second is a letter and the third is where you message begins. Let me explain - Each time you update the gist, you change the number, the ESP8266 will then detect the id change and then read the second line. If it detects a 't', it will draw a string based on the message. If it detects a 'b', it will draw the pixels everytime it detects a '1' in the message, thus displaying that respective image. I recommend editing your image in photoshop to be 128x64 pixels before uploading it to the board.

To duplicate this project, open the [WiFibox.ino](https://github.com/EngineeringDads/WiFi-Messagebox/blob/main/Code/WiFiBox.ino "WiFibox.ino") and upload it to the board, using your computer and a mini-usb cable.

# YOUR PROJECT TITLE
#### Video Demo:  [Arduino SHOOTER](https://www.youtube.com/watch?v=9pqOqYfGGoY)
#### Description:
You must have installed the Arduino IDE and, of course, an Arduino to play the game

Follow this schema:
![Circuitry](https://github.com/Zepelino/Arduino-SHOOTER/blob/main/circuitry.png)
The ideal was to key the speaker with a TIP120, but I don't have one, so it's going to be direct connected to the arduino

To make the program that was going to be uploaded to the Arduino, I used two libraries: the LiquidCrystal, that all the low level action to display things in the spaces in the lcd display; and the [PCM](https://github.com/damellis/PCM) library, that allows to play sounds that were previously encoded within an arduino - [here](https://www.instructables.com/Talking-Arduino-Playing-a-MP3-With-Arduino-Without/) you can find the encoder.

The code was divided into some header files. The `button.h` file has the `button` class, that initializes and handles the input of a button. The `entities.h` has the classes related with the entities in the game, such as the ship, called `Nave`, and so on. The `sound.h` has all the audio samples already encoded

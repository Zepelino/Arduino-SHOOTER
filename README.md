# YOUR PROJECT TITLE
#### Video Demo:  [Arduino SHOOTER](https://www.youtube.com/watch?v=9pqOqYfGGoY)
#### Description:

Arduino Shoother is a Shoot 'em up game made whithin an Arduino, it's a whole project including a circuitry and a program. Se, here goes some instructions:

#### How to make it run

You must have installed the Arduino IDE and, of course, an Arduino to play the game

Follow this schema:
![Circuitry](https://github.com/Zepelino/Arduino-SHOOTER/blob/main/circuitry.png)
The ideal was to key the speaker with a TIP120, but I don't have one, so it's going to be direct connected to the arduino

There are those three button to control things in the game: the red one is the action button that advances in the menus and shoots in the game. The white ones makes you move up and down in the lanes in the game. As well, there is that speaker to reproduce de sounds

#### Explaining the program

To make the program that was going to be uploaded to the Arduino, I used two libraries: the LiquidCrystal, that all the low level action to display things in the spaces in the lcd display; and the [PCM](https://github.com/damellis/PCM) library, that allows to play sounds that were previously encoded within an arduino - [here](https://www.instructables.com/Talking-Arduino-Playing-a-MP3-With-Arduino-Without/) you can find the encoder.

The code was divided into some header files. The `button.h` file has the `button` class, that initializes and handles the input of a button. The `entities.h` has the classes related with the entities in the game, such as the ship, called `Nave`, and so on. The `sound.h` has all the already encoded audio samples. The `sprite.h` has all the "sprites" used in the game by the lcd library.

The sound samples had to be too short due to the program memory limitation of the Arduino. And Because of this the program also uses a technique called object pooling, that basically is use and reuse the same objects once loaded in the start of the program to avoid dinamically alocate memory and take the risk of run out of memory - so, no arraylists containing al the entities to make it easier to iterate through all the objects, that's why all the objects are instaciated manually as well.



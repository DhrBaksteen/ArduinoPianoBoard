# Piano Keyboard Arduino Library
This library provides an easy to use interface from your Arduino code to the Cheerful Electronic Piano Board. It provides function to read the current state of the buttons as well as detecting transitions in button states. Several examples are provided that you can use to get familiar with the library or as the basis for your own projects.

## Installing the library
The easiest way to install the PianoKeys library is through the Arduino Library Manager in the Arduino IDE. To install the library open the IDE, click the *Shetch* menu and then *Include Library* > *Manage Libraries...*. This will open the Arduino Library Manager. In the window that appears search for *"Arduino Piano Board"* and click install. After installing you can start using the PianoKeys library and find its examples in the *File* > *Examples* menu. You can also refer to [this page](https://www.arduino.cc/en/guide/libraries) for more information about the Arduino Library Manager or how to install the library manually.

### Raspberry Pi installation
If you are using the library on your Raspberry Pi then you need to manually install it.

## Connecting the Piano Board
The Piano Board is connected to the SPI bus of your Arduino. The +5v and GND are connected to the respective pins.
| Board | Arduino Pin |
| --- | --- |
| `MISO` | 12 |
| `SCK` | 13 |
| `/SS`<sup>1</sup> | 10 |
| `BEEPER`<sup>2</sup> | 3 |

<sup>1</sup> The `/SS` line can be connected to any digital I/O pin. You can set it in the constructor.

<sup>2</sup> The `BEEPER` can be connected to any free digital pin that suits your project to use with the [`tone`](https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/) function. In the examples digital pin 3 is used. Connecting the `BEEPER` is optional. If you only want to use the Piano Board for its piano keys only, because you are providing your own audio source, such as the [OPL2 Audio Board](https://www.tindie.com/products/cheerful/opl2-audio-board/), then there is no need to connect this pin.

## Description of API
### Constructor `PianoKeys(const byte alternatePinSS)`
The `PianoKeys` library is initialized using the constructor. An instance of `PianoKeys` must be created before any of its functions can be used.

The optional parameter `alternatePinSS` may be provided if the `/SS` pin of the Piano Board is connected to a different Arduino pin than the default digital pin 10. For example when multiple SPI devices are connected. If this parameter is omitted then the library will use the default pin 10 for `/SS`.

### `void updateKeys()`
This function reads the current state of all button on the piano board and updates the internal button states. The `updateKeys` function must be called before `isKeyDown`, `wasKeyPressed`, `wasKeyReleased` or `getKeyState` is called.

### `bool isKeyDown(const byte key)`
The `isKeyDown` function will return `true` when the given `key` was held down at the time `updateKeys` was called. The parameter `key` is the index [0, 15]] or `KEY_C` through `KEY_USER_3` of the key to check.

### `bool wasKeyPresses(const byte key)`
The `wasKeyPressed` function will return `true` if the given `key` transitioned from being released to being pressed on the last call of `updateKeys`. The parameter `key` is the index [0, 15]] or `KEY_C` through `KEY_USER_3` of the key to check. 

Notice that this function will only notify about a change in key state. If during the next call to `updateKeys` the key is still held down then if will return `false` because the key did not transition from being released to being pressed.

### `bool wasKeyReleased(const byte key)`
This function is the opposite of `wasKeyPressed`. It will report `true` if the given `key` transitioned from being pressed to being released on the last call to `updateKeys`. The parameter `key` is the index [0, 15] or `KEY_C` through `KEY_USER_3` of the key to check.

Just as with `wasKeyPressed` this function will only notify about a change in state, so if the key remains released it will return `false` until the key transitions again from being pressed to being released.

### `unsigned int getKeyState()`
This function returns the state of all keys during the last call to `updateKeys` as a 16-bit number. Each bit represents one of the keys on the piano board where bit 0 represents `KEY_C` and bit 15 represents `KEY_USER_2`. A bit that is set (1) indicates that the key in question is not being pressed and a bit that is reset (0) indicates that the key is being held down. The function `getKeyMask` can be used to get a mask value for bit wise operations on the value obtained from `geyKeyState`.

### `unsigned int getKeyMask(cont byte key)`
This function returns a 16-bit number that can be used as a bit mask on the raw key state value that is obtained from `getKeyState`. The parameter `key` determines the index of the key [0, 15] for which we want to get the mask.

### Key indexes
The `PianoKeys.h` header file defines the following names for all of the keys on the piano board. These definitions may be used in any of the above functions that require a `key` parameter.

|Key|Definition|Value|   |Key|Definition|Value|
|--|--|--|--|--|--|--|
|C|`KEY_C`| 0||G#|`KEY_GS`|8|
|C#|`KEY_CS`|1||A|`KEY_A`| 9|
|D|`KEY_D`| 2||A#|`KEY_AS`|10|
|D#|`KEY_DS`|3||B|`KEY_B`| 11|
|E|`KEY_E`| 4||C|`KEY_C2`|12|
|F|`KEY_F`| 5||User 1|`KEY_USER_1`|13|
|F#|`KEY_FS`|6||User 2|`KEY_USER_2`|14|
|G|`KEY_G`| 7||User 3|`KEY_USER_3`|15|

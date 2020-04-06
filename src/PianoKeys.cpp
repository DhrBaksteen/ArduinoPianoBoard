/**
 * PianoKeys library for the Cheerful Electronis Piano Board.
 * Code by Maarten janssen (maarten@cheerful.nl) March 2020
 *
 *
 * This library provides an easy to use interface with the Piano Bard. It will read the key states and provides function
 * to detect whether keys were pressed, released and to read the current state of a key.
 *
 *
 * Connecting the Piano Board:
 *     Connect +5v and GND as indicated
 *     MISO - pin 12
 *     SCK  - pin 13
 *     /SS  - pin 10 (default)
 *     BEEPER - Optional, any free digital pin
 *
 * /SS can be set to an alternate pin using the alternate constructor. For example to use pin 7: PianoKeys piano(7);
 *
 *
 * Current version is v1.0.0, March 2020
 * Most recent version can be found on Github: https://github.com/DhrBaksteen/ArduinoPianoKeys
 */

#include <SPI.h>
#include "PianoKeys.h"


/**
 * Initialize the PionoKeys library with default /SS pin.
 */
PianoKeys::PianoKeys() {
  init();
}


/**
 * Initialize the PianoKeys library with alternate /SS pin.
 *
 * @param alternatePinSS - Alternate pin for /SS
 */
PianoKeys::PianoKeys(const byte alternatePinSS) {
  pinSS = alternatePinSS;
  init();
}


/**
 * Initialize the board.
 */
void PianoKeys::init() {
  pinMode(pinSS, OUTPUT);
  digitalWrite(pinSS, HIGH);
  SPI.begin();
}


/**
 * Read current state of the piano keyboard and update internal state.
 */
void PianoKeys::updateKeys() {
  oldKeyState = keyState;
  digitalWrite(pinSS, LOW);
  delayMicroseconds(5);
  keyState = SPI.transfer(0);
  keyState += (SPI.transfer(0) << 8);
  digitalWrite(pinSS, HIGH);
}


/**
 * Get the bit mask of the given key.
 *
 * @param key - Index of the key [0, 15] to get the key bit mask of.
 * @return The key's bit mask.
 */
unsigned int PianoKeys::getKeyMask(const byte key) {
  return 1 << (key % (KEY_USER_3 + 1));
}


/**
 * Get the current key state.
 *
 * @return The internal state of the piano keys after the last update.
 */
unsigned int PianoKeys::getKeyState() {
  return keyState;
}


/**
 * Was the given key pressed or held down during the last update?
 *
 * @param key - Index of the key [0, 15] to check.
 * @return True if the key was pressed during the last update.
 */
bool PianoKeys::isKeyDown(const byte key) {
  const unsigned int keyMask = getKeyMask(key);
  return (keyState & keyMask) == 0;
}


/**
 * Did the given key transition from being released to being pressed between the last two updates?
 *
 * @param key - Index of the key [0, 15] to check.
 * @return True if the key transitioned to being pressed.
 */
bool PianoKeys::wasKeyPressed(const byte key) {
  const unsigned int keyMask = getKeyMask(key);
  return (oldKeyState & keyMask) != 0 &&
    (keyState & keyMask) == 0;
}


/**
 * Did the given key transition from being pressed to being released between the last two updates?
 *
 * @param key - Index of the key [0, 15] to check.
 * @return True if the key transitioned to being released.
 */
bool PianoKeys::wasKeyReleased(const byte key) {
  const unsigned int keyMask = getKeyMask(key);
  return (oldKeyState & keyMask) == 0 &&
    (keyState & keyMask) != 0;
}

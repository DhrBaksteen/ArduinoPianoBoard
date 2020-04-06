/**
 * This is a demonstration sketch for the Cheerful Electronic Piano Board. You can use this skeych to debug the board
 * and try out the library functions. It will output debug messages to the serial monitor.
 *
 * Connecting the Piano Board:
 *     Connect +5v and GND as indicated
 *     MISO - pin 12
 *     SCK  - pin 13
 *     /SS  - pin 10
 *     BEEPER - Not connected
 *
 * /SS can be set to an alternate pin using the alternate constructor. For example to use pin 7: PianoKeys piano(7);
 *
 *
 * Code by Maarten Janssen (maarten@cheerful.nl) March 2020.
 * Most recent version can be found on Github: https://github.com/DhrBaksteen/ArduinoPianoKeys
 */

#include <PianoKeys.h>


const String keyNames[16] = {
	"C", "C#", "D", "D#",
	"E", "F", "F#", "G",
	"G#", "A", "A#", "B",
	"C2", "User 1", "User 2", "User 3"
};

PianoKeys piano;


void setup() {
	Serial.begin(9600);
	Serial.println("Press Piano Board keys to test!\n");
}


void loop() {
	// Read and update key states.
	piano.updateKeys();

	for (int i = KEY_C; i <= KEY_USER_3; i ++) {
		// Notify about keys that got pressed.
		if (piano.wasKeyPressed(i)) {
			Serial.print("Key ");
			Serial.print(keyNames[i]);
			Serial.println(" pressed");
		}

		// Notify about keys that got released.
		if (piano.wasKeyReleased(i)) {
			Serial.print("Key ");
			Serial.print(keyNames[i]);
			Serial.println(" released");
		}
	}

	// Print key state as a 16-bit integer;
	// Serial.println(piano.getKeyState());

	// Filter key state for keys F and G (0 indicates that the key is held down).
	// Serial.println(piano.getKeyState() & piano.getKeyMask(KEY_F));
	// Serial.println(piano.getKeyState() & piano.getKeyMask(KEY_G));

	// Show whether the C key is pressed (1 indicates that the key is held down).
	// Serial.println(piano.isKeyDown(KEY_C));

	delay(20);
}

/**
 * This is a demonstration sketch for the Cheerful Electronic Piano Board. You can use this as a base sketch to create a
 * piano. This sketch uses the tone command to produce tones through the Piano Board's build-in beeper. User keys are
 * used for the following functions:
 *     User 1 - Decrease octave
 *     User 2 - Increase ovtave
 *     User 3 - Enabel / disable vibrato effect
 *
 * Connecting the Piano Board:
 *     Connect +5v and GND as indicated
 *     MISO - pin 12
 *     SCK  - pin 13
 *     /SS  - pin 10
 *     BEEPER - pin 3
 *
 * /SS can be set to an alternate pin using the alternate constructor. For example to use pin 7: PianoKeys piano(7);
 * BEEPER can be connected to a different pin by changing the PIN_BEEPER definition below.
 *
 *
 * Code by Maarten Janssen (maarten@cheerful.nl) March 2020.
 * Most recent version can be found on Github: https://github.com/DhrBaksteen/ArduinoPianoKeys
 */

#include <PianoKeys.h>

#define PIN_BEEPER 3

PianoKeys piano;
const int frequencies[13] = { 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523 };
const float fMultiples[7] = { 0.125, 0.25, 0.5, 1.0, 2.0, 4.0, 8.0 };
int octave = 3;
int frequency = 0;
bool vibrato = false;


void setup() {
}


void loop() {
	bool anyKeyPressed = false;
	piano.updateKeys();

	// Handle keys that are being pressed or held down.
	for (int i = KEY_C; i <= KEY_C2; i ++) {
		// Start playing a note if key is being pressed.
		if (piano.wasKeyPressed(i)) {
			frequency = frequencies[i] * fMultiples[octave] ;
			tone(PIN_BEEPER, frequency);
		}

		// Register when piano keys are held down.
		if (piano.isKeyDown(i)) {
			anyKeyPressed = true;
		}
	}

	// If no more piano keys are pressed then stop all sound.
	if (!anyKeyPressed) {
		noTone(PIN_BEEPER);
		frequency = 0;
	}

	// Lower the octave when user key 1 is pressed.
	if (piano.wasKeyPressed(KEY_USER_1) && octave > 0) {
		octave --;
	}

	// Raise the octave when user key 2 is pressed.
	if (piano.wasKeyPressed(KEY_USER_2) && octave < 6) {
		octave ++;
	}

	// Toggle vibrato when user key 3 is pressed.
	if (piano.wasKeyPressed(KEY_USER_3)) {
		vibrato = !vibrato;
		if (!vibrato) {
			tone(PIN_BEEPER, frequency);
		}
	}

	// Apply vibrato when enabled.
	if (vibrato && frequency) {
		tone(PIN_BEEPER, frequency + (sin(millis() / 25) * 10));
	}

	delay(20);
}

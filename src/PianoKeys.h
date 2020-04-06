
#ifndef PIANO_KEYS_LIB_H_
  #define PIANO_KEYS_LIB_H_

  #define KEY_C  0
  #define KEY_CS 1
  #define KEY_D  2
  #define KEY_DS 3
  #define KEY_E  4
  #define KEY_F  5
  #define KEY_FS 6
  #define KEY_G  7
  #define KEY_GS 8
  #define KEY_A  9
  #define KEY_AS 10
  #define KEY_B  11
  #define KEY_C2 12
  #define KEY_USER_1 13
  #define KEY_USER_2 14
  #define KEY_USER_3 15

  #define DEFAULT_PIN_SS 10


  class PianoKeys {
    public:
      PianoKeys();
      PianoKeys(const byte alternatePinSS);
      void updateKeys();
      unsigned int getKeyMask(const byte key);
      unsigned int getKeyState();
      bool isKeyDown(const byte key);
      bool wasKeyPressed(const byte key);
      bool wasKeyReleased(const byte key);
    private:
      byte pinSS = DEFAULT_PIN_SS;
      unsigned int keyState = 0xFFFF;
      unsigned int oldKeyState = 0xFFFF;

      void init();
  };

#endif
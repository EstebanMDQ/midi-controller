
int pines[] = {8, 9, 10, 11};
int estados[] = {LOW, LOW, LOW, LOW};
int controles[] = {20, 21, 22, 23}; 
long debounces[] = {0, 0, 0, 0};
long debounceDelay = 50;    // the debounce time; increase if the output flickers


// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

//void noteOn(byte channel, byte pitch, byte velocity) {
//  MIDIEvent noteOn = {0x09, 0x90 | channel, pitch, velocity};
//  MIDIUSB.write(noteOn);
//}

//void noteOff(byte channel, byte pitch, byte velocity) {
//  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
//  MIDIUSB.write(noteOff);
//}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  MIDIEvent event = {0x0B, 0xB0 | channel, control, value};
  MIDIUSB.write(event);
}

void loop() {
//  noteOn(0, 48, 64);   // Channel 0, middle C, normal velocity
//  MIDIUSB.flush();
//  delay(500);
//
//  noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
//  MIDIUSB.flush();
//  delay(1500);
  unsigned long t = millis();
  int btn = 0;
  int val;
  for( int i = 0; i < 4 ; i++ ){
    btn = digitalRead(pines[i]);
    if( btn != estados[i] && debounces[i] < t) { 
      estados[i] = btn;
      debounces[i] = t + debounceDelay;
      if( btn == HIGH ) {
        val = 127;
      } else {
        val = 0;
      }
      controlChange(0, controles[i], val); 
      digitalWrite(13, HIGH);
    }
  }
  MIDIUSB.flush();
  digitalWrite(13, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  for( int i = 0; i < sizeof(pines) ; i++ ){
    pinMode(pines[i], INPUT);
  }
  
}


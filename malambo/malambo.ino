
//  configurations

// pins to be used as input
int pins[] = {8, 9, 11};

// current state for each output
int pinStatus[][3] = {
  {LOW, LOW, LOW},
  {LOW, LOW, LOW},
  {LOW, LOW, LOW}
};

// output command to use for each input
int midiControls[][3] = {
  {20, 21, 22},
  {23, 24, 25},
  {26, 27, 28}
};

// helper variables to debounce each button independently
long debounces[][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
};  

// debounce time
long debounceDelay = 50;    // the debounce time; increase if the output flickers


// bank change related config
int bankPin = 10;
int currentBank = 0;
long debounceBank = 0;

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

// function to send a control midi command
void controlChange(byte channel, byte control, byte value) {
  MIDIEvent event = {0x0B, 0xB0 | channel, control, value};
  MIDIUSB.write(event);
}

void loop() {
  unsigned long t = millis();
  int btn = 0;
  int val;
  
  // read bank change button
  btn = digitalRead(bankPin);
  if( btn == HIGH && debounceBank < t) {
    debounceBank = t + debounceDelay;
    currentBank += 1;
    if( currentBank > 2){
      currentBank = 0;
    }
  }  
  
  // read each button state
  for( int i = 0; i < 3 ; i++ ){
    btn = digitalRead(pins[i]);
    // check if the button changed state and debounce time has passed
    if( btn != pinStatus[currentBank][i] && debounces[currentBank][i] < t) {
      pinStatus[currentBank][i] = btn;
      debounces[currentBank][i] = t + debounceDelay;
      if( btn == HIGH ) {
        val = 127;
      } else {
        val = currentBank;
      }
      // send control change command
      controlChange(0, midiControls[currentBank][i], val);
      continue;
      // flash a led, just because we can
//      digitalWrite(13, HIGH);
    }
  }
  // flush midi commands
  MIDIUSB.flush();
  digitalWrite(13, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(bankPin, INPUT);
  for( int i = 0; i < sizeof(pins) ; i++ ){
    pinMode(pins[i], INPUT);
  }

}


const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to
const int blynk = 3;
// Variables will change:

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

int buttonStateB = 0;         // current state of the button
int lastButtonStateB = 0;     // previous state of the button



void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}
bool estado = true;

void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  buttonStateB = digitalRead(blynk);

  // compare the buttonState to its previous state
  if ((buttonState != lastButtonState)) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      estado = !estado;
      digitalWrite(ledPin, estado);
      if (estado)Serial.println("led encendido");
      else Serial.println("Led apapagado");
      Serial.println();
    }
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
///////////////////////////////////////////////////////////////////////////////////////
  // compare the buttonState to its previous state
  if ((buttonStateB != lastButtonStateB)) {
    // if the state has changed, increment the counter
    if (buttonStateB == HIGH) {
      estado = true;
    }
    else {
      estado = false;
    }
    digitalWrite(ledPin, estado);
    if (estado)Serial.println("led encendido 1");
    else Serial.println("Led apapagado 1");
    Serial.println();
  }

  // save the current state as the last state, for next time through the loop
  lastButtonStateB = buttonStateB;

///////////////////////////////////////////////////////////////////////////////////////


}

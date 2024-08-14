//Charging State Detector (CSD)
// The purpose of this program is to detect a device's Charging State.
// In Serial Monitor, send 0 or 1 to toggle Debug Mode.
// CSD: Send "Charging" or "Disconnected" when ezyCart Pogo Charger is connected or disconnected

const int analogPinCSD =  28; //PB1;
int chargingState = 0;
int isDebug = 1; 
int ADCValueCSD = 0;

// Function to calculate voltage CSD based on REFERENCE_VOLTAGE
double calculateVoltageCSD(int ADCValueCSD) {
  return REFERENCE_VOLTAGE * (ADCValueCSD / 1023.0); // 12-bit ADC for pico: 4095    // /1024.0 
}

void setup() {
  Serial.begin(9600);
 // analogReadResolution(12); // set 12-bit ADC reading for pico
  Serial.println("Setup Complete");
}

void loop() {
  // Read ADC values
  ADCValueCSD = analogRead(analogPinCSD);

  // Update Charging State based on ADCValueCSD
  if (ADCValueCSD < 100) {
    chargingState = 0; // Disconnected
  } else {
    chargingState = 1; // Charging
  }

  // Handle debug mode user input
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    //String incomingChar = Serial.readString();
    Serial.print("Received: ");
    Serial.println(incomingChar);

    if (incomingChar == '1') {
      isDebug = 1;
      Serial.println("Debug mode ON");
    } else if (incomingChar == '0') {
      isDebug = 0;
      Serial.println("Debug mode OFF");
    }
  }

  // Print data
  if (isDebug) {
    Serial.print("  ADC Value CSD: ");
    Serial.print(ADCValueCSD);
    Serial.print("  Charging State: ");
    Serial.println(chargingState);
  } else {

    Serial.print("1,");
    Serial.print(ADCValueCSD);
    Serial.println(",");
    Serial.print("2,");
    Serial.println(chargingState);
  }

  delay(100); // Add a delay between readings  
}

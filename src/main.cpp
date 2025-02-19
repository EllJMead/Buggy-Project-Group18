/*
#include "mbed.h"
#include "QEI.h"
#include "C12832.h"

// Define Encoder CPR
#define CPR 2048

// Create QEI objects for both encoders
QEI encoderLeft(PC_2, PC_3, NC, 1024, QEI::X4_ENCODING);  // Left Wheel Encoder
QEI encoderRight(PB_13, PB_14, NC, 1024, QEI::X4_ENCODING); // Right Wheel Encoder

// Initialize LCD (C12832)
C12832 lcd(D11, D13, D12, D7, D10); // SPI Pins for LCD

// Motor control pins
DigitalOut enable(PB_12);
DigitalOut direction1(PC_5);
DigitalOut direction2(PA_12);
DigitalOut bipolarR(PA_13);
DigitalOut bipolarL(PA_14);
PwmOut motor_pwm_R(PC_6); // PWM for Right Wheel
PwmOut motor_pwm_L(PA_11); // PWM for Left Wheel

// Potentiometers for speed control
AnalogIn potentiometerL(A0); // Potentiometer for Left Wheel
AnalogIn potentiometerR(A1); // Potentiometer for Right Wheel

// Timer for calculating RPM
Ticker rpm_ticker;

// Timer for LCD updates
Ticker display_update;

// Global variables for RPM calculation
volatile int lastLeftPulses = 0;
volatile int lastRightPulses = 0;
volatile float leftRPM = 0.0;
volatile float rightRPM = 0.0;

// Function to calculate RPM every second
void calculateRPM() {
    // Get current pulse counts
    int currentLeftPulses = encoderLeft.getPulses();
    int currentRightPulses = encoderRight.getPulses();

    // Calculate pulses per second
    int leftPulsesPerSecond = currentLeftPulses - lastLeftPulses;
    int rightPulsesPerSecond = currentRightPulses - lastRightPulses;

    // Convert to RPM
    leftRPM = ((float)leftPulsesPerSecond / CPR) * 60.0;
    rightRPM = ((float)rightPulsesPerSecond / CPR) * 60.0;

    // Store current pulses for next calculation
    lastLeftPulses = currentLeftPulses;
    lastRightPulses = currentRightPulses;
}

// Function to update the LCD display
void updateLCD() {
    // Clear  screen  once at the beginning
    static bool firstRun = true;
    if (firstRun) {
        lcd.cls();
        firstRun = false;
    }

    // Display pulse counts on the first line
    lcd.locate(0, 0);
    lcd.printf("L: %d  R: %d", encoderLeft.getPulses(), encoderRight.getPulses());

    // Display RPM values
    lcd.locate(0, 10); // display on line 2
    lcd.printf("L: %.2f RPM  R: %.2f RPM", leftRPM, rightRPM);

    // Display PWM duty cycles (we can remove if we want)
    lcd.locate(0, 20); // display on line 3
    lcd.printf("PWM L: %.2f  R: %.2f", motor_pwm_L.read(), motor_pwm_R.read());
}

int main() {
    // Initialize motor driver
    enable = 1;     // Enable motor driver
    bipolarR = 0;    // Set unipolar
    bipolarL = 0;    // Set unipolar
    direction1 = 1;  // Set direction (1 = forward, 0 = reverse)
    direction2 = 1;  // Set direction (1 = forward, 0 = reverse)
    motor_pwm_L.period_us(50); // 20kHz PWM frequency, most likely frequency with not too much noise
    motor_pwm_R.period_us(50); // 20kHz PWM frequency, not much noise same goes for this

    // Initialize LCD
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Initializing...");

    // Run RPM calculation every 1 second
    rpm_ticker.attach(&calculateRPM, 1.0);

    // Refresh LCD every 500ms (adjust as needed)
    display_update.attach(&updateLCD, 0.5);

    while (1) {
        // Read potentiometers and set PWM duty cycles
        float dutyLeft = potentiometerL.read();  // Read left potentiometer scale (0.0 to 1.0)
        float dutyRight = potentiometerR.read(); // Read right potentiometer scale (0.0 to 1.0)

        // Set PWM duty cycles (0.0 = stop, 1.0 = full speed), duty cycles are like one and of for long times
        motor_pwm_L.write(dutyLeft); // duty signal for left motor
        motor_pwm_R.write(dutyRight); // duty signal for right motor

        wait_us(100000); // Small delay, so smooth things out (0.1s)
    }
}
*/

#include "mbed.h" //Include the Mbed libraries
class LED //Begin LED class definition
{
protected: //Protected (Private) data member declaration
 DigitalOut outputSignal; //Declaration of DigitalOut object
 bool status; //Variable to recall the state of the LED
public: //Public declarations
 LED(PinName pin) : outputSignal(pin){off();} //Constructor - user provided pin name is assigned to the DigitalOut
 void on(void) //Public member function for turning the LED on
 {
 outputSignal = 0; //Set output to 0 (LED is active low)
 status = true; //Set the status variable to show the LED is on
 }
 void off(void) //Public member function for turning the LED off
 {
 outputSignal = 1; //Set output to 1 (LED is active low)
 status = false; //Set the status variable to show the LED is off
 }
 void toggle(void) //Public member function for toggling the LED
 {
 if (status) //Check if the LED is currently on
 off(); //Turn off if so
 else //Otherwise...
 on(); //Turn the LED on
 }
 bool getStatus(void) //Public member function for returning the status of the LED
 {
 return status; //Returns whether the LED is currently on or off
 }
};
int main() //Begin main function
{
 LED redLED(D5); //Create an object from the LED class. Associated with pin D5
 while(1) { //Begin infinite loop - IMPORTANT
 redLED.toggle(); //Toggle the LED
 wait_us(500000); //Wait for 0.5 seconds
 } //Loop infinitely
}
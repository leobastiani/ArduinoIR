/**
 * Copyright (c) 2017 Ehsan Zaery Moghaddam (zaerymoghaddam@gmail.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
//  Include following libraries to access IR sensor
#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 7;          //  The digital pin that the signal pin of the sensor is connected to
int VCC = 5;
int GND = 6;
IRrecv receiver(RECV_PIN);  //  Create a new receiver object that would decode signals to key codes
decode_results results;     //  A varuable that would be used by receiver to put the key code into

void setup() {
  Serial.begin(9600);       //  Setup serial port to send key codes to computer
  receiver.enableIRIn();    //  Enable receiver so that it would start processing infrared signals
  // pinos de saída para deixar o sensor apenas na placa do arduino
  pinMode(VCC, OUTPUT);
  pinMode(GND, OUTPUT);
  // agora escreve neles
  digitalWrite(GND, LOW);
  digitalWrite(VCC, HIGH);
}

void loop() {
  if(receiver.decode(&results)) {             //  Decode the button code and put it in "results" variable
    Serial.println(results.value, HEX);       //  Print the code as a hexadecimal value
    receiver.resume();                        //  Continue listening for new signals
  }
}


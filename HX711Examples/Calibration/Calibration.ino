/*
 Calibration of Breadbot using HX711 with loadcell and ESP8266 
 By: Toni Rosemann
 Date: November 11th, 2019

 On basis of https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all 

 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
*/

#include "HX711.h" 

HX711 scale; 

float calibration_factor = 405.94; //calibration value 2019-01-11
float offset             = 322342; 

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("Then put up to 3 beer bottles in defined order on the scale and compare with reference");
  
  scale.begin(4, 5); //GPIO4 is Data, GPIO5 is Serial Clock SCK
  scale.set_scale(calibration_factor);
  scale.set_offset(offset); //set fix offset for breadbot
  
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //this should equal almost the offset value with no load on the scale
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  Serial.print(scale.get_units(10), 3); //we use average of 10 values, and 3 decimal places
  Serial.print(" g"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.print(" GetOffset: ");
  Serial.print(scale.get_offset());
  Serial.println();  
}


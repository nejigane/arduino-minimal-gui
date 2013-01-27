#include <SPI.h>
#include <ListView.h>
#include <SliderView.h>

volatile bool rotating = false;
volatile bool clicked = false;
int8_t count = 0;
minimal::ListView view("Menu");

void setup() {
  Serial.begin(9600);
  minimal::AD12864SPI::begin(9, 8, 7);
  
  view.addItem(new minimal::SliderView("Port"));
  view.addItem("Sensors", onPress);
  view.addItem("Settings", onPress);
  view.draw();
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  digitalWrite(2, HIGH);
  digitalWrite(5, HIGH);
  attachInterrupt(0, onFall, FALLING);
  attachInterrupt(1, onClick, FALLING);
}

void loop() {
  if (clicked) {
    view.click();
    view.draw();
    delay(100);
    clicked = false;
  }
  if (rotating) {
    delay(2);
    if (digitalRead(2) == digitalRead(5)) {  
      count--;
    } 
    else {                                   
      count++;
    }
    rotating = false;
  }
  if (count >= 2) {
    count = 0;
    view.forward();
    view.draw();
    tone(6, 9600, 5);
  }
  if (count <= -2) {
    count = 0;
    view.backward();
    view.draw();
    tone(6, 9600, 5);
  }
}

void onPress(const char* name) {
  Serial.println(name);
}

void onFall() {
  rotating = true;
}

void onClick() {
  clicked = true;
}


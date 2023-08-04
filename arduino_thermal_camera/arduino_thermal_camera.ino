// Arduino UNO infrared camera using AMG8833 infrared sensor and SunFounder 8x8 RGB LED Display
// created by upir 2023
// youtube channel: www.youtube.com/upir_upir

// Youtube video: https://youtu.be/cKRsBncP3Vo

// Links from the video:
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
// AMG8833 infrared sensor: https://s.click.aliexpress.com/e/_DliMiMb
// SunFounder 8x8 RGB LED Display: https://s.click.aliexpress.com/e/_DFzrJab
// AMG8833 IR 8*8 Mini Module: https://s.click.aliexpress.com/e/_DczEQ5d
// Infrared documentation: https://learn.adafruit.com/adafruit-amg8833-8x8-thermal-camera-sensor/arduino-wiring-test
// SunFounder 8x8 RGB LED documentation: http://wiki.sunfounder.cc/index.php?title=Full_Color_RGB_LED_Matrix_Driver_Shield_%2B_RGB_Matrix_Screen
// Colorduino library: https://github.com/frederickk/Colorduino

// Looking for a bigger resolution? Try the InfiRay P2 Pro, and get 10% discount with code P2PRO0602
// https://www.pergear.com/products/infiray-p2-pro



#include <Wire.h> // IIC communication
#include <Adafruit_AMG88xx.h> // AMG8833 sensor for measuring temperatures
#include <Colorduino.h> // colorduino library for displaying on SunFounder 8x8 RGB LED display

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE]; // measured temperatures

void setup() {
    
    Colorduino.Init(); // initialize the 8x8 RGB LED display
    Serial.begin(9600); // start serial communication
    Serial.println(F("AMG88xx pixels"));

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
}


void loop() { 
    //read all the pixels
    amg.readPixels(pixels);

/*    Serial.print("[");
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      Serial.print(pixels[i-1]);
      Serial.print(", ");
      if( i%8 == 0 ) Serial.println();
    }
    Serial.println("]");
    Serial.println();*/

    ColorRGB colorRGB; // red green blue color
    ColorHSV colorHSV; // hue saturation brigtness color

    // set every RGB LED on the 8x8 display
    for(int y = 0; y < ColorduinoScreenHeight; y++) {
      for(int x = 0; x < ColorduinoScreenWidth; x++) {
        
          colorHSV.h = map(pixels[y * 8 + x], 15, 30, 0, 255); // map the temperature to hue value
          colorHSV.s=255;  // maximum saturation
          colorHSV.v=255;  // maximum brightness
          Colorduino.HSVtoRGB(&colorRGB, &colorHSV); // convert hue saturation brightness values to red green and blue values
          
          Colorduino.SetPixel(x, y, colorRGB.r, colorRGB.g, colorRGB.b); // set the pixel
        }
    }
  
    Colorduino.FlipPage(); // swap screen buffers to show it    

    // small delay
    delay(100);
}

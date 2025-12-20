#include <Adafruit_NeoPixel.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define PIN_WS2812B D6  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_LEDS    15  // The number of LEDs (pixels) on WS2812B LED strip

#define JOY_X A0     // Analog input for X-axis
#define JOY_SW D1

Adafruit_NeoPixel strip(NUM_LEDS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
ESP8266WebServer  server(80);

const char* ssid = "ESP8266_AP";
const char* pswd = "123456789#";

// ----- STATE -----
int speedDelay = 1000;
int r = 255, g = 0, b = 0;
bool animationOn = true;
bool clientConnected = false;

bool first = true;

int currentLED = 0;
unsigned long lastUpdate = 0;
int static_index = 1;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  WiFi.disconnect(true);   // clear previous settings
  WiFi.mode(WIFI_AP_STA);      // force AP mode
  delay(100);

  bool success = WiFi.softAP(ssid, pswd);
  Serial.println(success ? "\nAP started" : "\nAP failed!");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());


  // Connecting to the homw wifi
  /**WiFi.begin(ssid, pswd);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected. IP: " + WiFi.localIP().toString());**/
  
  /* // SERVER
  server.on("/", []() {
    String html = "<h1>ESP8266 LED Control</h1>";
    html += "<a href=\"/on\"><button>Start Chase</button></a><br>";
    html += "<a href=\"/off\"><button>Stop</button></a>";
    server.send(200, "text/html", html);
  });

  server.on("/on", []() {
    animationOn = true;
    server.send(200, "text/html", "<h1>Chase Started</h1><a href='/'>Back</a>");
  });

  server.on("/off", []() {
    animationOn = false;
    strip.clear();
    strip.show();
    server.send(200, "text/html", "<h1>Stopped</h1><a href='/'>Back</a>");
  });

  server.begin(); */

  // Web routes
  server.on("/", []() {
    String html = "<h1>LED Control</h1>";
    html += "<form action='/set' method='get'>";
    html += "Speed: <input type='range' min='50' max='1000' name='speed' value='" + String(speedDelay) + "'><br>";
    html += "Color: <input type='color' name='color' value='#" + String(toHex(r, g, b)) + "'><br>";
    html += "<input type='submit' value='Update'>";
    html += "</form>";
    server.send(200, "text/html", html);
  });

  server.on("/set", []() {
    if (server.hasArg("speed")) {
      speedDelay = server.arg("speed").toInt();
      Serial.println("Speed set via app: " + String(speedDelay));
    }
    if (server.hasArg("color")) {
      String hex = server.arg("color");
      long number = strtol(&hex[1], NULL, 16);
      r = (number >> 16) & 0xFF;
      g = (number >> 8) & 0xFF;
      b = number & 0xFF;
      Serial.printf("Color set via app: R%d G%d B%d\n", r, g, b);
    }
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();

  strip.begin();
  strip.show();

  //JOYSTICK
  pinMode(JOY_SW, INPUT_PULLUP);
}

void loop() {
  server.handleClient();

  clientConnected = true;
  Serial.println("Phone connected! Starting joystick + LED control...");
  
  handleJoystick();
  updateAnimation();

  /* if (animationOn) {
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.clear();
      strip.setPixelColor(i, strip.Color(255, 0, 0));
      strip.show();
      delay(1000);
    }

    for (int i = NUM_LEDS - 2; i > 0; i--) {
      strip.clear();
      strip.setPixelColor(i, strip.Color(255, 0, 0));
      strip.show();
      delay(1000);
    }
  } */

  /* // --- Joystick Handling ---
  int xValue = analogRead(JOY_X); // 0–1023
  if (xValue < 400) {
    speedDelay = 2000; // slow
    Serial.println("LEFT");
  } else if (xValue > 600) {
    speedDelay = 100; // fast
    Serial.println("RIGHT");
  } else {
    // leave current
    Serial.println("CENTER");
  }

  if (digitalRead(JOY_SW) == LOW) {
    animationOn = !animationOn;
    delay(200); // debounce
  }

  // --- Animation ---
  if (animationOn) {
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.clear();
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.show();
      delay(speedDelay);
    }

    for (int i = NUM_LEDS - 2; i > 0; i--) {
      strip.clear();
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.show();
      delay(speedDelay);
    }
  } */

  // JOYSTICK
  /**int xValue = analogRead(JOY_X);   // range: 0–1023
  int button = digitalRead(JOY_SW);

  // Detect X-axis direction
  if (xValue < 400) {
    Serial.println("LEFT");
  } else if (xValue > 600) {
    Serial.println("RIGHT");
  } else {
    Serial.println("CENTER");
  }

  // Detect button click
  if (button == LOW) {
    Serial.println("CLICK");
  }

  delay(200); // small debounce**/
}

// ----- Joystick -----
void handleJoystick() {
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck < 50) return; // check every 50ms
  lastCheck = millis();

  int xValue = analogRead(JOY_X);

  // --- LEFT / RIGHT handling ---
  static bool moved = false;  

  if (xValue < 400 && !moved) {       // LEFT
    speedDelay = min(speedDelay * 2, 2000); 
    Serial.println("Joystick LEFT → Slower speed: " + String(speedDelay));
    moved = true;
  } 
  else if (xValue > 600 && !moved) {  // RIGHT
    speedDelay = max(speedDelay / 2, 100);
    Serial.println("Joystick RIGHT → Faster speed: " + String(speedDelay));
    moved = true;
  } 
  else if (xValue >= 400 && xValue <= 600) {
    moved = false; 
  }

  // --- Joystick Button ---
  static unsigned long lastPress = 0;
  if (digitalRead(JOY_SW) == LOW && millis() - lastPress > 200) {
    animationOn = !animationOn;
    Serial.println(animationOn ? "Animation ON" : "Animation OFF");
    lastPress = millis(); // debounce via millis
  }

  yield(); // let WiFi handle its stuff
}


// ----- Animation -----
void updateAnimation() {
  if (!animationOn) return;

  unsigned long now = millis();
  if (now - lastUpdate >= (unsigned long)speedDelay) {
    lastUpdate = now;

    strip.clear();
    strip.setPixelColor(currentLED, strip.Color(r, g, b));
    strip.show();

    if (currentLED >= NUM_LEDS - 1 && static_index != -1) {
      static_index = -1;
    }
    
    if (currentLED == 0 && static_index != 1) {
      static_index = 1;
    }

    currentLED += static_index;
  }
}

// ----- Helpers -----
String toHex(int r, int g, int b) {
  char hex[7];
  sprintf(hex, "%02X%02X%02X", r, g, b);
  return String(hex);
}

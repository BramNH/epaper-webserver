#include <Arduino.h>
#include <WiFi.h>
#include <html.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// 2.13'' EPD Module
// GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display(GxEPD2_213_BN(/*CS=5*/ 5, /*DC=*/ 0, /*RES=*/ 2, /*BUSY=*/ 15)); // DEPG0213BN 122x250, SSD1680
GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> display(GxEPD2_213_Z98c(/*CS=5*/ 5, /*DC=*/17, /*RES=*/16, /*BUSY=*/4)); // GDEY0213Z98 122x250, SSD1680

const char *ssid = "ESP32-Access-Point";
const char *password = "test1234";
WiFiServer server(80);

void drawNameDateReason(const char name[], const char reason[], const char date[])
{
  display.setRotation(1); // set rotation to 1 (rotate right 90 degrees) to have enough space on small displays (landscape)
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby;
  uint16_t tbw, tbh;

  display.setFullWindow();
  // here we use paged drawing, even if the processor has enough RAM for full buffer
  // so this can be used with any supported processor board.
  // the cost in code overhead and execution time penalty is marginal
  // tell the graphics class to use paged drawing mode
  display.firstPage();
  do
  {
    // this part of code is executed multiple times, as many as needed,
    // in case of full buffer it is executed once
    // IMPORTANT: each iteration needs to draw the same, to avoid strange effects
    // use a copy of values that might change, don't read e.g. from analog or pins in the loop!
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 20);
    // display.setCursor(x, y - tbh);
    display.print(name);
    display.setTextColor(GxEPD_BLACK);
    display.print(reason);

    display.getTextBounds(date, 0, 0, &tbx, &tby, &tbw, &tbh);
    display.setCursor(0, display.height() - tbh);
    display.setTextColor(GxEPD_RED);
    display.print(date);

    // tell the graphics class to transfer the buffer content (page) to the controller buffer
    // the graphics class will command the controller to refresh to the screen when the last page has been transferred
    // returns true if more pages need be drawn and transferred
    // returns false if the last page has been transferred and the screen refreshed for panels without fast partial update
    // returns false for panels with fast partial update when the controller buffer has been written once more, to make the differential buffers equal
    // (for full buffered with fast partial update the (full) buffer is just transferred again, and false returned)
  } while (display.nextPage());
}

// Function to extract parameters from the GET request
String getParameterFromRequest(String request, String param)
{
  String paramPattern = param + "=";
  int paramStart = request.indexOf(paramPattern);
  if (paramStart == -1)
  {
    return ""; // Parameter not found
  }
  paramStart += paramPattern.length();
  int paramEnd = request.indexOf("&", paramStart);
  if (paramEnd == -1)
  {
    paramEnd = request.indexOf(" ", paramStart); // Look for the end of the request line
  }
  String p = request.substring(paramStart, paramEnd);
  p.replace('+', ' ');
  return p;
}

void setup()
{
  // Connect to Wi-Fi network with SSID and password
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  server.begin();
  
  display.init(115200);
}

void loop()
{
  WiFiClient client = server.accept(); // Listen for incoming clients
  if (client)
  {
    // Give the client time to send the data
    while (client.connected() && !client.available())
    {
      delay(1);
    }
    String request = client.readStringUntil('\r');

    // Parse the GET request and extract parameters
    String name = getParameterFromRequest(request, "name") + "\n";
    String date = getParameterFromRequest(request, "date");
    String reason = getParameterFromRequest(request, "reason");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();

    if (name.length() != 0 && date.length() != 0)
    {
      client.println(html_confirm_page);
      drawNameDateReason(name.c_str(), reason.c_str(), date.c_str());
    }
    else 
    {
      client.println(html_input_page);
      client.println();
    }
    // Close the connection
    client.stop();
  }
}
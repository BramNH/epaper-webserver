# E-Paper Webserver ESP32
A webserver with a simple input form page which input is printed onto an WeactStudio E-Paper display.

Published for basic WeactStudio E-Paper control. The one used in this project is a 2.13 inch 3 color (Black/White/Red) display. 
See https://github.com/ZinggJM/GxEPD2/tree/master/examples for more examples on different types and brands of E-paper displays. 

## Hardware connection

 <table>
  <tr>
    <td>

| E-Paper    | ESP32 Devkit V1 |
| --------   | ------- |
| BUSY    | 4    |
| RESET    | 16    |
| DC       | 17     |
| CS       | 5    |
| SCL    | 18    |
| SDA    | 23    |
| GND    | GND    |
| VCC    | 3.3V    |   

  </td>
    <td>
      <img src="https://github.com/user-attachments/assets/d04f6595-0771-4c24-bd09-ea4f58448dee" width="500" /> 
    </td>
  </tr>
</table>



## Notes
The refresh time of this 3 color display is very long (>10s). The display does have an partial update mode, to update only a specific area of the display, but this is also very slow. <i>For faster refresh times, consider a black and white only E-paper display!</i>

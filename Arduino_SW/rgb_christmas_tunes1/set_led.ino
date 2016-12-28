// this set led [ln] to colour [col]
/*
   0 = off
   1 = red
   2 = green
   3 = blue
   4 = yellow
   5 = orange
   6 = magenta
   7 = cian
   8 = white

  The RGB is a bit confused as the Neopixels colours are not defined in the way the
  original code assumed [ GRB rather than RGB ] 
*/


int set_led(int ln, int col) {
  //setup local variables
  int r = 0;
  int g = 0;
  int b = 0;

  if (col < 0 || col > 9 || ln < 0 || ln > 5) {        // check for legal led no and colour
    return false;
  }
  switch (col) {
    case 1:
      {
        //    Serial.println("GREEN");
        g = BRIGHT;
        r = 0;
        b = 0;
        break;
      }

    case 2:
      {
        //        Serial.println("RED");
        g = 0;
        r = BRIGHT;
        b = 0;
        break;
      }

    case 3:
      {
        //      Serial.println("BLUE");
        g = 0;
        r = 0;
        b = BRIGHT;
        break;
      }
    case 4:
      {
        //       Serial.println("YELLOW");
        g = BRIGHT;
        r = BRIGHT;
        b = BRIGHT / 6;
        break;
      }
    case 5:
      {
        //        Serial.println("ORANGE");
        g = BRIGHT / 3;
        r = BRIGHT;
        b = 0;
        break;
      }
    case 6:
      {
        //      Serial.println("MAGENTA");
        g = 0;
        r = BRIGHT;
        b = BRIGHT;
        break;
      }

    case 7:
      {
        //     Serial.println("CYAN");
        g = BRIGHT;
        r = 0;
        b = BRIGHT;
        break;
      }
    case 8:
      {
        //     Serial.println("WHITE");
        g = BRIGHT;
        r = BRIGHT;
        b = BRIGHT;
        break;
      }
    default:
      {
        //     Serial.println("OFF");
        r = 0;
        g = 0;
        b = 0;
        break;
      }
  }

  pixels.setPixelColor(ln, pixels.Color(g, r, b));
  pixels.show(); // This sends the updated pixel color to the hardware
}


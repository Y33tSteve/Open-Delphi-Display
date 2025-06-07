//elm327 interpreter

//DTC prefex code mapping
const String dtcMap[16] = {"P0","P1","P2","P3","C0","C1","C2","C3","B0","B1","B2","B3","U0","U1","U2","U3"};

//get A B from response return in global A B variable
void getAB2(String elm_rsp,String mode,String para) {  //41 05 2A 3C 01>
    elm_rsp.trim();
    String hexcode[16];
    uint8_t StringCount = 0;
    while (elm_rsp.length() > 0) {//keep reading each char
      int index = elm_rsp.indexOf(' ');//check space
      if (index == -1)  // No space found
      { //only data without space is now in hexcode {41,05,aa,bb}
        hexcode[StringCount++] = elm_rsp; //last byte
        //for (index=0;index<StringCount;index++) Serial.println(hexcode[index]);
        if ((hexcode[0] == mode) && (hexcode[1] == para)) {//check correct response
        A = strtol(hexcode[2].c_str(), NULL, 16);  //byte 3 save to A
        B = strtol(hexcode[3].c_str(), NULL, 16);  //byte 4 save to B
        } else A = 0xFF;//error
        break;
      } else {//found space
        hexcode[StringCount++] = elm_rsp.substring(0, index);//copy strings from 0 to space to hexcode
        elm_rsp = elm_rsp.substring(index + 1);//copy the rest behind space to elm_rsp
      }
    }  //while

}//getAB
/*------------------*/ 
String getPID(String pid) { //function to get pid response from elm327
    //Clear the Bluetooth Serial buffer
    while (BTSerial.available()>0) {
      BTSerial.read();
    }  
   String bt_response = "";
    // Determine the command to send
    if (pid == "ATRV") {
        // Custom command for voltage reading
        BTSerial.print("ATRV\r");
    } else {
        // Standard PID command
        BTSerial.print(pid + "\r");
    }

   delay(500);// Wait for a response

    // read the bluetooth response
   while (BTSerial.available()>0) {
    char incomingChar = BTSerial.read();
    // Check for the end character '>'    
    if (incomingChar == '>') {
      Serial.println(bt_response);
      BTSerial.flush();
    } else {
      bt_response.concat(incomingChar); // Append character to response
    }
   } //while BTSerial
   return bt_response; // Return the response (PID data or voltage)
}
/*------------------*/ 
/* VIN reading
String resp = "014 
0: 49 02 01 4D 50 42 
1: 41 4D 46 30 36 30 4E 
2: 58 34 33 37 30 39 33 "; */
//convert ascii code to Charactor
const char asciiTable[0x60]= " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}`";
char HextoChar(uint8_t asciiCode) {
  if ((asciiCode > 0x20) && (asciiCode < 0x80)) {
      return(asciiTable[asciiCode-32]);
  }
  else return '\0';//null-terminator
}
//----------------------------
String retrieveVIN() {
  String vin = "";
  getPID("0902");           // Send the VIN request
  delay(300);               // Wait for ELM327 to respond

  unsigned long timeout = millis() + 1000;
  while (millis() < timeout) {
    if (SerialBT.available()) {
      String line = SerialBT.readStringUntil('\r');
      line.trim();

      if (line.startsWith("49 02")) {
        // Skip the first 3 bytes: 49 02 xx
        for (int i = 6; i < line.length(); i += 3) {
          if (i + 1 >= line.length()) break;
          String hexByte = line.substring(i, i + 2);
          char c = (char) strtol(hexByte.c_str(), NULL, 16);
          vin += c;
        }
      }
    }
  }

  vin.trim();
  if (vin.length() == 17) {
    Serial.println("VIN: " + vin);
    return vin;
  } else {
    Serial.println("Invalid VIN or timeout");
    return "Cannot read VIN";
  }
}



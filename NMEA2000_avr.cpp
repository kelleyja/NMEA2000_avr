/* 
NMEA2000_SAME51.cpp

2016 Copyright (c) Kave Oy, www.kave.fi  All right reserved.

Author: Timo Lappalainen
Modified: Al Thomason to support the AVR CPUs.

See: https://github.com/thomasonw/NMEA2000_avr
     https://github.com/thomasonw/avr_can
     https://github.com/thomasonw/ATmegaxxM1-C1 
          

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-
  1301  USA
  
Inherited NMEA2000 object for Atmel AVR UCs with internal CAN
based setup. See also NMEA2000 library.
*/

#include <NMEA2000_avr.h> 
#include <CAN.h>                            // https://github.com/adafruit/arduino-CAN


//*****************************************************************************
tNMEA2000_avr::tNMEA2000_avr() : tNMEA2000() {
}

//*****************************************************************************
bool tNMEA2000_avr::CANSendFrame(unsigned long id, unsigned char len, const unsigned char *buf, bool wait_sent) {
  CAN_FRAME output;
  bool result;
  int TryCount=0;
  
    output.extended=true;
    output.id = id;
    output.length = len;
    for (int i=0; i<len && i<8; i++) output.data.bytes[i]=buf[i];
    
    do {
      if (TryCount>0) delay(3);
      result=CAN.sendFrame(output);
      TryCount++;
    } while (TryCount<2 && !result);
    
    return result;
}

//*****************************************************************************
bool tNMEA2000_avr::CANOpen() {
    //Can.begin(CAN_BPS_250K);
    CAN.begin(250E3)) {
    Serial.println("Starting CAN ...");
   
  //By default there are 7 mailboxes for each device that are RX boxes
  //This sets each mailbox to have an open filter that will accept extended
  //or standard frames
  int filter;
  //extended
  for (filter = 0; filter < 3; filter++) {
  	CAN.setRXFilter(filter, 0, 0, true);
  }  
  //standard
  for (int filter = 3; filter < 7; filter++) {
  	CAN.setRXFilter(filter, 0, 0, false);
  }  
    return true;
}

//*****************************************************************************
bool tNMEA2000_avr::CANGetFrame(unsigned long &id, unsigned char &len, unsigned char *buf) {
  bool HasFrame=false;
  CAN_FRAME incoming;

    if ( CAN.available() > 0 ) {           // check if data coming
        CAN.read(incoming); 
        id=incoming.id;
        len=incoming.length;
        for (int i=0; i<len && i<8; i++) buf[i]=incoming.data.bytes[i];
        HasFrame=true;
    }
    
    return HasFrame;
}

/* 
NMEA2000_avr.h

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

#ifndef _NMEA2000_AVR_H_
#define _NMEA2000_AVR_H_

#include <NMEA2000.h> 
#include <N2kMsg.h>

class tNMEA2000_avr : public tNMEA2000
{
protected:
    bool CANSendFrame(unsigned long id, unsigned char len, const unsigned char *buf, bool wait_sent);
    bool CANOpen();
    bool CANGetFrame(unsigned long &id, unsigned char &len, unsigned char *buf);
    
public:
    tNMEA2000_avr();
};

#endif

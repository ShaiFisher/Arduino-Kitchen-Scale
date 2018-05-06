# Arduino-Kitchen-Scale
Kitchen Scale for up to 2kg

Main Parts:

  * Arduino
  * Weight sensor + HX711 module
  * 4-digits 7-segments display
  * Push Button
  
  Wires:
  
    Scale:
    
      GND   => GND
      DT    => A1
      SCK   => A0
      VCC   => 5v
      
    4-digit 7-segment: (top left to top right, bottom left to bottom right):
    
       1 =>  1k res  => D7
       2 =>  D2
       3 =>  D12
       4 => 1k res => D8
       5 => 1k res => D9
       6 => D3
       7 => D11
       8 => D5
       9 => D6
       10 => D4
       11 => D13
       12 => 1k res => D10
       
    button:
    
       1 => 5v
       2 => A2
       2 => 10k res => gnd (parallel)

#include <HardwareSerial.h>

#define speed_add 0x61
#define rpm_add 0x62

// VP addresses of your variable icons
#define ICON1_VP_ADDRESS 0x1000
#define ICON2_VP_ADDRESS 0x1100

unsigned char Speed[8] = {0x5A, 0xA5, 0x05, 0x82, speed_add, 0x00, 0x00, 0x00};
unsigned char RPM[8] = {0x5A, 0xA5, 0x05, 0x82, rpm_add, 0x00, 0x00, 0x00};

void generateAndSendPacket(unsigned char packet[], byte varId, int value) {
  packet[6] = highByte(value);
  packet[7] = lowByte(value);
  Serial1.write(packet, 8);
}

void displayIcon(uint16_t vpAddress) {
  unsigned char packet[8] = {0x5A, 0xA5, 0x06, 0x80};
  
  // Send VP address
  packet[4] = (uint8_t)(vpAddress >> 8);
  packet[5] = (uint8_t)(vpAddress & 0xFF);
  
  // Send data (assuming you want to display the icon, not hide it)
  packet[6] = 1;
  
  Serial1.write(packet, sizeof(packet));
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 16, 17); // Replace with the correct pins for UART communication
}

void loop() {
  
    for(int s = 0; s <=200; s++){
        for(int r = 0; r <=4000; r+=10){
            Serial.println("Writing Data");
            generateAndSendPacket(Speed, speed_add, s);
            generateAndSendPacket(RPM, rpm_add, r);

            displayIcon(ICON1_VP_ADDRESS);
            delay(1000); // delay for a second
            displayIcon(ICON2_VP_ADDRESS);
            delay(1000); // delay for a second
        }
    }
}

#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
int s[4];
void setup()
{
  
    Serial.begin(9600);  // Debugging only
    Serial.println("setup");
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);   // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
    pinMode(led_pin,OUTPUT);
    digitalWrite(led_pin, false);

}
void loop()
{
//  //--------------Transmitting Code-----------------
//    const char *msg = "02MSGCODE";
//    digitalWrite(led_pin, true); // Flash a light to show transmitting
//    vw_send((uint8_t *)msg, strlen(msg));
//    vw_wait_tx(); // Wait until the whole message is gone
//    digitalWrite(13, false);
//    delay(2000);
//   
//    //--------------Transmitting END---------------------

    //---------------Reciving------------------------
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
         digitalWrite(led_pin, HIGH); // Flash a light to show received good message
        // Message with a good checksum received, print it.
        Serial.print("Got: ");
        switch(char(buf[1])){
          case '1':s[0]=1;//Serial.print(char(buf[1]));
          break;
          case '2':s[1]=1;//0Serial.print(char(buf[1]));
          break;
             case '3':s[2]=1;//0Serial.print(char(buf[1]));
          break;

          case '4':s[3]=1;//0Serial.print(char(buf[1]));
          break;
       
        }
        for (int i = 0; i < buflen; i++)
        {
            Serial.print(char(buf[i]));
            Serial.print(' ');
        }
        Serial.println();
        if(s[0]==1&&s[1]==1&&s[2]==1&&s[3]==1){
          Serial.println("GOT ALL Messages");
          s[0]=0;s[1]=0;s[2]=0;s[3]=0;
        }
//        vw_send(buf,buflen);
//        vw_wait_tx(); // Wait until the whole message is gone
//        digitalWrite(led_pin, LOW);
    }
}


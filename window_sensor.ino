#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#define key1  111111                        // signal: closed
#define key2  222222                        // signal: tilt
#define key3  333333                        // signal: open

const int switchPin                     = 3; // interrupt pin
const int switchPin_2                   = 1; // 2 red
const int statusLED                     = 4; // led
int val = 0;
int val_2 = 0;


void setup() {
    mySwitch.enableTransmit(2);
    pinMode(switchPin, INPUT);
    pinMode(switchPin_2, INPUT);
    
    digitalWrite(switchPin, LOW);
    digitalWrite(switchPin_2, LOW);
    
    pinMode(statusLED, OUTPUT);
    
    // start
    digitalWrite(statusLED, HIGH);
    delay(100);
    digitalWrite(statusLED, LOW);

   
  
} 
void sleep() {
    GIMSK |= _BV(PCIE);                     
    PCMSK |= _BV(PCINT3);                   
    ADCSRA &= ~_BV(ADEN);                   
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    
    sleep_enable();                         
    sei();                                  
    sleep_cpu();                            
    cli();                                  
    PCMSK &= ~_BV(PCINT3);                  
    sleep_disable();                        
    ADCSRA |= _BV(ADEN);                    
    sei();                                  
    } 
ISR(PCINT0_vect) {
    }
void loop() {
    sleep();
    // led, awaken info
    delay(200);
    digitalWrite(statusLED, HIGH);
    delay(200);
    digitalWrite(statusLED, LOW);
    
// long delay, for example: tilting window from open state can take some time for human ;)
    delay(5000);
    
    // reeds reading
    val = digitalRead(switchPin);
    val_2 = digitalRead(switchPin_2);
  
 
    // sending 
    
    if (val == 0)
    {
       for (int i = 0; i <= 2; i++) 
       {
          digitalWrite(statusLED, HIGH);
          mySwitch.send(key1, 20);
          delay(100);  
          digitalWrite(statusLED, LOW);
          delay(100);  
       }
      }
    
     if (val == 1 and val_2 == 1)
    {
       for (int i = 0; i <= 2; i++) 
       {
          digitalWrite(statusLED, HIGH);
          mySwitch.send(key3, 20);
          delay(100);    
          digitalWrite(statusLED, LOW);
          delay(100);    
       }
      }
      
    if (val == 1 and val_2 == 0)
    {
       for (int i = 0; i <= 2; i++) 
       {
          digitalWrite(statusLED, HIGH);
          mySwitch.send(key2, 20);
          delay(100);  
          digitalWrite(statusLED, LOW);
          delay(100);  
       }
    }
}

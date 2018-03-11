#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip=Adafruit_NeoPixel(15,6);
char Mode;

unsigned int r=0,g=0,b=0;
int con=1;
bool ch=true;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(32);
  strip.show();
}

void loop(){
    if(Serial.available()>0)
    {
    Mode=Serial.read();
    Serial.write(Mode);
    Serial.println();
    }

    switch (Mode) {
          case '1':
            ///////////////////////////////////////////
            strip.setBrightness(32);
            for(int m1=0;m1<15;m1+=3){
            strip.setPixelColor(m1,255,0,0);
            strip.show();
            }
            delay(200);
            strip.clear();
            for(int m1=1;m1<15;m1+=3){
              strip.setPixelColor(m1,255,255,0);
              strip.show();
            }
            delay(200);
            strip.clear();
            for(int m1=2;m1<15;m1+=3){
              strip.setPixelColor(m1,0,255,0);
              strip.show();
            }
            delay(200);
            strip.clear();
            ///////////////////////////////////////////
            break;
          case 'D':
            ///////////////////////////////////////////
            strip.setBrightness(32);
            for(int m1=0;m1<15;m1++){
              strip.setPixelColor(m1,255,0,0);
            }
            for(int t=1;t<256;t+=4){
              strip.setBrightness(t);
              delay(10);
              strip.show();
            }
            for(int t=255;t>0;t-=4){
              strip.setBrightness(t);
              delay(10);
              strip.show();
            }
            ///////////////////////////////////////////
            break;
          case '3':
            ///////////////////////////////////////////
            strip.setBrightness(32);
            for(int m1=0;m1<15;m1++){
              strip.setPixelColor(m1,255,0,255);
            }
            for(int t=1;t<256;t+=4){
              strip.setBrightness(t);
              delay(10);
              strip.show();
            }
            for(int t=255;t>0;t-=4){
              strip.setBrightness(t);
              delay(10);
              strip.show();
            }
            ///////////////////////////////////////////
            break;
          case '4':
            ///////////////////////////////////////////
            //(左)閃爍偶數
            strip.setBrightness(32);
            for(int m1=0;m1<15;m1+=2){
              strip.setPixelColor(m1,255,255,0);
              strip.show();
            }
            delay(200);
            strip.clear();
            ///////////////////////////////////////////
            break;
          case 'U':
            ///////////////////////////////////////////
            //(右)呼吸燈
            strip.setBrightness(32);
            for(int m1=0;m1<15;m1++){
              strip.setPixelColor(m1,0,0,255);
            }
            for(int t=1;t<256;t+=4){
              strip.setBrightness(t);
              delay(10);
              strip.show();
            }
            for(int t=255;t>0;t-=4){
              strip.setBrightness(t);
              delay(10);
              strip.show();
            }
            ///////////////////////////////////////////
            break;
          case '6':
            ///////////////////////////////////////////
            strip.setBrightness(32);
            for(int m1=0;m1<15;m1+=2){
              strip.setPixelColor(m1,255,255,0);
              strip.show();
            }
            delay(200);
            strip.clear();
            for(int m1=1;m1<15;m1+=2){
              strip.setPixelColor(m1,139,34,82);
              strip.show();
            }
            delay(200);
            strip.clear();
            ///////////////////////////////////////////
            break;
          case 'L':
            ///////////////////////////////////////////
            strip.setBrightness(32);
            meteorLamp2(139,34,82,8,35);
            meteorLamp2(0,0,255,8,35);
            delay(random(10,300));
            ///////////////////////////////////////////
            break;
          case 'R':
            ///////////////////////////////////////////
            strip.setBrightness(32);
            meteorLamp(139,34,82,8,35);
            meteorLamp(0,0,255,8,35);
            delay(random(10,300));
            ///////////////////////////////////////////
            break;
          case ' ':
            ///////////////////////////////////////////
            // for(int i=0;i<15;i++){
            // // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
            // strip.setPixelColor(i, strip.Color(0,150,0)); // Moderately bright green color.
            // strip.show(); // This sends the updated pixel color to the hardware.
            // delay(100); // Delay for a period of time (in milliseconds).
            // }
            strip.setBrightness(40);
            if(ch){
              if(con>0 && con<16){
                strip.setPixelColor(con-1, strip.Color(r,g,b));
                strip.setPixelColor(con, strip.Color(0,0,0));
                strip.show();
                Serial.println(con);
                delay(30);
                con++;  
              }else{
                con--;
                ch=false;
                r=random(0,255);
                g=random(0,255);
                b=random(0,255);
                Serial.print("R=");
                Serial.println(r);
                Serial.print("G=");
                Serial.println(g);
                Serial.print("B=");
                Serial.println(b);
                Serial.println(ch);
              }
            }else{
              if(con>0 && con<16){
                strip.setPixelColor(con-1, strip.Color(0,0,0));
                strip.setPixelColor(con, strip.Color(r,g,b));
                strip.show();
                Serial.println(con);
                delay(30);
                con--;  
              }else{
                con++;
                ch=true;
                r=random(0,255);
                g=random(0,255);
                b=random(0,255);
                Serial.print("R=");
                Serial.println(r);
                Serial.print("G=");
                Serial.println(g);
                Serial.print("B=");
                Serial.println(b);
              }
            }
            
            ///////////////////////////////////////////
            break;
          default:
            digitalWrite(5,LOW);
      }  
    
       
}


void meteorLamp(int r,int g,int b,int len,int delayMs) {
  for(int i=(0-len);i<=(int)strip.numPixels();i++){
    meteor(r,g,b,i,len);
    delay(delayMs);
  }
}
void meteorLamp2(int r,int g,int b,int len,int delayMs) {
  for(int i=(int)strip.numPixels();i>=(0-len);i--){
    meteor(r,g,b,i,len);
    delay(delayMs);
  }
}

void meteor(int r,int g,int b,int pos,int len){
  int n=255/((1+len)*len/2);
  int bright=255%((1+len)*len/2);
  int cnt=1;
  strip.clear();
  for(int i=pos;i<pos+len;i++){
    bright+=cnt*n;
    cnt++;
    if(i>=0&&i<(int)strip.numPixels()){
      strip.setPixelColor(i,
            map(bright,0,255,0,r),
            map(bright,0,255,0,g),
            map(bright,0,255,0,b));
    }
  }
  strip.show();
}

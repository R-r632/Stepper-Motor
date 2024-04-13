#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int m_dly,m_rot,mode,m,sm,m_speed;
long sys_dly,rot;
bool st,m_st,m_dir,dis;
void setup() {
  lcd.begin(16,2);
  lcd.backlight();
 
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  mode=EEPROM.read(0);
  if(mode>2)mode=0;
  m_speed =EEPROM.read(1);
  m_speed =m_speed+EEPROM.read(2)*100;
   m_speed =m_speed+EEPROM.read(3)*10000;
  if(m_speed>10000)m_speed=10;

   m_rot =EEPROM.read(4);
  m_rot =m_rot+EEPROM.read(5)*100;
   m_rot =m_rot+EEPROM.read(6)*10000;
  if(m_rot>10000)m_rot=0;
}

void loop() {
rot=m_rot*200;
 if (digitalRead(2)&digitalRead(3)&digitalRead(4))st=m_dly = 0;
if (!digitalRead(2)&!st){
if(m>0&m<4)sm++;
m_dly++;
  if(m_dly>50){
    m_dly=0;
    m=1;
    st=1;
    }
if(m>0)st=1;
    

if(m==4)m=0;
if(sm>1&m==1){sm=0;
EEPROM.update(0, mode);
}
if(sm>3&m==2){sm=0;
EEPROM.update(1, m_speed%100);
EEPROM.update(2, (m_speed/100)%100);
EEPROM.update(3, (m_speed/10000)%100);
}
if(sm>3&m==3){sm=0;
EEPROM.update(4, m_rot%100);
EEPROM.update(5, (m_rot/100)%100);
EEPROM.update(6, (m_rot/10000)%100);
}

  }
if (!digitalRead(3)&!st){
st=1;
if(m==0)dis=1;
  if(m==0){
    m_dir=!m_dir;
    }
    if(m!=0){ 
     if(sm==0)m++;
  if(m==1&sm==1)mode++;
  if(mode>2)mode=0;
 
  if(m==2&sm==1)m_speed =m_speed +10;
  if(m==2&sm==2)m_speed =m_speed +100;
  if(m==2&sm==3)m_speed =m_speed +1000;
  if(m_speed>10000)m_speed=10;
  if(m==3&sm==1)m_rot =m_rot +1;
  if(m==3&sm==2)m_rot =m_rot +10;
  if(m==3&sm==3)m_rot =m_rot +100;
  if(m==3&sm==4)m_rot =m_rot +1000;
  if(m_rot>10000)m_rot=1;
    if(m>4)m=1;}
    
  }
 if (!digitalRead(4)&!st){
st=1;
if(m==0)dis=1;
  if(m==0){
    m_st=!m_st;
    sys_dly=0;
    }
    if(m!=0){
      if(sm==0)m--;
    if(m==1&sm==1)mode--;
  if(mode<0)mode=3;

  if(m==2&sm==1)m_speed =m_speed -10;
  if(m==2&sm==2)m_speed =m_speed -100;
  if(m==2&sm==3)m_speed =m_speed -1000;
  if(m_speed<10)m_speed=10000;
if(m==3&sm==1)m_rot =m_rot -1;
  if(m==3&sm==2)m_rot =m_rot -10;
  if(m==3&sm==3)m_rot =m_rot -100;
  if(m==3&sm==4)m_rot =m_rot -1000;
  if(m_rot<0)m_rot=10000;
  
    if(m<1)m=4;}
  } 
  
if((m==0&!m_st)|dis){ 
  dis=0;
  lcd.setCursor(0, 0);
   lcd.print("Mode:");
   lcd.print(mode);
   lcd.print(" Rot:");
   if(m_rot<1|mode==0)lcd.print("inf");
   else lcd.print(m_rot);
   lcd.print("    ");
   lcd.setCursor(0, 1);
   lcd.print("Moter:");
  if(m_st)lcd.print("ON ");
  else lcd.print("OFF");
  lcd.print(" Dir:");
  if(m_dir)lcd.print("FW");
  else lcd.print("RW");
  digitalWrite(8,0); 
  }
//------------------------------------
if(m_st){
if(mode==0){
digitalWrite(8,m_dir);
digitalWrite(9,0);
delayMicroseconds(10400-m_speed);
digitalWrite(9,1);
delayMicroseconds(10400-m_speed);}
if(mode>0&sys_dly<rot){
  sys_dly++;
digitalWrite(8,m_dir);
digitalWrite(9,0);
delayMicroseconds(10400-m_speed);
digitalWrite(9,1);
delayMicroseconds(10400-m_speed);
}else if(mode==1) m_st=0;
else if(mode==2) {m_st=0;m_dir=!m_dir; }

}

//--------------------
if(m==1){ 
  lcd.setCursor(0, 0);
   lcd.print("    Set Mode    ");
   lcd.setCursor(0, 1);
   if(sm==0) lcd.print("[--------------]");
  else{ lcd.print("     Mode:");
   lcd.print(mode);
   lcd.print("     ");}

}
if(m==2){ 
  lcd.setCursor(0, 0);
   lcd.print("   Set Speed    ");
   lcd.setCursor(0, 1);
   if(sm==0) lcd.print("[--------------]");
  else{ lcd.print("  Speed:");
   lcd.print(m_speed);
   lcd.print("      ");}}
if(m==3){ 
  lcd.setCursor(0, 0);
   lcd.print(" Set Rotations  ");
   lcd.setCursor(0, 1);
   if(sm==0) lcd.print("[--------------]");
  else{ lcd.print("   Rot:");
   lcd.print(m_rot);
   lcd.print("       ");}
}
if(m==4){ 
  lcd.setCursor(0, 0);
   lcd.print("      Exit      ");
   lcd.setCursor(0, 1);
  lcd.print("XXXXXXXXXXXXXXXX");
  }
}

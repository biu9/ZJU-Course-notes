#include <ArduinoJson.h>

#include <ArduinoJson.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // I2C

#include <Wire.h>
#include <ArduinoJson.h>
//User Modified Part
#define wifi_ssid     "iQOO3"    
#define wifi_psw      "a1756127061"     
//#define clientIDstr   "gw77zYa96eU.3213123"
#define clientIDstr   "gw77zYa96eU.3213123"
#define timestamp     "998"
#define ProductKey    "gw77zYa96eU"
#define DeviceName    "3213123"
#define DeviceSecret  "08b6d7b24bf1c9fbfcfe1fe2a5cae734"
//#define password      "715bc7fe87634833b2af61e850fb8be5bee5ad2417f7eb00cf34735298cf756d"
#define password      "4A7321E76D3CF06B90F9824B1882FFE9C10B134E"



//Logic Preset
#define OFF           0
#define ON            1
#define MUTE          2
#define KEEP_OFF      2
#define KEEP_ON       3

//#define AC_ON   digitalWrite(ACPin,HIGH)
//#define AC_OFF  digitalWrite(ACPin,LOW)

//#define Fan_ON      digitalWrite(FanPin,HIGH)
//#define Fan_OFF     digitalWrite(FanPin,LOW)

#define Buzzer_ON   digitalWrite(BuzzerPin,HIGH)
#define Buzzer_OFF  digitalWrite(BuzzerPin,LOW)

//#define Pump_ON     digitalWrite(PumpPin,HIGH)
//#define Pump_OFF    digitalWrite(PumpPin,LOW)


//ATcmd Format
#define AT                    "AT\r"
#define AT_OK                 "OK"
#define AT_REBOOT             "AT+REBOOT\r"
#define AT_ECHO_OFF           "AT+UARTE=OFF\r"
#define AT_MSG_ON             "AT+WEVENT=ON\r"

#define AT_WIFI_START         "AT+WJAP=%s,%s\r"
#define AT_WIFI_START_SUCC    "+WEVENT:STATION_UP"

#define AT_MQTT_AUTH          "AT+MQTTAUTH=%s&%s,%s\r"
#define AT_MQTT_CID           "AT+MQTTCID=%s|securemode=2\\,signmethod=hmacsha1\\,timestamp=%s|\r"
#define AT_MQTT_SOCK          "AT+MQTTSOCK=%s.iot-as-mqtt.cn-shanghai.aliyuncs.com,1883\r"

#define AT_MQTT_AUTOSTART_OFF "AT+MQTTAUTOSTART=OFF\r"
#define AT_MQTT_ALIVE         "AT+MQTTKEEPALIVE=500\r"
#define AT_MQTT_START         "AT+MQTTSTART\r"
#define AT_MQTT_START_SUCC    "+MQTTEVENT:CONNECT,SUCCESS"
#define AT_MQTT_PUB_SET       "AT+MQTTPUB=/sys/%s/%s/thing/event/property/post,1\r"
#define AT_MQTT_PUB_ALARM_SET "AT+MQTTPUB=/sys/%s/%s/thing/event/GasAlarm/post,1\r"
#define AT_MQTT_PUB_DATA      "AT+MQTTSEND=%d\r"
//#define JSON_DATA_PACK        "{\"id\":\"100\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":{\"RoomTemp\":%d.%02d,\"AC\":%d,\"Fan\":%d,\"Buzzer\":%d,\"GasDetector\":%d}}\r"
#define JSON_DATA_PACK        "{\"id\":\"100\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":{\"temp\":%d}}\r"
#define JSON_DATA_PACK_2      "{\"id\":\"110\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":{\"LightDetector\":%d,\"Curtain\":%d,\"Light\":%d,\"SoilHumi\":%d,\"Pump\":%d,\"eCO2\":%d,\"TVOC\":%d}}\r"
#define JSON_DATA_PACK_ALARM  "{\"id\":\"110\",\"version\":\"1.0\",\"method\":\"thing.event.GasAlarm.post\",\"params\":{\"GasDetector\":%d}}\r"
#define AT_MQTT_PUB_DATA_SUCC "+MQTTEVENT:PUBLISH,SUCCESS"
#define AT_MQTT_UNSUB         "AT+MQTTUNSUB=2\r"
#define AT_MQTT_SUB           "AT+MQTTSUB=2,/sys/%s/%s/thing/service/property/set,1\r"
#define AT_MQTT_SUB_SUCC      "+MQTTEVENT:2,SUBSCRIBE,SUCCESS"
#define AT_MQTT_CLOSE          "AT+MQTTCLOSE\r"

#define AT_BUZZER_MUTE           "\"Buzzer\":2"


#define DEFAULT_TIMEOUT       10   //seconds
#define BUF_LEN               512
#define BUF_LEN_DATA          512

char      ATcmd[BUF_LEN];
char      ATbuffer[BUF_LEN];
char      ATdata[BUF_LEN_DATA];
#define BuzzerPin             3
int   Buzzer = OFF;

String data;  //new add
int frequency; // new add
int ColorGreen = 0;// new add
int ColorRed = 0; // new add
int ColorBlue = 0; // new add

void setup() {
  //Serial Initial
  Serial3.begin(115200);
  Serial.begin(115200);
  
  String inString="";
  pinMode(7,OUTPUT);  //板载LED
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  //Pin Initial
//  Pin_init();
  //BEEP(1);
  
  //Cloud Initial
  while(1)
  {
    if(!WiFi_init())continue;
    //BEEP(2);
    if(!Ali_connect())continue;
    break;
  }
  //BEEP(3);
   if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check the wiring!"));
    while (1);
  }

    /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}


// new function for Json format
int parse(String data){
  
  StaticJsonBuffer<512> jsonBuffer;
  
  int commaPosition;  
  commaPosition = data.indexOf('{');
  data= data.substring(commaPosition, data.length());
  //Serial.println(data);
  
  JsonObject& root = jsonBuffer.parseObject(data);
  const char* method  = root["method"];
  const char* id      = root["id"];
  int      Frequency  = root["params"]["Frequency"];
  ColorRed = root["params"]["ColorRed"];
  ColorGreen = root["params"]["ColorGreen"];
  ColorBlue = root["params"]["ColorBlue"];
  const char* version1 = root["version"];
  
  // Print values.
  Serial.println("==============Start================");
  Serial.println(method);
  Serial.println(id);
  Serial.println(Frequency);
  
  Serial.println(version1);
  
  return Frequency;  
}

void loop() {
 String inString;
 double tmp = bmp.readTemperature();
 delay(1000);
  if (Serial3.available()>0){
    delay(100);
    inString=Serial3.readString();
    if (inString!=""){
      data=inString;
    }
  }
  Serial.println(data);
  delay(10);
  frequency=parse(data); 
  
  if (frequency==0) { frequency=10;}
    
  Serial.println(frequency);

  Serial.println("12345678910=====================");
  if(!Upload(tmp))
     Serial.println("!Upload");
  else if(Upload(tmp))
     Serial.println("Upload");
  Serial3.readString();
  Serial.println("12345678910");
  
  while(Serial3.available()==0) {
    int delay_seconds=1.0/frequency*1000;
    delay(frequency);
    analogWrite(7,ColorRed);
    analogWrite(8,ColorGreen);
    analogWrite(9,ColorBlue);
    
    delay(frequency);
    analogWrite(7,0);
    analogWrite(8,0);
    analogWrite(9,0);
  }
  //MsgReceive
 // if(check_send_cmd(AT,AT_BUZZER_MUTE,DEFAULT_TIMEOUT))Buzzer_mute();
}


bool Upload(double tmp)
{
  bool flag;
  int len;

  //int  PhotoResistors=ColorBlue;
  cleanBuffer(ATcmd,BUF_LEN);
  // snprintf是sprintf的安全版本，当输入的字符大于size-1时会将后面的字符丢弃。而返回值为字符串的真实长度。
  snprintf(ATcmd,BUF_LEN,AT_MQTT_PUB_SET,ProductKey,DeviceName);//将ProductKey,DeviceName赋值给AT_MQTT_PUB_SET里面的变量后，拷贝给ATcmd。不超过AT_MQTT_PUB_SET 100的长度
  flag = check_send_cmd(ATcmd,AT_OK,DEFAULT_TIMEOUT);
   
  cleanBuffer(ATdata,BUF_LEN_DATA);
  len=snprintf(ATdata,BUF_LEN_DATA,JSON_DATA_PACK,tmp);
    
  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_PUB_DATA,len-1);
  Serial.println("Upload================");
  Serial.println(ATdata);
  Serial.println("Upload================");
  
  flag = check_send_cmd(ATcmd,">",DEFAULT_TIMEOUT);  //检测是否有“>”回应
  if(flag) flag = check_send_cmd(ATdata,AT_MQTT_PUB_DATA_SUCC,20);
  return flag;
}


/* bool Upload()
{
  bool flag;
  int inte1,frac1;
  int len;

  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_PUB_SET,ProductKey,DeviceName);
  flag = check_send_cmd(ATcmd,AT_OK,DEFAULT_TIMEOUT);
   
  
  cleanBuffer(ATdata,BUF_LEN_DATA);

  inte1 = (int)(RoomTemp);
  frac1 = (RoomTemp - inte1) * 100;
  
  len = snprintf(ATdata,BUF_LEN_DATA,JSON_DATA_PACK,inte1,frac1,AC,Fan,Buzzer,GasDetector);
  
  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_PUB_DATA,len-1);
  flag = check_send_cmd(ATcmd,">",DEFAULT_TIMEOUT);
  if(flag) flag = check_send_cmd(ATdata,AT_MQTT_PUB_DATA_SUCC,20);
  
  
//  delay(500);
  
  cleanBuffer(ATdata,BUF_LEN_DATA);
  len = snprintf(ATdata,BUF_LEN_DATA,JSON_DATA_PACK_2,LightDetector,Curtain,Light,SoilHumi,Pump,eCO2,TVOC);

  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_PUB_DATA,len-1);
  flag = check_send_cmd(ATcmd,">",DEFAULT_TIMEOUT);
  if(flag) flag = check_send_cmd(ATdata,AT_MQTT_PUB_DATA_SUCC,20);

  return flag;
}
*/

bool Ali_connect()
{
  bool flag;
  bool flag1;

  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_AUTH,DeviceName,ProductKey,password);
  flag = check_send_cmd(ATcmd,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;

  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_CID,clientIDstr,timestamp);
  flag = check_send_cmd(ATcmd,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;

  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_SOCK,ProductKey);
  flag = check_send_cmd(ATcmd,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;

  flag = check_send_cmd(AT_MQTT_AUTOSTART_OFF,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;

  flag = check_send_cmd(AT_MQTT_ALIVE,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;

  flag = check_send_cmd(AT_MQTT_START,AT_MQTT_START_SUCC,20);
  if(!flag)return false;

  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_PUB_SET,ProductKey,DeviceName);
  flag = check_send_cmd(ATcmd,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;

  //flag = check_send_cmd(AT_MQTT_UNSUB,AT_OK,DEFAULT_TIMEOUT);
  //if(!flag)return false;
  
  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_MQTT_SUB,ProductKey,DeviceName);
  flag = check_send_cmd(ATcmd,AT_MQTT_SUB_SUCC,DEFAULT_TIMEOUT);
  if(!flag){ BEEP(4);flag1 = check_send_cmd(AT_MQTT_CLOSE,AT_OK,DEFAULT_TIMEOUT);}
  return flag;
}

bool WiFi_init()
{
  bool flag;

  flag = check_send_cmd(AT,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;
  
  flag = check_send_cmd(AT_REBOOT,AT_OK,20);
  if(!flag)return false;
  delay(5000);

  flag = check_send_cmd(AT_ECHO_OFF,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;

  flag = check_send_cmd(AT_MSG_ON,AT_OK,DEFAULT_TIMEOUT);
  if(!flag)return false;
  
  cleanBuffer(ATcmd,BUF_LEN);
  snprintf(ATcmd,BUF_LEN,AT_WIFI_START,wifi_ssid,wifi_psw);
  flag = check_send_cmd(ATcmd,AT_WIFI_START_SUCC,20);
  return flag;
}

bool check_send_cmd(const char* cmd,const char* resp,unsigned int timeout)
{
  int i = 0;
  unsigned long timeStart;
  timeStart = millis();
  cleanBuffer(ATbuffer,BUF_LEN);
  Serial3.print(cmd);
  Serial3.flush();
  while(1)
  {
    while(Serial3.available())
    {
      ATbuffer[i++] = Serial3.read();
      if(i >= BUF_LEN)i = 0;
    }
    if(NULL != strstr(ATbuffer,resp))break;
    if((unsigned long)(millis() - timeStart > timeout * 1000)) break;
  }
  
  if(NULL != strstr(ATbuffer,resp))return true;
  return false;
}

void cleanBuffer(char *buf,int len)
{
  for(int i = 0;i < len;i++)
  {
    buf[i] = '\0';
  } 
}

/*
void Pin_init()
{
  pinMode(ACPin,OUTPUT);
  digitalWrite(ACPin,LOW);
  pinMode(BuzzerPin,OUTPUT);
  digitalWrite(BuzzerPin,LOW);
  pinMode(PumpPin,OUTPUT);
  digitalWrite(PumpPin,LOW);
  pinMode(CurtainOpenPin,OUTPUT);
  digitalWrite(CurtainOpenPin,LOW);
  pinMode(CurtainClosePin,OUTPUT);
  digitalWrite(CurtainClosePin,LOW);
  pinMode(Light1Pin,OUTPUT);
  digitalWrite(Light1Pin,LOW);
  pinMode(Light2Pin,OUTPUT);
  digitalWrite(Light2Pin,LOW);
  pinMode(Light3Pin,OUTPUT);
  digitalWrite(Light3Pin,LOW);
  pinMode(FanPin,OUTPUT);
  digitalWrite(FanPin,LOW);
  Curtain_ON();
}
*/

void BEEP(int b_time)
{
  for(int i = 1;i <= b_time;i++)
  { 
    digitalWrite(BuzzerPin,HIGH);
    delay(100);
    digitalWrite(BuzzerPin,LOW);
    delay(100);
  }
}
void Buzzer_mute()
{
  Buzzer_OFF;
  Buzzer = MUTE;
}

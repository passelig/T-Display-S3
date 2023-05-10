
//InfluxDB & Grafana Tutorial
//The DIY Life by Michael Klements
//21 January 2022

#include <Wire.h>                                                   //Import the required libraries
#include "DHT.h"
//#include "Seeed_BMP280.h"
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"


// The influx client library can be found here: 
// https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define WIFI_SSID "Gunnar"                                                                                        //Network Name
#define WIFI_PASSWORD "Hemmelig"                                                                                //Network Password
#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"                                                                                     //InfluxDB v2 server url, e.g. https://eu-central-1-1.aws.cloud2.influxdata.com (Use: InfluxDB UI -> Load Data -> Client Libraries)
#define INFLUXDB_TOKEN "z96gqOCcpcJiV_hZ8A1q-JUCUtA42HRCLRmg3Nz9QSsClCUw7RdqvYnjBsdGmAw5w-cvUiqDQKaAt4h0DdZe2w=="                                                                                 //InfluxDB v2 server or cloud API token (Use: InfluxDB UI -> Data -> API Tokens -> <select token>)
#define INFLUXDB_ORG "86ea0b1b23ab37ae"                                                                                     //InfluxDB v2 organization id (Use: InfluxDB UI -> User -> About -> Common Ids )
#define INFLUXDB_BUCKET "3robdig"                                                                                         //InfluxDB v2 bucket name (Use: InfluxDB UI ->  Data -> Buckets)
#define TZ_INFO "AEDT+11"                                                                                                 //InfluxDB v2 timezone

DHT dht(16,DHT22);                                                   //DHT sensor parameters

int temp = 0;                                                       //Variables to store sensor readings
int humid = 0;

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);                 //InfluxDB client instance with preconfigured InfluxCloud certificate


Point sensor("gunnarUke12");                                            //Data point

void setup() 
{
  Serial.begin(115200); 
  Serial.println("Hello Serial Monitor");                                            //Start serial communication
  
  dht.begin();                                                      //Connect to the DHT Sensor
  
  WiFi.mode(WIFI_STA);                                              //Setup wifi connection
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to wifi");                               //Connect to WiFi
  while (wifiMulti.run() != WL_CONNECTED) 
  {
    Serial.println("Not Connected");
    delay(100);
  }
  Serial.println();

  sensor.addTag("device", DEVICE);                                   //Add tag(s) - repeat as required
  sensor.addTag("SSID", WIFI_SSID);

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");                 //Accurate time is necessary for certificate validation and writing in batches

  if (client.validateConnection())                                   //Check server connection
  {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } 
  else 
  {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop()                                                          //Loop function
{
  temp = dht.readTemperature();                                      //Record temperature
  humid = dht.readHumidity();                                        //Record temperature
  
  sensor.clearFields();                                              //Clear fields for reusing the point. Tags will remain untouched

  sensor.addField("temperature", temp);                              // Store measured value into point
  //sensor.addField("humidity", humid);                                // Store measured value into point
  

    
  if (wifiMulti.run() != WL_CONNECTED)                               //Check WiFi connection and reconnect if needed
    Serial.println("Wifi connection lost");

  if (!client.writePoint(sensor))                                    //Write data point
  {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  
  Serial.print("Temp: ");                                            //Display readings on serial monitor
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humid);
  delay(1000);                                                      //Wait 60 seconds
}

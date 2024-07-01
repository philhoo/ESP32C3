#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "ASUS";
const char* password = "18503731373";

// 定义
String url = "https://api.seniverse.com/v3/weather/now.json";
String city = "changsha";
String key = "SyFLExvm55g9_SqqB";
String language = "zh-Hans";
String unit = "c";
void setup() {
  Serial.begin(115200);

  // 连接 WiFi
  WiFi.begin(ssid, password);

  Serial.print("正在连接 Wi-Fi");
  
  // 检测是否连接成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

  Serial.println("连接成功");
  Serial.print("IP 地址：");
  Serial.println(WiFi.localIP());

  // 创建 HTTPClient 对象
  HTTPClient http;

  // 发送GET请求
  http.begin(url+"?key="+key+"&location="+city+"&language="+language+"&unit="+unit);

  int httpCode = http.GET();

  // 获取响应状态码
  Serial.printf("HTTP 状态码: %d", httpCode);

  // 获取响应正文
  String response = http.getString();
  Serial.println("响应数据");
  Serial.println(response);

  http.end();

  // 创建 DynamicJsonDocument 对象
  DynamicJsonDocument doc(1024);

  // 解析 JSON 数据
  deserializeJson(doc, response);

  // 从解析后的 JSON 文档中获取值
  unsigned int temp = doc["results"][0]["now"]["temperature"].as<unsigned int>();
  String info = doc["results"][0]["now"]["text"].as<String>();

  Serial.printf("当前温度: %d°C\n", temp);
  Serial.printf("当前天气: %s\n", info);
}


void loop() {

}


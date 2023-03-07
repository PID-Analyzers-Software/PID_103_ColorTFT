#include "inc/MenuRenderer.h"
#include "inc/Menu.h"
#include "inc/SleepTimer.h"
#include "inc/DataSource.h"
#include "inc/RangeSet.h"
#include <Adafruit_ADS1015.h>
#include "SSD1306.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library


SSD1306GasMenuRenderer::SSD1306GasMenuRenderer(SSD1306Wire* display) : SSD1306MenuRenderer(display)

{


}

void SSD1306GasMenuRenderer::render(Menu* menu)
{
  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "Select Detector");
  m_display->drawLine(10, 16, 256, 16);
  m_display->drawString(64, 30 , menu->getName());
  m_display->display();
}



SSD1306RunMenuRenderer::SSD1306RunMenuRenderer(SSD1306Wire* display, DataSource* dataSource, GasManager* gasManager) : SSD1306MenuRenderer(display),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{

}
//SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.1);


void SSD1306RunMenuRenderer::render(Menu* menu)
{
  const float multiplier = 0.125F; //GAIN 1

  Gas& selectedGas = m_gasManager->getSelectedGas();
  int64_t startMicros = esp_timer_get_time();

  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_LEFT);
  m_display->setFont(ArialMT_Plain_10);
  //date & time
  struct tm timeinfo;
  getLocalTime(&timeinfo, 10);

  int64_t passed = esp_timer_get_time() - startMicros;
  char dateString[30] = { 0 };
  char timeString[30] = { 0 };
  strftime(dateString, 30, "%b %d %y", &timeinfo);
  strftime(timeString, 30, "%H:%M", &timeinfo);

  m_display->drawString(0, 0, String(timeString));

  m_display->setTextAlignment(TEXT_ALIGN_CENTER);

  m_display->drawString(105, 0, String("90%").c_str());
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  //m_display->drawString(64, 0, String(selectedGas.getName()).c_str());
  //m_display->drawString(64, 0, "CO2");
  m_display->drawString(64, 0, String(selectedGas.getName()).c_str());
  m_display->drawLine(0, 14, 256, 14);
  m_display->setFont(ArialMT_Plain_24);
  if (m_dataSource->getDoubleValue() > 10001) {
    m_display->drawString(60, 18, "xxx");
  } else {
    m_display->drawString(60, 18, String(m_dataSource->getDoubleValue(), 0).c_str());

  }
  m_display->setFont(ArialMT_Plain_10);
  m_display->drawString(105, 30, "ppm");   //Unit
  m_display->drawLine(0, 49, 256, 49);
  m_display->drawString(64, 51,  String(String(m_dataSource->getRawMiliVolts()) + "mV").c_str());

  //  Serial.print(String(timeString));
  //  Serial.print((", " + String(m_dataSource->getDoubleValue(), 0) + ",ppm," + String(m_dataSource->getRawMiliVolts()) + "mV\n").c_str());

  m_display->display();
  delay(100);

}

///////////////////////////

SSD1306SleepTimerMenuRenderer::SSD1306SleepTimerMenuRenderer(SSD1306Wire* display, SleepTimer* sleepTimer) : SSD1306MenuRenderer(display),
  m_sleepTimer(sleepTimer)
{
}

void SSD1306SleepTimerMenuRenderer::render(Menu* menu)
{
  //int interval = m_sleepTimer->getSelectedInterval();

  //String intervalText = interval > 0 ? String(interval) : "CONTINUOUS";

  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "TIMER SLEEP");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawString(64, 30 , menu->getName());
  m_display->display();
}

///////////////////////////

SSD1306RangeMenuRenderer::SSD1306RangeMenuRenderer(SSD1306Wire* display, Range* range) : SSD1306MenuRenderer(display),
  m_range(range)
{
}

void SSD1306RangeMenuRenderer::render(Menu* menu)
{
  int range = m_range->getSelectedRange();

  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "Range");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawString(64, 30 , menu->getName());
  m_display->display();
}

///////////////////////////////

SSD1306FlashLoggerMenuRenderer::SSD1306FlashLoggerMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger) : SSD1306MenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void SSD1306FlashLoggerMenuRenderer::render(Menu* menu)
{
  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "DATA LOGGER");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawString(64, 30 , menu->getName());
  m_display->drawString(64, 40 , m_dataLogger->isFlashStoreSessionRunning() ? "Started" : "Idle");
  m_display->display();


}

///////////////////////////////

SSD1306WiFiDumpMenuRenderer::SSD1306WiFiDumpMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger) : SSD1306MenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void SSD1306WiFiDumpMenuRenderer::render(Menu* menu)
{
  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "WIFI DATA DUMP");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawString(64, 30, menu->getName());
  m_display->drawString(64, 40, m_dataLogger->isWiFiDumpRunning() ? "Started" : "Idle");
  m_display->display();


}

SSD1306WiFiRealTimeDumpMenuRenderer::SSD1306WiFiRealTimeDumpMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger) : SSD1306MenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void SSD1306WiFiRealTimeDumpMenuRenderer::render(Menu* menu)
{
  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "WIFI REAL-TIME DUMP");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawString(64, 30, menu->getName());
  m_display->drawString(64, 40, m_dataLogger->isWiFiDumpRunning() ? "Started" : "Idle");
  m_display->display();


}

SSD1306NTPSyncMenuRenderer::SSD1306NTPSyncMenuRenderer(SSD1306Wire* display, TimeSync* timeSync) : SSD1306MenuRenderer(display),
  m_timeSync(timeSync)
{

}

void SSD1306NTPSyncMenuRenderer::render(Menu* menu)
{
  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "NTP Sync");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawString(64, 30, menu->getName());
  m_display->drawString(64, 40, m_timeSync->isNTCSyncRunning() == true ? "In Progress!" : "Idle");
  m_display->display();

}

SSD1306ShowTimeMenuRenderer::SSD1306ShowTimeMenuRenderer(SSD1306Wire* display) : SSD1306MenuRenderer(display)
{

}

void SSD1306ShowTimeMenuRenderer::render(Menu* menu)
{
  int64_t startMicros = esp_timer_get_time();

  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);

  struct tm timeinfo;
  getLocalTime(&timeinfo, 10);

  int64_t passed = esp_timer_get_time() - startMicros;

  Serial.println("render time: " + String((uint32_t)(passed / 1000)));

  char dateString[30] = { 0 };
  char timeString[30] = { 0 };
  strftime(dateString, 30, "%b %d %y", &timeinfo);
  strftime(timeString, 30, "%H:%M:%S", &timeinfo);

  m_display->drawString(64, 0, "Current DateTime");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawString(64, 28, String(dateString));
  m_display->drawString(64, 45, String(timeString));
  m_display->display();



}







SSD1306CalStartMenuRenderer::SSD1306CalStartMenuRenderer(SSD1306Wire* display) : SSD1306MenuRenderer(display)
{

}
void SSD1306CalStartMenuRenderer::render(Menu* menu)
{ m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "Calibration");
  m_display->drawLine(10, 16, 256, 16);
  m_display->drawString(64, 24, "<DOWN>: Start");
  m_display->drawString(64, 36, "<UP>: Finish");
  m_display->display();
}




SSD1306ZEROMenuRenderer::SSD1306ZEROMenuRenderer(SSD1306Wire* display, DataSource* dataSource, GasManager* gasManager) : SSD1306MenuRenderer(display),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{

}
void SSD1306ZEROMenuRenderer::render(Menu* menu)
{
  const float multiplier = 0.125F; //GAIN 1
  double sensor_val = m_dataSource->getDoubleValue();

  m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "Calibration - Zero");
  m_display->drawLine(10, 16, 256, 16);
  m_display->drawString(64, 22, "Zero Gas: 0 ppm");
  m_display->drawString(64, 32, String("Det: " + String(m_dataSource->getRawMiliVolts()) + "mV").c_str());
  m_display->drawString(64, 45, "<S>: Confirm");
  m_display->display();
}

SSD1306CalGasMenuRenderer::SSD1306CalGasMenuRenderer(SSD1306Wire* display, DataSource* dataSource, GasManager* gasManager) : SSD1306MenuRenderer(display),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{

}
void SSD1306CalGasMenuRenderer::render(Menu* menu)
{ m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "Calibration - Cal Gas");
  m_display->drawLine(10, 16, 256, 16);
  m_display->drawString(64, 22, "Cal Gas: 7500 ppm");
  m_display->drawString(64, 32, String("Det: " + String(m_dataSource->getRawMiliVolts()) + "mV").c_str());
  m_display->drawString(64, 45, "<S>: Confirm");

  m_display->display();
}


SSD1306CalResMenuRenderer::SSD1306CalResMenuRenderer(SSD1306Wire* display, GasManager* gasManager) : SSD1306MenuRenderer(display),
  m_gasManager(gasManager)

{

}
void SSD1306CalResMenuRenderer::render(Menu* menu)
{ m_display->clear();
  m_display->setColor(WHITE);
  m_display->setTextAlignment(TEXT_ALIGN_CENTER);
  m_display->drawString(64, 0, "Calibration - Result");
  m_display->drawLine(10, 16, 256, 16);
  m_display->drawString(64, 24, "Calibration Finished");
  m_display->drawString(64, 40, "<DOWN>: Restart");
  m_display->drawString(64, 48, "<UP>: Finish");
  m_display->display();
}

/////////////////////////

///////////
//// SSD1327
///////////

SSD1327GasMenuRenderer::SSD1327GasMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display) : SSD1327MenuRenderer(display)
{

}



void SSD1327GasMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(64, 0, menu->getParentName().c_str());
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 30, menu->getName().c_str());
  m_display->sendBuffer();

}

SSD1327RunMenuRenderer::SSD1327RunMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataSource* dataSource, GasManager* gasManager) : SSD1327MenuRenderer(display),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{


}

void SSD1327RunMenuRenderer::render(Menu* menu)
{
  const float multiplier = 0.125F; //GAIN 1

  double sensor_val = m_dataSource->getDoubleValue();
  //Serial.print("ADC A0: ");
  //Serial.println(ads_val);
  //Serial.println("15: " + String(digitalRead(15)));

  Gas& selectedGas = m_gasManager->getSelectedGas();

  m_display->clearBuffer();
  m_display->drawStr(64, 0, String(selectedGas.getName() + " " + String(sensor_val) + "sccm").c_str());
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 30, String(String(m_dataSource->getRawMiliVolts()) + "mV").c_str());
  m_display->sendBuffer();

}

///////////////////////////

SSD1327SleepTimerMenuRenderer::SSD1327SleepTimerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, SleepTimer* sleepTimer) : SSD1327MenuRenderer(display),
  m_sleepTimer(sleepTimer)
{






}

void SSD1327SleepTimerMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(64, 0, "TIMER SLEEP");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 30, menu->getName().c_str());
  m_display->sendBuffer();
}

///////////////////////////////

SSD1327FlashLoggerMenuRenderer::SSD1327FlashLoggerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger) : SSD1327MenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void SSD1327FlashLoggerMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(64, 0, "DATA LOGGER");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 30, menu->getName().c_str());
  m_display->drawStr(64, 40, m_dataLogger->isFlashStoreSessionRunning() ? "Started" : "Idle");
  m_display->sendBuffer();


}

///////////////////////////////

SSD1327WiFiDumpMenuRenderer::SSD1327WiFiDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger) : SSD1327MenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void SSD1327WiFiDumpMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(64, 0, "WIFI DATA DUMP");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 30, menu->getName().c_str());
  m_display->drawStr(64, 40, m_dataLogger->isWiFiDumpRunning() ? "Started" : "Idle");
  m_display->sendBuffer();


}

SSD1327WiFiRealTimeDumpMenuRenderer::SSD1327WiFiRealTimeDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger) : SSD1327MenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void SSD1327WiFiRealTimeDumpMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(64, 0, "WIFI REAL-TIME DUMP");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 30, menu->getName().c_str());
  m_display->drawStr(64, 40, m_dataLogger->isWiFiDumpRunning() ? "Started" : "Idle");
  m_display->sendBuffer();


}

SSD1327NTPSyncMenuRenderer::SSD1327NTPSyncMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, TimeSync* timeSync) : SSD1327MenuRenderer(display),
  m_timeSync(timeSync)
{

}

void SSD1327NTPSyncMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(64, 0, "NTP Sync");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 30, menu->getName().c_str());
  m_display->drawStr(64, 40, m_timeSync->isNTCSyncRunning() == true ? "In Progress!" : "Idle");
  m_display->sendBuffer();

}

SSD1327ShowTimeMenuRenderer::SSD1327ShowTimeMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display) : SSD1327MenuRenderer(display)
{

}

void SSD1327ShowTimeMenuRenderer::render(Menu* menu)
{
  int64_t startMicros = esp_timer_get_time();

  m_display->clearBuffer();

  struct tm timeinfo;
  getLocalTime(&timeinfo, 10);

  int64_t passed = esp_timer_get_time() - startMicros;

  Serial.println("render time: " + String((uint32_t)(passed / 1000)));

  char dateString[30] = { 0 };
  char timeString[30] = { 0 };
  strftime(dateString, 30, "%b %d %y", &timeinfo);
  strftime(timeString, 30, "%H:%M:%S", &timeinfo);

  m_display->drawStr(64, 0, "Current DateTime");
  m_display->drawLine(10, 24, 256, 24);
  m_display->drawStr(64, 28, String(dateString).c_str());
  m_display->drawStr(64, 45, String(timeString).c_str());
  m_display->sendBuffer();

}



/*
  TFT Display
*/




TFTGasMenuRenderer::TFTGasMenuRenderer(TFT_eSPI* display) : TFTMenuRenderer(display)

{


}

void TFTGasMenuRenderer::render(Menu* menu)
{
  // 
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  //  m_display->setCursor(50, 14, 4);
  m_display->drawRightString("Select Gas", 270, 14, 4);    // Draw text centre at position 120, 54 using font 6
  m_display->setTextColor(TFT_YELLOW);
  //  m_display->setCursor(70, 70, 4);
  m_display->drawRightString(menu->getName(), 220, 100, 4);
}



TFTRunMenuRenderer::TFTRunMenuRenderer(TFT_eSPI* display, DataSource* dataSource, GasManager* gasManager) : TFTMenuRenderer(display),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{

}
//SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.1);


void TFTRunMenuRenderer::render(Menu* menu)
{
  const float multiplier = 0.125F; //GAIN 1
  Gas& selectedGas = m_gasManager->getSelectedGas();
  int64_t startMicros = esp_timer_get_time();
  //date & time
  struct tm timeinfo;
  getLocalTime(&timeinfo, 10);

  int64_t passed = esp_timer_get_time() - startMicros;
  char dateString[30] = { 0 };
  char timeString[30] = { 0 };
  strftime(dateString, 30, "%b %d %y", &timeinfo);
  strftime(timeString, 30, "%H:%M", &timeinfo);



  // block //
  // 
  //m_display->fillRect(0, 0, 200, 200, TFT_BLACK);


  m_display->setTextColor(TFT_BLACK); // Background is not defined so it is transparent
  m_display->setCursor (300, 5);
  m_display->setTextFont(2);        // Select font 1 which is the Adafruit GLCD font
  m_display->print("battery");

  m_display->setTextSize(2);           // We are using a text size multiplier of 1
  // The new larger fonts do not need to use the .setCursor call, coords are embedded
  m_display->setTextColor(TFT_RED, TFT_BLACK); // Do not plot the background colour
  // Overlay the black text on top of the rainbow plot (the advantage of not drawing the backgorund colour!)
  m_display->setCursor(50, 14, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println(String(timeString));       // Draw text centre at position 120, 54 using font 6    m_display->setTextColor(TFT_GREEN, TFT_BLACK);  // Set text colour to white and background to black
  m_display->setTextColor(TFT_GREEN); // Do not plot the background colour

  m_display->setCursor(250, 14, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("96%");       // Draw text centre at position 120, 54 using font 6
  m_display->setTextColor(TFT_YELLOW); // Do not plot the background colour
  m_display->setCursor(30, 90, 4);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("PID");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(30, 135, 4);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("CO");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(105, 150, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("2");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(30, 180, 4);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("CO");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(30, 225, 4);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("NO");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(30, 270, 4);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("NO");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(105, 285, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("2");       // Draw text centre at position 120, 54 using font 6

  //m_display->setCursor(135, 90, 4);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->setTextColor(TFT_YELLOW, TFT_BLACK);

  m_display->drawRightString(String(String(m_dataSource->getRawMiliVolts() / 1000)).c_str(), 230, 90, 4);     // Draw text centre at position 120, 54 using font 6
  m_display->drawRightString(String(String(530 + m_dataSource->getRawMiliVolts() / 100)).c_str(), 230, 135, 4);  // Draw text centre at position 120, 54 using font 6
  m_display->drawRightString(String(String(m_dataSource->getRawMiliVolts() / 100.1, 1)).c_str(), 230, 180, 4);   // Draw text centre at position 120, 54 using font 6
  m_display->drawRightString("1.7", 230, 225, 4);      // Draw text centre at position 120, 54 using font 6
  m_display->drawRightString("0.9", 230, 270, 4);      // Draw text centre at position 120, 54 using font 6

  m_display->setCursor(250, 100, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("ppm");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(250, 145, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("ppm");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(250, 190, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("ppm");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(250, 235, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("ppm");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(250, 280, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("ppm");       // Draw text centre at position 120, 54 using font 6


  m_display->setCursor(30, 400, 2);    // Set cursor to x = 76, y = 150 and use font 4
  m_display->println("Log-ON");       // Draw text centre at position 120, 54 using font 6
  m_display->setCursor(200, 400, 2);    // Set cursor to x = 76, y = 150 and use font 4
  //m_display->setTextColor(TFT_RED); // Do not plot the background colour
  m_display->println("Alarm-ON");       // Draw text centre at position 120, 54 using font 6
  delay(20);
  // block -end //


}

///////////////////////////

TFTSleepTimerMenuRenderer::TFTSleepTimerMenuRenderer(TFT_eSPI* display, SleepTimer* sleepTimer) : TFTMenuRenderer(display),
  m_sleepTimer(sleepTimer)
{
}

void TFTSleepTimerMenuRenderer::render(Menu* menu)
{


   
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  //  m_display->setCursor(50, 14, 4);
  m_display->drawRightString("Sleep Timer", 270, 14, 4);    // Draw text centre at position 120, 54 using font 6
  m_display->setTextColor(TFT_YELLOW);
  //  m_display->setCursor(70, 70, 4);
  m_display->drawRightString(menu->getName(), 220, 100, 4);
  //delay(1000);
}

///////////////////////////

TFTRangeMenuRenderer::TFTRangeMenuRenderer(TFT_eSPI* display, Range* range) : TFTMenuRenderer(display),
  m_range(range)
{
}

void TFTRangeMenuRenderer::render(Menu* menu)
{
  int range = m_range->getSelectedRange();

   
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  //  m_display->setCursor(50, 14, 4);
  m_display->drawRightString("Set Range", 270, 14, 4);    // Draw text centre at position 120, 54 using font 6
  m_display->setTextColor(TFT_YELLOW);
  //  m_display->setCursor(70, 70, 4);
  m_display->drawRightString(menu->getName() + "ppm", 300, 100, 4);
  //delay(1000);
}

///////////////////////////////

TFTFlashLoggerMenuRenderer::TFTFlashLoggerMenuRenderer(TFT_eSPI* display, DataLogger* dataLogger) : TFTMenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void TFTFlashLoggerMenuRenderer::render(Menu* menu)
{
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  m_display->setCursor(50, 14, 4);
  m_display->println("flashlogger");


}

///////////////////////////////

TFTWiFiDumpMenuRenderer::TFTWiFiDumpMenuRenderer(TFT_eSPI* display, DataLogger* dataLogger) : TFTMenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void TFTWiFiDumpMenuRenderer::render(Menu* menu)
{
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  m_display->setCursor(50, 14, 4);
  m_display->println("wifidump");


}

TFTWiFiRealTimeDumpMenuRenderer::TFTWiFiRealTimeDumpMenuRenderer(TFT_eSPI* display, DataLogger* dataLogger) : TFTMenuRenderer(display),
  m_dataLogger(dataLogger)
{


}

void TFTWiFiRealTimeDumpMenuRenderer::render(Menu* menu)
{
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  m_display->setCursor(50, 14, 4);
  m_display->println("TFTWiFiRealTimeDumpMenuRenderer");


}

TFTNTPSyncMenuRenderer::TFTNTPSyncMenuRenderer(TFT_eSPI* display, TimeSync* timeSync) : TFTMenuRenderer(display),
  m_timeSync(timeSync)
{

}

void TFTNTPSyncMenuRenderer::render(Menu* menu)
{
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  m_display->setCursor(50, 14, 4);
  m_display->println("TFTNTPSyncMenuRenderer");


}

TFTShowTimeMenuRenderer::TFTShowTimeMenuRenderer(TFT_eSPI* display) : TFTMenuRenderer(display)
{

}

void TFTShowTimeMenuRenderer::render(Menu* menu)
{


  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  m_display->setCursor(50, 14, 4);
  m_display->println("TFTShowTimeMenuRenderer");


}







TFTCalStartMenuRenderer::TFTCalStartMenuRenderer(TFT_eSPI* display) : TFTMenuRenderer(display)
{

}
void TFTCalStartMenuRenderer::render(Menu* menu)
{ m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  m_display->setCursor(50, 14, 4);
  m_display->println("TFTCalStartMenuRenderer");
}





TFTZEROMenuRenderer::TFTZEROMenuRenderer(TFT_eSPI* display, DataSource* dataSource, GasManager* gasManager) : TFTMenuRenderer(display),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{

}
void TFTZEROMenuRenderer::render(Menu* menu)
{
  const float multiplier = 0.125F; //GAIN 1
  double sensor_val = m_dataSource->getDoubleValue();
   
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  //  m_display->setCursor(50, 14, 4);
  m_display->drawRightString("Cal Zero", 200, 14, 4);    // Draw text centre at position 120, 54 using font 6
  m_display->setTextColor(TFT_YELLOW);
  //  m_display->setCursor(70, 70, 4);
  m_display->drawRightString("Zero Gas: 0 ppm", 280, 100, 2);
  m_display->drawRightString("Det: 232 mV", 280, 150, 2);
  m_display->drawRightString("<Select>: Confirm", 280, 200, 2);
  m_display->drawRightString("<Down>: Skip", 280, 250, 2);

}

TFTCalGasMenuRenderer::TFTCalGasMenuRenderer(TFT_eSPI* display, DataSource* dataSource, GasManager* gasManager) : TFTMenuRenderer(display),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{

}
void TFTCalGasMenuRenderer::render(Menu* menu)
{
   
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  //  m_display->setCursor(50, 14, 4);
  m_display->drawRightString("Cal Cal", 200, 14, 4);    // Draw text centre at position 120, 54 using font 6
  m_display->setTextColor(TFT_YELLOW);
  //  m_display->setCursor(70, 70, 4);
  m_display->drawRightString("Cal Gas: 1000 ppm", 280, 100, 2);
  m_display->drawRightString("Det:  1443 mV", 280, 150, 2);
  m_display->drawRightString("<Select>: Confirm", 280, 200, 2);
  m_display->drawRightString("<Down>: Skip", 280, 250, 2);

}


TFTCalResMenuRenderer::TFTCalResMenuRenderer(TFT_eSPI* display, GasManager* gasManager) : TFTMenuRenderer(display),
  m_gasManager(gasManager)

{

}
void TFTCalResMenuRenderer::render(Menu* menu)
{
  m_display->setTextFont(2);
  m_display->setTextColor(TFT_RED);
  m_display->setCursor(50, 14, 4);
  m_display->println("14:23");
}

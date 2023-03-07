#pragma once

class Menu;
class SSD1306Wire;
class TFT_eSPI;
class U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI;
class Adafruit_ADS1115;
class GasManager;
class GasMenuItem;
class RunMenuItem;
class SleepTimer;
class DataLogger;
class DataSource;
class TimeSync;
class Range;


class MenuRenderer
{
public:

	virtual void render(Menu* menu) = 0;
};

class SSD1306MenuRenderer : public MenuRenderer
{
protected:	
	SSD1306Wire* 			m_display;

public:

	SSD1306MenuRenderer(SSD1306Wire* display) : m_display(display)
	{}

	void render(Menu* menu);
	
};

class SSD1306GasMenuRenderer : public SSD1306MenuRenderer
{


public:

	SSD1306GasMenuRenderer(SSD1306Wire* display);
	
	void render(Menu* menu);
	
};

class SSD1306RunMenuRenderer : public SSD1306MenuRenderer
{
	DataSource* 		m_dataSource;
	GasManager*			m_gasManager;
	
public:

	SSD1306RunMenuRenderer(SSD1306Wire* display, DataSource* dataSource, GasManager* gasManager);

	void render(Menu* menu);
};

class SSD1306SleepTimerMenuRenderer : public SSD1306MenuRenderer
{
	SleepTimer* m_sleepTimer;
	
public:	
	
	SSD1306SleepTimerMenuRenderer(SSD1306Wire* display, SleepTimer* sleepTimer);
	
	void render(Menu* menu);
};

class SSD1306RangeMenuRenderer : public SSD1306MenuRenderer
{
    Range* m_range;

public:

    SSD1306RangeMenuRenderer(SSD1306Wire* display, Range* range);

    void render(Menu* menu);
};



class SSD1306FlashLoggerMenuRenderer : public SSD1306MenuRenderer
{
	DataLogger* m_dataLogger;
	
public:	
	
	SSD1306FlashLoggerMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger);
	
	void render(Menu* menu);
};

class SSD1306WiFiDumpMenuRenderer : public SSD1306MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1306WiFiDumpMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1306WiFiRealTimeDumpMenuRenderer : public SSD1306MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1306WiFiRealTimeDumpMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1306NTPSyncMenuRenderer : public SSD1306MenuRenderer
{
	TimeSync* m_timeSync;

public:

	SSD1306NTPSyncMenuRenderer(SSD1306Wire* display, TimeSync* timeSync);

	void render(Menu* menu);
};

class SSD1306ShowTimeMenuRenderer : public SSD1306MenuRenderer
{

public:

	SSD1306ShowTimeMenuRenderer(SSD1306Wire* display);

	void render(Menu* menu);
};



class SSD1306CalStartMenuRenderer : public SSD1306MenuRenderer
{

public:

    SSD1306CalStartMenuRenderer(SSD1306Wire* display);

    void render(Menu* menu);
};



class SSD1306ZEROMenuRenderer : public SSD1306MenuRenderer
{
    DataSource* 		m_dataSource;
    GasManager*				m_gasManager;
public:

    SSD1306ZEROMenuRenderer(SSD1306Wire* display, DataSource* dataSource, GasManager* gasManager);
    void render(Menu* menu);
};


class SSD1306CalGasMenuRenderer : public SSD1306MenuRenderer
{
    DataSource* 		m_dataSource;
    GasManager*				m_gasManager;
public:

    SSD1306CalGasMenuRenderer(SSD1306Wire* display,  DataSource* dataSource, GasManager* gasManager);
    void render(Menu* menu);
};



class SSD1306CalResMenuRenderer : public SSD1306MenuRenderer
{
    GasManager*				m_gasManager;

public:

    SSD1306CalResMenuRenderer(SSD1306Wire* display, GasManager* gasManager);
    void render(Menu* menu);
};


///////////
//// SSD1327
///////////

class SSD1327MenuRenderer : public MenuRenderer
{
protected:
	U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* m_display;

public:

	SSD1327MenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display) : m_display(display)
	{}

	void render(Menu* menu);

};

class SSD1327GasMenuRenderer : public SSD1327MenuRenderer
{
public:

	SSD1327GasMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display);

	void render(Menu* menu);

};

class SSD1327RunMenuRenderer : public SSD1327MenuRenderer
{
	DataSource* m_dataSource;
	GasManager* m_gasManager;

public:

	SSD1327RunMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataSource* dataSource, GasManager* gasManager);

	void render(Menu* menu);
};

class SSD1327SleepTimerMenuRenderer : public SSD1327MenuRenderer
{
	SleepTimer* m_sleepTimer;

public:

	SSD1327SleepTimerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, SleepTimer* sleepTimer);

	void render(Menu* menu);
};

class SSD1327FlashLoggerMenuRenderer : public SSD1327MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1327FlashLoggerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1327WiFiDumpMenuRenderer : public SSD1327MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1327WiFiDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1327WiFiRealTimeDumpMenuRenderer : public SSD1327MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1327WiFiRealTimeDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1327NTPSyncMenuRenderer : public SSD1327MenuRenderer
{
	TimeSync* m_timeSync;

public:

	SSD1327NTPSyncMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, TimeSync* timeSync);

	void render(Menu* menu);
};


class SSD1327InfoMenuRenderer : public SSD1327MenuRenderer
{
    //TimeSync* m_timeSync;

public:

    SSD1327InfoMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display);

    void render(Menu* menu);
};




class SSD1327ShowTimeMenuRenderer : public SSD1327MenuRenderer
{

public:

	SSD1327ShowTimeMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display);

	void render(Menu* menu);
};

///////////
////TFT
///////////
class TFTMenuRenderer : public MenuRenderer
{
protected:
    TFT_eSPI* 			m_display;

public:

    TFTMenuRenderer(TFT_eSPI* display) : m_display(display)
    {}

    void render(Menu* menu);

};

class TFTGasMenuRenderer : public TFTMenuRenderer
{


public:

    TFTGasMenuRenderer(TFT_eSPI* display);

    void render(Menu* menu);

};

class TFTRunMenuRenderer : public TFTMenuRenderer
{
    DataSource* 		m_dataSource;
    GasManager*			m_gasManager;

public:

    TFTRunMenuRenderer(TFT_eSPI* display, DataSource* dataSource, GasManager* gasManager);

    void render(Menu* menu);
};

class TFTSleepTimerMenuRenderer : public TFTMenuRenderer
{
    SleepTimer* m_sleepTimer;

public:

    TFTSleepTimerMenuRenderer(TFT_eSPI* display, SleepTimer* sleepTimer);

    void render(Menu* menu);
};

class TFTRangeMenuRenderer : public TFTMenuRenderer
{
    Range* m_range;

public:

    TFTRangeMenuRenderer(TFT_eSPI* display, Range* range);

    void render(Menu* menu);
};



class TFTFlashLoggerMenuRenderer : public TFTMenuRenderer
{
    DataLogger* m_dataLogger;

public:

    TFTFlashLoggerMenuRenderer(TFT_eSPI* display, DataLogger* dataLogger);

    void render(Menu* menu);
};

class TFTWiFiDumpMenuRenderer : public TFTMenuRenderer
{
    DataLogger* m_dataLogger;

public:

    TFTWiFiDumpMenuRenderer(TFT_eSPI* display, DataLogger* dataLogger);

    void render(Menu* menu);
};

class TFTWiFiRealTimeDumpMenuRenderer : public TFTMenuRenderer
{
    DataLogger* m_dataLogger;

public:

    TFTWiFiRealTimeDumpMenuRenderer(TFT_eSPI* display, DataLogger* dataLogger);

    void render(Menu* menu);
};

class TFTNTPSyncMenuRenderer : public TFTMenuRenderer
{
    TimeSync* m_timeSync;

public:

    TFTNTPSyncMenuRenderer(TFT_eSPI* display, TimeSync* timeSync);

    void render(Menu* menu);
};

class TFTShowTimeMenuRenderer : public TFTMenuRenderer
{

public:

    TFTShowTimeMenuRenderer(TFT_eSPI* display);

    void render(Menu* menu);
};



class TFTCalStartMenuRenderer : public TFTMenuRenderer
{

public:

    TFTCalStartMenuRenderer(TFT_eSPI* display);

    void render(Menu* menu);
};



class TFTZEROMenuRenderer : public TFTMenuRenderer
{
    DataSource* 		m_dataSource;
    GasManager*				m_gasManager;
public:

    TFTZEROMenuRenderer(TFT_eSPI* display, DataSource* dataSource, GasManager* gasManager);
    void render(Menu* menu);
};


class TFTCalGasMenuRenderer : public TFTMenuRenderer
{
    DataSource* 		m_dataSource;
    GasManager*				m_gasManager;
public:

    TFTCalGasMenuRenderer(TFT_eSPI* display,  DataSource* dataSource, GasManager* gasManager);
    void render(Menu* menu);
};



class TFTCalResMenuRenderer : public TFTMenuRenderer
{
    GasManager*				m_gasManager;

public:

    TFTCalResMenuRenderer(TFT_eSPI* display, GasManager* gasManager);
    void render(Menu* menu);
};





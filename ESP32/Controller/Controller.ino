//SPI 2
const uint8_t HSPICLK = 14;
const uint8_t HSPICS0 = 15;
const uint8_t HSPIMISO = 12;
const uint8_t HSPIMOSI = 13;
const uint8_t HSPIHD = 4;
const uint8_t HSPIWP = 2;

//SPI 3
const uint8_t VSPICLK = 18;
const uint8_t VSPICS0 = 5;
const uint8_t VSPIMISO = 19;
const uint8_t VSPIMOSI = 23;
const uint8_t VSPIHD = 21;
const uint8_t VSPIWP = 22;

//Ultra-Low Noise Analog Pre-Amp
const uint8_t SENSORVP = 36;
const uint8_t SENSORVN = 39;

//Analog to Digital Converter (12bit SAR)
const uint8_t ADC1CH0 = SENSORVP;
const uint8_t ADC1CH2 = SENSORVN;
const uint8_t ADC1CH4 = 32; 
const uint8_t ADC1CH5 = 33; 
const uint8_t ADC1CH6 = 34;
const uint8_t ADC1CH7 = 35;
const uint8_t ADC2CH0 = 4;
const uint8_t ADC2CH1 = 0; 
const uint8_t ADC2CH2 = 2; 
const uint8_t ADC2CH3 = 15; 
const uint8_t ADC2CH4 = 13; 
const uint8_t ADC2CH5 = 12; 
const uint8_t ADC2CH6 = 14; 
const uint8_t ADC2CH7 = 27; 
const uint8_t ADC2CH8 = 25;
const uint8_t ADC2CH9 = 26;

//Capacitive Touch Sensors
const uint8_t TOUCH0 = ADC2CH1;
const uint8_t TOUCH1 = ADC2CH2;
const uint8_t TOUCH2 = ADC2CH3;
const uint8_t TOUCH3 = ADC2CH4;
const uint8_t TOUCH4 = ADC2CH5;
const uint8_t TOUCH5 = ADC2CH6;
const uint8_t TOUCH6 = ADC2CH7;
const uint8_t TOUCH8 = ADC1CH5;
const uint8_t TOUCH9 = ADC1CH4;

//ESP-WROOM-32 onboard SDIO flash memory https://www.sdcard.org/cht/downloads/pls/simplified_specs/archive/partE1_100.pdf
//Must support SPI mode, pinout suggests support for SD 4bit mode, possibly supports SD 1bit mode
                            //  SD 4bit,    SD 1bit,              SPI
const uint8_t FLASHCLK = 6;     //  Clock ---------------------------------------
const uint8_t FLASHCMD = 11;    //  Command Line (CMD),               Data Input
const uint8_t FLASHDATA0 = 7;   //  DATA0,      DATA,                 Data Output
const uint8_t FLASHDATA1 = 8;   //  DATA1,      Interupt (IRQ)-------------------
const uint8_t FLASHDATA2 = 9;   //  DATA2,      Read Wait (optional), NC
const uint8_t FLASHDATA3 = 10;  //  DATA3,      NC,                   Card Select

//Digital to Analog Converter (8bit)
//const uint8_t DAC1 = 25;
//onst uint8_t DAC2 = 26;

const uint8_t BOOTBTN = ADC2CH1;
const uint8_t LEDPIN = 16;

const uint8_t TFTLED = 25;
const uint8_t TFTRST = 26;
const uint8_t TFTRS = 27;
const uint8_t TFTCS = HSPICS0; 
const uint8_t TFTCLK = HSPICLK; 
const uint8_t TFTSDI = HSPIMOSI; 

//#define CONFIG_DISABLE_HAL_LOCKS 1
#include "TFTInterface.h"
#include "Networks.h"

TFT_22_ILI9225 tft = TFT_22_ILI9225(TFTRST, TFTRS, TFTCS, TFTSDI, TFTCLK, TFTLED, 128);
//TFT_22_ILI9225 tft = TFT_22_ILI9225(TFTRST, TFTRS, TFTCS, TFTLED, 128);
TFTInterface tfti = TFTInterface(&tft);//(TFTRST, TFTRS, TFTCS, TFTSDI, TFTCLK, TFTLED, 128);
Networks net;

void setup()
{
    Serial.begin(115200);
    WiFi.onEvent(WiFiEvent);
    
    //SPIClass tftspi = SPIClass(VSPI); //Use hardware SPI 2 (HSPI)
    tft.begin();//tftspi);
    tft.setFont(Terminal6x8);
    tft.setOrientation(1);
    digitalWrite(TFTLED, HIGH);
    //tft.setBacklight(true);
    //tft.setBacklightBrightness(255);
    
    nvs_handle nvsh;
    nvs_open("WiFi", NVS_READWRITE, &nvsh);
    net = Networks(nvsh);
}

// String Keyboard()
// {
//     if(tfti.Page("Keyboard"))
//     {

//     }
// }

void loop()
{
    //tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
    //tft.drawText(10, 10, "hello!", COLOR_WHITE);
    
    tfti.fill(0xFFFF);
    //tfti.draw();
    tfti.fillRect(50, 50, 100, 100, 0x0FF0);
    //tfti.draw();
    Serial.println("AAAA");
    /*delay(500);
    while(WiFi.status() != WL_CONNECTED)
    {
        NetworkList nl = net.scan();
        tft.clear();
        for(int i = 0; i < nl.listLen; i++)
        {
          Serial.println(nl[i]);
          tft.drawText(10, 10 * (i+1), nl[i], COLOR_WHITE);
        }
        Serial.println("Connecting...");
        String pass = net.getPassword("Telstra5B50AA");
        Serial.println(pass);
        WiFi.begin("Telstra5B50AA", pass.c_str());
        delay(1000);
    }*/
}

void WiFiEvent(WiFiEvent_t event){
    switch(event) {
        case SYSTEM_EVENT_AP_START:
            Serial.println("AP Started");
            WiFi.softAPsetHostname("lol");
            break;
        case SYSTEM_EVENT_AP_STOP:
            Serial.println("AP Stopped");
            break;
        case SYSTEM_EVENT_STA_START:
            Serial.println("STA Started");
            WiFi.setHostname("lol");
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            Serial.println("STA Connected");
            WiFi.enableIpV6();
            break;
        case SYSTEM_EVENT_AP_STA_GOT_IP6:
            Serial.print("STA IPv6: ");
            Serial.println(WiFi.localIPv6());
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.print("STA IPv4: ");
            Serial.println(WiFi.localIP());
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("STA Disconnected");
            break;
        case SYSTEM_EVENT_STA_STOP:
            Serial.println("STA Stopped");
            break;
        default:
            break;
    }
}

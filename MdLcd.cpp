#include "MdLcd.h"
#include <M5Stack.h>

void MdLcd::displayJpgImage(const char* path)
{
    M5.Lcd.drawJpgFile(SD, path);
}

void MdLcd::displayJpgImageCoordinate(const char* path, uint16_t x, uint16_t y)
{
    M5.Lcd.drawJpgFile(SD, path, x, y);
}

void MdLcd::clearDisplay()
{
    M5.Lcd.clear();
}

void MdLcd::fillBackgroundWhite()
{
    M5.Lcd.fillScreen(0xFFFF);
}

void MdLcd::displayText(const char* text, int x, int y)
{
    M5.Lcd.setCursor(x, y);
    M5.Lcd.setTextColor(0x0000, 0xFFFF);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print(text);
}

void MdLcd::displayDateText(String text, int x, int y)
{
    M5.Lcd.setCursor(x, y);
    M5.Lcd.setTextColor(0x0000, 0xFFFF);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print(text);
}





/*if (MENU_WBGT ,  MENU_MUSIC) {
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD , MENU_WBGT_Y_CRD );
    }else if (MENU_WBGT , MENU_DATE) {
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD , MENU_WBGT_Y_CRD );
    }else if (MENU_MUSIC , MENU_MEASURE) {
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD , MENU_MUSIC_Y_CRD );
    }else if (MENU_MUSIC , MENU_WBGT){
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD , MENU_MUSIC_Y_CRD );
    }else if (MENU_MEASURE , MENU_MUSIC) {
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD , MENU_MEASURE_Y_CRD );
    }else if(MENU_MEASURE , MENU_WBGT){
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD , MENU_MEASURE_Y_CRD );
    }else if (MENU_DATE , MENU_WBGT) {
    mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD , MENU_DATE_Y_CRD );
    }else if(MENU_DATE , MENU_MEASURE){
    mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD , MENU_DATE_Y_CRD );
     }*/
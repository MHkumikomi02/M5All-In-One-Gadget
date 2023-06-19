#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;

const char* g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char* g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,  
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,  
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateMachine(State state, Action action)
{
    setState(state);
    setAction(action);

}

FocusState AppControl::getFocusState()
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)
{
    m_focus_state = fs;
}

void AppControl::displayTitleInit()
{
    mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH,TITLE_X_CRD,TITLE_Y_CRD );
}

void AppControl::displayMenuInit()
{
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD , MENU_WBGT_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD , MENU_MUSIC_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD , MENU_MEASURE_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD , MENU_DATE_Y_CRD );

    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH, COMMON_BUTTON_UP_X_CRD , COMMON_BUTTON_UP_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH, COMMON_BUTTON_DECIDE_X_CRD , COMMON_BUTTON_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH, COMMON_BUTTON_DOWN_X_CRD , COMMON_BUTTON_DOWN_Y_CRD);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{
  if(MENU_WBGT == current_state && next_state == MENU_MUSIC){  //音楽プレーヤーにフォーカス
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD , MENU_WBGT_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD , MENU_MUSIC_Y_CRD );
    setFocusState(MENU_MUSIC);
  }else if(MENU_WBGT == current_state && next_state ==MENU_DATE){ //時刻表示にフォーカス
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD , MENU_WBGT_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD , MENU_DATE_Y_CRD );
    setFocusState(MENU_DATE);
  }else if(MENU_MUSIC == current_state && next_state == MENU_MEASURE ){  //距離測定にフォーカス
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,  MENU_MUSIC_X_CRD , MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD , MENU_MEASURE_Y_CRD );
    setFocusState(MENU_MEASURE);
  }else if(MENU_MUSIC == current_state && next_state == MENU_WBGT ){  //熱中症にフォーカス
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,  MENU_MUSIC_X_CRD , MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD , MENU_WBGT_Y_CRD );
    setFocusState(MENU_WBGT);
  }else if( MENU_MEASURE== current_state && next_state == MENU_DATE ){  //時刻表示にフォーカス
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,  MENU_MEASURE_X_CRD , MENU_MEASURE_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD , MENU_DATE_Y_CRD );
    setFocusState(MENU_DATE);
  }else if( MENU_MEASURE== current_state && next_state == MENU_MUSIC ){  //音楽プレーヤーにフォーカス
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,  MENU_MEASURE_X_CRD , MENU_MEASURE_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD , MENU_MUSIC_Y_CRD );
    setFocusState(MENU_MUSIC);
  }else if(MENU_DATE == current_state && next_state == MENU_WBGT ){  //熱中症にフォーカス
   mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD , MENU_DATE_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD , MENU_WBGT_Y_CRD );
    setFocusState( MENU_WBGT);
  }else if(MENU_DATE == current_state && next_state == MENU_MEASURE ){  //距離測定にフォーカス
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD , MENU_DATE_Y_CRD );
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH,  MENU_MEASURE_X_CRD , MENU_MEASURE_Y_CRD );
    setFocusState(MENU_MEASURE);
  }

}

void AppControl::displayWBGTInit()
{
    double temperature;
    double humidity;
    WbgtIndex index;

    mwbgt.getWBGT(&temperature, &humidity, &index);
    

    if (index == SAFE) {
        mlcd.displayJpgImageCoordinate(COMMON_WBGT_safe_IMG_PATH, COMMON_WBGT_IMG_PATH_X_CRD, COMMON_WBGT_IMG_PATH_Y_100);
    } else if (index == ATTENTION) {
        mlcd.displayJpgImageCoordinate(COMMON_WBGT_attention_IMG_PATH, COMMON_WBGT_IMG_PATH_X_CRD, COMMON_WBGT_IMG_PATH_Y_100);
    } else if (index == ALERT) {
        mlcd.displayJpgImageCoordinate(COMMON_WBGT_alert_IMG_PATH, COMMON_WBGT_IMG_PATH_X_CRD, COMMON_WBGT_IMG_PATH_Y_100);
    } else if (index == HIGH_ALERT) {
        mlcd.displayJpgImageCoordinate(COMMON_WBGT_high_alert_IMG_PATH, COMMON_WBGT_IMG_PATH_X_CRD, COMMON_WBGT_IMG_PATH_Y_100);
    } else if (index == DANGER) {
        mlcd.displayJpgImageCoordinate(COMMON_WBGT_danger_IMG_PATH, COMMON_WBGT_IMG_PATH_X_CRD, COMMON_WBGT_IMG_PATH_Y_100);
    }

    mlcd.displayJpgImageCoordinate(COMMON_ORANGE_degree_IMG_PATH, COMMON_WBGT_IMG_PATH_253 , COMMON_WBGT_IMG_PATH_Y_CRD );
    mlcd.displayJpgImageCoordinate(COMMON_BLUE_percent_IMG_PATH, COMMON_WBGT_IMG_PATH_253 , COMMON_BLUE_IMG_PATH_Y_CRD ); 
    mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, COMMON_WBGT_IMG_PATH_186 , COMMON_WBGT_IMG_PATH_Y_CRD );
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, COMMON_WBGT_IMG_PATH_186 , COMMON_BLUE_IMG_PATH_Y_CRD );
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_WBGT_IMG_PATH_120 , COMMON_BUTTON_DOWN_Y_CRD );  
}


void AppControl::displayTempHumiIndex()
{
    double temperature;
    double humidity;
    WbgtIndex index;

    mwbgt.getWBGT(&temperature, &humidity, &index);

    int intTemperature = (int)temperature; // 温度を整数型に変換
    int intHumidity = (int)humidity; // 湿度を整数型に変換

    // 温度の整数部分を表示
    int digit = intTemperature / 10; // 十の位を取り出す
    mlcd.displayJpgImageCoordinate(g_str_orange[digit], COMMON_WBGT_IMG_PATH_120, COMMON_WBGT_IMG_PATH_Y_CRD);
    digit = intTemperature % 10; // 一の位を取り出す
    mlcd.displayJpgImageCoordinate(g_str_orange[digit], COMMON_WBGT_IMG_PATH_153, COMMON_WBGT_IMG_PATH_Y_CRD);

    // 温度の少数部分を表示
    double fractionPart = temperature - (int)temperature;
    if (fractionPart > 0.0) {
    digit = (int)(fractionPart * 10); // 一桁を取り出す
    mlcd.displayJpgImageCoordinate(g_str_orange[digit], COMMON_WBGT_IMG_PATH_220, COMMON_WBGT_IMG_PATH_Y_CRD);
    }

    // 湿度の整数部分を表示
    digit = intHumidity / 10; // 十の位を取り出す
    mlcd.displayJpgImageCoordinate(g_str_blue[digit], COMMON_WBGT_IMG_PATH_120, COMMON_BLUE_IMG_PATH_Y_CRD);
    digit = intHumidity % 10; // 一の位を取り出す
    mlcd.displayJpgImageCoordinate(g_str_blue[digit], COMMON_WBGT_IMG_PATH_153, COMMON_BLUE_IMG_PATH_Y_CRD);

    // 湿度の少数部分を表示
    fractionPart = humidity - (int)humidity;
    if (fractionPart > 0.0) {
    digit = (int)(fractionPart * 10); // 一桁を取り出す
    mlcd.displayJpgImageCoordinate(g_str_blue[digit], COMMON_WBGT_IMG_PATH_220, COMMON_BLUE_IMG_PATH_Y_CRD);
    }

}


void AppControl::displayMusicInit()
{

}

void AppControl::displayMusicStop()
{

}

void AppControl::displayMusicTitle()
{
}

void AppControl::displayNextMusic()
{

}

void AppControl::displayMusicPlay()
{

}

void AppControl::displayMeasureInit()
{

}

void AppControl::displayMeasureDistance()
{

}

void AppControl::displayDateInit()
{

}

void AppControl::displayDateUpdate()
{

}

void AppControl::controlApplication()
{
    mmplay.init();
 

    while (1) {

        switch (getState()) {
        case TITLE:
            switch (getAction()) {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
                displayTitleInit();
                setStateMachine(TITLE, DO);
                
                break;

            case DO:
                if(m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed){
                   setStateMachine(TITLE, EXIT);
                }
                
                break;

            case EXIT:
                setBtnAllFlgFalse();
                mlcd.clearDisplay();
                setStateMachine(MENU, ENTRY);
                break;
            default:
                break;
            }

            break;

        case MENU:

            switch (getAction()) {
            case ENTRY:
                displayMenuInit();
                setStateMachine(MENU, DO);
                break;

            
            case DO:
                if(m_flag_btnC_is_pressed){
                switch(getFocusState()){
                    case MENU_WBGT:
                        focusChangeImg(MENU_WBGT, MENU_MUSIC);
                        break;
                    case MENU_MUSIC:
                        focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                        break;
                    case MENU_MEASURE:
                        focusChangeImg(MENU_MEASURE, MENU_DATE);
                        break;
                    case MENU_DATE:
                        focusChangeImg(MENU_DATE, MENU_WBGT);
                        break;
                    }  
            }else if(m_flag_btnA_is_pressed){
                switch(getFocusState()){
                    case MENU_DATE:
                        focusChangeImg(MENU_DATE, MENU_MEASURE);
                        break;
                     case MENU_MEASURE:
                        focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                        break;
                    case MENU_MUSIC:
                        focusChangeImg(MENU_MUSIC, MENU_WBGT);
                        break;
                    case MENU_WBGT:
                        focusChangeImg(MENU_WBGT, MENU_DATE);
                        break;
                    }
            }else if(m_flag_btnB_is_pressed){
                switch(getFocusState()){
                    case MENU_WBGT:
                        focusChangeImg(MENU_DATE, MENU_WBGT);
                        mlcd.fillBackgroundWhite();
                        setStateMachine(WBGT, ENTRY);
                        break;
                    case MENU_MUSIC:
                        focusChangeImg(MENU_WBGT, MENU_MUSIC);
                        setStateMachine(MUSIC_PLAY, ENTRY);
                        break;
                    case MENU_MEASURE:
                        focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                        setStateMachine(MEASURE, ENTRY);
                        break;
                    case MENU_DATE:
                        focusChangeImg(MENU_MEASURE, MENU_DATE);
                        setStateMachine(DATE, ENTRY);
                        break;
                    }

            }
                setBtnAllFlgFalse();
                break;
            case EXIT:
                 setStateMachine(WBGT, ENTRY);
            default:
                break;
            }

            break;

        case WBGT:

            switch (getAction()) {
            case ENTRY:
            setStateMachine(WBGT, DO);
                break;

            case DO:
            displayWBGTInit();
            displayTempHumiIndex();
            setStateMachine(WBGT, EXIT);
                break;
            case EXIT: 
            if(m_flag_btnB_is_pressed){
            setStateMachine(MENU, DO);
            }
            break;

             break;
        }
        case MUSIC_STOP:
            switch (getAction()) {
            case ENTRY:
            setStateMachine(MUSIC_STOP, DO);
                break;

            case DO:
                break;

            case EXIT:
            setStateMachine(MENU, DO);
                break;

            default:
                break;
            }

            break;

        case MUSIC_PLAY:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
            setStateMachine(MENU, DO);
                break;

            default:
                break;
            }

            break;

        case MEASURE:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
            setStateMachine(MENU, DO);
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
            setStateMachine(MENU, DO);
                break;

            default:
                break;
            }

        default:
            break;
        }
    }
}

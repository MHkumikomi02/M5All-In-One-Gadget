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
    mlcd.clearDisplay();
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(Music_nowstopping_IMG_PATH, COMMON_WBGT_IMG_PATH_X_CRD , COMMON_WBGT_IMG_PATH_Y_CRD );
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, COMMON_BUTTON_UP_X_CRD , COMMON_BUTTON_UP_Y_CRD ); 
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_WBGT_IMG_PATH_120 , COMMON_BUTTON_UP_Y_CRD );
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, COMMON_BUTTON_DOWN_X_CRD , COMMON_BUTTON_UP_Y_CRD ); 
}

void AppControl::displayMusicStop()
{
    mmplay.init();
    mmplay.stopMP3();
}

void AppControl::displayMusicTitle()
{
    char* title =  mmplay.getTitle();
    mlcd.displayText(title, TITLE_X_CRD , COMMON_BUTTON_DECIDE_X_CRD);
}

void AppControl::displayNextMusic()
{
    
}

void AppControl::displayMusicPlay()
{
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(Music_nowplaying_IMG_PATH, COMMON_WBGT_IMG_PATH_X_CRD , COMMON_WBGT_IMG_PATH_Y_CRD );
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH, COMMON_BUTTON_UP_X_CRD , COMMON_BUTTON_UP_Y_CRD ); 
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_WBGT_IMG_PATH_120 , COMMON_BUTTON_UP_Y_CRD );
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, COMMON_BUTTON_DOWN_X_CRD , COMMON_BUTTON_UP_Y_CRD ); 
}

void startMusicPlayback()
{
    // 次の音楽ファイルを選択する
    mmplay.selectNextMusic();
    // 音楽の再生準備を行う
    mmplay.prepareMP3();
    // 音楽を再生する
    while (mmplay.isRunningMP3()) {
        mmplay.playMP3();
    }
    // 音楽再生が終了したら次の曲へ移動する
    mmplay.selectNextMusic();
}

void NextMusicPlay()
{   // 現在の音楽再生が終了しているか確認
    if (!mmplay.isRunningMP3()) {
        // 次の音楽ファイルを選択する
        mmplay.selectNextMusic();
        // 音楽の再生準備を行う
        mmplay.prepareMP3();
        // 音楽を再生する
        mmplay.playMP3();
    }
}

void StopMusic()
{
    if (mmplay.isRunningMP3()) {
        mmplay.stopMP3();
    }
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
            Serial.println("MENU ENTRY");
            mlcd.fillBackgroundWhite();
            displayMenuInit();
            setStateMachine(MENU, DO);
            break;

            
            case DO:
            Serial.println("MENU DO");
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
                        setBtnAllFlgFalse();
                        mlcd.clearDisplay();
                        mlcd.fillBackgroundWhite();
                        setStateMachine(WBGT, ENTRY);
                        break;
                    case MENU_MUSIC:
                        setBtnAllFlgFalse();
                        mlcd.clearDisplay();
                        mlcd.fillBackgroundWhite();
                        setStateMachine(MUSIC_STOP, ENTRY);
                        break;
                    case MENU_MEASURE:
                        setBtnAllFlgFalse();
                        mlcd.clearDisplay();
                        mlcd.fillBackgroundWhite();
                        setStateMachine(MEASURE, ENTRY);
                        break;
                    case MENU_DATE:
                        setBtnAllFlgFalse();
                        mlcd.clearDisplay();
                        mlcd.fillBackgroundWhite();
                        setStateMachine(DATE, ENTRY);
                        break;
                    }

            }
                setBtnAllFlgFalse();
                break;
            case EXIT:
            Serial.println("MENU EXIT");
            setStateMachine(WBGT, ENTRY);
            default:
                break;
            }

            break;

        case WBGT:

            switch (getAction()) {
            case ENTRY:
            Serial.println("WBGT ENTRY");
            setStateMachine(WBGT, DO);
            setBtnAllFlgFalse();
                break;

            case DO:
            Serial.println("WBGT DO");
            displayWBGTInit();
            displayTempHumiIndex();

            if(m_flag_btnB_is_pressed){
            setBtnAllFlgFalse();
            mlcd.clearDisplay();
            setStateMachine(WBGT, EXIT);
            }
            break;
            case EXIT:
            Serial.println("WBGT EXIT");
            setStateMachine(MENU, ENTRY);
            break;
           default:         
           setStateMachine(MENU, ENTRY);  
             break;
        }
            break;

        case MUSIC_STOP:
            switch (getAction()) {
            case ENTRY:
            Serial.println("MUSIC_STOP ENTRY");
            setBtnAllFlgFalse();
            displayMusicInit();
            displayMusicTitle();
            setStateMachine(MUSIC_STOP, DO); 
            break;

            case DO:
            Serial.println("MUSIC_STOP DO");
 
                if(m_flag_btnA_is_pressed){
                setBtnAllFlgFalse();
                displayMusicTitle();
                displayMusicPlay();
                startMusicPlayback();
                setStateMachine(MUSIC_PLAY, ENTRY);
                }else if(m_flag_btnB_is_pressed)
                {
                setBtnAllFlgFalse();
                mlcd.clearDisplay();
                setStateMachine(MENU, ENTRY);
                }else if(m_flag_btnC_is_pressed)
                {
                setBtnAllFlgFalse();
                mlcd.clearDisplay();
                setStateMachine(MUSIC_PLAY, ENTRY);
                }
                break;
            setStateMachine(MUSIC_STOP, EXIT);

            case EXIT:
            Serial.println("MUSIC_STOP EXIT");
            setBtnAllFlgFalse();
            mlcd.clearDisplay();
            setStateMachine(MENU, ENTRY);
                break;

            default:
            setStateMachine(MENU,ENTRY);
                break;
            }

            break;

        case MUSIC_PLAY:
             switch (getAction()) {
            case ENTRY:
            Serial.println("MUSIC_PLAY ENTRY");
            setBtnAllFlgFalse();
            displayMusicTitle();
            displayMusicPlay();
            startMusicPlayback();
            setStateMachine(MUSIC_STOP, EXIT);
            
                break;

            case DO:
            Serial.println("MUSIC_PLAY DO");
            
                if(m_flag_btnA_is_pressed){
                setBtnAllFlgFalse();
                StopMusic();
                setStateMachine(MUSIC_STOP, ENTRY);
                }

                if(m_flag_btnB_is_pressed){
                setBtnAllFlgFalse();
                mlcd.clearDisplay();
                setStateMachine(MUSIC_STOP, ENTRY);
    
            setStateMachine(MUSIC_PLAY, EXIT);
                break;

            case EXIT:
            Serial.println("MUSIC_PLAY EXIT");
            setStateMachine(MENU, ENTRY);
                break;

            default:
            setStateMachine(MENU, ENTRY);
                break;
             }
        }

            break;

        case MEASURE:

            switch (getAction()) {
            case ENTRY:
            Serial.println("MEASURE ENTRY");
            setStateMachine(MEASURE, DO);
                break;

            case DO:
            Serial.println("MEASURE DO");
            setStateMachine(MEASURE, EXIT);
                break;

            case EXIT:
            Serial.println("MEASURE EXIT");
            setStateMachine(MENU, ENTRY);
                break;

            default:
            Serial.println("MEASURE default");
            setStateMachine(MENU, ENTRY);
                break;
            }

            break;

        case DATE:
            switch (getAction()) {
            case ENTRY:
            Serial.println("DATE ENTRY");
            setStateMachine(DATE, DO);
                break;

            case DO:
            Serial.println("DATE DO");
            setStateMachine(MEASURE, EXIT);
                break;

            case EXIT:
            Serial.println("DATE EXIT");
            setStateMachine(MENU, ENTRY);
                break;

            default:
            Serial.println("DATE default");
            setStateMachine(MENU, ENTRY);
                break;
            }

        default:
        setStateMachine(MENU, ENTRY);
            break;
     
        }
    }
 
}

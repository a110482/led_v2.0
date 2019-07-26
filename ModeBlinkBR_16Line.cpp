//
// Created by elijah on 2019/1/28.
//

#include "ModeBlinkBR_16Line.h"

ModeBlinkBR_16Line::ModeBlinkBR_16Line(unsigned long interval) {
    this->interval = interval;
    this->_step = 0;
}

bool ModeBlinkBR_16Line::process(CRGB *leds_ptr, Range range) {
    unsigned long now = millis();
    if(now - this->_time_stamp < this->interval*(1+this->coefficient_of_correction/100.0)){ return false;}
    this->_time_stamp = now;

    //const CHSV color_red = CHSV(90, 255, 255);
    const CRGB color_red = CRGB(0, 255, 0);
    const CHSV color_blue = CHSV(160, 255, 255);

    // 等效於腳本 -> {紅, 關}x6 -> {藍, 關}x6
    if (this->_step % 2 == 1){
        for (int i = range.start_index; i<range.end_index; i++){
            leds_ptr[i] =  CHSV(0, 0, 0);
        }
    } else if(_step < 12){
        for (int i = range.start_index; i<range.end_index; i++){
            leds_ptr[i] =  color_red;
        }
    } else{
        for (int i = range.start_index; i<range.end_index; i++){
            leds_ptr[i] =  color_blue;
        }
    }

    // 一個循環需要24步驟
    _step += 1;
    if(_step >= 24){
        _step = 0;
    }
    return true;
}
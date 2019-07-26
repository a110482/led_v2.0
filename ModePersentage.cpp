//
//  ModePersentage.cpp
//  SetLedMode
//
//  Created by elijah tam on 2019/1/16.
//  Copyright © 2019 elijah tam. All rights reserved.
//

#include "ModePersentage.h"
ModePersentage::ModePersentage(uint8_t *persentage)
:ModePersentage(persentage, false)
{
}
ModePersentage::ModePersentage(uint8_t *persentage, bool need_reverse){
    this->_persentage = persentage;
    this->need_reverse = need_reverse;
    this->_time_stamp = 0;
    this->_interval = 40;
    this->_interval_increase = true;
}
int ModePersentage::_number_of_light_led(){
    float rate = *this->_persentage/100.0;
    return this->_number_each_line*rate;
}

bool ModePersentage::process(CRGB *leds_ptr, Range range){
    unsigned long time_now = millis();
    if((time_now - this->_time_stamp) <= this->_interval){
        return false;
    }
    this->_time_stamp = time_now;
    int light_led = this->_number_of_light_led();

    /*
    // 開始新的循環
    if (this->_step == 0){
        this->target_index = rand()%light_led;
    }
    */

    for(int i=range.start_index; i < range.end_index; i++){
        bool dir = true; // 表示當燈的序號是正向還是反向 (因為燈的多排序列是用S形編號)
        if (this->need_reverse){
            dir = i / this->_number_each_line%2 == 0;
        }
        if ((i % this->_number_each_line) < light_led && dir){
            int color = rand()%40;
            int brightness = rand()%500;
            if (brightness > 155){
                brightness = 155;
            }
            leds_ptr[i] = CHSV(235+color, 100+brightness, 255);
        }
        else if ((i % this->_number_each_line) >= (this->_number_each_line - light_led) && !dir){
            leds_ptr[i] = CHSV(0, 255, 255);
        }
        else{
            leds_ptr[i] = CHSV(100, 0, 150);
        }
    }

    // 調整時間
    if (_interval_increase){
        _interval += 10;
    } else{
        _interval -= 10;
    }

    // 時間上下界
    if (_interval > 60 || _interval < 40){
        _interval_increase = !_interval_increase;
    }

    return true;
}
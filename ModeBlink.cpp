//
// Created by elijah on 2019/1/11.
//

#include "ModeBlink.h"

ModeBlink::ModeBlink(unsigned long high_time,unsigned long low_time) {
    this->high_time = high_time;
    this->low_time = low_time;
    _time_stamp = 0;
    _led_is_high = false;
}
bool ModeBlink::process(CRGB *leds_ptr, Range range){
    unsigned long time_now = millis();
    if (_led_is_high && (time_now-_time_stamp) > low_time){
        _led_is_high = !_led_is_high;
        for(int i = range.start_index; i < range.end_index; i++){
            leds_ptr[i] = CHSV(97, 255, 255);
        }
        _time_stamp = time_now;
        return true;
    }
    else if (!_led_is_high && (time_now-_time_stamp) > high_time){
        _led_is_high = !_led_is_high;
        for(int i = range.start_index; i < range.end_index; i++){
            leds_ptr[i] = CHSV(0, 255, 0);
        }
        _time_stamp = time_now;
        return true;
    }
    return false;
}
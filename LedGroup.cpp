//
// Created by elijah on 2019/1/11.
//

#include "LedGroup.h"

LedGroup::LedGroup(int s_index, int e_index, CRGB *leds_ptr,  ModeProtocol *mode)
:LedGroup(s_index, e_index, leds_ptr, mode, LED_NUMBER_EACH_LINE)
{
}

LedGroup::LedGroup(int s_index, int e_index, CRGB *leds_ptr,  ModeProtocol *mode, int led_num_each_line) {
    start_index = s_index;
    end_index = e_index;
    this->mode = mode;
    this->leds_ptr = leds_ptr;
    this->led_num_each_line = led_num_each_line;
    Range range = Range(s_index, e_index, this->led_num_each_line);
    this->_range = range;
}

bool LedGroup::do_animate() {
    if (this->mode == NULL){
        return false;
    }
    return this->mode->process(this->leds_ptr, this->_range);
}
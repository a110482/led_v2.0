//
// Created by elijah on 2019/2/11.
//

#include "ModeBlack.h"

ModeBlack::ModeBlack() {}
bool ModeBlack::process(CRGB *leds_ptr, Range range) {
    for(int i = range.start_index; i< range.end_index; i++){
        leds_ptr[i] = CHSV(97, 255, 0);
    }
    return true;
}
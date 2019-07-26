//
// Created by elijah on 2019/1/11.
//

#ifndef SETLEDMODE_MODEBLINK_H
#define SETLEDMODE_MODEBLINK_H


#include "ModeProtocol.h"
class CRGB;
class LedGroup;

class ModeBlink: public ModeProtocol {
public:
    /**
     * @param high_time     亮燈的時間
     * @param low_time      暗燈的時間
     */
    ModeBlink(unsigned long high_time,unsigned long low_time);
    unsigned long high_time;    // 保持亮的時間
    unsigned long low_time;     // 暗的時間
    virtual bool process(CRGB *leds_ptr, Range range);
private:
    unsigned long _time_stamp;  // 計時器
    bool _led_is_high;  // 紀錄現在led是否為高電位
};


#endif //SETLEDMODE_MODEBLINK_H

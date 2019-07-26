//
// Created by elijah on 2019/1/11.
//

#ifndef SETLEDMODE_MODEDIRECTION_H
#define SETLEDMODE_MODEDIRECTION_H

#include "ModeProtocol.h"
#include "SLMConfig.h"

class CRGB;
class LedGroup;


class ModeDirection: public ModeProtocol {
public:
    /**
     * @param turn_right    true是右轉 false是左轉
     * @param _interval     閃爍頻率
     * @param fade_out_scale    淡出亮度  數字越大 淡化效果越大 (0- > 255)
     */
    ModeDirection(bool turn_right, unsigned long _interval, int fade_out_scale);
    bool turn_right;   // 左轉或右轉
    unsigned long _interval;    // 刷新速度 多久會跑完一次循環(單排)
    int fade_out_scale;    // 淡出速度
    virtual bool process(CRGB *leds_ptr, Range range);
private:
    unsigned long _time_stamp;  // 計時器
    void _fade_all(CRGB *leds_ptr, Range range);    // 淡化所有的led
    int _get_light_row_and_count(Range range);      // 取得當前應點亮排數
    int _light_row;      // 現在準備點亮第幾排;
    int _delay_times;   // 延遲每個循環間的間隔
};


#endif //SETLEDMODE_MODEDIRECTION_H

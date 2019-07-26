//
// Created by elijah on 2019/1/25.
//

#ifndef LIBRARIES_WATERLEVEL_H
#define LIBRARIES_WATERLEVEL_H

#include "ModeProtocol.h"

class ModeWaterLevel: public ModeProtocol {
public:
    ModeWaterLevel();
    /**
     * @param level 水的高度 0~100
     * @param color 0是無色   1是藍色   2 是綠色   3是黃色
     * @param interval 時間間隔 單位毫秒
        */
    ModeWaterLevel(uint8_t *level, int color, int interval);
    virtual bool process(CRGB *leds_ptr, Range range);
private:
	uint8_t *level;
    int color;
    int _interval;
    unsigned long _time_stamp;
    CHSV get_color_setting();
};


#endif //LIBRARIES_WATERLEVEL_H

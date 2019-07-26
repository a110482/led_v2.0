//
//  ModePersentage.h
//  SetLedMode
//
//  Created by elijah tam on 2019/1/16.
//  Copyright © 2019 elijah tam. All rights reserved.
//

#ifndef ModePersentage_h
#define ModePersentage_h

#include "ModeProtocol.h"
#include "SLMConfig.h"


class ModePersentage: public ModeProtocol{
public:
    /**
     * @param persentage   水位高度 (換算成百分比 輸入 0->100)
     * @param need_reverse      燈排列是否有反序
     */
    ModePersentage(uint8_t *persentage, bool need_reverse);
    ModePersentage(uint8_t *persentage); // 0~100;
    virtual bool process(CRGB *leds_ptr, Range range);
private:
	uint8_t *_persentage;     // 百分比
    int _number_each_line = SIDE_LED_NUMBER_EACH_LINE;
    int _number_of_light_led();      // 每行要點亮幾顆燈
    unsigned long _interval;
    unsigned long _time_stamp;
    bool need_reverse;
    bool _interval_increase;
};

#endif /* ModePersentage_h */




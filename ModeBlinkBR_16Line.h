//
// Created by elijah on 2019/1/28.
//

#ifndef LIBRARIES_MODEBLINKBR_16LINE_H
#define LIBRARIES_MODEBLINKBR_16LINE_H

#include "ModeProtocol.h"

/**
 * @class  紅藍燈閃爍模式 for 16排燈用的
 */
class ModeBlinkBR_16Line: public ModeProtocol {
public:
    /**
     * @param interval  時間間隔
     */
    ModeBlinkBR_16Line(unsigned long interval);
    virtual bool process(CRGB *leds_ptr, Range range);

private:
    int _step;     // 紀錄正在哪個步驟
    unsigned long _time_stamp;
};


#endif //LIBRARIES_MODEBLINKBR_16LINE_H

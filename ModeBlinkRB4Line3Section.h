//
// Created by elijah on 2019/1/24.
//

#ifndef LIBRARIES_ModeBlinkRB4Line3Section_H
#define LIBRARIES_ModeBlinkRB4Line3Section_H

#include "ModeProtocol.h"
class CRGB;
class LedGroup;
/**
 * @class 把燈條切成三段的腳本操作模式
 */
class ModeBlinkRB4Line3Section: public ModeProtocol {
public:
    /**
     * @param step_time  每步驟的時間間隔
     * @param script_len    腳本長度
     * @param script    腳本檔案 請參閱 ModeBlinkRB4Line3SectionScript.h
     * @param need_reverse   燈條是否正反排列
     */
    ModeBlinkRB4Line3Section(int interval, int script_len, char script[][12], bool need_reverse);
    ModeBlinkRB4Line3Section(int interval, int script_len, char script[][12]);
    bool need_reverse;
    char *script;     // 腳本: '0' 表示off '1' 表示紅  '2' 表示藍色
    int bright;
    virtual bool process(CRGB *leds_ptr, Range range);
    int _step;  // 紀錄現在執行到哪一個腳本
private:
    int script_len; // 腳本長度
    unsigned long _time_stamp;  // 計時器
    int _section_0;  // 第一節數量
    int _section_1;  // 第二節
    int _section_2;
    void set_sections(int led_number_each_line);
};


#endif //LIBRARIES_ModeBlinkRB4Line3Section_H

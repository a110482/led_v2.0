//
// Created by elijah on 2019/2/12.
//

#ifndef LIBRARIES_ModeBlinkRB4Line5Section_H
#define LIBRARIES_ModeBlinkRB4Line5Section_H

#include "ModeProtocol.h"
#include "SLMConfig.h"

class CRGB;
class LedGroup;
/**
 * 把17d顆led燈拆成5段
 */

class ModeBlinkRB4Line5Section: public ModeProtocol {
public:
    /**
     * @param step_time  每一偵的時間間隔
     * @param script_len  腳本總長度
     * @param script  腳本  參閱  ModeBlinkRB4Line5SectionScript.h
     * @param need_reverse  是否需要反序(反序還沒做好)
     */
    ModeBlinkRB4Line5Section(int interval, int script_len, char script[][5], bool need_reverse);
    ModeBlinkRB4Line5Section(int interval, int script_len, char script[][5]);
    bool need_reverse;
    char *script;     // 腳本: '0' 表示off '1' 表示紅  '2' 表示藍色
    int bright;
    virtual bool process(CRGB *leds_ptr, Range range);
    int _step;  // 紀錄現在執行到哪一個腳本
private:
    int script_len; // 腳本長度
    unsigned long _time_stamp;  // 計時器
	const int *_section = led_cut_into_five_section_setting;
    void set_sections(int led_number_each_line);
};


#endif //LIBRARIES_ModeBlinkRB4Line5Section_H

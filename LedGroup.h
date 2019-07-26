//
// Created by elijah on 2019/1/11.
//

#ifndef SETLEDMODE_LEDGROUP_H
#define SETLEDMODE_LEDGROUP_H

#include "ModeProtocol.h"
#include "SLMConfig.h"
#include "Range.h"
/**
 * @class  // 記錄一個群組的led 通常是一整塊燈片
 */

class LedGroup {
public:
    /**
     * @param s_index   led起始index
     * @param e_index    led終點index
     * @param leds_ptr      fastLed 物件 拿來對led下指令用的
     * @param mode      模式class
     * @param led_num_each_line
     */
    LedGroup(int s_index, int e_index, CRGB *leds_ptr,  ModeProtocol *mode, int led_num_each_line);
    LedGroup(int s_index, int e_index, CRGB *leds_ptr,  ModeProtocol *mode);
    int start_index; // led 起點位置
    int end_index;
    int led_num_each_line;
    ModeProtocol *mode;
    CRGB *leds_ptr;
    bool do_animate();  // 對mode物件下指令開始繪製led燈
    Range _range;
private:

};


#endif //SETLEDMODE_LEDGROUP_H

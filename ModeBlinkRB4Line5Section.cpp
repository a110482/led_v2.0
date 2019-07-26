//
// Created by elijah on 2019/2/12.
//

#include "ModeBlinkRB4Line5Section.h"

// 預設不反序
ModeBlinkRB4Line5Section::ModeBlinkRB4Line5Section(int interval, int script_len, char script[][5], bool need_reverse){
    this->interval = interval;
    this->script = &script[0][0];
    this->need_reverse = need_reverse;
    this->_time_stamp = millis();
    this->_step = 0;
    this->bright = 255;
    this->script_len = script_len;
}
ModeBlinkRB4Line5Section::ModeBlinkRB4Line5Section(int interval, int script_len, char script[][5])
        :ModeBlinkRB4Line5Section(interval, script_len, script, false)
{
}
bool ModeBlinkRB4Line5Section::process(CRGB *leds_ptr, Range range){
    // 時間間隔
    unsigned long time_now = millis();
    if ((time_now - this->_time_stamp) < this->interval*(1 + this->coefficient_of_correction / 100.0)){ return false;}
    this->_time_stamp = time_now;

    // 讀取相對應的script
    char *script_now = (this->script + 5*this->_step);

    this->_step += 1;
    if (this->_step >= this->script_len){this->_step=0;}
    // 點燈
    bool reverse;
    for (int i=range.start_index; i<range.end_index; i++){
        reverse = i/range.led_num_each_line%2 != 0;  // 是否需要反序
        int res_i = i;    // 0 1 2 3 4 5 to 0 1 2 5 4 3
        if (reverse && this ->need_reverse){
            int n = i%range.led_num_each_line;   // 正在屬第幾顆
            int row = i/range.led_num_each_line;
            int max = (row + 1)*range.led_num_each_line - 1;
            res_i = max - n;
        }

        // 開始點燈  判斷腳本範圍落點用i
        // 下燈光指令用 res_i
        char led_color_code = '0';    // 黑色
        int index_of_line = i%range.led_num_each_line;  //正在屬第幾顆

        int section = 0;    // 正在第幾節
        int section_index_buffer = 0;
        for (section = 0; section < 5; section++){
            section_index_buffer += this->_section[section];
            if (section_index_buffer > index_of_line){
                break;
            }
        }


        led_color_code = *(script_now+section); //找到單筆顏色設定黨位置
        // 下命令
        if (led_color_code == '1'){
            leds_ptr[res_i] = CHSV(97, 255, this->bright);   // 紅色
        } else if (led_color_code == '2'){
            leds_ptr[res_i] = CHSV(0, 255, this->bright);  // 藍色
        }else if (led_color_code == '3') {
            leds_ptr[res_i] = CHSV(0, 0, this->bright);  // 白色
        }else{
            leds_ptr[res_i] = CHSV(160, 255, 0);
        }
    }
    return true;
}

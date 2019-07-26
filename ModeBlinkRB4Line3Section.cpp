//
// Created by elijah on 2019/1/24.
//

#include "ModeBlinkRB4Line3Section.h"

// 預設不反序
ModeBlinkRB4Line3Section::ModeBlinkRB4Line3Section(int interval, int script_len, char script[][12], bool need_reverse){
    this->interval = interval;
    this->script = &script[0][0];
    this->need_reverse = need_reverse;
    this->_time_stamp = millis();
    this->_step = 0;
    this->_section_0 = 0;
    this->_section_1 = 0;
    this->_section_2 = 0;
    this->bright = 255;
    this->script_len = script_len;
}
ModeBlinkRB4Line3Section::ModeBlinkRB4Line3Section(int interval, int script_len, char script[][12])
:ModeBlinkRB4Line3Section(interval, script_len, script, false)
{
}
bool ModeBlinkRB4Line3Section::process(CRGB *leds_ptr, Range range){
    // 時間間隔
    unsigned long time_now = millis();
    if ((time_now - this->_time_stamp) < this->interval*(1 + this->coefficient_of_correction / 100.0)){ return false;}
    this->_time_stamp = time_now;

    // 計算每小組燈有幾棵
    this->set_sections(range.led_num_each_line);

    // 讀取相對應的script
    char *script_now = (this->script + 12*this->_step);

    this->_step += 1;
    if (this->_step >= this->script_len){this->_step=0;}
    //Serial.println(_step);
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
        int section;    // 正在第幾節
        if (index_of_line >= (this->_section_0 + this->_section_1)){
            section = 2;
        } else if (index_of_line >= this->_section_0){
            section = 1;
        } else{
            section = 0;
        }
        int setting_index = (i-range.start_index)/range.led_num_each_line*3 + section; //找到單筆設定黨位置

        led_color_code = *(script_now+setting_index);
        // 下命令
        if (led_color_code == '1'){
            leds_ptr[res_i] = CHSV(97, 255, this->bright);   // 紅色
        } else if (led_color_code == '2'){
            leds_ptr[res_i] = CHSV(0, 255, this->bright);  // 藍色
        } else{
            leds_ptr[res_i] = CHSV(160, 255, 0);
        }
    }
    return true;
}

void ModeBlinkRB4Line3Section::set_sections(int led_number_each_line){
    if (this->_section_0 != 0){ return;}
    int res = led_number_each_line/3;
    this->_section_0 = this->_section_2 = res;
    this->_section_1 = led_number_each_line - 2*res;
}
//
// Created by elijah on 2019/1/25.
//

#include "ModeWaterLevel.h"

ModeWaterLevel::ModeWaterLevel() {}
ModeWaterLevel::ModeWaterLevel(uint8_t *level, int color, int interval) {
    this->level = level;
    this->color = color;
    this->_interval = interval;
    this->_time_stamp = 0;
}

bool ModeWaterLevel::process(CRGB *leds_ptr, Range range) {
    unsigned long now = millis();
    if (now - this->_time_stamp < _interval){ return false;}
    this->_time_stamp = now;

    // 計算單排顯示幾顆
    int level_val = *this->level;
    int len = level_val*(range.led_num_each_line - 2)/100 + 2;    // 最下面兩顆要做外框

    for (int i = range.start_index; i<range.end_index; i++){
        // 設定顏色
        CHSV color_setting = this->get_color_setting();
        CHSV color_black = CHSV(40, 255, 0);
        // 填充
        leds_ptr[i] = (i-range.start_index)/range.led_num_each_line <= len ? color_setting:color_black;

        // 描繪外框
        // 右側
        if ((i-range.start_index)%range.led_num_each_line <= 1){
            leds_ptr[i] = CHSV(100, 255, 255);
        }
        // 左側
        else if ((i-range.start_index)%range.led_num_each_line >= 14){
            leds_ptr[i] = CHSV(100, 255, 255);
        }
        // 底部
        else if ((i-range.start_index) < range.led_num_each_line*2){
            leds_ptr[i] = CHSV(100, 255, 255);
        }
    }
    /*
    // 描繪外框
    // 右側
    int bound_buffer = range.start_index+range.led_num_each_line*2;
    for(int i = range.start_index; i<bound_buffer; i++){
        leds_ptr[i] = CHSV(40, 255, 255);
    }
    // 左側
    bound_buffer = range.end_index - range.led_num_each_line*2;
    for(int i = range.end_index - 1; i > bound_buffer - 1; i--){
        leds_ptr[i] = CHSV(40, 255, 255);
    }
    // 底部
    bound_buffer = (range.end_index - range.start_index)/range.led_num_each_line;
    for(int i = 0; i<bound_buffer; i++){
        if (i%2 == 0){
            int index = range.start_index + i*range.led_num_each_line;
            leds_ptr[index] = CHSV(40, 255, 255);
            leds_ptr[index+1] = CHSV(40, 255, 255);
        } else{
            int index = range.start_index + (i + 1)*range.led_num_each_line;
            leds_ptr[index-1] = CHSV(40, 255, 255);
            leds_ptr[index-2] = CHSV(40, 255, 255);
        }
    }
     */
    return true;
}

CHSV ModeWaterLevel::get_color_setting() {
    int r = rand()%155;
    if (this->color == 0){
        return CHSV(90, 255, 0);
    }
    else if (this->color == 1){
        return CHSV(160, 255, r+100); // 藍
    }
    else if (this->color == 2){
        return CHSV(90, 255, r+100);  // 紅
    }
    else if (this->color == 3){
        return CHSV(45, 255, r+100);  // 黃
    }
    else{
        return CHSV(90, 255, r+100);
    }
}
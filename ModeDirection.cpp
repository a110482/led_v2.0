//
// Created by elijah on 2019/1/11.
//

#include "ModeDirection.h"

ModeDirection::ModeDirection(bool turn_right, unsigned long _interval, int fade_out_scale) {
    this-> turn_right = turn_right;
    this-> _interval = _interval;
    this-> fade_out_scale = fade_out_scale;
    _time_stamp = 0;
    _delay_times = 0;
}

bool ModeDirection::process(CRGB *leds_ptr, Range range) {
    unsigned long time_now = millis();
    if  ((time_now - _time_stamp) < _interval){ // 是否要刷新led
        return false;
    }
    _time_stamp = time_now;

    // 淡出
    for (int i = range.start_index; i < range.end_index; i++) {
        leds_ptr[i] -= CRGB(0, fade_out_scale*2, fade_out_scale);
        //leds_ptr[i].nscale8(fade_out_scale);  // 官方範例的淡出方法 實測比較沒效率
    }

    // 延遲第一排點亮
    if(_delay_times > 0){
        _delay_times -= 1;
        return true;
    }

    int start_index = this->_get_light_row_and_count(range) * range.led_num_each_line + range.start_index;
    int end_index = start_index + range.led_num_each_line;
    // 點亮新的整排led
    for(int i=start_index; i < end_index; i++ ){
        leds_ptr[i] = CRGB(0, 255, 120);
    }

    // 已點亮最後一排 加入延遲點亮
    if((start_index == range.start_index && turn_right) || (end_index == range.end_index && !turn_right)){
        _delay_times = 5;
    }
    return true;
}

void ModeDirection::_fade_all(CRGB *leds_ptr, Range range) {
    for (int i = range.start_index; i < range.end_index; i++) {
        leds_ptr[i].nscale8(fade_out_scale);
    }
}

int ModeDirection::_get_light_row_and_count(Range range){
    const int max_row_number = (range.end_index - range.start_index)/range.led_num_each_line;
    // 準備跳排
    if (turn_right){
        _light_row -= 1;
    }
    else{
        _light_row += 1;
    }

    // 檢查上下界
    if (_light_row < 0){
        _light_row = max_row_number - 1;
    }
    else if(_light_row >= max_row_number){
        _light_row = 0;
    }
    return _light_row;
}

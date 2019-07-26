//
// Created by elijah on 2019/1/14.
//

#include "Range.h"

Range::Range() {}
/**
 * @param start_index   起始位置
 * @param end_index     終點位置
 * @param led_num_each_line     每排有幾棵燈
 */
Range::Range(int start_index, int end_index, int led_num_each_line) {
    this->start_index = start_index;
    this->end_index = end_index;
    this->led_num_each_line = led_num_each_line;
}
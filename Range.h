//
// Created by elijah on 2019/1/14.
//

#ifndef SETLEDMODE_RANGE_H
#define SETLEDMODE_RANGE_H


class Range {
public:
    Range();
    Range(int, int, int);
    int start_index; // led 起點位置
    int end_index;
    int led_num_each_line;
};


#endif //SETLEDMODE_RANGE_H

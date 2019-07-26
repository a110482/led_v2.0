//
// Created by elijah on 2019/1/11.
//

#ifndef SETLEDMODE_MODEPROTOCOL_H
#define SETLEDMODE_MODEPROTOCOL_H

#include "Range.h"
#include "FastledBridgePath.h"


class CRGB;
class LedGroup;
/**
 * @class 規定mode的格式
 */
class ModeProtocol {
public:
	unsigned long interval = 200; // 基礎循環時間
	float coefficient_of_correction = 100;	// 0~100 但實際在計算時間最多只會把時間變成兩倍(100=2倍)
	bool active_correction = false;
    virtual bool process(CRGB *leds_ptr, Range range);
};


#endif //SETLEDMODE_MODEPROTOCOL_H

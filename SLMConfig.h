//
//  SLMConfig.h
//  SetLedMode
//
//  Created by elijah tam on 2019/1/16.
//  Copyright © 2019 elijah tam. All rights reserved.
//

#ifndef SLMConfig_h
#define SLMConfig_h
#pragma once

/**
 *  預設每排有 16棵燈
 */
#define LED_NUMBER_EACH_LINE 16
#define SIDE_LED_NUMBER_EACH_LINE 14   // 每pin接多少燈
//const int led_cut_into_five_section_setting[5] = { 3, 4, 3, 4, 3 };		// 17顆燈
const int led_cut_into_five_section_setting[5] = { 3, 3, 2, 3, 3 };		// 14

#define LED_NUM_TOP 256     // 上方led燈數量
#define NUM_LED   SIDE_LED_NUMBER_EACH_LINE*14 + LED_NUM_TOP      // 總數量



#ifndef DATA_PIN_TOP
#define DATA_PIN_TOP 18   // 上
#endif

#ifndef DATA_PIN_LEFT_FRONT
#define DATA_PIN_LEFT_FRONT 16   // 左前
#endif

#ifndef DATA_PIN_LEFT_BACK
#define DATA_PIN_LEFT_BACK 14   // 左後
#endif

#ifndef DATA_PIN_LEFT_BACK_2
#define DATA_PIN_LEFT_BACK_2 12   // 左後
#endif

#ifndef DATA_PIN_RIGHT_FRONT
#define DATA_PIN_RIGHT_FRONT 10   // 右前
#endif

#ifndef DATA_PIN_RIGHT_BACK
#define DATA_PIN_RIGHT_BACK 8   // 右後
#endif

#ifndef DATA_PIN_RIGHT_BACK_2
#define DATA_PIN_RIGHT_BACK_2 6   // 右後
#endif

#ifndef DATA_PIN_BACK_LEFT
#define DATA_PIN_BACK_LEFT 4   // 後左
#endif

#ifndef DATA_PIN_BACK_RIGHT
#define DATA_PIN_BACK_RIGHT 2   // 後右
#endif

#define BLINK_SPEED 50      // 燈條 暴閃間隔(ms)
#define BLINK_SPEED_256 50  // 256燈 暴閃間隔(ms)
#define DIR_SPEED 150       // 方向燈速度 (每條中間間格)
#define FADE_OUT_SCALE 30   // 方向燈淡出速度 (數字越大 維持亮的時間越短)

#endif /* SLMConfig_h */
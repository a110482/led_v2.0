#include "SLM.h"
#include "FastLED.h"
#pragma once
#include <Wire.h>

//#define NEED_HIDE_LED_FUNCTION	// 隱藏led方向燈等功能(只顯示水位計) 如不需要請註解

struct ModbusData {
	uint8_t led_mode_setting;
	uint8_t led_speed;
	uint8_t led_flash_light_display_mode;
	uint8_t water_level;
	uint8_t led_square_switch;
};

ModbusData modbus_data;


CRGB leds_0[NUM_LED]; 
LedGroup group_left = LedGroup(0, SIDE_LED_NUMBER_EACH_LINE *5, leds_0, NULL, SIDE_LED_NUMBER_EACH_LINE);
LedGroup group_right = LedGroup(SIDE_LED_NUMBER_EACH_LINE *5, SIDE_LED_NUMBER_EACH_LINE *10, leds_0, NULL, SIDE_LED_NUMBER_EACH_LINE);
LedGroup group_back = LedGroup(SIDE_LED_NUMBER_EACH_LINE *10, SIDE_LED_NUMBER_EACH_LINE *14, leds_0, NULL, SIDE_LED_NUMBER_EACH_LINE);
LedGroup group_left_top = LedGroup(SIDE_LED_NUMBER_EACH_LINE *14, SIDE_LED_NUMBER_EACH_LINE *14 + 256, leds_0, NULL, 16);

LedGroup *groups[] = {
  &group_left_top,
  &group_left,
  &group_right,
  &group_back,
  NULL
};


// command
// 對應狀態碼   0000  0010     0110         0011      0100  0001   0101   0111
enum FLASH_MODE{OFF, BLINK=8, BREAK, RIGHT, BREAK_RIGHT, LEFT, BREAK_LEFT, WATER_LEVEL=15};
enum LED_SQUARE_MODE{SQ_OFF, SQ_ON};

uint8_t black = 0; // 為了用水位功能設置全黑
//int mode_setting_code[4] = {0,0,0,0};  //讀取自電位 會轉換成設定模式 FLASH_MODE
FLASH_MODE mode_setting = FLASH_MODE(OFF);    // 設定的模式
FLASH_MODE mode_now = FLASH_MODE(OFF);    // 正在閃的模式
LED_SQUARE_MODE led_square_mode_setting = LED_SQUARE_MODE(SQ_OFF);    // 方形燈設定的模式
LED_SQUARE_MODE led_square_mode_now = LED_SQUARE_MODE(SQ_OFF);    // 方形燈設定的模式

void setup() {
  // LED
  Serial.begin(9600);
  // for test
  //modbus_data.led_mode_setting = 4;

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

  LEDS.addLeds<WS2812, DATA_PIN_LEFT_FRONT, RGB>(leds_0, 0, SIDE_LED_NUMBER_EACH_LINE);    // 左前
  LEDS.addLeds<WS2812, DATA_PIN_LEFT_BACK, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE, SIDE_LED_NUMBER_EACH_LINE*2);   // 左後
  LEDS.addLeds<WS2812, DATA_PIN_LEFT_BACK_2, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE*3, SIDE_LED_NUMBER_EACH_LINE*2);   // 左後

  LEDS.addLeds<WS2812, DATA_PIN_RIGHT_FRONT, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE*5, SIDE_LED_NUMBER_EACH_LINE);   // 右前
  LEDS.addLeds<WS2812, DATA_PIN_RIGHT_BACK, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE*6, SIDE_LED_NUMBER_EACH_LINE*2);   // 右後
  LEDS.addLeds<WS2812, DATA_PIN_RIGHT_BACK_2, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE*8, SIDE_LED_NUMBER_EACH_LINE*2);   // 右後

  LEDS.addLeds<WS2812, DATA_PIN_BACK_LEFT, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE*10, SIDE_LED_NUMBER_EACH_LINE*2);    // 後左
  LEDS.addLeds<WS2812, DATA_PIN_BACK_RIGHT, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE*12, SIDE_LED_NUMBER_EACH_LINE*2);    // 後右
  LEDS.addLeds<WS2812, DATA_PIN_TOP, RGB>(leds_0, SIDE_LED_NUMBER_EACH_LINE*14, LED_NUM_TOP);    // 上方
  LEDS.setBrightness(100);
  LEDS.clear();
  FastLED.show();
  Serial.println("led v2.02 init");
}

void loop() {
	// 調整模式
	unsigned long now = millis();
	static unsigned long st = 0;

	load_mode_setting();
	update_setting();

    // led
	int i = 0;
	bool need_display = false;
	while (groups[i] != NULL) {
		if (groups[i]->do_animate()) {
			need_display = true;
		}
		i++;
	}
	if (need_display) {
		FastLED.show();
	}
	
    
  
  if (Serial.available()) {
	  char cmd = 'x';
	  while (Serial.available())
	  {
		  cmd = Serial.read();
		  delay(1);
	  }
	  if (cmd == '0') {
		  mode_setting = FLASH_MODE(OFF);
	  }
	  if (cmd == '1') {
		  mode_setting = FLASH_MODE(BLINK);
	  }
	  if (cmd == '7') {
		  mode_setting = FLASH_MODE(WATER_LEVEL);;
	  }
  }
}
unsigned long _time_stamp = 0;
// 從電位讀取狀態 並轉換為設定

void load_mode_setting(){
	unsigned long now = millis();
	// 顯示模式
	static int last_mode = -1;
	static int last_led_square_mode = -1;
	static int last_falsh_light_display_mode = -1;
	static int last_led_speed = -1;

	int mode_code = modbus_data.led_mode_setting;
	int led_square_mode_code = modbus_data.led_square_switch;
#ifdef NEED_HIDE_LED_FUNCTION
	if (mode_code != 15) {
		mode_code = 0;
	}
#endif

	static unsigned long st = 0;
	//  顯示模式
	if (last_mode != mode_code && now - st > 100) {
		last_mode = mode_code;
		st = now;
		mode_setting = FLASH_MODE(mode_code);
		last_falsh_light_display_mode = -1;
		last_led_speed = -1;
		return;		// 一次只做一件事
	}

	//  方形燈顯示模式
	if (last_led_square_mode != led_square_mode_code && now - st > 100) {
		last_led_square_mode = led_square_mode_code;
		st = now;
		led_square_mode_now = LED_SQUARE_MODE(led_square_mode_code);
		last_falsh_light_display_mode = -1;
		last_led_speed = -1;
		return;		// 一次只做一件事
	}

	// 報閃模式
	
	int display_mode = modbus_data.led_flash_light_display_mode;
	display_mode = display_mode < 0 ? 0 : display_mode > 3 ? 3 : display_mode;
	if (last_falsh_light_display_mode != display_mode) {
		last_falsh_light_display_mode = display_mode;
		mode_now = FLASH_MODE(OFF);	// 強迫重繪led
		last_led_speed = -1;
		return;
	}

	// 報閃速度
	int led_speed = modbus_data.led_speed;
	led_speed = led_speed < 0 ? 0 : led_speed > 100 ? 100 : led_speed;
	if (last_led_speed != led_speed) {
		last_led_speed = led_speed;
		float coefficient_of_correction = 100 - led_speed;
		group_left_top.mode->coefficient_of_correction = coefficient_of_correction;
		group_left.mode->coefficient_of_correction = coefficient_of_correction;
		group_right.mode->coefficient_of_correction = coefficient_of_correction;
		group_back.mode->coefficient_of_correction = coefficient_of_correction;
		return;
	}
}

/*
	取得報閃燈模式
*/
ModeProtocol* get_flash_mode_class() {
	switch (modbus_data.led_flash_light_display_mode)
	{
	case 1:
		return new ModeBlinkRB4Line5Section(BLINK_SPEED, 24, script_blink_br_7, true);
	case 2:
		return new ModeBlinkRB4Line3Section(BLINK_SPEED, 24, script_blink_br, true);
	case 3:
		return new ModeBlinkRB4Line5Section(BLINK_SPEED, 24, script_blink_br_6, true);
	default:
		return new ModeBlack();
	}
}

/*
	取得方形燈的閃爍模式
*/
ModeProtocol* get_led_square_mode_class() {
	switch (modbus_data.led_square_switch)
	{
	case 0:
		return new ModeBlack();
		break;
	case 1:
		return new ModeBlinkBR_16Line(BLINK_SPEED_256);
		break;
	default:
		return new ModeBlack();
		break;
	}
}

void update_setting(){
    if(mode_setting == mode_now && led_square_mode_now == led_square_mode_setting){return;}
    mode_now = mode_setting;
	led_square_mode_now = led_square_mode_setting;
    Serial.print("mode: ");
    Serial.println(mode_now);

    del_all_mode();
    LEDS.clear();
    if(mode_now == OFF){
		group_left_top.mode = get_led_square_mode_class();
		group_left.mode = new ModeBlack();
		group_right.mode = new ModeBlack();
		group_back.mode = new ModeBlack();
    }
    else if (mode_now == BREAK){
        group_left_top.mode = get_led_square_mode_class();
        group_left.mode = get_flash_mode_class();
        group_right.mode = get_flash_mode_class();
        group_back.mode = new ModeBlink(BLINK_SPEED, BLINK_SPEED);
    }
    else if (mode_now == BREAK_LEFT){
        group_left_top.mode = get_led_square_mode_class();
        group_left.mode = new ModeDirection(true, DIR_SPEED, FADE_OUT_SCALE);
        group_right.mode = get_flash_mode_class();
        group_back.mode = new ModeBlink(BLINK_SPEED, BLINK_SPEED);
    }
    else if (mode_now == BREAK_RIGHT){
        group_left_top.mode = get_led_square_mode_class();
        group_left.mode = get_flash_mode_class();
        group_right.mode = new ModeDirection(true, DIR_SPEED, FADE_OUT_SCALE);
        group_back.mode = new ModeBlink(BLINK_SPEED, BLINK_SPEED);
    }
    else if (mode_now == LEFT){
        group_left_top.mode = get_led_square_mode_class();
        group_left.mode = new ModeDirection(true, DIR_SPEED, FADE_OUT_SCALE);
		group_right.mode = get_flash_mode_class();
        group_back.mode = new ModeDirection(true, DIR_SPEED, FADE_OUT_SCALE);
    }
    else if (mode_now == RIGHT){
        group_left_top.mode = get_led_square_mode_class();
        group_left.mode = get_flash_mode_class();
        group_right.mode = new ModeDirection(true, DIR_SPEED, FADE_OUT_SCALE);
        group_back.mode = new ModeDirection(false, DIR_SPEED, FADE_OUT_SCALE);
    }
    else if (mode_now == BLINK){
        group_left_top.mode = get_led_square_mode_class();
        group_left.mode = get_flash_mode_class();
        group_right.mode = get_flash_mode_class();
        group_back.mode = get_flash_mode_class();
    }
    else if (mode_now == WATER_LEVEL){
        group_left_top.mode = new ModeWaterLevel(&modbus_data.water_level, 1, 50);
        group_left.mode = new ModePersentage(&modbus_data.water_level);
        group_right.mode = new ModePersentage(&modbus_data.water_level);
        group_back.mode = new ModePersentage(&modbus_data.water_level);
    }
}

// 刪除所有指針
void del_all_mode(){
  delete group_left_top.mode;
  delete group_left.mode;
  delete group_right.mode;
  delete group_back.mode;
  group_left_top.mode = NULL;
  group_left.mode = NULL;
  group_right.mode = NULL;
  group_back.mode = NULL;
}

void receiveEvent(int howMany) {
	//Serial.println("receiveEvent");
	while (5 < Wire.available()) {
		char c = Wire.read();
	}
	modbus_data.led_mode_setting = Wire.read();
	modbus_data.led_speed = Wire.read();
	modbus_data.led_flash_light_display_mode = Wire.read();
	modbus_data.water_level = Wire.read();
	modbus_data.led_square_switch = Wire.read();
	//modbus_data.led_mode_setting = 15;
	//modbus_data.water_level = 100;
}

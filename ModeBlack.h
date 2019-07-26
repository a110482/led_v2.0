//
// Created by elijah on 2019/2/11.
//

#ifndef LIBRARIES_MODEBLACK_H
#define LIBRARIES_MODEBLACK_H

#include "ModeProtocol.h"
class CRGB;
class LedGroup;
/**
 * @class 全黑的模式
 */
class ModeBlack: public ModeProtocol {
public:
    ModeBlack();
    virtual bool process(CRGB *leds_ptr, Range range);
};


#endif //LIBRARIES_MODEBLACK_H

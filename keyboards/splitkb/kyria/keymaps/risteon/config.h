/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// use together with EXTRAFLAGS += -flto
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 60000
#    define OLED_BRIGHTNESS 100

#    define SPLIT_WPM_ENABLE
#    define WPM_LAUNCH_CONTROL
#    define WPM_SAMPLE_PERIODS 5
#    define WPM_SAMPLE_SECONDS 25
#endif

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

// Disable TAPPING_FORCE_HOLD only for meta-bksp mod tap
#define TAPPING_FORCE_HOLD_PER_KEY
#define TAPPING_TERM 150
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

#define ENCODER_RESOLUTION 2

#ifdef RGBLIGHT_ENABLE
// RGB config
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
// turn off when suspended
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGBLIGHT_SLEEP
// #    define RGBLIGHT_EFFECT_BREATHING
// #    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #    define RGBLIGHT_EFFECT_SNAKE
// #    define RGBLIGHT_EFFECT_KNIGHT
// #    define RGBLIGHT_EFFECT_CHRISTMAS
// #    define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #    define RGBLIGHT_EFFECT_RGB_TEST
// #    define RGBLIGHT_EFFECT_ALTERNATING
// #    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL 150
#    endif
#endif // RGBLIGHT_ENABLE

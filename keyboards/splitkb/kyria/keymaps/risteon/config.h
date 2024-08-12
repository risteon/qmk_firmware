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
#endif

// Disable TAPPING_FORCE_HOLD only for meta-bksp mod tap
#define TAPPING_FORCE_HOLD_PER_KEY
#define TAPPING_TERM 150
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

#define SPLIT_WPM_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define OLED_TIMEOUT 60000
#define OLED_BRIGHTNESS 100

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define WPM_LAUNCH_CONTROL
#define WPM_SAMPLE_PERIODS 5
#define WPM_SAMPLE_SECONDS 25

#define ENCODER_RESOLUTION 2

#ifdef RGBLIGHT_ENABLE
// RGB config
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
// turn off when suspended
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGBLIGHT_SLEEP
#endif // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// bug in rgb_matrix.c? slave half does not work well with this
//#   define RGB_DISABLE_TIMEOUT 12000
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGBLIGHT_SLEEP                 // allows us to use rgblight_suspend() and rgblight_wakeup() in keymap.c
#    define RGBLIGHT_TIMEOUT 300000        // ms

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

/* Disable the animations you don't want/need.  You will need to disable a good number of these    *
 * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#    define ENABLE_RGB_MATRIX_SOLID_COLOR
// #    define ENABLE_RGB_MATRIX_ALPHAS_MODS
//#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
// #    define ENABLE_RGB_MATRIX_BREATHING
// #    define DISABLE_RGB_MATRIX_BREATHING
// #    define ENABLE_RGB_MATRIX_BAND_SAT
// #    define ENABLE_RGB_MATRIX_BAND_VAL
//#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE

#endif // RGB_MATRIX_ENABLE

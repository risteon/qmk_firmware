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
#define NO_ACTION_ONESHOT
#define WPM_LAUNCH_CONTROL
#define WPM_SAMPLE_PERIODS 10
#define WPM_SAMPLE_SECONDS 1

#define ENCODER_RESOLUTION 2

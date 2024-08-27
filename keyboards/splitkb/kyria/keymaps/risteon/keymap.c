/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include QMK_KEYBOARD_H

char wpm_str[10];

enum layers {
    _QWERTY = 0,
    //_DVORAK,
    //_COLEMAK_DH,
    _LOWER,
    _RAISE,
    _WINDOW,
    _LEFT_HAND,
    //_NAV,
    //_SYM,
    //_NUMBERS,
    _ADJUST,
};

enum kyria_keycodes { QWERTY = SAFE_RANGE, ADJUST_HOLD, EXT_ADJ, INVALID };

// Aliases for readability
#define QWERTY DF(_QWERTY)
// #define COLEMAK DF(_COLEMAK_DH)
// #define DVORAK DF(_DVORAK)

// #define SYM MO(_SYM)
// #define NAV MO(_NAV)
// #define FKEYS MO(_NUMBERS)
#define ADJUST MO(_ADJUST)

// #define CTL_ESC MT(MOD_LCTL, KC_ESC)
// #define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
// #define CTL_MINS MT(MOD_RCTL, KC_MINUS)
// #define ALT_ENT MT(MOD_LALT, KC_ENT)
#define ALT_ESC LALT_T(KC_ESC)
#define ALT_QUOT RALT_T(KC_QUOT)

#define LOWER LT(_LOWER, KC_TAB)
#define RAISE LT(_RAISE, KC_ENT)
#define LEFT_HAND OSL(_LEFT_HAND)

// Windows/i3 defines
#define W_QUIT LGUI(LSFT(KC_Q))

// TODO: derive from rev2 spec?
#define KYRIA_LED_COUNT 20

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  L-ALT |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  R-ALT |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |Adjust|  |Adjust|      |   N  |   M  | ,  < | . >  | /  ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Mute |Ct/Esc| Lower| Shift|      |  |      | Space| Raise|GUI/Bk|      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     INVALID, KC_Q, KC_W, KC_E,     KC_R,    KC_T,                                       KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,   INVALID,
     KC_LALT, KC_A, KC_S, KC_D,     KC_F,    KC_G,                                       KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_RALT,
     INVALID, KC_Z, KC_X, KC_C,     KC_V,    KC_B,  INVALID,  ADJUST,  ADJUST, INVALID,  KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, INVALID,
                          KC_MUTE, LCTL_T(KC_ESC), LOWER, KC_LSFT, INVALID, INVALID,  KC_SPC, RAISE, LGUI_T(KC_BSPC), INVALID
    ),


/*
 * Lower
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |                              |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+                              +------+------+------+------+------+------|
 * |      |+rGUI+|+RCTL+|+lALT+|+SHFT+|  LH  |                              |  <-  | DOWN |  UP  |  ->  |   ~  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Print|  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  |      |      |  F6  |  `   |   |  | Home | End  |      |
 * `------+------+------+------+------+------+-------------|  |-------------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      | Ctrl |      |      |      |
 *                      |      |      |      |      |      |  |      | Shift|      |      |      |
 *                        `--------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      INVALID, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, INVALID,
 INVALID,OSM(MOD_RGUI),OSM(MOD_RCTL),OSM(MOD_LALT),OSM(MOD_LSFT),LEFT_HAND,                  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_TILD, INVALID,
      KC_PSCR, KC_F1,   KC_F2,    KC_F3,    KC_F4,   KC_F5, INVALID, INVALID, INVALID, INVALID, KC_F6,   KC_GRV , KC_PIPE, KC_HOME, KC_END,  INVALID,
                                _______, _______,  _______, _______, INVALID, INVALID,LCTL(KC_LSFT), _______, _______, INVALID
    ),

/*
 * Raise
 *
 * ,-----------------------------------------.                              ------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+                              +------+------+------+------+------+------|
 * |      |   (  |   )  |   {  |   }  |  DEL |                              |   \  |  -_  |  =+  |   [  |   ]  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |  |      |      |  F12 |   "  |ISO / |Pg Dn |Pg Up |      |
 * `------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      INVALID,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, INVALID,
      INVALID, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR,  KC_DEL,                                     KC_BSLS, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, INVALID,
      INVALID,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, INVALID, INVALID, INVALID, INVALID, KC_F12,  KC_QUOT, KC_NUBS, KC_PGDN, KC_PGUP, INVALID,
                                 _______, _______, _______, _______, INVALID, INVALID, _______, _______, _______, INVALID
    ),

/*
 * Window
 *
 * ,------------------------------------------                              ------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+                              +------+------+------+------+------+------|
 * |      | Quit | FLOAT|      |GU+ENT|      |                              |  <-  | DOWN |  UP  |  ->  |      |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      | Print|/FLOAT| Vol- | Vol+ | Exit |      |      |  |      |      |ADJUST|      |      |  INS | CAPS |      |
 * `------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_WINDOW] = LAYOUT(
      INVALID,LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),                                    LGUI(KC_6),LGUI(KC_7),LGUI(KC_8),LGUI(KC_9),LGUI(KC_0),INVALID,
      INVALID, W_QUIT,LGUI(KC_SPC),INVALID,LGUI(KC_ENT),INVALID,          LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_DOWN)),LGUI(LSFT(KC_UP)),LGUI(LSFT(KC_RGHT)),INVALID,INVALID,
      INVALID, KC_PSCR,LSG(KC_SPC), KC_VOLD, KC_VOLU, LSG(KC_E), INVALID, INVALID, INVALID, INVALID, ADJUST_HOLD, INVALID, INVALID, KC_INS, KC_CAPS, INVALID,
                                  _______, _______, _______, _______, _______, INVALID, INVALID, _______, _______, INVALID
    ),

/*
 * Left hand control layer:
 *
 * ,------------------------------------------                              ------------------------------------------.
 * |      | GUI+Q| GUI+W| GUI+E| GUI+R|      |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+                              +------+------+------+------+------+------|
 * |      | Quit | FLOAT|      |GU+ENT|      |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      | Print|/FLOAT| Vol- | Vol+ | Exit |      |      |  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_LEFT_HAND] = LAYOUT(
      INVALID,LGUI(KC_Q),LGUI(KC_W),LGUI(KC_E),LGUI(KC_R), INVALID,                                  _______, _______, _______, _______, _______, _______,
      INVALID,  W_QUIT,  LGUI(KC_SPC), INVALID, LGUI(KC_ENT),XXXXXXX,                                _______, _______, _______, _______, _______, _______,
      INVALID, KC_PSCR,LSG(KC_SPC), KC_VOLD, KC_VOLU, LSG(KC_E), INVALID, INVALID, _______, _______, _______, _______, _______, _______, _______, _______,
                                      INVALID, _______, _______, _______, INVALID, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer: Default layer settings, RGB
 *
 *                      v-------------------------------------------------------RGB CONTROL--------------------v
 * ,------------------------------------------                              ------------------------------------------.
 * |      | Reset|      | RGB  |RGBMOD| HUE+ |                              | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+                              +------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      | Bri- | Bri+ |      |      |      |      |      |  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------|  |------+------+------+------+------+------+------+------'
 *                      |      | Exit |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      XXXXXXX, QK_BOOT, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI,                                     RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, EXT_ADJ, XXXXXXX, XXXXXXX, EE_CLR , EE_CLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef OLED_ENABLE
// WPM-responsive animation stuff here
#define ANIM_WPM_LOWER 20 // above this wpm value typing animation to triggered
#define ANIM_FRAME_DURATION_MAX 450 // longest animation duration in ms
#define ANIM_FRAME_DURATION_MIN 50 // shortest animation duration in ms
#define IDLE_FRAME_DURATION 300 // base value for how long each idle animation will last in ms
#define ANIM_FRAME_RATIO 2.5 // how aggressively animation speeds up with wpm
#define MAX(x, y) (((x) > (y)) ? (x) : (y)) // Math.max macro

uint32_t curr_anim_duration = 0; // variable animation duration
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
// -1: uninitialized (blank), 0: first dual frame set (low WPM), 1: second dual frame set (high WPM)
int8_t current_image_set = -1;

// Frame diffs
static const char PROGMEM diffs [982] = {
    0x80, 0xc0, 0xc0, 0xe0, 0xf0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0,
    0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf0, 0xf8,
    0xfc, 0xfe, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0x70, 0xe0, 0xc0,
    0x80, 0x00, 0x00, 0x80, 0xf0, 0xf8, 0xfc, 0x02, 0x30, 0x70, 0x70, 0x70, 0x60, 0x60, 0x60, 0xe0,
    0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
    0x7f, 0x7f, 0x7f, 0x78, 0xf8, 0xf8, 0xf8, 0xfc, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xc7, 0xcf, 0xcf,
    0xcf, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xc1, 0xc3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf0, 0xe0, 0x80, 0x30, 0xe0,
    0xe0, 0xc3, 0x9f, 0xff, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x01, 0x80, 0xe0, 0xf0, 0x38, 0x08, 0x80,
    0xc0, 0x41, 0x61, 0x71, 0x71, 0x71, 0x71, 0x71, 0x31, 0x33, 0xe3, 0xe0, 0xe0, 0xe0, 0xe3, 0xe3,
    0xe3, 0xe3, 0xc3, 0xc3, 0x41, 0xc1, 0xc1, 0xc0, 0xc8, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x9c,
    0x9c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x19, 0x39, 0x31, 0x31, 0x31, 0x31, 0x31, 0x33, 0x73, 0x73,
    0x63, 0x63, 0x03, 0x01, 0x20, 0x78, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x8f,
    0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x9f, 0x9f, 0x1f, 0x1f, 0x1e, 0x10, 0x80, 0x81, 0x8f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x3f, 0x3f, 0x07, 0x80, 0x20, 0xf0, 0xd0, 0x98, 0x9c, 0x9e,
    0xba, 0xbb, 0x9b, 0x8b, 0xa3, 0x33, 0x33, 0x77, 0x37, 0x32, 0x00, 0x44, 0x66, 0x6e, 0x6e, 0x66,
    0x22, 0x88, 0xcc, 0xcd, 0xcd, 0xdd, 0xdc, 0xdc, 0xd9, 0x99, 0x0b, 0x03, 0x93, 0xbb, 0xbb, 0xbb,
    0x93, 0x03, 0x27, 0x37, 0x77, 0x77, 0x77, 0x67, 0x27, 0x0f, 0x4f, 0x6e, 0xee, 0x6e, 0x6e, 0x8e,
    0xce, 0xde, 0xde, 0xcc, 0xc4, 0xdc, 0x9c, 0x9c, 0xbc, 0xbc, 0x38, 0x38, 0xb8, 0x38, 0x18, 0x08,
    0x78, 0x79, 0x71, 0x31, 0x91, 0xf1, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07,
    0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x0e, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x01, 0x20, 0x38, 0x30, 0x30, 0x30, 0x70, 0x70, 0x70, 0x60,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x83, 0x83, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xc7,
    0x87, 0x87, 0x86, 0x86, 0x06, 0x06, 0x0e, 0x0e, 0x0e, 0x0c, 0x0c, 0x8d, 0x8d, 0x9d, 0xdc, 0xfc,
    0xfd, 0x79, 0x39, 0x1b, 0x19, 0x38, 0x3a, 0x3b, 0x33, 0x33, 0x37, 0x37, 0x73, 0x71, 0x74, 0x76,
    0x66, 0x66, 0x66, 0xe2, 0xe8, 0xec, 0xec, 0xcc, 0xcd, 0xdd, 0xdd, 0xdd, 0xdd, 0x99, 0x80, 0x90,
    0x99, 0xbb, 0x9b, 0xcb, 0xe3, 0xf1, 0x3c, 0x1e, 0x0f, 0x07, 0x01, 0x07, 0x0f, 0x0f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x0f, 0x0f, 0x01, 0x0c, 0x0e, 0x07, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x20, 0x20,
    0x10, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0c, 0x08, 0x08, 0x18, 0x18, 0x18, 0x10, 0x10,
    0x30, 0x30, 0x20, 0x20, 0x60, 0x60, 0x40, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x40, 0x20, 0x10, 0x08,
    0x04, 0x02, 0x01, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x40, 0x01, 0x01, 0x01, 0x02, 0x06, 0x02,
    0x02, 0x02, 0x02, 0x00, 0x04, 0xf8, 0x02, 0x01, 0x04, 0x04, 0x04, 0x04, 0x03, 0x00, 0x16, 0x10,
    0x10, 0x14, 0x24, 0x28, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00, 0x00, 0x22, 0x23, 0x21, 0x22, 0x14,
    0x07, 0x08, 0x10, 0x40, 0x80, 0xc0, 0x80, 0x80, 0x80, 0x80, 0xc0, 0x60, 0x20, 0x30, 0x10, 0x00,
    0x00, 0x01, 0x01, 0x01, 0x02, 0x04, 0x0c, 0x08, 0x08, 0x18, 0x18, 0x18, 0x10, 0x10, 0x30, 0x20,
    0x20, 0x20, 0x60, 0x40, 0x40, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xc0, 0x00, 0x00, 0x03,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0e, 0x80, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00,
    0x00, 0x80, 0x40, 0x20, 0x20, 0x40, 0x80, 0xc1, 0xc1, 0xc0, 0xc2, 0xc6, 0x82, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x84, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0f, 0x04, 0x00, 0x01, 0x0f, 0x0f, 0x0f, 0x03,
    0x00, 0x00, 0x00, 0x80, 0x20, 0x08, 0x04, 0x02, 0x01, 0x04, 0x84, 0x04, 0x04, 0x03, 0x00, 0x16,
    0x14, 0x14, 0x14, 0x24, 0x28, 0x28, 0x28, 0x20, 0x22, 0x23, 0x21, 0x22, 0x14, 0x00, 0xfc, 0xff,
    0xff, 0x03, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x3e, 0xfc, 0xf0, 0xc0, 0x05, 0x08, 0x00, 0x40,
    0xfc, 0xfc, 0xfc, 0x7c, 0x7c, 0x7c, 0x38, 0x38, 0x18, 0x01, 0x02, 0x01, 0x00, 0x08, 0x02, 0x60,
    0x62, 0x43, 0x9b, 0x98, 0x9f, 0xbf, 0xbf, 0xb8, 0xf8, 0xf8, 0xd0, 0xd0, 0x07, 0x17, 0x01, 0x80,
    0xc0, 0x80, 0x80, 0x02, 0x08, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x00,
    0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe,
    0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0x60, 0x00, 0x10, 0x08, 0x04, 0x80, 0xc0, 0xc0, 0xc1,
    0xc0, 0xc0, 0x80, 0x44, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0f, 0x04, 0x00, 0x01, 0x0f, 0x0f, 0x0f,
    0x03, 0x00, 0x81, 0x83, 0x8f, 0xef, 0xe7, 0xc3, 0xc1, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0xfc, 0xff, 0xff, 0x03, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x3e, 0xfc, 0xf0, 0xc0,
    0x00, 0x00, 0x10, 0xfc, 0xfc, 0xfc, 0x7c, 0x7c, 0x7c, 0x38, 0x38, 0x18, 0x03, 0x03, 0x02, 0x00,
    0x00, 0x04, 0x05, 0x05, 0x05, 0x05, 0x07, 0x07, 0x06, 0x06, 0x02, 0x02, 0x01, 0x00, 0x08, 0x02,
    0x00, 0x00, 0x00, 0x40, 0x60, 0x60, 0x83, 0x1b, 0x18, 0x1f, 0x3f, 0x3f, 0x38, 0x38, 0x38, 0xb0,
    0xf0, 0x90, 0x90, 0x90, 0x10, 0x17, 0x07, 0x80, 0x80, 0x0c, 0x0c, 0x0d, 0x0f, 0x0f, 0x0b, 0x0b,
    0x09, 0x09, 0x00, 0x00, 0x01, 0x01, 0x80, 0x00, 0x30, 0x70, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x60, 0x7c, 0x7f, 0x7f, 0x7e, 0x78, 0x30, 0x20, 0x01, 0x03, 0x07,
    0x0f, 0x1f, 0x3f, 0x3f, 0x07, 0x01,
};
// Block starts
static const uint16_t PROGMEM block_starts [50] = {
    173, 292, 359, 387, 485, 527, 613, 647, 776, 872, 908, 962, 171, 291, 330, 417,
    430, 469, 148, 170, 269, 291, 329, 397, 430, 449, 518, 541, 548, 566, 573, 578,
    595, 717, 148, 183, 190, 269, 329, 341, 397, 431, 455, 518, 539, 566, 573, 706,
    726, 852,
};
// Block lengths
static const uint16_t PROGMEM block_lengths [50] = {
    27, 50, 11, 86, 17, 76, 15, 118, 75, 10, 27, 11, 32, 15, 12, 2,
    24, 4, 4, 32, 15, 15, 13, 22, 15, 24, 9, 1, 1, 3, 1, 13,
    2, 1, 4, 1, 13, 27, 7, 1, 29, 1, 17, 9, 16, 3, 26, 13,
    15, 17,
};
// Image starts
static const uint16_t PROGMEM image_sections [5] = {
    0, 12, 18, 34, 50,
};
// sections into diffs for each image
static const uint16_t PROGMEM diff_blocks_image_sections[4] = {
    0, 523, 612, 783,
};

void render_diffs(uint8_t image) {
    oled_buffer_reader_t reader;

    const uint16_t block_start_for_image = pgm_read_word(image_sections + image);
    const uint16_t block_end_for_image = pgm_read_word(image_sections + image + 1);
    uint16_t block_position = pgm_read_word(diff_blocks_image_sections + image);

    char b;
    for (uint16_t block_counter = block_start_for_image; block_counter < block_end_for_image; block_counter++) {
        const uint16_t start_position = pgm_read_word(block_starts + block_counter);
        const uint16_t length = pgm_read_word(block_lengths + block_counter);
        for (uint16_t i = 0; i < length; i++) {
            b = pgm_read_byte(diffs + block_position + i);
            reader = oled_read_raw(start_position + i);
            oled_write_raw_byte(*reader.current_element ^ b, start_position + i);
        }
        block_position += length;
    }
}

void build_up_image(int8_t image) {
    if (image == current_image_set) {
        return;
    }
    current_image_set = image;
    oled_clear();
    if (image == -1) {
        return;
    }
    render_diffs(0);
    if (image == 1) {
       render_diffs(2);
    }
}

// Images credit j-inc(/James Incandenza) and pixelbenny. Credit to obosob for initial animation approach.
static void render_anim(void) {
    // variable animation duration. Don't want this value to get near zero as it'll bug out.
    curr_anim_duration = MAX(ANIM_FRAME_DURATION_MIN, ANIM_FRAME_DURATION_MAX - ANIM_FRAME_RATIO * get_current_wpm());

    if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        oled_off();
    } else {
        if(get_current_wpm() > ANIM_WPM_LOWER) {
            if(timer_elapsed32(anim_timer) > curr_anim_duration) {
                anim_timer = timer_read32();
                build_up_image(1);
                render_diffs(3);
            }
        } else if(timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
            anim_timer = timer_read32();
            build_up_image(0);
            render_diffs(1);
        }
    }
}

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_anim();
        oled_set_cursor(0, 0);
        uint8_t n  = get_current_wpm();
        wpm_str[3] = '\0';
        wpm_str[2] = '0' + n % 10;
        wpm_str[1] = '0' + (n /= 10) % 10;
        wpm_str[0] = '0' + n / 10;
        oled_write_P(PSTR("WPM: "), false);
        oled_write(wpm_str, false);
    } else {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Keymap: risteon\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            /* case _DVORAK:
                oled_write_P(PSTR("Dvorak\n"), false);
                break; */
            /* case _COLEMAK_DH:
                oled_write_P(PSTR("Colemak DH\n"), false);
                break; */
            case _LOWER:
                oled_write_P(PSTR("Lower\n"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("Raise\n"), false);
                break;
            /* case _NUMBERS:
                oled_write_P(PSTR("Numbers\n"), false);
                break; */
            case _WINDOW:
                oled_write_P(PSTR("Navigation\n"), false);
                break;
            case _LEFT_HAND:
                oled_write_P(PSTR("Left Nav\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
#    ifdef OLED_ENABLE
    oled_on();
    anim_sleep = timer_read32();
#    endif

    if (index == 0) {
        if (IS_LAYER_ON(_RAISE)) {
            // Brightness control
            if (clockwise) {
                tap_code(KC_BRIU);
            } else {
                tap_code(KC_BRID);
            }
        } else if (IS_LAYER_ON(_ADJUST)) {
#    if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            // Brightness control
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
#    endif
        } else { // default
            // Volume control
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    } else if (index == 1) {
        if (IS_LAYER_ON(_ADJUST)) {
#    if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            // Brightness control
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
#    endif
        } else {
            // Default: Scrollwheel
            if (clockwise) {
#    ifdef MOUSEKEY_ENABLE
                tap_code(KC_WH_U);
#    else
                tap_code(KC_RGHT);
#    endif
            } else {
#    ifdef MOUSEKEY_ENABLE
                tap_code(KC_WH_D);
#    else
                tap_code(KC_LEFT);
#    endif
            }
        }
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        oled_on();
        anim_sleep = timer_read32();
    }
#endif
    switch (keycode) {
#ifdef RGBLIGHT_LAYER_BLINK
        case INVALID:
            if (record->event.pressed) {
                rgblight_blink_layer(0, 250);
                return false;
                break;
            }
#endif // RGBLIGHT_LAYER_BLINK
        case ADJUST_HOLD:
            if (record->event.pressed) {
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_WINDOW);
                layer_on(_ADJUST);
#ifdef RGBLIGHT_LAYER_BLINK
                rgblight_blink_layer(1, 1000);
#endif // RGBLIGHT_LAYER_BLINK
            }
            return false;
            break;
        case EXT_ADJ:
            if (record->event.pressed) {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
};

// // Delete is backspace on shift. ko_make_basic supports the mod tap
// const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, LGUI_T(KC_BSPC), KC_DEL);
// // This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
//     &delete_key_override,
//     NULL // Null terminate the array of overrides!
// };
//
// Disable tapping force hold option for LGUI_T(KC_BSPC)
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_BSPC):
            return false;
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _WINDOW);
}

#ifdef RGBLIGHT_LAYER_BLINK
const rgblight_segment_t PROGMEM        _no_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, KYRIA_LED_COUNT, HSV_RED});
const rgblight_segment_t PROGMEM        _adj_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, KYRIA_LED_COUNT, HSV_GREEN});
const rgblight_segment_t *const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(_no_layer, _adj_layer);

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

// Note we user post_process_record_user because we want the state
// after the flag has been flipped...
// void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case INVALID:
//             if (record->event.pressed) {
//                 rgblight_blink_layer(0, 250);
//                 break;
//             }
//     }
// }
#endif // RGBLIGHT_LAYER_BLINK

// Tap Dance declarations
enum {
    TD_ESC_CAPS,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

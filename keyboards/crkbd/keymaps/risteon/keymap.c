/*
Copyright 2019 @foostan
Copyright 2022 @risteon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>


enum crkbd_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _WINDOW,
  _NUMPAD,
  _ADJUST
};

enum crkbd_keycodes {
QWERTY = SAFE_RANGE,
  NUMPAD,
  ADJUST,
  BACKLIT,
  EXT_NUM,
  EXT_ADJ
};

#define LOWER LT(_LOWER, KC_TAB)
#define RAISE LT(_RAISE, KC_ENT)
//#define LOWER MO(_LOWER)
//#define RAISE MO(_RAISE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,------------------------------------------  ------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------  +------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+-------  +------+------+------+------+------+------|
 * |  -_  |   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+-------  +------+------+------+------+------+------|
 *                      | Ctrl |Lower |Shift |  |Space |Raise | GUI  |
 *                      ----------------------  ----------------------
 */
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  LALT_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K, KC_L,KC_SCLN,RALT_T(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   LOWER, KC_LSFT,     KC_SPC,   RAISE, KC_LGUI
                                      //`--------------------------'  `--------------------------'

  ),

/* Lower
 * ,------------------------------------------  ------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * |   `  | rGUI |+RCTL+|+lALT+|+SHFT+|+rALT+|  |  <-  | DOWN |  UP  |  ->  | Ins  |  |   |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * | Print|  F1  |  F2  |  F3  |  F4  |  F5  |  |  F6  |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 *                      |      |      |      |  |Space+|      |      |
 *                      ----------------------  ----------------------
 */
  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 KC_GRV,KC_RGUI,OSM(MOD_RCTL),OSM(MOD_LALT),OSM(MOD_LSFT),OSM(MOD_RALT),         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_INS, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PSCR, KC_F1,   KC_F2,    KC_F3,    KC_F4,   KC_F5,                   KC_F6,LSFT(KC_NUHS),LSFT(KC_NUBS),KC_HOME,KC_END,_______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______, C_S_T(KC_SPC),_______, _______
                                      //`--------------------------'  `--------------------------'
  ),

/* Raise
 * ,------------------------------------------  ------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * | Del  |   (  |   )  |   {  |   }  |      |  |      |  -_  |  =+  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  |  F12 |ISO # |ISO / |Pg Dn |Pg Up |      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 *                      |      |      |      |  |      |      |      |
 *                      ----------------------  ----------------------
 */
  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_DEL, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, _______,                      _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                      KC_F12, KC_NUHS, KC_NUBS, KC_PGDN, KC_PGUP, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

/* Window
 * ,------------------------------------------  ------------------------------------------.
 * | CAPS |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * | Exit | Quit | FLOAT|+lALT+|+SHFT+|+rALT+|  |  <-  | DOWN |  UP  |  ->  |      |      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |ADJUST|Numpad|      |      |      |      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 *                      |      |      |      |  |      |      |      |
 *                      ----------------------  ----------------------
 */
  [_WINDOW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
 KC_CAPS,LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),         LGUI(KC_6),LGUI(KC_7),LGUI(KC_8),LGUI(KC_9),LGUI(KC_0),_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 LGUI(LSFT(KC_E)),LGUI(LSFT(KC_Q)),LGUI(KC_SPC),OSM(MOD_LALT),OSM(MOD_LSFT),OSM(MOD_RALT),LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_DOWN)),LGUI(LSFT(KC_UP)),LGUI(LSFT(KC_RGHT)),_______,_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                       ADJUST, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

/* Adjust
 *                      v---------------------------RGB CONTROL--------------------v
 * ,------------------------------------------  ------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ |  | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * | Exit |      |MUSmod|      |      |AGnorm|  |AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------+  +------+------+------+------+------+------|
 *                      |      |      |      |  |      |      |      |
 *                      ----------------------  ----------------------
 */
  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI,                      RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      EXT_ADJ, _______, MU_MOD, _______, _______,  AG_NORM,                      AG_SWAP, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _WINDOW);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADJUST:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_WINDOW);
        layer_off(_NUMPAD);
        layer_on(_ADJUST);
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
}

#ifdef OLED_ENABLE
// Todo: process_record_user would be defined twice

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE

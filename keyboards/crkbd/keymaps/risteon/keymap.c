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

enum crkbd_layers { _QWERTY, _LOWER, _RAISE, _WINDOW, _LEFT_HAND, _ADJUST };

enum crkbd_keycodes { QWERTY = SAFE_RANGE, ADJUST, BACKLIT, EXT_NUM, EXT_ADJ, INVALID, TEST_1, TEST_2 };

#define LOWER LT(_LOWER, KC_TAB)
#define RAISE LT(_RAISE, KC_ENT)
#define LEFT_HAND OSL(_LEFT_HAND)
// #define LOWER MO(_LOWER)
// #define RAISE MO(_RAISE)

// Windows/i3 defines
#define W_QUIT LGUI(LSFT(KC_Q))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
     * ,------------------------------------------  ------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------  +------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+-------  +------+------+------+------+------+------|
     * |  -_  |   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+-------  +------+------+------+------+------+------|
     *                   |Ctrl(Esc)|Lower |Shift |  |Space |Raise |GUI/Bk|
     *                      ----------------------  ----------------------
     */
    [_QWERTY] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        LALT_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RALT_T(KC_QUOT),
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_MINS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        LCTL_T(KC_ESC), LOWER, KC_LSFT, KC_SPC, RAISE, LGUI_T(KC_BSPC)
        //`--------------------------'  `--------------------------'

        ),

    /* Lower
     * ,------------------------------------------  ------------------------------------------.
     * |      |   !  |   @  |   #  |   $  |   %  |  |   ^  |   &  |   *  |   (  |   )  |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      |+rGUI+|+RCTL+|+lALT+|+SHFT+|  LH  |  |  <-  | DOWN |  UP  |  ->  |   ~  |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  |  F6  |  `   |  |   | Home | End  |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     *                      |      |      |      |  |CtlSft|      |      |
     *                      ----------------------  ----------------------
     */
    [_LOWER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        INVALID, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, INVALID,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        INVALID, OSM(MOD_RGUI), OSM(MOD_RCTL), OSM(MOD_LALT), OSM(MOD_LSFT), LEFT_HAND, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TILD, INVALID,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        INVALID, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_GRV, KC_PIPE, KC_HOME, KC_END, INVALID,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, LCTL(KC_LSFT), _______, _______
        //`--------------------------'  `--------------------------'
        ),

    /* Raise
     * ,------------------------------------------  ------------------------------------------.
     * |      |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      |   (  |   )  |   {  |   }  | Del  |  |  \   |  -_  |  =+  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  |  F12 |   "  |ISO / |Pg Dn |Pg Up |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     *                      |      |      |      |  |      |      |      |
     *                      ----------------------  ----------------------
     */
    [_RAISE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        INVALID, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_DEL, KC_BSLS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_QUOT, KC_NUBS, KC_PGDN, KC_PGUP, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______
        //`--------------------------'  `--------------------------'
        ),

    /* Window
     * ,------------------------------------------  ------------------------------------------.
     * |      |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      | Quit | FLOAT|GU+ENT|+SHFT+|      |  |  <-  | DOWN |  UP  |  ->  |      |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      | Print|/FLOAT| Vol- | Vol+ | Exit |  |ADJUST|      | Print|  Ins | CAPS |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     *                      |      |      |      |  |      |      |      |
     *                      ----------------------  ----------------------
     */
    [_WINDOW] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        INVALID, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        INVALID, LGUI(LSFT(KC_Q)), LGUI(KC_SPC), LGUI(KC_ENT), OSM(MOD_LSFT), INVALID, LGUI(LSFT(KC_LEFT)), LGUI(LSFT(KC_DOWN)), LGUI(LSFT(KC_UP)), LGUI(LSFT(KC_RGHT)), INVALID, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_PSCR, LSG(KC_SPC), KC_VOLD, KC_VOLU, LSG(KC_E), ADJUST, _______, KC_PSCR, KC_INS, KC_CAPS, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______
        //`--------------------------'  `--------------------------'
        ),

    /* Left hand control layer
     *
     * ,------------------------------------------  ------------------------------------------.
     * |      | GUI+Q| GUI+W| GUI+E| GUI+R|      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      | Quit | FLOAT|GU+ENT|+SHFT+|      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      | Print|/FLOAT| Vol- | Vol+ | Exit |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     *                      |      |      |      |  |      |      |      |
     *                      ----------------------  ----------------------
     */
    [_LEFT_HAND] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.           ,-----------------------------------------------------.
        INVALID, LGUI(KC_Q), LGUI(KC_W), LGUI(KC_E), LGUI(KC_R), INVALID, _______, _______, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
        INVALID, W_QUIT, LGUI(KC_SPC), LGUI(KC_ENT), OSM(MOD_LSFT), XXXXXXX, _______, _______, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
        INVALID, KC_PSCR, LSG(KC_SPC), KC_VOLD, KC_VOLU, LSG(KC_E), _______, _______, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------|
        INVALID, INVALID, INVALID, _______, _______, _______
        //`--------------------------'                                      `--------------------------'
        ),
    /* Adjust
     *                      v---------------------------RGB CONTROL--------------------v
     * ,------------------------------------------  ------------------------------------------.
     * |      | Reset|Debug | RGB  |RGBMOD| HUE+ |  | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * | Exit |      |MUSmod| TEST1| TEST2|      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     * |      | Bri- | Bri+ |      |      |      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------+  +------+------+------+------+------+------|
     *                      | Exit |      |      |  |      |      |      |
     *                      ----------------------  ----------------------
     */
    [_ADJUST] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, QK_BOOT, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        EXT_ADJ, XXXXXXX, XXXXXXX, TEST_1, TEST_2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        EXT_ADJ, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
        //`--------------------------'  `--------------------------'
        )

};

static uint32_t key_timer;               // timer to track the last keyboard activity
static void     refresh_rgb(void);       // refreshes the activity timer and RGB, invoke whenever activity happens
static void     check_rgb_timeout(void); // checks if enough time has passed for RGB to timeout
bool            is_rgb_timeout = false;  // store if RGB has timed out or not in a boolean

void refresh_rgb() {
    key_timer = timer_read32(); // store time of last refresh
    if (is_rgb_timeout) {       // only do something if rgb has timed out
        is_rgb_timeout = false;
        rgb_matrix_enable_noeeprom();
    }
}

void check_rgb_timeout() {
    if (!is_rgb_timeout && timer_elapsed32(key_timer) > RGBLIGHT_TIMEOUT) {
        rgb_matrix_disable_noeeprom();
        is_rgb_timeout = true;
    }
}

/* Runs at the end of each scan loop, check if RGB timeout has occured */
void housekeeping_task_user(void) {
#ifdef RGBLIGHT_TIMEOUT
    if (rgb_matrix_is_enabled()) {
        check_rgb_timeout();
    }
#endif
}

/* Runs after each key press, check if activity occurred */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_TIMEOUT
    if (record->event.pressed) refresh_rgb();
#endif

    /* rest of the function code here */
}

/* Runs after each encoder tick, check if activit occurred */
void post_encoder_update_user(uint8_t index, bool clockwise) {
#ifdef RGBLIGHT_TIMEOUT
    refresh_rgb();
#endif
}

// Remove shift+bksp = del for now
// Delete is backspace on shift. ko_make_basic supports the mod tap
// const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, LGUI_T(KC_BSPC), KC_DEL);
// This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
// &delete_key_override,
// NULL // Null terminate the array of overrides!
// };

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ADJUST:
            if (record->event.pressed) {
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_WINDOW);
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
        case TEST_1:
            if (record->event.pressed) {
            }
            return false;
            break;
        case TEST_2:
            if (record->event.pressed) {
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
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

#    define L_BASE 0
#    define L_LOWER 2
#    define L_RAISE 4
#    define L_ADJUST 8

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
        case L_ADJUST | L_LOWER:
        case L_ADJUST | L_RAISE:
        case L_ADJUST | L_LOWER | L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);
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
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
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

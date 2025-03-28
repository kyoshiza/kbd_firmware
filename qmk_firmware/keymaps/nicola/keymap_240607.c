/* Copyright 2018-2019 eswai <@eswai>
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
/*
 For Corne V4
 * (C) 2020 Sadao Ikebe @bonyarou
 * modifyed by 2024 Kenji Yoshizawa
 */

#include QMK_KEYBOARD_H
#include "bootloader.h"
#include "nicola.h" // NICOLA親指シフト
#include "a2j/translate_ansi_to_jis.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keymap_layers {
  _QWERTY, // QWERTY LAYER
// NICOLA親指シフト
  _NICOLA, // NICOLA親指シフト入力レイヤー
// NICOLA親指シフト
  _FUNC1, // FUNCTION LAYER 1
  _FUNC2, // FUNCTION LAYER 2
  _LED    // LED SETTING LAYER
};

enum custom_keycodes {
  KC_EISU = NG_SAFE_RANGE,
  KC_KANA2
};

	    /*
     * ┌───┬───┬───┬───┬───┬───┬───┐┌───┬───┬───┬───┬───┬───┬───┐
     * │ Tab  │  Q   │  W   │  E   │  R   │  T   │  ↓  ││  ↑  │  Y   │  U   │  I   │  O   │  P   │  BS  │
     * ├───┼───┼───┼───┼───┼───┼───┤├───┼───┼───┼───┼───┼───┼───┤
     * │ LCtl │  A   │  S   │  D   │  F   │  G   │  ←  ││  →  │  H   │  J   │  K   │  L   │  ;   │  '   │
     * ├───┼───┼───┼───┼───┼───┼───┘└───┼───┼───┼───┼───┼───┼───┤
     * │ LShf │  Z   │  X   │  C   │  V   │  B   │                │  N   │  M   │  ,   │  .   │  /   │ Esc  │
     * └───┴───┴─┬─┴──┬┴───┴┬──┴──┐    ┌──┴──┬┴───┴┬──┴─┬─┴───┴───┘
     *                     │  Fn1   │  無変換  │   Spc    │    │   Enter  │   変換   │   Fn2  │
     *                     └────┴─────┴─────┘    └─────┴─────┴────┘
     */
#ifdef LAYOUT_split_3x6_3_ex2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY]= LAYOUT_split_3x6_3_ex2( \
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,  KC_DOWN,    KC_UP,      KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,   KC_G,  KC_LEFT,    KC_RIGHT,   KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                          KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                         MO(_FUNC1),KC_EISU, KC_SPC,    KC_ENT, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),

  // NICOLA親指シフト
  // デフォルトレイヤーに関係なくQWERTYで
  [_NICOLA] = LAYOUT_split_3x6_3_ex2( \
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_TAB,     NG_Q,    NG_W,    NG_E,    NG_R,   NG_T,  KC_DOWN,   KC_UP,      NG_Y,    NG_U,    NG_I,    NG_O,    NG_P, NG_BSLS, \
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    NG_A,    NG_S,    NG_D,    NG_F,   NG_G,  KC_LEFT,   KC_RIGHT,   NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN, NG_QUOT, \
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    NG_Z,    NG_X,    NG_C,    NG_V,   NG_B,                         NG_N,    NG_M, NG_COMM,  NG_DOT,  NG_SLSH, KC_ESC, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                       MO(_FUNC1),NG_SHFTL,KC_TRNS,    KC_TRNS,NG_SHFTR,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),
  

  [_FUNC1] = LAYOUT_split_3x6_3_ex2( \
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_PGDN,    KC_PGUP,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_HOME,    KC_END,  KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT,LCTL(LALT(KC_DEL)),XXXXXXX, XXXXXXX, XXXXXXX, MO(_LED),            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                         MO(_FUNC1),KC_EISU,KC_TRNS,   KC_TRNS, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),

  
  [_FUNC2] = LAYOUT_split_3x6_3_ex2( \
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_PGDN,    KC_PGUP, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME,    KC_END,  KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV, \
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT,LCTL(LALT(KC_DEL)),XXXXXXX, XXXXXXX, XXXXXXX, MO(_LED),            KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                         MO(_FUNC1),KC_EISU,KC_TRNS,   KC_TRNS, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),

  [_LED] = LAYOUT_split_3x6_3_ex2( \
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,    XXXXXXX,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  //|--------+--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, RGB_M_T,RGB_M_SW, RGB_M_P, RGB_M_G, RGB_M_R, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------|--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      RGB_M_X, RGB_M_B, RGB_M_SN,XXXXXXX, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                         MO(_FUNC1),KC_EISU,KC_TRNS,   KC_TRNS, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  )
};
#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_QWERTY] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                        MO(_FUNC1),KC_EISU, KC_SPC,     KC_ENT, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),

  // NICOLA親指シフト
  // デフォルトレイヤーに関係なくQWERTYで
  [_NICOLA] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,     NG_Q,    NG_W,    NG_E,    NG_R,   NG_T,                          NG_Y,    NG_U,    NG_I,    NG_O,    NG_P, NG_BSLS, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    NG_A,    NG_S,    NG_D,    NG_F,   NG_G,                          NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN, NG_QUOT, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    NG_Z,    NG_X,    NG_C,    NG_V,   NG_B,                          NG_N,    NG_M, NG_COMM,  NG_DOT,  NG_SLSH, KC_ESC, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                       MO(_FUNC1),NG_SHFTL,KC_TRNS,    KC_TRNS,NG_SHFTR,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC1] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,                       KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   KC_LSFT,LCTL(LALT(KC_DEL)),XXXXXXX, XXXXXXX, XXXXXXX,MO(_LED),                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                         MO(_FUNC1),KC_EISU,KC_TRNS,   KC_TRNS, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC2] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,LCTL(LALT(KC_DEL)),XXXXXXX, XXXXXXX, XXXXXXX,MO(_LED),             KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                         MO(_FUNC1),KC_EISU,KC_TRNS,   KC_TRNS, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  ),

  [_LED] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      RGB_M_T,RGB_M_SW, RGB_M_P, RGB_M_G, RGB_M_R, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      RGB_M_X, RGB_M_B, RGB_M_SN,XXXXXXX, XXXXXXX, XXXXXXX, \
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                         MO(_FUNC1),KC_EISU,KC_TRNS,   KC_TRNS, KC_KANA2,MO(_FUNC2)
                                      //`--------------------------'  `--------------------------'
  )
};
#endif


void matrix_init_user(void) {
  // NICOLA親指シフト
  set_nicola(_NICOLA);
  // NICOLA親指シフト
}

#ifdef RGB_MATRIX_ENABLE
// 明度の上限を抑える
void set_color(int index, uint8_t hsvred, uint8_t hsvgreen, uint8_t hsvblue) {
    HSV hsv = (HSV){hsvred, hsvgreen, hsvblue};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // 一度白消灯
//    rgb_matrix_set_color_all(0,0,0);
    // レイヤーごとにLEDを切り替える
    switch (get_highest_layer(layer_state | default_layer_state)) {
      case _QWERTY:
        return false;
      case _NICOLA:
        if (is_keyboard_left()) {
          // left
          set_color(18, HSV_GREEN);
          set_color(17, HSV_GREEN);
          set_color(12, HSV_GREEN);
          set_color(11, HSV_GREEN);
          set_color( 4, HSV_GREEN);
          set_color( 3, HSV_GREEN);
          set_color(21, HSV_GREEN);
          set_color(19, HSV_GREEN);
          set_color(16, HSV_GREEN);
          set_color(13, HSV_GREEN);
          set_color(10, HSV_GREEN);
          set_color( 5, HSV_GREEN);
          set_color( 2, HSV_GREEN);
          set_color(22, HSV_GREEN);
          set_color(20, HSV_GREEN);
          set_color(15, HSV_GREEN);
          set_color(14, HSV_GREEN);
          set_color( 9, HSV_GREEN);
          set_color( 6, HSV_GREEN);
          set_color( 1, HSV_GREEN);
          set_color( 8, HSV_GREEN);
          set_color( 7, HSV_GREEN);
          set_color( 0, HSV_GREEN);
        }else{
          // right
          set_color(44, HSV_GREEN);
          set_color(26, HSV_GREEN);
          set_color(27, HSV_GREEN);
          set_color(34, HSV_GREEN);
          set_color(35, HSV_GREEN);
          set_color(40, HSV_GREEN);
          set_color(41, HSV_GREEN);
          set_color(45, HSV_GREEN);
          set_color(25, HSV_GREEN);
          set_color(28, HSV_GREEN);
          set_color(33, HSV_GREEN);
          set_color(36, HSV_GREEN);
          set_color(39, HSV_GREEN);
          set_color(42, HSV_GREEN);
          set_color(24, HSV_GREEN);
          set_color(29, HSV_GREEN);
          set_color(32, HSV_GREEN);
          set_color(37, HSV_GREEN);
          set_color(38, HSV_GREEN);
          set_color(43, HSV_GREEN);
          set_color(23, HSV_GREEN);
          set_color(30, HSV_GREEN);
          set_color(31, HSV_GREEN);
        }
        return false;
      default:
        if (is_keyboard_left()) {
          // left
          set_color(18, HSV_BLUE);
          set_color(17, HSV_BLUE);
          set_color(12, HSV_BLUE);
          set_color(11, HSV_BLUE);
          set_color( 4, HSV_BLUE);
          set_color( 3, HSV_BLUE);
          set_color(21, HSV_BLUE);
          set_color(19, HSV_BLUE);
          set_color(16, HSV_BLUE);
          set_color(13, HSV_BLUE);
          set_color(10, HSV_BLUE);
          set_color( 5, HSV_BLUE);
          set_color( 2, HSV_BLUE);
          set_color(22, HSV_BLUE);
          set_color(20, HSV_BLUE);
          set_color(15, HSV_BLUE);
          set_color(14, HSV_BLUE);
          set_color( 9, HSV_BLUE);
          set_color( 6, HSV_BLUE);
          set_color( 1, HSV_BLUE);
          set_color( 8, HSV_BLUE);
          set_color( 7, HSV_BLUE);
          set_color( 0, HSV_BLUE);
        }else{
          // right
          set_color(44, HSV_BLUE);
          set_color(26, HSV_BLUE);
          set_color(27, HSV_BLUE);
          set_color(34, HSV_BLUE);
          set_color(35, HSV_BLUE);
          set_color(40, HSV_BLUE);
          set_color(41, HSV_BLUE);
          set_color(45, HSV_BLUE);
          set_color(25, HSV_BLUE);
          set_color(28, HSV_BLUE);
          set_color(33, HSV_BLUE);
          set_color(36, HSV_BLUE);
          set_color(39, HSV_BLUE);
          set_color(42, HSV_BLUE);
          set_color(24, HSV_BLUE);
          set_color(29, HSV_BLUE);
          set_color(32, HSV_BLUE);
          set_color(37, HSV_BLUE);
          set_color(38, HSV_BLUE);
          set_color(43, HSV_BLUE);
          set_color(23, HSV_BLUE);
          set_color(30, HSV_BLUE);
          set_color(31, HSV_BLUE);
        }
        return false;
    }
}
#endif // RGB_MATRIX_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_EISU:
      if (record->event.pressed) {
        // NICOLA親指シフト
        send_string(SS_TAP(X_INT5));  // Win (Muhenkan key)
//        send_string(SS_TAP(X_GRV));   // Win
//        send_string(SS_TAP(X_MHEN));  // Win
//        send_string(SS_TAP(X_LANG2)); // Mac
        nicola_off();
        // NICOLA親指シフト
//        for(int i=0; i<RGBLED_NUM; ++i) {
//           rgblight_setrgb_at(0, 0, 64, i);  // BLUE
//        }
      }
      return false;
      break;
    case KC_KANA2:
      if (record->event.pressed) {
        // NICOLA親指シフト
        send_string(SS_TAP(X_INT4)); // Win (Henkan key)
//        send_string(SS_TAP(X_HENK)); // Win
//        send_string(SS_TAP(X_LANG1)); // Mac
        nicola_on();
        // NICOLA親指シフト
//        for(int i=0; i<RGBLED_NUM; ++i) {
//            rgblight_setrgb_at(0, 64, 0, i);  // GREEN
//        }
      }
      return false;
      break;
  }

  // NICOLA親指シフト
  bool a = true;
  if (nicola_state()) {
    nicola_mode(keycode, record);
    a = process_nicola(keycode, record);
  }
  if (a == false) return false;
  // NICOLA親指シフト

// as kbd101 layer driver on windows recognizes the IME on/off key,
// we no longer need to disguise as 106 keyboard
//   bool continue_process = process_jtu(keycode, record);
//   if (continue_process == false) {
//     return false;
//   }
  return process_record_user_a2j(keycode, record);
  
//  return true;
}

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GIMP,
};

enum custom_keycodes {
  C_LOWER = SAFE_RANGE,
  C_RAISE,
  LEAD_C,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_ESC,    JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,                      JP_Y,    JP_U,    JP_I,    JP_O,    JP_P, KC_BSPC,
  JP_MHEN,    JP_A,    JP_S,    JP_D,    JP_F,    JP_G,                      JP_H,    JP_J,    JP_K,    JP_L, KC_SCLN,  KC_DEL,
  KC_LWIN,    JP_Z,    JP_X,    JP_C,    JP_V,    JP_B, XXXXXXX, XXXXXXX,    JP_N,    JP_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LALT,
                             XXXXXXX, C_RAISE, KC_LSFT,  KC_SPC,  KC_ENT, KC_LCTL, C_LOWER, XXXXXXX
),
[_LOWER] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,    JP_1,    JP_2,    JP_3,    JP_4,    JP_5,                      JP_6,    JP_7,    JP_8,    JP_9,    JP_0, _______,
  JP_ZKHK, JP_MINS, JP_CIRC,  JP_YEN,   JP_AT, XXXXXXX,                   XXXXXXX, JP_LBRC, JP_RBRC, JP_BSLS, JP_COLN, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                             _______, _______, _______, KC_TAB, _______,  _______, _______, _______
),
[_RAISE] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                   XXXXXXX, KC_HOME,  KC_END, XXXXXXX, XXXXXXX, _______,
  JP_HENK,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                   KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, _______,
  KC_LCTL,  KC_F11,  KC_F12,  KC_APP, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRIU, KC_BRID,                   XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, KC_PSCR,                   XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX,
  _______, KC_MAIL, XXXXXXX,  KC_INS, XXXXXXX,TO(_GIMP), XXXXXXX, XXXXXXX, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PDOT, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
    }
    switch (keycode) {
        case C_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            }
            else {
                layer_off(_LOWER);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        case C_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            }
            else {
                layer_off(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        default:
            break;
    }
    return true;
}


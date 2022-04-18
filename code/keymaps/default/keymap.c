#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define FF_NXT LCTL(KC_TAB)
#define FF_PRV LCTL(LSFT(KC_TAB))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,          KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,          KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_PSCR,          KC_F12,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, ADJUST,  KC_LGUI,KC_LALT,  LOWER,   KC_SPC,  KC_LSFT,          KC_ENT,  KC_RALT, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT(
  KC_GRV,  KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_HOME,          KC_PGUP,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  KC_TILD , KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_END ,          KC_PGDN,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS,
  KC_TRNS, KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_BSPC,          KC_BSPC,   KC_F12,  KC_MUTE, KC_MPLY, KC_VOLD, KC_VOLU, KC_PIPE,
  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_LCTL,          KC_ENT,    KC_BSPC, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END

  ),

  [_RAISE] = LAYOUT(

  KC_ESC ,  KC_1,    KC_2,  KC_3,   KC_4,    KC_5,     FF_PRV,          _______,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TRNS, KC_4,    KC_5,  KC_6,   KC_PLUS, _______,  FF_NXT,          _______,    KC_MS_L, KC_MS_D, KC_MS_U,  KC_MS_R,  KC_RBRC, KC_ENT,
  KC_ACL1,  KC_7,    KC_8,  KC_9,   KC_MINS, _______,  _______,          _______,   KC_WH_L, KC_WH_D, KC_WH_U,  KC_WH_R, _______, KC_BSLS,
  KC_ENT , KC_COMM, KC_0,  KC_DOT, KC_TRNS, KC_BTN1,  KC_BTN2,          KC_ENT,     KC_BSPC,  KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END

  ),

  [_ADJUST] = LAYOUT(
     RESET,  _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, CALTDEL,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     KC_CAPS, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,  _______, _______, _______,         _______, _______,  _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  )

};







bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
        if (record->event.pressed) {
            writePinLow(B0);
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            writePinHigh(B0);
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
      return false;
      break;
    case RAISE:
        if (record->event.pressed) {
            writePinLow(D5);
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            writePinHigh(D5);
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

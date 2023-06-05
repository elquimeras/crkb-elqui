// ### include {{{
#include QMK_KEYBOARD_H
#include "keymap_german_mac_iso_qmk.h"
#include "mctechnology17.h"
#include <stdio.h>
//}}}

enum {
  TD_PC,
  TD_COMI,
  TD_SLA,
  TD_CAPLOCK,
  TD_ALT,
  TD_COMM,
  TD_DOT,
  TD_PRNA,
  TD_PRNB,
  TD_BRKA,
  TD_BRKB,
  TD_SLASH,
};

// ### START LAYOUTS {{{
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,   KC_S,  KC_D,    KC_F,  KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  TD(TD_PC), TD(TD_COMI),
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,   TD(TD_COMM), KC_DOT, TD(TD_SLA), RSFT_T(KC_ENT),
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       KC_RCMD, KC_SPC, MO(_NUMBER),    MO(_SYMBOL), KC_SPC, TD(TD_ALT)
                                      //|--------------------------|  |--------------------------|
  ),
  [_NUMBER] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  XXXXXXX, RGB_HUI, RGB_HUD, RGB_MOD, RGB_TOG,                      KC_1,   KC_2,   KC_3,   KC_KP_ASTERISK,   SCMD(KC_7),   KC_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_AT, KC_QUOTE, XXXXXXX, KC_VOLU, LALT(KC_G),                   KC_4,    KC_5,   KC_6,   TD(TD_PRNA),    TD(TD_PRNB),    KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX, XXXXXXX, XXXXXXX,  KC_MPRV,  KC_VOLD,  KC_MNXT,                   KC_7,    KC_8,   KC_9,   TD(TD_BRKA),    TD(TD_BRKB),    KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LCTL(KC_LALT), KC_SPC, KC_TRNS,    MO(_SYMBOL), KC_0, KC_RALT
                                      //|--------------------------|  |--------------------------|
  ),
  [_SYMBOL] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_EXLM,  KC_UP, LALT(KC_3), KC_DLR, KC_PERC,                     KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  TD(TD_CAPLOCK),  KC_LEFT,  KC_DOWN,  KC_RGHT,  MACRO1,  MACRO2,              KC_MINS, KC_EQL, RALT(KC_LBRC),  RALT(KC_RBRC), KC_PIPE, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   LALT(KC_2), LSFT(KC_0), TD(TD_SLASH), KC_LBRC, XXXXXXX, MACRO3,            KC_UNDS, KC_PLUS, RALT(KC_QUOT), RALT(KC_NUHS), KC_BSLS, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      KC_LGUI, KC_SPC, MO(_NUMBER),    KC_TRNS, KC_SPC, KC_RALT
                                      //|--------------------------|  |--------------------------|
  ),
    // }}}
    /* ### 3 FUNTIONS LAYOUT {{{
          .------------------------------------------------.
       .-------------------------------------------------. |    F1  |  F2   | F3
       |   F4  | SPELL |TRADUCT|                         |DE_F21 | DE_F22| | |
       |         |
          |--------+-------+-------+-------+-------+-------|
       |-------+-------+-------+-------+-------+---------| |    F5  |  F6   | F7
       |    F8 |   \   |ALFRED |                         |C-A-DEL|QMKBEST|DE_F24
       |CLR_LIN|BRI_UP |         |
          |--------+-------+-------+-------+-------+-------|
       |-------+-------+-------+-------+-------+---------| |    F9  |   F10 |
       F11 |   F12 |ALFRED |EMOJI  | |L_SHIFT|L_SHIFT|R_SHIFT|       | BRI_UP| |
          '---------------------------------------------------------|
       |----------------------------------------------------------' |  CTRL    |
       CMD       |   ALT  |       |  TAB   |   ´   |          CTRL |
                                   '--------------------------------'
       '--------------------------------'
    */
    [_FUNCTION] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        DE_F1, DE_F2, DE_F3, DE_F4, SPELL, TRADUCT, DE_F22, DE_F21, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        DE_F5, DE_F6, DE_F7, DE_F8, DE_BSLS, SNIPPET, TASKM, QMKBEST, DE_F24,
        DE_F23, DE_BRI_UP, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        DE_F9, DE_F10, DE_F11, DE_F12, CLIPBRD, EMOJI, DE_LSFT, DE_LSFT,
        DE_RSFT, XXXXXXX, DE_BRI_DN, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        DE_LCTL, DE_LGUI, DE_LALT, DE_TAB, DE_ACUT, DE_RCTL
        //`--------------------------'  `--------------------------'
        ),
    // }}}
    /* ### 4 MEDIA LAYOUT {{{
     * LCAG(kc) Hold Left Control, Alt and GUI and press kc
     * LSG(kc) Hold Left Shift and GUI and press kc
     * LAG(kc) 	Hold Left Alt and Left GUI and press kc
          .------------------------------------------------.
     .-------------------------------------------------. |
     |SC_FLOW|TXTSNIP|SC_SHOT|OP_TERM|       |                         |POS1
     |POS2   |LANG_1 |LANG_2 | STOP  |  DELETE |
          |--------+-------+-------+-------+-------+-------|
     |-------+-------+-------+-------+-------+---------| |        |SC_SPSF|SC_RE
     |       |       |       |                         |POS3   |POS4   |LANG_3 |
     |VOL_UP |PLAY/PAUS|
          |--------+-------+-------+-------+-------+-------|
     |-------+-------+-------+-------+-------+---------| |        |       | | |
     |       |                         |       |       |  MUTE |  PREV |VOL_DOW|
     NEXT   |
          '---------------------------------------------------------|
     |----------------------------------------------------------' |  CTRL    |
     CMD       |   ALT  |       |  SPACE | ALTGR |          CTRL |
                                   '--------------------------------'
     '--------------------------------'
    */
    [_MEDIA] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        XXXXXXX, SC_FLOW, TXTSNIP, SC_SHOT, OP_TERM, XXXXXXX, POS1, POS2,
        DE_LANG1, DE_LANG2, DE_STOP, DE_DEL,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        XXXXXXX, SC_SPSF, SC_RE, XXXXXXX, XXXXXXX, XXXXXXX, POS3, POS4,
        DE_LANG3, XXXXXXX, DE_VOL_UP, DE_PLAY,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        DE_MUTE, DE_PREV, DE_VOL_DN, DE_NEXT,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        DE_LCTL, DE_LGUI, DE_SPC, DE_ENT, DE_RALT, DE_RCTL
        //`--------------------------'  `--------------------------'
        ),
    // }}}
    /* ### 5 MOUSE RGB BOOT LAYOUT {{{
          .------------------------------------------------.
       .-------------------------------------------------. |RAINBOW | LALT
       |RAINBOW|       |       |       |
       |RGBBRI-|RGBBRI+|WH_LEFT|WH_RIGH|WH_DOWN| WH_UP   |
          |--------+-------+-------+-------+-------+-------|
       |-------+-------+-------+-------+-------+---------| | |CLICK_1|CLICK_2|
       |       |       |                         |RGBSAT-|RGBSAT+| |CLICK_1| UP
       |CLICK_2  |
          |--------+-------+-------+-------+-------+-------|
       |-------+-------+-------+-------+-------+---------| | L_SHIFT|       | |
       |       | BOOT  |                         |RGBHUE-|RGBHUE+|       | LEFT
       | DOWN  | RIGHT   |
          '---------------------------------------------------------|
       |----------------------------------------------------------' |  CTRL    |
       CMD       | SPACE  |       |RGBANI- |RGBANI+|   RGBTOG      |
                                   '--------------------------------'
       '--------------------------------'
    */
    // ### MC: add _MOUSE LAYOUT_5

    [_MOUSE] = LAYOUT_split_3x6_3(
        // RGB_MODE_SWIRL, RGB_MODE_BREATHE, RGB_MODE_RAINBOW
        // RGB_MOD, RGB_RMOD,
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        RGB_MODE_RAINBOW, DE_LALT, RGB_MODE_RAINBOW, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_VAI, RGB_VAD, DE_MS_WH_LEFT, DE_MS_WH_RIGHT, DE_MS_WH_UP,
        DE_MS_WH_DOWN,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        XXXXXXX, DE_MS_BTN1, DE_MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAI,
        RGB_SAD, XXXXXXX, DE_MS_BTN3, DE_MS_UP, DE_MS_BTN4,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        DE_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, RGB_HUI, RGB_HUD,
        XXXXXXX, DE_MS_LEFT, DE_MS_DOWN, DE_MS_RIGHT,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        DE_LCTL, DE_LGUI, DE_SPC, XXXXXXX, XXXXXXX, RGB_TOG
        //`--------------------------'  `--------------------------'
        )};
// }}}
// END LAYOUTS }}}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ;, twice for :
    [TD_PC] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
    [TD_COMI] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),
    [TD_SLA] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_CAPLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_LALT),
    [TD_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_GRV),
    [TD_DOT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, RALT(KC_DOT)),
    [TD_PRNA] = ACTION_TAP_DANCE_DOUBLE(KC_ASTR, RALT(KC_QUOT)),
    [TD_PRNB] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, RALT(KC_NUHS)),
    [TD_BRKA] = ACTION_TAP_DANCE_DOUBLE(RALT(KC_LBRC), KC_GRV),
    [TD_BRKB] = ACTION_TAP_DANCE_DOUBLE(RALT(KC_RBRC), LSFT(KC_GRV)),
    [TD_SLASH] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_7), RALT(KC_NUBS)),
};


#ifdef COMBO_ENABLE // {{{
enum combo_events {
  EM_EMAIL,
  BSPC_LSFT_CLEAR,
  EM_EMAIL_ES,
  EM_EMAIL_DE,
  COMBO_LENGTH
};
uint16_t COMBO_LEN =
    COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM email_combo[] = {DE_F24, COMBO_END};
const uint16_t PROGMEM clear_line_combo[] = {DE_F23, COMBO_END};
const uint16_t PROGMEM email_combo_es[] = {DE_F22, COMBO_END};
const uint16_t PROGMEM email_combo_de[] = {DE_F21, COMBO_END};

combo_t key_combos[] = {
    [EM_EMAIL] = COMBO_ACTION(email_combo),
    [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
    [EM_EMAIL_ES] = COMBO_ACTION(email_combo_es),
    [EM_EMAIL_DE] = COMBO_ACTION(email_combo_de),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
  case EM_EMAIL:
    if (pressed) {
      SEND_STRING("suscribe to my channel");
    }
    break;
  case BSPC_LSFT_CLEAR:
    if (pressed) {
      tap_code16(KC_END);
      tap_code16(S(KC_HOME));
      tap_code16(KC_BSPC);
    }
    break;
  case EM_EMAIL_ES:
    if (pressed) {
      SEND_STRING("mctechnology17");
    }
    break;
  case EM_EMAIL_DE:
    if (pressed) {
      SEND_STRING("like and subscribe");
    }
    break;
  }
}
#endif
// END COMBO_ENABLE }}}

// vim: set sw=2 ts=2 sts=2 et ft=c fdm=marker:

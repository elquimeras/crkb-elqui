/* ========================================
FileName: oled_setup.c
Date: 15:17 23.September.2022
Author: Marcos Ivan Chow Castro @mctechnology17
Email: mctechnology170318@gmail.com
GitHub: https://github.com/mctechnology17
Brief: define keymap for the wired corne keyboard
Use: in your keymap file, include this file
     #include "oled_setup.c"
===========================================
Inspired by Tyler Thrailkill @snowe/@snowe2010

Copyright QMK Community
Copyright 2022 Marcos Ivan Chow Castro @mctechnology17
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

// ### OLED_ENABLE {{{
#ifdef OLED_ENABLE
#include QMK_KEYBOARD_H
#include "mctechnology17.h"
#include "quantum.h"
#include <stdio.h>
#define RENDER_LAYER     // render_layer (+372)
uint8_t mod_state;       // get_mods()
uint8_t current_wpm = 0; // current_wpm parte como 0
// ### ifdef DOG_ENABLE {{{
#ifdef DOG_ENABLE
led_t led_usb_state;
#define ANIM_SIZE_DOG 96 // numero de pixeles en cada frame del perro
#define ANIM_FRAME_DURATION_DOG                                                \
  200 // para bongocat y el perro cuanto tiempo mostrar cada frame
uint32_t anim_dog_timer;
uint32_t anim_dog_sleep;
uint8_t current_dog_frame = 0; // current dog frame
bool showedJump = true;
bool isJumping = false;
#endif
//}}}
// ### ifdef BONGOCAT_KEYBOARD_ENABLE {{{
#ifdef BONGOCAT_KEYBOARD_ENABLE
#define WPM                                                                    \
  15 // si current_wpm >= WPM entonces el gato empieza a tocar el keyboard
#define ANIM_FRAME_DURATION 200 // cuanto tiempo mostrar cada frame
#define ANIM_SIZE_CAT 320       // numero de pixeles en cada frame del gato
uint32_t anim_cat_timer;
uint32_t anim_cat_sleep;
uint8_t current_cat_frame = 0; // current cat frame
char wpm_str[4];
#endif
// }}} BONGOCAT
// TODO INCLUIR ESTAS DEF
// NOTE: comment out to disable
// ### ifdef MUSIC_BARS_ENABLE {{{
// #    ifdef MUSIC_BARS_ENABLE
// #        define ANIM_INVERT false
// #        define ANIM_RENDER_WPM true
// #        define FAST_TYPE_WPM 10 // 45 (default) Switch to fast animation
// when over words per minute #        include "music-bars.c" #    endif CRAB
// }}}
// ### ifdef DOG_ENABLE {{{
#ifdef DOG_ENABLE
// ### matrix dog {{{
static void render_dog(int DOG_X, int DOG_Y) { 
  // esta funcion contiene los frames y logica de la animacion del perro
  static const char PROGMEM sit[2][ANIM_SIZE_DOG] = {
    // frames de sit
    { // 'sit1' 32x22px
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04,
      0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08,
      0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06,
      0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20,
      0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },

    { // 'sit2' 32x22px
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9,
      0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
      0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20,
      0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

  static const char PROGMEM walk[2][ANIM_SIZE_DOG] = {
    // frames de walk
    { // 'walk1' 32x22px
      0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90,
      0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90,
      0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00,
      0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f,
      0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },

    { // 'walk2' 32x22px  
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20,
      0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20,
      0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01,
      0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
      0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05,
      0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }};

  static const char PROGMEM run[2][ANIM_SIZE_DOG] = {
    // frames de run
    { // 'run1' 32x22px
      0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80,
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04,
      0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00,
      0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03,
      0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32,
      0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    },

    { // 'run2' 32x22px
      0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10,
      0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01,
      0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10,
      0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }};

  static const char PROGMEM bark[2][ANIM_SIZE_DOG] = {
    // frames de bark
    { // 'bark1' 32x22px
      0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18,
      0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48,
      0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28,
      0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05,
      0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },

    { // 'bark2' 32x22px
      0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90,
      0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0,
      0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28,
      0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05,
      0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }};

  static const char PROGMEM sneak[2][ANIM_SIZE_DOG] = {
    // frames de sneak
    { // 'sneak1' 32x22px
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40,
      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80,
      0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02,
      0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09,
      0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11,
      0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04,
      0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
    },

    { // 'sneak2' 32x22px
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40,
      0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03,
      0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04,
      0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09,
      0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06,
      0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    }};
  // matrix }}}

  // ### logic animation dog {{{
  void animate_dog(void) {
    if (isJumping || !showedJump) {
      oled_set_cursor(DOG_X, DOG_Y + 2);
      oled_write("     ", false);
      oled_set_cursor(DOG_X, DOG_Y - 1);
      showedJump = true;
    } else {
      oled_set_cursor(DOG_X, DOG_Y - 1);
      oled_write("     ", false);
      oled_set_cursor(DOG_X, DOG_Y);
    }

    // cada accion del perro (sit, walk, run, bark y sneak) tiene 2 frames
    current_dog_frame = (current_dog_frame + 1) % 2; 
    // con esta formula current_dog_frame toma los valores 1 y 0 los cuales se van turnando

    if (led_usb_state.caps_lock) { // si esta activado Caps Lock
      oled_write_raw_P(bark[abs(1 - current_dog_frame)],
                       ANIM_SIZE_DOG); // perro ladra

    } else if ((keyboard_report->mods & MOD_BIT(KC_LSFT)) ||
               (keyboard_report->mods &
                MOD_BIT(KC_RSFT))) { // KC_LSFT o KC_RSFT presionado
      oled_write_raw_P(sneak[abs(1 - current_dog_frame)],
                       ANIM_SIZE_DOG); // perro en sneaking

    } else if ((keyboard_report->mods & MOD_BIT(KC_LCTL)) ||
               (keyboard_report->mods &
                MOD_BIT(KC_RCTL))) { // KC_LCTL o KC_RCTL presionado
      oled_write_raw_P(walk[abs(1 - current_dog_frame)],
                       ANIM_SIZE_DOG); // perro camina

    } else if (keyboard_report->mods & MOD_BIT(KC_LGUI)) { // KC_LGUI presionado
      oled_write_raw_P(run[abs(1 - current_dog_frame)],
                       ANIM_SIZE_DOG); // perro corre

    } else { // si no se cumple ninguna de las condiciones anteriores
      oled_write_raw_P(sit[abs(1 - current_dog_frame)],
                       ANIM_SIZE_DOG); // perro se sienta
    }
  }

  if (timer_elapsed32(anim_dog_timer) > ANIM_FRAME_DURATION_DOG) {
    anim_dog_timer = timer_read32();
    animate_dog();

    if (current_wpm != 0) {
      anim_dog_sleep = timer_read32();
    }
  }
}
// logic animation }}}
#endif
// }}}
// ### ifdef BONGOCAT_KEYBOARD_ENABLE {{{
#ifdef BONGOCAT_KEYBOARD_ENABLE
// ### matrix cat {{{
static void render_cat(void) { // esta funcion contiene los frames y logica de
                               // la animacion del gato

  static const char PROGMEM idle[1][ANIM_SIZE_CAT] = {
    // frames de idle
    {
      0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00,
      0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83,
      0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
      0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30,
      0xc0, 0x00, 0xe0, 0x1f, 0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04, 0x00, 0x00,
      0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0,
      0x3f, 0x03, 0x80, 0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
      0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05, 0x00, 0x00, 0xf0,
      0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80,
      0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38,
      0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1e, 0x01, 0x00,
      0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x0c, 0x30, 0xc0,
      0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x80, 0x00, 0x00, 0xe1,
      0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0e,
      0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0,
      0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19, 0x19, 0x41,
      0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02,
      0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09,
      0x70, 0x80, 0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10,
      0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
      0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02,
      0x01,
    }};

  static const char PROGMEM tap[2][ANIM_SIZE_CAT] = {
    // frames de tap
    {
      0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff,
      0xff, 0x7c, 0x70, 0x40, 0x40, 0x61, 0x5e, 0x80, 0xc0, 0xbc, 0x03,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
      0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0f, 0x3f,
      0xf8, 0xf0, 0xf0, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01,
      0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0,
      0x3f, 0x03, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0xf0,
      0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80,
      0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38,
      0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1e, 0x01, 0x00,
      0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x0c, 0x30, 0xc0,
      0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x80, 0x00, 0x00, 0xe1,
      0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0e,
      0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0,
      0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19, 0x19, 0x41,
      0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02,
      0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09,
      0x70, 0x80, 0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10,
      0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
      0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02,
      0x01,
    },
    {
      0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00, 0x03,
      0x0c, 0x30, 0xc0, 0x00, 0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83, 0x80, 0x80,
      0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x03, 0x00, 0x00,
      0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe0, 0x1f,
      0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x31,
      0x05, 0x41, 0x12, 0x04, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01,
      0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80, 0x78, 0x07, 0x02, 0x02,
      0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05,
      0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79,
      0x07, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
      0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe, 0xff, 0xff,
      0xff, 0xfc, 0xf0, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x0f, 0x3f, 0xff, 0x03, 0x01, 0x03,
      0x07, 0x18, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x18, 0x60, 0x80, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3c,
      0x00, 0x00, 0x00, 0x00, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e,
      0x0e, 0x01, 0xf3, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80,
      0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08,
      0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
      0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01
    },
  };
  // }}}
  // ### logic animation cat {{{
  void animate_cat(void) {
    if (current_wpm < WPM) {
      oled_write_raw_P(
        idle[0],
        ANIM_SIZE_CAT
      ); // gato en idle (solo hay un frame en esta accion)
    }
    if (current_wpm >= WPM) {
      current_cat_frame = (current_cat_frame + 1) % 2; // para alternar entre los 2 frames de tap
      oled_write_raw_P(
        tap[abs((2 - 1) - current_cat_frame)],
        ANIM_SIZE_CAT
      ); // gato haciendo tap
    }
  }

  if (timer_elapsed32(anim_cat_timer) > ANIM_FRAME_DURATION) { 
    // timer_elapsed32(anim_cat_timer) tiempo transcurrido en ms desde la ultima vez que se actualizo anim_cat_timer

    anim_cat_timer = timer_read32(); // se actualiza anim_cat_timer
    animate_cat();                   // se ejecuta animate_cat()

    if (current_wpm != 0) {
      anim_cat_sleep = timer_read32(); // se actualiza anim_cat_sleep
    }
  }
}
// logic animation cat }}}
// ### render_wpm contador de palabras {{{
static void render_wpm(void) {
  oled_write(" WPM\n", false);
  wpm_str[3] = '\0';
  wpm_str[2] = '0' + current_wpm % 10;
  wpm_str[1] = '0' + (current_wpm /= 10) % 10;
  wpm_str[0] = '0' + current_wpm / 10;
  oled_write(" ", false);
  oled_write(wpm_str, false); // printear valor de WPM
}
// }}}
#endif
// }}}
// ### ifdef RENDER_LAYER imprime la capa actual {{{
#ifdef RENDER_LAYER
// esta funcion muestra las capas en el OLED y resalta la capa presente
static void render_layer(void) {
  if (IS_LAYER_ON(_NUMBER)) {
    oled_write_P(
      PSTR("NUMP\n"),
      layer_state_is(_NUMBER) && 
      !layer_state_is(_SYMBOL) &&
      !layer_state_is(_FUNCTION) && 
      !layer_state_is(_MEDIA)
    );
  } else {
    oled_write_P(PSTR("MACOS"), layer_state_is(_DEFAULT));
  }

  oled_write_P(
    PSTR("SYMB\n"),
    layer_state_is(_SYMBOL) && !layer_state_is(_MEDIA)
  );
  oled_write_P(
    PSTR("FUNC\n"),
    layer_state_is(_FUNCTION) && !layer_state_is(_MEDIA)
  );
  
  if (IS_LAYER_ON(_MOUSE)) {
    oled_write_P(
      PSTR("MOUSE"),
      layer_state_is(_MOUSE) && !layer_state_is(_SYMBOL) &&
      !layer_state_is(_FUNCTION) && !layer_state_is(_MEDIA)
    );
  } else {
    oled_write_P(PSTR("MEDIA"), layer_state_is(_MEDIA));
  }
}
#endif
//}}}
//  ### oled_rotation_t {{{
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  } else {
#ifdef BONGOCAT_KEYBOARD_ENABLE
    return OLED_ROTATION_270;
#elif OCEAN_DREAM_ENABLE
    return OLED_ROTATION_270;
#else
    return OLED_ROTATION_180; // flips the display 180 degrees if offhand
#endif
  }
  return rotation;
}
//}}}
// ### oled_render_keylog {{{
char keylog_str[24] = {};
const char code_to_name[60] = {
    ' ', ' ',  ' ', ' ', 'a',  'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j',  'k', 'l', 'm',  'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v',  'w', 'x', 'y',  'z', '1', '2', '3', '4', '5', '6',
    '7', '8',  '9', '0', 'R',  'E', 'B', 'T', '_', '-', '=', '[',
    ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};
void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  // snprintf(keylog_str, sizeof(keylog_str), "%dx%d\nk%2d\n  %c",
  // record->event.key.row, record->event.key.col, keycode, name);
  snprintf(keylog_str, sizeof(keylog_str), "\n KEY\n\n  %c", name);
  // snprintf(keylog_str, sizeof(keylog_str), "KEY %c", name);
}
void oled_render_keylog(void) { oled_write(keylog_str, false); }
// }}}
// ### oled_task_user indica que poner en cada OLED {{{
// el OLED es de 128x32 pixeles
// cada page es de 8 pixeles a lo largo del lado con 128 px
// por lo que hay 16 pages a lo largo de los 128 px
bool oled_task_user(void) { // funcion en la cual se indica que poner en cada OLED
  current_wpm = get_current_wpm();
#ifdef DOG_ENABLE // {{{
// if ((timer_elapsed32(anim_dog_sleep) > 60000) &&
// (timer_elapsed32(anim_cat_sleep) > 60000) && (current_wpm == 0)) {
#ifdef BONGOCAT_KEYBOARD_ENABLE // {{{
                                // TODO: con las variables de export se podria
                                // solucionar esto de que no se apagan bien las
                                // pantallas
  if ((timer_elapsed32(anim_dog_sleep) > 60000) &&
      (timer_elapsed32(anim_cat_sleep) > 60000) &&
      (current_wpm == 0)
  ) {
    if (is_oled_on()) {
      oled_off();
    }
    timer_init();
    return false;
  }

  // #        else
  // if ((timer_elapsed32(anim_dog_sleep) > 60000) && (current_wpm == 0)) {
  // if (is_oled_on()) {
  // oled_off();
  // }
  // timer_init();
  // return false;
  // }
#endif                        // }}}
#endif                        // }}}
  if (is_keyboard_master()) { // OLED del master
#ifdef LUNA_ENABLE            // {{{
    led_usb_state = host_keyboard_led_state();
    // render_luna(0, 13);
    render_luna(0, 1);
#endif            // }}}
#ifdef DOG_ENABLE // {{{
                  // TODO: ver si esto soluciona el problema
                  // de que se mantiene encendido el OLED
    if (current_wpm != 0 && !is_oled_on()) {
      oled_on();
    }
    led_usb_state = host_keyboard_led_state();
    render_dog(0, 1); // lo del perro
#else
#ifdef MC_TECHNOLOGY // {{{
    oled_render_logo_mctechnology();
#endif               // }}}
#endif               // }}}
#ifdef RENDER_LAYER  // {{{
    oled_set_cursor(0, 5);
    render_layer(); // lo de las capas
#endif              // }}}
    // oled_render_keylog {{{
    oled_set_cursor(0, 10);
    oled_render_keylog();
    // oled_set_cursor(0, 14);
    // oled_write("corne", false);
    // }}}
  } else {                // OLED del slave
#ifdef OCEAN_DREAM_ENABLE // {{{
    render_stars();
#endif             // }}}
#ifdef CRAB_ENABLE // {{{
    oled_render_anim();
#endif              // }}}
#ifdef DEMON_ENABLE // {{{
    oled_render_anim();
#endif                   // }}}
#ifdef MUSIC_BARS_ENABLE // {{{
    oled_render_anim();
#endif                 // }}}
#ifdef BONGOCAT_ENABLE // {{{
    render_anim_bongocat();
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("WPM"), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
#endif                          // }}}
#ifdef BONGOCAT_KEYBOARD_ENABLE // TODO {{{
    render_cat();               // lo del gato
    oled_set_cursor(0, 11);
    render_wpm(); // lo del WPM
    oled_set_cursor(0, 14);
    oled_write("chow", false);
#endif // }}}
  }
  return false;
}
// }}}
// ### process_record_user {{{
// process_record_user() se ejecuta cada vez que se presiona una tecla
// se usa para imprimir en el OLED cada tecla que se presiona
// y para las SEND_STRING("") que se para enviar una respuesta predeterminada
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  mod_state = get_mods();

  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("like a boss qmk");
      }
      break;
    case KC_LCTL:
    case KC_RCTL:
      #ifdef OCEAN_DREAM_ENABLE
          is_calm = (record->event.pressed) ? true : false;
      #endif
      #ifdef LUNA_ENABLE
          if (record->event.pressed) {
            isSneaking = true;
          } else {
            isSneaking = false;
          }
      #endif
      break;
    case KC_SPC:
      #ifdef LUNA_ENABLE
          if (record->event.pressed) {
            isJumping = true;
            showedJump = false;
          } else {
            isJumping = false;
          }
      #endif
      break;
    case MACRO1:
      if (record->event.pressed) {
        SEND_STRING("git commit /m @@");
      }
      return false;
    case MACRO2:
      if (record->event.pressed) {
        SEND_STRING("git commit /m @@ //no/verify");
      }
      return false;
    case MACRO3:
      if (record->event.pressed) {
        SEND_STRING("git diff HEAD ");
      }
      return false;
  }

  return true;
}
// }}}
#endif // OLED_DRIVER_ENABLE
// OLED_ENABLE }}}
// vim: set sw=2 ts=2 sts=2 et ft=c fdm=marker:
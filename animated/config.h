/* ========================================
FileName: config.h
Date: 15:40 05.September.2022
Author: Marcos Ivan Chow Castro @mctechnology17
Email: mctechnology170318@gmail.com
GitHub: https://github.com/mctechnology17
Brief: delcarar macros y carga fuentes

SIENTETE LIBRE DE MODIFICAR EL CODIGO A TU GUSTO O DE OCUPAR LO QUE NECESITES
NO OLVIDES REFERENCIAR A LOS AUTORES DE LOS CODIGOS QUE OCUPES
========================================= */
#pragma once
// #define COMBO_COUNT 2
// ### define master o slave{{{
#define MASTER_LEFT
// #define EE_HANDS
// #define MASTER_RIGHT
// }}}
// ### WPM config {{{
#define SPLIT_WPM_ENABLE
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
// #define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define RETRO_TAPPING
//}}}
// ### OLED config {{{
// #define OLED_BRIGHTNESS 120
// #define OLED_DISABLE_TIMEOUT
// #define SPLIT_OLED_ENABLE
//}}}
// ### activar solo si BONGOCAT_KEYBOARD = yes DOG = true {{{
#ifdef RGBLIGHT_ENABLE // si la linea RGBLIGHT_ENABLE = yes esta en rules.mk
#    undef RGBLED_NUM
#    define RGBLED_NUM 12 // 54 (default) numero de LEDs en el teclado
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT \
        { 6, 6 } // 27, 27 (default) numero de LEDs en cada mitad del teclado
// #    define RGBLIGHT_EFFECT_BREATHING
// #    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_LIMIT_VAL 110
#    define RGBLIGHT_HUE_STEP 5
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif
// activar solo si BONGOCAT_KEYBOARD = yes DOG = true }}}
// ### OLED_FONT_H {{{
#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
// }}}
// ### size optimisations {{{
// size optimisations
// #define NO_DEBUG
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// }}}

#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash. 
#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 8
#   define RGB_MATRIX_VAL_STEP 8
#   define RGB_MATRIX_SPD_STEP 10

#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define RGB_MATRIX_DIGITAL_RAIN
#endif


// vim: set sw=2 ts=2 sts=2 et ft=c fdm=marker:

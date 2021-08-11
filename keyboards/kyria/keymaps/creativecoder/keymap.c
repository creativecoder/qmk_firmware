/* Copyright 2021 Grant M. Kinney
 *
 * Based on the Miryoku layout by Manna Harbour
 * https://github.com/manna-harbour/miryoku
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

enum layers { BASE, MBO, MEDIA, NAV, MOUSE, SYM, NUM, FUN };

bool is_app_switcher_active = false;
uint16_t app_switcher_timer = 0;

#include "oled.h"
#include "encoders.h"

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used
#define XXX KC_NO

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)

#define LAYOUT_creativecoder( \
    K00, K01, K02, K03, K04,                     K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14,                     K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, \
              K34, K35, K36, K37, K38, K39, K40, K41, K42, K43 \
) \
LAYOUT( \
XXX, K00, K01, K02, K03, K04,                     K05, K06, K07, K08, K09, XXX, \
XXX, K10, K11, K12, K13, K14,                     K15, K16, K17, K18, K19, XXX, \
XXX, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, XXX, \
               K34, K35, K36, K37, K38, K39, K40, K41, K42, K43 \
)

enum custom_keycodes {
    RELEASE_LGUI = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_creativecoder(
      KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,                                                                                          KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
      LCTL_T(KC_A),      LALT_T(KC_R),      LGUI_T(KC_S),      LSFT_T(KC_T),      KC_G,                                                                                          KC_M,              LSFT_T(KC_N),      LGUI_T(KC_E),      LALT_T(KC_I),      LCTL_T(KC_O),
      KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              LT(NUM, KC_LBRC),  U_NU,              U_NU,              LT(NAV, KC_RBRC),  KC_K,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
                         RELEASE_LGUI,      U_NU,              LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUN, KC_DEL),   U_NU,              U_NU
    ),
    [NAV] = LAYOUT_creativecoder(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,
                        KC_TRNS, U_NA,    U_NA,    U_NA,    U_NA,    KC_ENT,  KC_BSPC, KC_DEL,  U_NU,    U_NA
    ),
    [MOUSE] = LAYOUT_creativecoder(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, U_NU,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, U_NU,
                        U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_BTN1, KC_BTN3, KC_BTN2, U_NP,    U_NP
    ),
    [MEDIA] = LAYOUT_creativecoder(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, U_NU,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,
                        U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_MSTP, KC_MPLY, KC_MUTE, U_NA,    KC_MUTE
    ),
    [MBO] = LAYOUT_creativecoder(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_TRNS,                                     KC_TRNS, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                        U_NA,    U_NA,    KC_BTN2, KC_BTN3, KC_BTN1, KC_BTN1, KC_BTN3, KC_BTN2, U_NA,    U_NA
    ),
    [NUM] = LAYOUT_creativecoder(
      KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                                      U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NA,    U_NA,    KC_DOT,  KC_0,    KC_MINS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA
    ),
    [SYM] = LAYOUT_creativecoder(
      KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NA,    U_NA,    KC_LPRN, KC_RPRN, KC_UNDS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA
    ),
    [FUN] = LAYOUT_creativecoder(
      KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NA,    U_NA,    KC_APP,  KC_SPC,  KC_TAB,  U_NA,    U_NA,    U_NA,    U_NA,    U_NA
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RELEASE_LGUI:
        if (record->event.pressed && is_app_switcher_active) {
            unregister_code(KC_LGUI);
            is_app_switcher_active = false;
        }
        break;
    }
    return true;
};

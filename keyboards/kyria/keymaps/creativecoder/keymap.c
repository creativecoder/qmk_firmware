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

#include "encoders.h"
#include "layout.h"
#include "oled.h"

#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)

enum custom_keycodes {
    RELEASE_LGUI = SAFE_RANGE,
    CPY_URL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_kyria_3x5(
      KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,                                                                                          KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
      LCTL_T(KC_A),      LALT_T(KC_R),      LGUI_T(KC_S),      LSFT_T(KC_T),      KC_G,                                                                                          KC_M,              LSFT_T(KC_N),      LGUI_T(KC_E),      LALT_T(KC_I),      LCTL_T(KC_O),
      KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              LT(NUM, KC_LBRC),  U_NU,              U_NU,              LT(NAV, KC_RBRC),  KC_K,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
                                            RELEASE_LGUI,      LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), U_NU,              U_NU,              LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUN, KC_DEL),   U_NU
    ),
    [NAV] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  CPY_URL,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    KC_ENT,  KC_BSPC, KC_DEL,  U_NU
    ),
    [MOUSE] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, U_NU,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, U_NU,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_BTN1, KC_BTN3, KC_BTN2, U_NU
    ),
    [MEDIA] = LAYOUT_kyria_3x5(
      RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, U_NU,
      U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,
                        U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_MSTP, KC_MPLY, KC_MUTE, KC_MUTE
    ),
    [MBO] = LAYOUT_kyria_3x5(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_TRNS,                                     KC_TRNS, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                        U_NU,    KC_BTN2, KC_BTN3, KC_BTN1, U_NA,    U_NA,    KC_BTN1, KC_BTN3, KC_BTN2, U_NU
    ),
    // [NUM] = LAYOUT_kyria_3x5(
    //   KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    //   KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                                      U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
    //   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
    //                     U_NU,    KC_DOT,  KC_0,    KC_MINS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    // ),
    // [SYM] = LAYOUT_kyria_3x5(
    //   KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    //   KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
    //   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
    //                     U_NU,    KC_LPRN, KC_RPRN, KC_UNDS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    // ),
    [NUM] = LAYOUT_kyria_3x5(
      KC_BSLS, KC_7,    KC_8,    KC_9,    KC_SLSH,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                                      U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_DOT,  KC_1,    KC_2,    KC_3,    KC_ASTR, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_GRV,  KC_0,    KC_MINS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [SYM] = LAYOUT_kyria_3x5(
      KC_PIPE, KC_AMPR, KC_LCBR, KC_RCBR, KC_PERC,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_COLN, KC_HASH, KC_LPRN, KC_RPRN, KC_PLUS,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_CIRC, KC_DLR,  KC_LBRC, KC_RBRC, KC_AT,   U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_TILD, KC_EXLM, KC_UNDS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
    [FUN] = LAYOUT_kyria_3x5(
      KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                     U_NA,    U_NA,    U_NA,    U_NA,    RESET,
      KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK,                                     U_NA,    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
      KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                        U_NU,    KC_APP,  KC_SPC,  KC_TAB,  U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU
    ),
};

// Initialize variable holding the binary representation of active modifiers.
uint8_t mod_state;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();

    switch (keycode) {
        case RELEASE_LGUI:
            if (record->event.pressed && is_app_switcher_active) {
                unregister_code(KC_LGUI);
                is_app_switcher_active = false;
            }
            return true;
        case CPY_URL:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Temporarily cancel both shifts
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_LGUI);
                    tap_code(KC_L);
                    tap_code(KC_C);
                    tap_code(KC_T);
                    tap_code(KC_V);
                    unregister_code(KC_LGUI);
                    tap_code(KC_ENT);
                    // Reapplying modifier state so that the held shift key(s) still work
                    set_mods(mod_state);
                } else {
                    register_code(KC_LGUI);
                    tap_code(KC_L);
                    tap_code(KC_C);
                    unregister_code(KC_LGUI);
                }
            }
            return false;
    }
    return true;
};

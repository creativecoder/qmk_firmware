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

enum layers { BASE, MBO, MEDIA, NAV, MOUSE, SYM, NUM, FUN };

enum custom_keycodes {
    RELEASE_LGUI = SAFE_RANGE,
};

bool is_app_switcher_active = false;
uint16_t app_switcher_timer = 0;

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

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255, 255, 254, 0,   0,  0,   0,   0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240, 240, 192,192, 48,  48,  48, 48,  192, 192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48,  48,  48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128, 128, 224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7, 255, 255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255, 255, 127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3,   12,  12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63,  63,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12,  12,  51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,   0,   0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3,   15,  63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,   0,   255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207, 239, 255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,   0,   0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224, 192, 128,  1,  3,  7, 15, 30, 28, 60, 56,120, 112, 112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case MOUSE:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case MEDIA:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case NUM:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case SYM:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case FUN:
            oled_write_P(PSTR("Function keys\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool ccw) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case NUM:
                // Select next/previous window
                if (ccw) {
                    tap_code16(LSG(KC_GRV));
                } else {
                    tap_code16(LGUI(KC_GRV));
                }
                break;
            case FUN:
                // Brightness up/down
                if (ccw) {
                    tap_code(KC_SLCK);
                } else {
                    tap_code(KC_PAUS);
                }
                break;
            case SYM:
            default:
                // Select next/previous application
                if (!is_app_switcher_active) {
                    is_app_switcher_active = true;
                    register_code(KC_LGUI);
                }
                if (ccw) {
                    app_switcher_timer = timer_read();
                    tap_code16(S(KC_TAB));
                } else {
                    app_switcher_timer = timer_read();
                    tap_code16(KC_TAB);
                }
                break;

        }
    }
    else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case NAV:
                // Select next/previous tab
                if (ccw) {
                    tap_code16(LSG(KC_LBRC));
                } else {
                    tap_code16(LSG(KC_RBRC));
                }
                break;
            case MEDIA:
                // Volume control
                if (ccw) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
            case MOUSE:
                // Mouse scroll up/down
                if (ccw) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
                break;
            default:
                // Page up/Page down
                if (ccw) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
                break;

        }
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_app_switcher_active && timer_elapsed(app_switcher_timer) > 1000) {
        unregister_code(KC_LGUI);
        is_app_switcher_active = false;
    }
}
#endif

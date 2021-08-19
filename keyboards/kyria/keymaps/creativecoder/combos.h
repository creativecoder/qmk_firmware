enum combos {
    BACK,
    FORWARD,
    PREV_TAB,
    NEXT_TAB,
    SHOW_DESKTOP,
    MISSION_CONTROL,
    APP_WINDOWS,
    NOTIFICATION_CENTER,
};

const uint16_t PROGMEM back_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM forward_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM prev_tab_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM next_tab_combo[] = {KC_Y, KC_QUOT, COMBO_END};
const uint16_t PROGMEM show_desktop_combo[] = {KC_L, KC_QUOT, COMBO_END};
const uint16_t PROGMEM mission_control_combo[] = {KC_H, KC_SLSH, COMBO_END};
const uint16_t PROGMEM app_windows_combo[] = {KC_K, KC_SLSH, COMBO_END};
const uint16_t PROGMEM notification_center_combo[] = {KC_QUOT, KC_SLSH, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [BACK] = COMBO(back_combo, LGUI(KC_LBRC)),
    [FORWARD] = COMBO(forward_combo, LGUI(KC_RBRC)),
    [PREV_TAB] = COMBO(prev_tab_combo, LSG(KC_LBRC)),
    [NEXT_TAB] = COMBO(next_tab_combo, LSG(KC_RBRC)),
    [SHOW_DESKTOP] = COMBO(show_desktop_combo, KC_F11),
    [MISSION_CONTROL] = COMBO(mission_control_combo, LCTL(KC_UP)),
    [APP_WINDOWS] = COMBO(app_windows_combo, LCTL(KC_DOWN)),
    [NOTIFICATION_CENTER] = COMBO(notification_center_combo, LCAG(KC_LEFT)),
};

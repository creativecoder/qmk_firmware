enum combos {
    BACK,
    FORWARD,
    PREV_TAB,
    NEXT_TAB,
};

const uint16_t PROGMEM back_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM forward_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM prev_tab_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM next_tab_combo[] = {KC_Y, KC_QUOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [BACK] = COMBO(back_combo, LGUI(KC_LBRC)),
    [FORWARD] = COMBO(forward_combo, LGUI(KC_RBRC)),
    [PREV_TAB] = COMBO(prev_tab_combo, LSG(KC_LBRC)),
    [NEXT_TAB] = COMBO(next_tab_combo, LSG(KC_RBRC)),
};

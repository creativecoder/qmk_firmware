enum combos {
    BACK,
    FORWARD,
};

const uint16_t PROGMEM back_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM forward_combo[] = {KC_U, KC_Y, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [BACK] = COMBO(back_combo, LGUI(KC_LBRC)),
    [FORWARD] = COMBO(forward_combo, LGUI(KC_RBRC)),
};

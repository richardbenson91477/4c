#include "type.h"

// match order of types in type.h
const char *type_id_names[] = {
    "':nil",
    "':function",
    "':number",
    "':number-array",
    "':boolean",
    "':string",
    "':user",
};

enum type_ids type_id_from_symbol (char *_s) {

    return type_id_nil;
}


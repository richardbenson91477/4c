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

enum type_ids type_id_from_symbol (char *_s, uint32_t s_n) {
    printf("debug: type_id_from_symbol\n");

    if (NULL == _s) {
        fprintf(stderr, "error: type_id_from_symbol: NULL\n");
        return type_id_nil;
    }
    else if ('\0' == *_s) {
        fprintf(stderr, "error: type_id_from_symbol: NIL\n");
        return type_id_nil;
    }
    else if (0 == s_n) {
        fprintf(stderr, "error: type_id_from_symbol: zero\n");
        return type_id_nil;
    }

    // function variable
    if ('_' == *_s) {
        return type_id_func;
    }
    // number constant
    if (('-' == *_s) || isdigit(*_s)) {
        return type_id_num;
    }
    // string constant
    else if ('\"' == *_s) {
        return type_id_string;
    }
    // built-in constant
    else if ('\'' == *_s) {
        // built-in type name
        if ((s_n > 2) && (':' == *(_s + 1))) {
            for (uint32_t c = 0; c < 7; c++) {
                if (! strcmp (type_id_names[c], _s))
                    return c;
            }

            fprintf(stderr, "error: type_id_from_symbol: unknown built-in type \"%s\"\n", _s);
            return type_id_nil;
        }
        // 'nil type
        else if (! strcmp ("'nil", _s)) {
            // NOTE: this type_id_nil is not an error
            return type_id_nil;
        }
        // else fall through
    }
    else if (':' == *_s) {
        return type_id_user;
    }

    // non-function variable or built-in constant, with possible special end character 
    char e = *(_s + s_n - 1);
    // ':number-array
    if ('.' == e) {
        return type_id_num_array;
    }
    // ':boolean
    else if ('^' == e) {
        return type_id_bool;
    }
    // ':string
    else if ('$' == e) {
        return type_id_string;
    }
    
    // ':number by default
    return type_id_num;
}


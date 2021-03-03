#include "type.h"

// match order of types in type.h
const char *type_id_syms[] = {
    "':nil",
    "':func",
    "':int",
    "':float",
    "':bool",
    "':str",
    "':list",
//    "':type",
    "':user",
};

enum type_ids type_id_from_const_sym (char *_s, uint32_t s_n) {
    printf("debug: type_id_from_const_sym\n");

    if (NULL == _s) {
        fprintf(stderr, "error: type_id_from_const_sym: NULL\n");
        return type_id_nil;
    }
    else if ('\0' == *_s) {
        fprintf(stderr, "error: type_id_from_const_sym: NIL\n");
        return type_id_nil;
    }
    else if (0 == s_n) {
        fprintf(stderr, "error: type_id_from_const_sym: zero\n");
        return type_id_nil;
    }

    // string constant
    if ('\"' == *_s) {
        return type_id_str;
    }
    // int or float constant
    else if (('-' == *_s) || isdigit(*_s)) {
        for (uint32_t c = 0; c < s_n; c ++) {
            if ('.' == *(_s + c))
                return type_id_float;
        }
        return type_id_int;
    }
    // user-defined type
    else if (':' == *_s) {
        return type_id_user;
    }
    // built-in constant
    else if ('\'' == *_s) {
        // built-in type name
        if ((s_n > 2) && (':' == *(_s + 1))) {
            for (uint32_t c = 0; c < 7; c++) {
                if (! strcmp (type_id_syms[c], _s))
                    return c;
            }

            fprintf(stderr, "error: type_id_from_const_sym: unknown built-in type \"%s\"\n", _s);
            return type_id_nil;
        }
        // 'nil type
        else if (! strcmp ("'nil", _s)) {
            // NOTE: this type_id_nil is not an error
            return type_id_nil;
        }
        // types of other predefined constants
        else if (! strcmp ("'true", _s)) {
            return type_id_bool;
        }
        else if (! strcmp ("'false", _s)) {
            return type_id_bool;
        }
        else if (! strcmp ("'spc", _s)) {
            return type_id_str;
        }
        else if (! strcmp ("'nl", _s)) {
            return type_id_str;
        }
        // else fall through
    }

    // ':nil by default
    return type_id_nil;
}


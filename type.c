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

bool type_ids_from_const_sym (struct type_info *_ti) {
    fprintf(stderr, "debug: type_id_from_const_sym\n");

    if (NULL == _ti) {
        fprintf(stderr, "error: type_id_from_const_sym: NULL type_info\n");
        return false;
    }

    const char *_s = _ti->sym_s;
    const uint32_t s_n = _ti->sym_n;

    if (NULL == _s) {
        fprintf(stderr, "error: type_id_from_const_sym: NULL sym\n");
        return false;
    }
    else if ('\0' == *_s) {
        fprintf(stderr, "error: type_id_from_const_sym: NIL sym\n");
        return false;
    }
    else if (0 == s_n) {
        fprintf(stderr, "error: type_id_from_const_sym: zero sym len\n");
        return false;
    }

    // string constant
    if ('\"' == *_s) {
        _ti->type_id = type_id_str;
        return true;
    }
    // int or float constant
    else if (('-' == *_s) || isdigit(*_s)) {
        for (uint32_t c = 0; c < s_n; c ++) {
            if ('.' == *(_s + c)) {
                _ti->type_id = type_id_float;
                return true;
            }
        }
        _ti->type_id = type_id_int;
        return true;
    }
    // user-defined type
    else if (':' == *_s) {
        _ti->type_id = type_id_user;
        return true;
    }
    // built-in constant
    else if ('\'' == *_s) {
        // built-in type name
        if ((s_n > 2) && (':' == *(_s + 1))) {
            for (uint32_t c = 0; c < 7; c++) {
                if (0 == strcmp (type_id_syms[c], _s)) {
                    _ti->type_id = c;
                    return true;
                }
            }

            fprintf(stderr, "error: type_id_from_const_sym: unknown built-in type \"%s\"\n", _s);
            return false;
        }
        // 'nil type
        else if (0 == strcmp ("'nil", _s)) {
            _ti->type_id = type_id_nil;
            return true;
        }
        // types of other predefined constants
        else if (0 == strcmp ("'true", _s)) {
            _ti->type_id = type_id_bool;
            return true;
        }
        else if (0 == strcmp ("'false", _s)) {
            _ti->type_id = type_id_bool;
            return true;
        }
        else if (0 == strcmp ("'spc", _s)) {
            _ti->type_id = type_id_str;
            return true;
        }
        else if (0 == strcmp ("'nl", _s)) {
            _ti->type_id = type_id_str;
            return true;
        }
        // else fall through
    }

    return false;
}


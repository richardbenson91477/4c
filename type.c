#include "type.h"

// match order of types in type.h
const char *type_id_syms[_4C_TYPE_ID_N] = {
    "#:nil",
    "#:func",
    "#:list",
    "#:var",
    "#:int",
    "#:float",
    "#:bool",
    "#:str",
    "#:const",
    "#:pconst",
    "#:ptype",
    "#:utype",
};

bool type_ids_from_const_sym (struct type_info *_ti) {
    fprintf(stderr, "debug: type_ids_from_const_sym\n");

    if (NULL == _ti) {
        fprintf(stderr, "error: type_ids_from_const_sym: NULL type_info\n");
        return false;
    }

    const char *_s = _ti->sym_s;
    const int32_t s_n = _ti->sym_n;

    if (NULL == _s) {
        fprintf(stderr, "error: type_ids_from_const_sym: NULL sym\n");
        return false;
    }
    else if ('\0' == *_s) {
        fprintf(stderr, "error: type_ids_from_const_sym: NIL sym\n");
        return false;
    }
    else if (0 == s_n) {
        fprintf(stderr, "error: type_ids_from_const_sym: zero sym len\n");
        return false;
    }

    // string constant
    if ('\"' == *_s) {
        _ti->type_id = type_id_const;
        _ti->subtype_id = type_id_str;
        return true;
    }
    // int or float constant
    else if (('-' == *_s) || isdigit(*_s)) {
        _ti->type_id = type_id_const;

        for (int32_t c = 0; c < s_n; c ++) {
            if ('.' == *(_s + c)) {
                _ti->subtype_id = type_id_float;
                return true;
            }
        }
        _ti->subtype_id = type_id_int;
        return true;
    }
    // user-defined type
    else if (':' == *_s) {
        _ti->type_id = type_id_utype;
        // TODO: check deeper (e.g. :users:joe)
        return true;
    }
    // predefined type name
    else if ('#' == *_s) {
        for (int32_t c = 0; c < _4C_TYPE_ID_N; c++) {
            if (0 == strcmp (type_id_syms[c], _s)) {
                _ti->type_id = type_id_ptype;
                _ti->subtype_id = c;
                return true;
            }
        }

        fprintf(stderr, "error: type_ids_from_const_sym: unknown predefined type \"%s\"\n", _s);
        return false;
    }
    // predefined constant
    else if ('\'' == *_s) {
        // 'nil type
        if (0 == strcmp ("'nil", _s)) {
            _ti->type_id = type_id_pconst;
            _ti->subtype_id = type_id_nil;
            return true;
        }
        // types of other predefined constants
        else if (0 == strcmp ("'true", _s)) {
            _ti->type_id = type_id_pconst;
            _ti->subtype_id = type_id_bool;
            return true;
        }
        else if (0 == strcmp ("'false", _s)) {
            _ti->type_id = type_id_pconst;
            _ti->subtype_id = type_id_bool;
            return true;
        }
        else if (0 == strcmp ("'spc", _s)) {
            _ti->type_id = type_id_pconst;
            _ti->subtype_id = type_id_str;
            return true;
        }
        else if (0 == strcmp ("'nl", _s)) {
            _ti->type_id = type_id_pconst;
            _ti->subtype_id = type_id_str;
            return true;
        }
        else {
            fprintf(stderr, "error: type_ids_from_const_sym: unknown predefined constant \"%s\"\n", _s);
            return false;
        }
    }

    fprintf(stderr, "error: type_ids_from_const_sym: failed to deduce type of \"%s\"\n", _s);
    return false;
}


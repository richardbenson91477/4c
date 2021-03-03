-- early draft --  
-- this doc looks best when converted to html with "markdown" --

4c programming language - version 1.0 specification
===
_Foresee: To see beforehand_

## Overview
**4c** is an imperitive _(as opposed to functional)_ programming language with a LISP-like syntax.  
4c aims to be easily reasoned about by a programmer, while maintaining high performance.

**4cc** (the reference 4c compiler) compiles 4c code.  
__FIXME:__ be more specific about the generated code

This document describes the 4c language; its syntax, standard built-in types, functions, constants, and so on.  

### Rationale
__TODO__ 

### Potential benefits
  * LISP-like syntax rather than the standard "Algol family" syntax.  

### Potential drawbacks
  * LISP-like syntax rather than the standard "Algol family" syntax.  

## Syntax
### Basic program structure
; **Comments** follow semicolons  

**Function calls** take the following form:  
(function-name _arg**1**_ .. _arg**n**_)
 
Where  

  * _function-name_ specifies a built-in function or a variable of type ':func
  * _arg_ is any of the following:

    -   An _inner_ function call which returns a result to its _outer_ function  
        Example: (+ **(+ 1 1)** 2)

    -   A list  
        Example: [3 x 'false (+ y z)]

    -   A constant  
        Examples: 3 "Hello" 'nl

    -   A variable name  
        Examples: x my-string

**Lists** of values take the following form:  
[_list-item_**1**_ .. _list-item_**n**_]  

Where _list-item_ is any of the follwing:  

  * A function call
  * An _inner_ list
  * A constant
  * A variable name

### Constants
Number constants (type ':number):

  *  -9..9**.**9..9 .. 0 .. 9..9**.**9..9

String constants (type ':str):

  *  "This is a string"

### Built-in constants
'nil (empty value)  
'true (':bool true)  
'false (':bool false)  
'spc (blank-space ':str)  
'nl (newline ':str)  

### Built-in type names
':nil (empty type)  
':func (function type)  
':i32 (unsigned 32-bit integer)  
':s32 (signed 32-bit integer)  
':i64 (unsigned 64-bit integer)  
':s64 (signed 64-bit integer)  
':f32 (32-bit floating point number)  
':f64 (64-bit floating point number)  
':bool (boolean 'true or 'false)  
':str (string)  
':list (list)  

### User-defined types

  * **:**type-name  
        Names beginning with a colon (:) have their own type (see _def-type_).  
        Example: :employee (a user-defined type named :employee)  

## Built-in functions
(**set** _var-name_ _value_)  
Description: reference _value_ with the variable _var-name_  
Returns: 'nil  
Example: (set x-times-y (\* x y)) (computes x multiplied by y and sets the variable x-times-y to the result)

__FIXME:__ very volatile below this line  

(def-type :type-name [var-list]) -> 'nil  
(do [args] type-name [fn1..fnn]) -> ':func that returns type _type-name_  
(return value-for-do) -> 'nil  
(if ':bool [true-fns] [false-fns]) -> 'nil  
(while ':bool) [fn-list] [per-loop fn-list]) -> 'nil  
(print args) -> 'nil  
(input) -> ':str  
(and ':bool ':bool) -> ':bool  
(or ':bool ':bool) -> ':bool  
(not ':bool) -> ':bool  
(+ num num) -> ':number  
(- num num) -> ':number  
(\* num num) -> ':number  
(/ num num) -> ':number  
(% num num) -> ':number  
(= num num) -> ':bool  
(!= num num) -> ':bool  
(> num num) -> ':bool  
(< num num) -> ':bool  
(<= num num) -> ':bool  
(>= num num) -> ':bool  
(str-dup source-string) -> ':str  
(str-from-char char) -> ':str  
(str-cat string string) -> ':str  
(str-cmp string string) -> ':bool  
(new :type instance-var [extra-args]) -> ':bool  
    (set :type.new (do [this :type extra-params] ':bool
      [alloc/init this.vars]  
    ))  
(del :type instance-var [extra-args]) -> ':bool  
    (set :type.del (do [this :type extra-params] ':bool  
      [dealloc/deinit this.vars]  
    ))  

## Credits

### Authors
Richard A. Benson <richardbenson91477@protonmail.com><br>

### Special thanks to  
__FIXME:__ be more thankful

## Legal stuff

###This license applies to all code in this repository except where otherwise specified.

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>


4c programming language
===
_Foresee: To see beforehand_

## Overview
**4c** is an imperitive _(as opposed to functional)_ programming language with a LISP-like syntax.  
**4cc** (the 4c compiler) compiles 4c code to GNU assembly (GAS).  

This document describes the 4c language; its syntax and standard built-in types, functions, constants, etc.

### Rationale
Languages that intend to improve on C while filling the same niche are currently a dime-a-dozen. I believe this is a good thing. Let's add another.

### Potential benefits
  * Variable names specify their own types.  
  * Lisp-like syntax rather than the standard "Algol family" syntax.  

### Potential down-sides
  * Variable names specify their own types.  
  * Lisp-like syntax rather than the standard "Algol family" syntax.  

## Syntax
### Basic program structure
; **Comments** follow semicolons  

**Function calls** take the following form:  
(function-name _arg\_1_ .. _arg\_n_)
 
Where  

  * _function-name_ names a built-in function or a variable of type 'function
  * _arg_ is any of the following:

    -   an inner function call which returns a result to its outer function, e.g. (+ **(+ 1 1)** 2)
    -   a constant (e.g. 3, "Hello", 'nl)
    -   a variable name

**Lists** of values take the following form:  
[_list-item\_1 .. _list-item\_n]  

Where _list-item_ is any of the follwing:  

  * thing1
  * thing2
  * FIXME

### Constants
-9..9**.**9..9 .. 9..9**.**9..9  
"string constant"
### Built-in constants
'nil (empty type)  
'true ('boolean with value set to true)  
'false ('boolean with value set to false)  
'spc (blank-space string)  
'nl (newline string)  
### Built-in type names
'function  
'number  
'number-array  
'string   
'boolean  
### Variables

\_function-var  
number-var  
number-array-var.  
boolean-var^  
string-var$  
:type-name  
:type-name:instance-name  
:type-name:instance-name.var-instance  

## Built-in functions
(**def** _var-name_ _value_)  
description: reference _value_ with the variable _var-name_  
returns: 'nil  
 
(**set** _var-name_ _value_)  
description: assign _value_ to the variable referenced by _var-name_  
returns: 'nil  

(def-type :type-name [var-list]) -> 'nil  
(do [arg-list] [fn-list] default-return-value) -> 'function instance  
(return value-for-do) -> 'nil  
(if ('function->'boolean) [true-fn-list] [false-fn-list]) -> 'nil  
(while ('function->'boolean) [fn-list] [per-loop fn-list]) -> 'nil  
(print value) -> 'nil  
(input) -> 'string instance  
(and 'boolean 'boolean) -> 'boolean  
(or 'boolean 'boolean) -> 'boolean  
(not 'boolean) -> 'boolean  
(+ num num) -> 'number  
(- num num) -> 'number  
(* num num) -> 'number  
(/ num num) -> 'number  
(% num num) -> 'number  
(= num num) -> 'boolean  
(!= num num) -> 'boolean  
(> num num) -> 'boolean  
(< num num) -> 'boolean  
(<= num num) -> 'boolean  
(>= num num) -> 'boolean  
(str-copy target-string-var source-string) -> 'boolean  
(str-from char-number) -> 'string  
(str-add string string) -> 'string  
(str-cmp string string) -> 'boolean  
(**new** :type var [extra-args]) -> 'boolean  
(def :type.\_new (do [:type:this extra-param-vars]  
  [alloc/init :type:this.vars]  
))  

(**del** :type var [extra-args]) -> 'boolean  
(def :type.\_del (do [:type:this extra-param-vars]  
  [dealloc/deinit :type:this.vars]  
))  

## Internals
### 'function type
function name  
function argument names and types  
memory label   
### 'number type
TODO RIGHT  
### 'number-array type
TODO  
### 'string type 
memory address (if dynamic) or memory label (if static)
length in bytes
### 'boolean type
var name  
truth flag

===
## Credits

© 2021 Richard A. Benson <richardbenson91477@protonmail.com><br>


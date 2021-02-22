4c (foresee) programming language
===
_Foresee: To see beforehand_

## Overview
**4c** is an imperitive (not functional) language with a LISP-like syntax  
**4cc** (the 4c compiler) compiles 4c code to GNU assembly (GAS)

## Syntax
### Basic program structure
; comments follow semicolons

(function-name _arg\_1_ .. _arg\_n_)  
  
where _function-name_ is a built-in function or a variable of type 'function   
and _arg_ is any of the following:
  
  * an inner function to return a result to the outer function, e.g. (+ **(+ 1 1)** 2)  
  * a constant  
  * a variable name  
  
[list-item\_1 .. list-item\_n]  
### Constants
-9..9**.**9..9 .. 9..9**.**9..9  
"string constant"
### Identifiers
TODO: Gory academic details  
### Built-in type names
'function  
'number  
'number-array  
'string   
'boolean  
### Built-in constants
'nil  
'true  
'false  
'spc  
'nl  
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


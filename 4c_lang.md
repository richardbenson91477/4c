4c (foresee) language
=======================
Foresee: To see beforehand

## Overview
4c is an imperitive (not functional) language with a LISP-like syntax  
4cc (the 4c compiler) compiles 4c code to GNU assembly

## Syntax
### Basics
; comments follow semicolons
### Constants
-9...9.9...9 ... 9...9.9...9  
"string constant"
### Identifiers
...  
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
'spc$  
'nl$  
### Variables
number-var  
number-array-var.  
boolean-var^  
string-var$  
:type-name  
:type-name:instance-name  
:type-name:instance-name.var-instance  
### Program structure
(function args)  
[list of items]  

## Built-in functions
NOTE: "bool" in result types below are shorthand for one of the predefined 'boolean-s 'true and 'false  
  
(def var-name value) 'nil  
(set var-name value) 'nil  
(def-type :type-name [var-list]) 'nil  
(do [arg-list] [fn-list] default-return-value) -> 'function instance  
(return value-for-do) -> 'nil  
(if (bool function) [true-fn-list] [false-fn-list]) -> 'nil  
(while (bool function) [fn-list] [per-loop fn-list]) -> 'nil  
(print value) -> 'nil  
(input) -> 'string instance  
(and bool bool) ->   
(or bool bool) -> bool  
(not bool) -> 'true or 'false  
(+ num num) -> num  
(- num num) -> num  
(* num num) -> num  
(/ num num) -> num  
(% num num) -> num  
(= num num) -> 'true or 'false  
(!= num num) -> bool  
(> num num) -> bool  
(< num num) -> bool  
(<= num num) -> bool  
(>= num num) -> bool  
(str-copy target-string-var source-string) -> bool  
(str-from char-number) -> string  
(str-add string string) -> string  
(str-cmp string string) -> bool  
(new :type var [extra-args]) -> bool  
(del :type var [extra-args]) -> bool  

(def :type.new (do [:type:this extra-param-vars] [alloc/init :type:this.vars]))  
(def :type.del (do [:type:this extra-param-vars] [dealloc/deinit :type:this.vars]))  

## Internals
### 'function internals
function name  
function argument types  
memory label   
### 'number internals
TODO RIGHT  
### 'number array internals
TODO  
### 'string internals
memory address  
memory label  
string length  
### 'boolean internals
var name  
flag bit # 

===
## Credits
  
© 2021 Richard A. Benson <richardbenson91477@protonmail.com><br>


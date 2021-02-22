-- early draft --

4c programming language - version 1.0 specification
===
_Foresee: To see beforehand_

## Overview
**4c** is an imperitive _(as opposed to functional)_ programming language with a LISP-like syntax.  
4c is designed to facilitate compilation to native machine code, rather than interpretable byte-code. 

**4cc** (the reference 4c compiler) compiles 4c code to GNU assembly (GAS).

This document describes the 4c language; its syntax and standard built-in types, functions, constants, etc.

### Rationale
Languages that intend to improve on C while filling the same niche are currently a dime-a-dozen.

I believe this is a good thing. Let's add another.

### Potential benefits
  * Variable names specify their own types.  
  * Lisp-like syntax rather than the standard "Algol family" syntax.  

### Potential drawbacks
  * Variable names specify their own types.  
  * Lisp-like syntax rather than the standard "Algol family" syntax.  

## Syntax
### Basic program structure
; **Comments** follow semicolons  

**Function calls** take the following form:  
(function-name _arg\_1_ .. _arg\_n_)
 
Where  

  * _function-name_ specifies a built-in function or a variable of type ':function
  * _arg_ is any of the following:

    -   an _inner_ function call which returns a result to its _outer_ function, e.g. (+ **(+ 1 1)** 2)
    -   a constant (e.g. 3, "Hello", 'nl)
    -   a variable name

**Lists** of values take the following form:  
[_list-item\_1 .. _list-item\_n]  

Where _list-item_ is any of the follwing:  

  * a function call
  * a constant
  * a variable name

Note: list elements are left _unevaluated_ until required, e.g. (do [x] ...) does not _automatically_ become (do [3] ...) when x is set to 3. (Or ever, in this case, since _do_ requires variable names)

### Constants
Number constants (type ':number):

  *  -9..9**.**9..9 .. 0 .. 9..9**.**9..9

String constants (type ':string):

  *  "This is a string"

### Built-in constants
'nil (empty value)  
'true (':boolean true)  
'false (':boolean false)  
'spc (blank-space ':string)  
'nl (newline ':string)  

### Built-in type names
':function  
':number  
':number-array  
':boolean  
':string  

### Variables
Variable names describe their own types:  

  * **\_**function-var  
        Names beginning with underscore (\_) have type ':function.  
        Example: _main

  * number-var  
        Otherwise plain names have type ':number by default.  
        Example: x

  * number-array-var**.**  
        Names ending with period (.) have type ':number-array.  
        Example: square-roots.

  * boolean-var**^**  
        Names ending with carat (^) have type ':boolean.  
        Example: full-screen^

  * string-var**$**  
        Names ending with a dollar sign ($) have type ':string.  
        Example: error-msg$

  * **:**type-name  
        Names beginning with a colon (:) have their own type (see _def-type_).  
        Example: :users

  * **:**type-name**:**instance-name  
        Names beginning with :type-name-: have the type :type-name.  
        Example: :users:hans

  * **:**type-name**:**instance-name**.**var-instance  
        Names beginning with :type-name:instance-name. are variables belonging to _:instance-name_ of type _:type-name_ and have their own type determined by the name _var-instance_.  
        Example: :users:hans:full-name^

## Built-in functions
(**def** _var-name_ _value_)  
Description: reference _value_ with the variable _var-name_  
Returns: 'nil  
Example: (def \_main (do [] [(print ("Hello, world!" + 'nl))] 0))  
gives the ':function returned by _do_ the label \_main
 
(**set** _var-name_ _value_)  
Description: assign _value_ to the variable referenced by _var-name_  
Returns: 'nil  
Example: (set two-times-two (\* 2 2))  
gives the variable two-times-two the value 4  

(def-type :type-name [var-list]) -> 'nil  
(do [arg-list] [fn-list] default-return-value) -> ':function instance  
(return value-for-do) -> 'nil  
(if (':function->':boolean) [true-fn-list] [false-fn-list]) -> 'nil  
(while (':function->':boolean) [fn-list] [per-loop fn-list]) -> 'nil  
(print value) -> 'nil  
(input) -> 'string instance  
(and ':boolean ':boolean) -> ':boolean  
(or ':boolean ':boolean) -> ':boolean  
(not ':boolean) -> ':boolean  
(+ num num) -> ':number  
(- num num) -> ':number  
(* num num) -> ':number  
(/ num num) -> ':number  
(% num num) -> ':number  
(= num num) -> ':boolean  
(!= num num) -> ':boolean  
(> num num) -> ':boolean  
(< num num) -> ':boolean  
(<= num num) -> ':boolean  
(>= num num) -> ':boolean  
(str-copy target-string-var source-string) -> ':boolean  
(str-from char-number) -> 'string  
(str-add string string) -> 'string  
(str-cmp string string) -> ':boolean  
(**new** :type var [extra-args]) -> ':boolean  
(def :type.\_new (do [:type:this extra-param-vars]  
  [alloc/init :type:this.vars]  
))  

(**del** :type var [extra-args]) -> ':boolean  
(def :type.\_del (do [:type:this extra-param-vars]  
  [dealloc/deinit :type:this.vars]  
))  

## Internals

### ':function type
function name  
function argument names and types  
memory label   

### ':number type
TODO RIGHT  

### ':number-array type
TODO  

### ':string type 
memory address (if dynamic) or memory label (if static)
length in bytes

### ':boolean type
var name  
truth flag

===
## Credits

© 2021 Richard A. Benson <richardbenson91477@protonmail.com><br>


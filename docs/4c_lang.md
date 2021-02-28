-- early draft --  
-- this doc looks best when converted to html with "markdown" --

4c programming language - version 1.0 specification
===
_Foresee: To see beforehand_

## Overview
**4c** is an imperitive _(as opposed to functional)_ programming language with a LISP-like syntax.  
4c is designed to facilitate compilation to native machine code (as in the languages C/C++), rather than interpretable (or JIT-able) byte-code, symbols, and so forth.  
4c code is intended to be as easily parsed and reasoned about by a programmer as is reasonably attainable.  

**4cc** (the reference 4c compiler) compiles 4c code to GNU assembly (GAS).

This document describes the 4c language; its syntax and standard built-in types, functions, constants, etc.

### Rationale
The hydra known as "Modern C++" has great value in terms of performance and capabilities - at a usability cost that many people would like to avoid paying. Simpler to use languages like Python already exist - with an obvious performance cost. Many "C performance with modern features" languages have come forth to try and remedy the situation. Perhaps one will dethrone C++ - or perhaps none will. Nevertheless, they have their own inherent value to those who enjoy using them. I do not _expect_ 4c to become popular - nor do I plan to force the issue. 4c is simply my personal attempt to avoid using "Modern C++" - if others find it useful, that's great.  

### Potential benefits
  * Variable and function names specify their own types.  
  * Lisp-like syntax rather than the standard "Algol family" syntax.  

### Potential drawbacks
  * Variable and function names specify their own types.  
  * Lisp-like syntax rather than the standard "Algol family" syntax.  

## Syntax
### Basic program structure
; **Comments** follow semicolons  

**Function calls** take the following form:  
(function-name _arg**1**_ .. _arg**n**_)
 
Where  

  * _function-name_ specifies a built-in function or a variable of type ':function
  * _arg_ is any of the following:

    -   An _inner_ function call which returns a result to its _outer_ function  
        Example: (+% **(+% 1 1)** 2)

    -   A list  
        Example: [3 x$ 'false^ (+% y z)]

    -   A constant  
        Examples: 3 "Hello" 'nl$

    -   A variable name  
        Examples: x my-string$

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

String constants (type ':string):

  *  "This is a string"

### Built-in constants
'nil (empty value)  
'true^ (':boolean true)  
'false^ (':boolean false)  
'spc$ (blank-space ':string)  
'nl$ (newline ':string)  

### Built-in type names
':nil  
':function  
':number  
':number-array  
':boolean  
':string  

### Variables
Variable names describe their own types:  

  * **\_**function-var  
        Names beginning with the character \_ have type ':function.  
        If there is not a special end character, the return type is ':nil. The end character % has return type ':number. Other end characters follow the conventions below.  
        Example 1: \_main% (a function that returns a ':number)  
        Example 2: \_do-nothing (a function that returns ':nil)  
        Example 3: \_is-ok^ (a function that returns a ':boolean)  

  * number-var  
        Otherwise plain names have type ':number by default.  
        Example: x (a variable holding a ':number)  

  * number-array-var**.**  
        Names ending with period (.) have type ':number-array.  
        Example: square-roots. (an array of ':number-s)  

  * boolean-var**^**  
        Names ending with carat (^) have type ':boolean.  
        Example: full-screen^ (a variable holding a ':bool)  

  * string-var**$**  
        Names ending with a dollar sign ($) have type ':string.  
        Example: error-msg$ (a variable holding a ':string)  

  * **:**type-name  
        Names beginning with a colon (:) have their own type (see _def-type_).  
        Example: :employee (a user-defined type named :employee)  

  * **:**type-name**:**instance-name  
        Names beginning with :type-name: have the type :type-name.  
        Example: :employee:hans (a variable holding an :employee)  

  * **:**type-name**:**instance-name**.**var-instance  
        Names beginning with :type-name:instance-name. are variables belonging to _:instance-name_ of type _:type-name_ and have their own type determined by the name _var-instance_.  
        Example: :employee:hans:full-name$ (a variable holding a ':string)  

## Built-in functions
(**set** _var-name_ _value_)  
Description: assign _value_ to the variable referenced by _var-name_  
Returns: 'nil  
Example: (set x-times-y (\*% x y)) (computes x multiplied by y and assignes the result to the variable x-times-y 

(def-type :type-name [var-list]) -> 'nil  
(do\_ [arg-list] type-name [fn-list] default-return-value) -> ':function that returns type _type-name_  
(return($,%,^) value-for-do) -> (depends on end character)  
(if ':boolean [true-fn-list] [false-fn-list]) -> 'nil  
(while ':boolean) [fn-list] [per-loop fn-list]) -> 'nil  
(print args) -> 'nil  
(input$) -> ':string  
(eval($,%,^) ':function func-args) -> (depends on end character)  
(and^ ':boolean ':boolean) -> ':boolean  
(or^ ':boolean ':boolean) -> ':boolean  
(not^ ':boolean) -> ':boolean  
(+% num num) -> ':number  
(-% num num) -> ':number  
(\*% num num) -> ':number  
(/% num num) -> ':number  
(%% num num) -> ':number  
(=^ num num) -> ':boolean  
(!=^ num num) -> ':boolean  
(>^ num num) -> ':boolean  
(<^ num num) -> ':boolean  
(<=^ num num) -> ':boolean  
(>=^ num num) -> ':boolean  
(str-dup^ source-string) -> ':string  
(str-from-char$ char) -> ':string  
(str-cat$ string string) -> ':string  
(str-cmp^ string string) -> ':boolean  
(new^ :type instance-var [extra-args]) -> ':boolean  
    (set :type._new^ (do\_ [:type:this extra-param-vars] ':boolean  
      [alloc/init :type:this.vars]  
    ))  
(del^ :type instance-var [extra-args]) -> ':boolean  
    (set :type.\_del^ (do\_ [:type:this extra-param-vars]  ':boolean  
      [dealloc/deinit :type:this.vars]  
    ))  

===
## Credits

© 2021 Richard A. Benson <richardbenson91477@protonmail.com><br>

Special thanks to: TODO

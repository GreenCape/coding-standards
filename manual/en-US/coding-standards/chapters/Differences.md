Differences
===========

The style rules of the Joomla! Coding Standard were created long before PSR-1
and PSR-2 emerged. Thus, the Joomla! project decided NOT to follow these standards,
since the Joomla! Coding Standard is well accepted in the community.

Changes from PSR
----------------

The changes from PSR-1 and PSR-2 are:

  - PHP prior to 5.3 is not supported.
  - Property names MUST be declared in `$camelCase`.
  - Code MUST use tabs for indenting, not spaces.
  - Opening braces for control structures MUST go on the next line.
  - The `while` keyword in a `do while` statement goes on a new line.
  - There MUST be one blank line after the `case` body.
  
Changes from version 1
----------------------

  - Missing rules from PSR-1 and PSR-2 have been added, where suitable.
  - The soft line limit has been reduced to 120 characters.
  - The rules for conditional and unconditional file inclusion have been dropped,
    because it might be needed to include files multiple times (f.x., template blocks),
  - The reference operator `&` MUST not be used with objects, since objects
    always are handled by reference.
  - Use spaces to align assignments.
  - Rules for the concatenation operator have been extended to cover binary operators
    in general.
  - PSR-5 has been included for DocBlock comments.
  

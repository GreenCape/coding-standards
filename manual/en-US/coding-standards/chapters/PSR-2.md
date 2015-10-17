Joomla! Coding Standard
=======================

The intent of this guide is to reduce cognitive friction when scanning code
from different authors. It does so by enumerating a shared set of rules and
expectations about how to format and use PHP code.

The style rules herein were created before PSR-1 and PSR-2 emerged. Thus, the
Joomla! project decided NOT to follow these standards, since the Joomla! Coding
Standard is well accepted in the community.

However, this document describes the Joomla! Coding Standard similar to the
structure of the PSR-2 standard, embedding the (modified) rules from PSR-1. 

The Joomla! Coding Standard applies to all code committed to any part of the
Joomla! project, e.g., the CMS Version 4 and up, the Framework, and Joomla!
applications.

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD",
"SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be
interpreted as described in [RFC 2119].

1. Overview
-----------

- Files MUST use only `<?php` and `<?=` tags.

- Files MUST use only UTF-8 without BOM for PHP code.

- Files SHOULD *either* declare symbols (classes, functions, constants, etc.)
  *or* cause side-effects (e.g. generate output, change .ini settings, etc.)
  but SHOULD NOT do both.

- Namespaces and classes MUST follow an "autoloading" PSR: [[PSR-0], [PSR-4]].

- Class names MUST be declared in `StudlyCaps`.

- Class constants MUST be declared in all upper case with underscore separators.

- Method and property names MUST be declared in `camelCase`.

- Code MUST use tabs for indenting, not spaces.

- There MUST NOT be a hard limit on line length; the soft limit MUST be 120
  characters; lines SHOULD be 80 characters or less.

- There MUST be one blank line after the `namespace` declaration, and there
  MUST be one blank line after the block of `use` declarations.

- Opening braces for classes MUST go on the next line, and closing braces MUST
  go on the next line after the body.

- Opening braces for methods MUST go on the next line, and closing braces MUST
  go on the next line after the body.

- Visibility MUST be declared on all properties and methods; `abstract` and
  `final` MUST be declared before the visibility; `static` MUST be declared
  after the visibility.
  
- Control structure keywords MUST have one space after them; method and
  function calls MUST NOT.

- Opening braces for control structures MUST go on the next line, and closing
  braces MUST go on the next line after the body.

- Opening parentheses for control structures MUST NOT have a space after them,
  and closing parentheses for control structures MUST NOT have a space before.

### 1.1. Example

This example encompasses some of the rules below as a quick overview:

```php
<?php
namespace Vendor\Package;

use FooInterface;
use BarClass as Bar;
use OtherVendor\OtherPackage\BazClass;

class Foo extends Bar implements FooInterface
{
	public function sampleFunction($a, $b = null)
	{
		if ($a === $b)
		{
			bar();
		}
		elseif ($a > $b) 
		{
			$foo->bar($arg1);
		} 
		else 
		{
			BazClass::bar($arg2, $arg3);
		}
	}

	final public static function bar()
	{
		// method body
	}
}
```

2. General
----------

PHP code MUST be `E_ALL` and SHOULD be `E_STRICT` compliant.

### 2.1. Files

#### 2.1.1. PHP Tags

PHP code MUST use the long `<?php ?>` tags or the short-echo `<?= ?>` tags; it
MUST NOT use the other tag variations.

The closing `?>` tag MUST be omitted from files containing only PHP.

> It is not required by PHP. Leaving this out prevents trailing white space from being accidentally injected into the output that can introduce errors in the Joomla session (see the PHP manual on [Instruction separation]).

#### 2.1.2. Character Encoding

PHP code MUST use only UTF-8 without BOM.

#### 2.1.3. Side Effects

A file SHOULD declare new symbols (classes, functions, constants,
etc.) and cause no other side effects, or it SHOULD execute logic with side
effects, but SHOULD NOT do both.

The phrase "side effects" means execution of logic not directly related to
declaring classes, functions, constants, etc., *merely from including the
file*.

"Side effects" include but are not limited to: generating output, explicit
use of `require` or `include`, connecting to external services, modifying ini
settings, emitting errors or exceptions, modifying global or static variables,
reading from or writing to a file, and so on.

The following is an example of a file with both declarations and side effects;
i.e, an example of what to avoid:

```php
<?php
// side effect: change ini settings
ini_set('error_reporting', E_ALL);

// side effect: loads a file
include "file.php";

// side effect: generates output
echo "<html>\n";

// declaration
function foo()
{
	// function body
}
```

The following example is of a file that contains declarations without side
effects; i.e., an example of what to emulate:

```php
<?php
// declaration
function foo()
{
	// function body
}

// conditional declaration is *not* a side effect
if (! function_exists('bar')) {
	function bar()
	{
		// function body
	}
}
```

#### 2.1.4. Line Endings

All PHP files MUST use the Unix LF (linefeed) line ending.

#### 2.1.5. File Endings

All PHP files MUST end with a single blank line.

### 2.2. Lines

There MUST NOT be a hard limit on line length.

The soft limit on line length MUST be 120 characters; automated style checkers
MUST warn but MUST NOT error at the soft limit.

Lines SHOULD NOT be longer than 80 characters; lines longer than that SHOULD
be split into multiple subsequent lines of no more than 80 characters each.

There MUST NOT be trailing whitespace at the end of non-blank lines.

Blank lines MAY be added to improve readability and to indicate related
blocks of code.

There MUST NOT be more than one statement per line.

### 2.3. Indenting

Code MUST use tabs for indenting, and MUST NOT use spaces for indenting.

### 2.4. Keywords and True/False/Null

PHP [keywords] MUST be in lower case.

Arguments to the PHP language constructs `echo`, `include`, `include_once`,
`require` and `require_once` MUST NOT be enclosed in parenthesis.

The PHP constants `true`, `false`, and `null` MUST be in lower case.

3. Namespace, Use Declarations and Class Names
----------------------------------------------

Namespaces and classes MUST follow an "autoloading" PSR: [[PSR-0], [PSR-4]].

This means each class is in a file by itself, and is in a namespace of at
least one level: a top-level vendor name.

Class names MUST be declared in `StudlyCaps`.

Code MUST use formal namespaces.

There MUST be one blank line after the `namespace` declaration.

When present, all `use` declarations MUST go after the `namespace`
declaration.

There MUST be one `use` keyword per declaration.

There MUST be one blank line after the `use` block.

For example:

```php
<?php
namespace Vendor\Package;

use FooClass;
use BarClass as Bar;
use OtherVendor\OtherPackage\BazClass;

// ... additional PHP code ...

```

3.1. Global Namespace
---------------------

Usage of the global namespace SHOULD be avoided. Especially global variables SHOULD
not be used at all. Use OOP and factory patterns instead.


4. Classes, Class Constants, Properties, and Methods
----------------------------------------------------

The term "class" refers to all classes, interfaces, and traits.

### 4.1. Extends and Implements

The `extends` and `implements` keywords MUST be declared on the same line as
the class name.

The opening brace for the class MUST go on its own line; the closing brace
for the class MUST go on the next line after the body.

```php
<?php
namespace Vendor\Package;

use FooClass;
use BarClass as Bar;
use OtherVendor\OtherPackage\BazClass;

class ClassName extends ParentClass implements \ArrayAccess, \Countable
{
	// constants, properties, methods
}
```

Lists of `implements` MAY be split across multiple lines, where each
subsequent line is indented once. When doing so, the first item in the list
MUST be on the next line, and there MUST be only one interface per line.

```php
<?php
namespace Vendor\Package;

use FooClass;
use BarClass as Bar;
use OtherVendor\OtherPackage\BazClass;

class ClassName extends ParentClass implements
	\ArrayAccess,
	\Countable,
	\Serializable
{
	// constants, properties, methods
}
```

### 4.2. Constants

Class constants MUST be declared in all upper case with underscore separators.
For example:

```php
<?php
namespace Vendor\Model;

class Foo
{
	const VERSION = '1.0';
	const DATE_APPROVED = '2012-06-01';
}
```

### 4.3. Properties

Property names MUST be declared in `$camelCase`.

Visibility MUST be declared on all properties.

The `var` keyword MUST NOT be used to declare a property.

There MUST NOT be more than one property declared per statement.

Property names SHOULD NOT be prefixed with a single underscore to indicate
protected or private visibility.

A property declaration looks like the following.

```php
<?php
namespace Vendor\Package;

class ClassName
{
	public $foo = null;
}
```

### 4.4. Methods

Method names MUST be declared in `camelCase()`.

Visibility MUST be declared on all methods.

Method names SHOULD NOT be prefixed with a single underscore to indicate
protected or private visibility.

Method names MUST NOT be declared with a space after the method name. The
opening brace MUST go on its own line, and the closing brace MUST go on the
next line following the body. There MUST NOT be a space after the opening
parenthesis, and there MUST NOT be a space before the closing parenthesis.

A method declaration looks like the following. Note the placement of
parentheses, commas, spaces, and braces:

```php
<?php
namespace Vendor\Package;

class ClassName
{
	public function fooBarBaz($arg1, &$arg2, $arg3 = [])
	{
		// method body
	}
}
```    

### 4.5. Method Arguments

In the argument list, there MUST NOT be a space before any comma, and there
MUST be one space after each comma.

Method arguments with default values MUST go at the end of the argument
list.

```php
<?php
namespace Vendor\Package;

class ClassName
{
	public function foo($arg1, &$arg2, $arg3 = [])
	{
		// method body
	}
}
```

Argument lists MAY be split across multiple lines, where each subsequent line
is indented once. When doing so, the first item in the list MUST be on the
next line, and there MUST be only one argument per line.

When the argument list is split across multiple lines, the closing parenthesis
and opening brace MUST be placed together on their own line with one space
between them.

```php
<?php
namespace Vendor\Package;

class ClassName
{
	public function aVeryLongMethodName(
		ClassTypeHint $arg1,
		&$arg2,
		array $arg3 = []
	) {
		// method body
	}
}
```

### 4.6. `abstract`, `final`, and `static`

When present, the `abstract` and `final` declarations MUST precede the
visibility declaration.

When present, the `static` declaration MUST come after the visibility
declaration.

```php
<?php
namespace Vendor\Package;

abstract class ClassName
{
	protected static $foo;

	abstract protected function zim();

	final public static function bar()
	{
		// method body
	}
}
```

### 4.7. Method and Function Calls

When making a method or function call, there MUST NOT be a space between the
method or function name and the opening parenthesis, there MUST NOT be a space
after the opening parenthesis, and there MUST NOT be a space before the
closing parenthesis. In the argument list, there MUST NOT be a space before
each comma, and there MUST be one space after each comma.

```php
<?php
bar();
$foo->bar($arg1);
Foo::bar($arg2, $arg3);
```

Argument lists MAY be split across multiple lines, where each subsequent line
is indented once. When doing so, the first item in the list MUST be on the
next line, and there MUST be only one argument per line.

```php
<?php
$foo->bar(
	$longArgument,
	$longerArgument,
	$muchLongerArgument
);
```

5. Control Structures
---------------------

The general style rules for control structures are as follows:

- There MUST be one space after the control structure keyword
- There MUST NOT be a space after the opening parenthesis
- There MUST NOT be a space before the closing parenthesis
- There MUST be one space between the closing parenthesis and the opening brace
- The opening brace MUST go on the next line.
- The structure body MUST be indented once
- The closing brace MUST be on the next line after the body

The body of each structure MUST be enclosed by braces. This standardizes how
the structures look, and reduces the likelihood of introducing errors as new
lines get added to the body.

### 5.1. Conditional (Boolean) Expressions

For conjunction of boolean expressions `||` or `&&` MUST be used.

If a condition expression goes over multiple lines, all lines MUST be indented
by one level and the closing brace MUST go on the same line as the last parameter.

```php
if ($test1
	&& $test2)
{
	echo 'True';
}

### 5.2. `if`, `elseif`, `else`

An `if` structure looks like the following. Note the placement of parentheses,
spaces, and braces; and that `else` and `elseif` are on their own line.

```php
<?php
if ($expr1)
{
	// if body
} 
elseif ($expr2) 
{
	// elseif body
} 
else 
{
	// else body
}
```

The keyword `elseif` SHOULD be used instead of `else if` so that all control
keywords look like single words.


### 5.3. `switch`, `case`

A `switch` structure looks like the following. Note the placement of
parentheses, spaces, and braces. The `case` statement MUST be indented once
from `switch`, and the `break` keyword (or other terminating keyword) MUST be
indented at the same level as the `case` body. There MUST be a comment such as
`// no break` when fall-through is intentional in a non-empty `case` body.

There MUST be one blank line after the `case` body.

```php
<?php
switch ($expr) 
{
	case 0:
		echo 'First case, with a break';
		break;

	case 1:
		echo 'Second case, which falls through';
		// no break

	case 2:
	case 3:
	case 4:
		echo 'Third case, return instead of break';
		return;

	default:
		echo 'Default case';
		break;
}
```


### 5.4. `while`, `do while`

A `while` statement looks like the following. Note the placement of
parentheses, spaces, and braces.

```php
<?php
while ($expr) 
{
	// structure body
}
```

Similarly, a `do while` statement looks like the following. Note the placement
of parentheses, spaces, and braces.

```php
<?php
do
{
	// structure body
}
while ($expr);
```

### 5.5. `for`

A `for` statement looks like the following. Note the placement of parentheses,
spaces, and braces.

```php
<?php
for ($i = 0; $i < 10; $i++) 
{
	// for body
}
```

### 5.6. `foreach`
    
A `foreach` statement looks like the following. Note the placement of
parentheses, spaces, and braces.

```php
<?php
foreach ($iterable as $key => $value)
{
	// foreach body
}
```

### 5.7. `try`, `catch`

A `try catch` block looks like the following. Note the placement of
parentheses, spaces, and braces.

```php
<?php
try
{
	// try body
}
catch (FirstExceptionType $e)
{
	// catch body
}
catch (OtherExceptionType $e)
{
	// catch body
}
```

6. Closures
-----------

Closures MUST be declared with a space after the `function` keyword, and a
space before and after the `use` keyword.

The opening brace MUST go on the same line, and the closing brace MUST go on
the next line following the body.

There MUST NOT be a space after the opening parenthesis of the argument list
or variable list, and there MUST NOT be a space before the closing parenthesis
of the argument list or variable list.

In the argument list and variable list, there MUST NOT be a space before each
comma, and there MUST be one space after each comma.

Closure arguments with default values MUST go at the end of the argument
list.

A closure declaration looks like the following. Note the placement of
parentheses, commas, spaces, and braces:

```php
<?php
$closureWithArgs = function ($arg1, $arg2) {
	// body
};

$closureWithArgsAndVars = function ($arg1, $arg2) use ($var1, $var2) {
	// body
};
```

Argument lists and variable lists MAY be split across multiple lines, where
each subsequent line is indented once. When doing so, the first item in the
list MUST be on the next line, and there MUST be only one argument or variable
per line.

When the ending list (whether or arguments or variables) is split across
multiple lines, the closing parenthesis and opening brace MUST be placed
together on their own line with one space between them.

The following are examples of closures with and without argument lists and
variable lists split across multiple lines.

```php
<?php
$longArgs_noVars = function (
	$longArgument,
	$longerArgument,
	$muchLongerArgument
) {
	// body
};

$noArgs_longVars = function () use (
	$longVar1,
	$longerVar2,
	$muchLongerVar3
) {
	// body
};

$longArgs_longVars = function (
	$longArgument,
	$longerArgument,
	$muchLongerArgument
) use (
	$longVar1,
	$longerVar2,
	$muchLongerVar3
) {
	// body
};

$longArgs_shortVars = function (
	$longArgument,
	$longerArgument,
	$muchLongerArgument
) use ($var1) {
	// body
};

$shortArgs_longVars = function ($arg) use (
	$longVar1,
	$longerVar2,
	$muchLongerVar3
) {
	// body
};
```

Note that the formatting rules also apply when the closure is used directly
in a function or method call as an argument.

```php
<?php
$foo->bar(
	$arg1,
	function ($arg2) use ($var1) {
		// body
	},
	$arg3
);
```

7. Operators
------------

### 7.1. Assignments

Assignments SHOULD be aligned with spaces.

There MUST be at least one space before the operator and exactly one after it.

```php
$foo    = 'foo';
$bar    = 'bar';
$foobar = 'foobar';
```

Assignments in arrays SHOULD be aligned with spaces as well.

There MUST be at least one space before the operator and exactly one after it.

When splitting array definitions onto several lines, the last value MAY also
have a trailing comma. This is valid PHP syntax and helps to keep code diffs minimal.

```php
$options = array(
	'foo'  => 'foo',
	'spam' => 'spam',
);
```

### 7.2. References

The reference operator `&` MUST not be used with objects, since objects
always are handled by reference.

When using references for arrays or scalars, there MUST be a space before the
reference operator and no space between it and the function or variable name.

```php
<?php
$reference = &$this->scalar;
```

### 7.4. Binary Operators

There MUST be one space before and after any binary operator.

```php
$foobar  = $foo . $bar;
$sum     = $a + 2;
$complex = $a + 2 * $b - $c;
```

The expression MAY be split across multiple lines on the operators with the
least precedence. In that case it MUST be split on all operators on the same
level.

Each subsequent line is indented once. The operator MUST be the first item on
the next line, and there MUST be only one argument or variable per line.

```php
$foobar = $foo
	. $bar
	. 'something very long'
	. 'something even longer';

$sum = $a 
	+ 2;

$complex = $a
	+ 2 * $b
	- $c;
```

8. Commenting
=============

### 8.1. Inline Commenting

Inline comments to explain code follow the convention for C (`/* … */`)
and C++ single line (`// ...`) comments.

The C++ style SHOULD be used for making code notes. Comments with more
than two lines SHOULD C style comments.

Perl/shell style comments (`#`) are not permitted in PHP files.

> Code notes are strongly encouraged to help other people, including your
> future-self, follow the purpose of the code. Always provide notes where
> the code is performing particularly complex operations.
>
> However, if you need more than a one-liner to explain the code, consider
> moving the code into its own method and put the comment into the DocBlock
> instead.

### 8.2. DocBlock Headers

DocBlock comments MUST follow the rules described in the proposal for [PSR-5],
that currently is in the draft state.

Whereas normal code indenting uses tabs, all whitespace in a DocBlock uses
real spaces. This provides better readability in source code browsers.
The minimum whitespace between any text elements, such as tags, variable types,
variable names and tag descriptions, is two real spaces. Variable types and tag
descriptions should be aligned according to the longest DocBlock tag and
type-plus-variable respectively.

The following sections define, which tags have to be used in which order. 

#### 8.2.1. File DocBlock Headers

The file header DocBlock consists of the following required and optional
elements in the following order:

  - Short description (required).
  - Long description (optional, followed by a blank line).
  - `@package` (generally optional but required when files contain only procedural code)
  - `@copyright` (required)
  - `@license` (required and must be compatible with the Joomla license)
  - `@deprecated` (optional)
  - `@link` (optional)
  - `@see` (optional)
  - `@since` (generally optional but required when files contain only procedural code)

```
<?php
/**
 * Part of the Joomla Framework ORM Package
 *
 * @copyright  Copyright (C) 2015 Open Source Matters, Inc. All rights reserved.
 * @license    GNU General Public License version 2 or later; see LICENSE
 */
```


#### 8.2.2. Class DocBlock Headers

#### 8.2.3. Class Property DocBlocks

#### 8.2.4. Class Method DocBlocks

[RFC 2119]: http://www.ietf.org/rfc/rfc2119.txt
[PSR-0]: https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-0.md
[PSR-1]: https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-1-basic-coding-standard.md
[PSR-2]: https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-2-coding-style-guide.md
[PSR-4]: https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-4-autoloader.md
[PSR-5]: https://github.com/php-fig/fig-standards/pull/169
[keywords]: http://php.net/manual/en/reserved.keywords.php
[Instruction separation]: http://php.net/basic-syntax.instruction-separation

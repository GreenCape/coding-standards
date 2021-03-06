<?php
/**
 * Test file for the Joomla! Coding Standard
 */

// Valid: Asterisks are aligned with one space between asterisk and tag.
/**
 * @see foo()
 */

// Invalid: Asterisks are not aligned.
/**
* @see foo()
*/

// Invalid: Too many spaces between asterisk and tag.
/**
 *  @see foo()
 */

// Invalid: No spaces between asterisk and tag.
/**
 *@see foo()
 */

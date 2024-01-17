/** */;
/** Functions for working with single characters.

    Character literals are enclosed in ['a'] pair of single quotes.

    {[
      let digit = '7'
    ]}

    The functions in this module work on ASCII characters (range 0-255) only,
    {b not Unicode}.

    Note that in Rescript source code you can include only the characters from 0-127 range.
    Full list of available characters is available {{: https://www.w3schools.com/charsets/ref_html_ascii.asp } here}.

    Characters from 128-255 range can still be handled, but only as codes.
*/;
type nonrec t = char;
/** {1 Create}

    You can also create a {!Char} using single quotes:

    {[
      let char = 'c'
    ]}
*/;
/** Convert an ASCII {{: https://en.wikipedia.org/wiki/Code_point } code point } to a character.

    The full range of extended ASCII is from [0] to [255].
    For numbers outside that range, you get [None].

    {2 Examples}

    {[
      Char.fromCode(65) == Some('A')
      Char.fromCode(66) == Some('B')
      Char.fromCode(3000) == None
      Char.fromCode(-1) == None
    ]}
*/
external fromCode: int => option(char) = ;
/** Converts a string to character.

    Returns [None] when the [string] isn't of length one.

    {2 Examples}

    {[
      Char.fromString("A") == Some('A')
      Char.fromString(" ") == Some(' ')
      Char.fromString("") == None
      Char.fromString("abc") == None
      Char.fromString(" a") == None
    ]}
*/
external fromString: string => option(char) = ;
/** Detect lower case ASCII characters.

    {2 Examples}

    {[
      Char.isLowercase('a') == true
      Char.isLowercase('b') == true
      Char.isLowercase('z') == true
      Char.isLowercase('0') == false
      Char.isLowercase('A') == false
      Char.isLowercase('-') == false
    ]}
*/
external isLowercase: char => bool = ;
/** Detect upper case ASCII characters.

    {2 Examples}

    {[
      Char.isUppercase('A') == true
      Char.isUppercase('B') == true
      Char.isUppercase('Z') == true
      Char.isUppercase('h') == false
      Char.isUppercase('0') == false
      Char.isUppercase('-') == false
    ]}
*/
external isUppercase: char => bool = ;
/** Detect upper and lower case ASCII alphabetic characters.

    {2 Examples}

    {[
      Char.isLetter('a') == true
      Char.isLetter('b') == true
      Char.isLetter('E') == true
      Char.isLetter('Y') == true
      Char.isLetter('0') == false
      Char.isLetter('-') == false
    ]}
*/
external isLetter: char => bool = ;
/** Detect when a character is a number.

    {2 Examples}

    {[
      Char.isDigit('0') == true
      Char.isDigit('1') == true
      Char.isDigit('9') == true
      Char.isDigit('a') == false
      Char.isDigit('b') == false
    ]}
*/
external isDigit: char => bool = ;
/** Detect upper case, lower case and digit ASCII characters.

    {2 Examples}

    {[
      Char.isAlphanumeric('a') == true
      Char.isAlphanumeric('b') == true
      Char.isAlphanumeric('E') == true
      Char.isAlphanumeric('Y') == true
      Char.isAlphanumeric('0') == true
      Char.isAlphanumeric('7') == true
      Char.isAlphanumeric('-') == false
    ]}
*/
external isAlphanumeric: char => bool = ;
/** Detect if a character is a {{: https://en.wikipedia.org/wiki/ASCII#Printable_characters } printable } character

    A Printable character has a {!Char.toCode} in the range 32 to 127, inclusive ([' '] to ['~']).

    {2 Examples}

    {[
      Char.isPrintable('G') == true
      Char.isPrintable('%') == true
      Char.isPrintable(' ') == true
      Char.isPrintable('	') == false
      Char.isPrintable('') == false
    ]}
*/
external isPrintable: char => bool = ;
/** Detect one of the following characters:
    - ['	'] (tab)
    - ['
'] (newline)
    - [''] (vertical tab)
    - [''] (form feed)
    - [''] (carriage return)
    - [' '] (space)

    {2 Examples}

    {[
      Char.isWhitespace('	') == true
      Char.isWhitespace(' ') == true
      Char.isWhitespace('?') == false
      Char.isWhitespace('G') == false
    ]}
*/
external isWhitespace: char => bool = ;
/** Converts an ASCII character to lower case, preserving non alphabetic ASCII characters.

    {2 Examples}

    {[
      Char.toLowercase('A') == 'a'
      Char.toLowercase('B') == 'b'
      Char.toLowercase('7') == '7'
    ]}
*/
external toLowercase: char => char = ;
/** Convert an ASCII character to upper case, preserving non alphabetic ASCII characters.

    {2 Examples}

    {[
      Char.toUppercase('a') == 'A'
      Char.toUppercase('b') == 'B'
      Char.toUppercase('7') == '7'
    ]}
*/
external toUppercase: char => char = ;
/** Convert [char] to the corresponding ASCII {{: https://en.wikipedia.org/wiki/Code_point } code point}.

    {2 Examples}

    {[
      Char.toCode('A') == 65
      Char.toCode('B') == 66
    ]}
*/
external toCode: char => int = ;
/** Convert a character into a [string].

    {2 Examples}

    {[
      Char.toString('A') == "A"
      Char.toString('{') == "{"
      Char.toString('7') == "7"
    ]}
*/
external toString: char => string = ;
/** Converts a digit character to its corresponding {!Int}.

    Returns [None] when the character isn't a digit.

    {2 Examples}

    {[
      Char.toDigit("7") == Some(7)
      Char.toDigit("0") == Some(0)
      Char.toDigit("A") == None
      Char.toDigit("") == None
    ]}
*/
external toDigit: char => option(int) = ;
/** Test two {!Char}s for equality */ external equal: (t, t) => bool = ;
/** Compare two {!Char}s */ external compare: (t, t) => int = ;
/** The unique identity for {!Comparator} */
type nonrec identity;
external comparator: TableclothComparator.t(t, identity) = ;

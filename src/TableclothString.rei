/** */;
/** Functions for working with ["strings"] */;
type nonrec t = string;
/** {1 Create}

    Strings literals are created with the ["double quotes"], [`backticks`] syntax.
    {b Warning} If string contains non-ASCII characters, use [`backticks`]

*/;
/** Converts the given character to an equivalent string of length one. */
external fromChar: char => string = ;
/** Create a string from an {!Array} of characters.

    Note that these must be individual characters in single quotes, not strings of length one.

    {2 Examples}

    {[
      String.fromArray([]) == ""
      String.fromArray(['a', 'b', 'c']) == "abc"
    ]}
*/
external fromArray: array(char) => string = ;
/** Create a string from a {!List} of characters.

    Note that these must be individual characters in single quotes, not strings of length one.

    {2 Examples}

    {[
      String.fromList(list{}) == ""
      String.fromList(list{'a', 'b', 'c'}) == "abc"
    ]}
*/
external fromList: list(char) => string = ;
/** Create a string by repeating a string [count] time.

    {3 Exceptions}

    If [count] is negative, [String.repeat] throws a [RangeError] exception.

    {2 Examples}

    {[
      String.repeat("ok", ~count=3) == "okokok"
      String.repeat("", ~count=3) == ""
      String.repeat("ok", ~count=0) == ""
    ]}
*/
external repeat: (string, ~count: [@ns.namedArgLoc] int) => string = ;
/** Create a string by providing a length and a function to choose characters.

    Returns an empty string if the length is negative.

    {2 Examples}

    {[
      String.initialize(8, ~f=Fun.constant('9')) == "99999999"
    ]}
*/
external initialize: (int, ~f: [@ns.namedArgLoc] (int => char)) => string = ;
/** {1 Basic operations} */;
/** Get the character at the specified index

    {3 Exceptions}

    If index out of range, throws a [Invalid_argument] exception.
    Concider using {!getAt}, it returns an [option<char>]

    {2 Examples}

    {[
      String.get("stressed", 1) == 't'
    ]}

*/
external get: (string, int) => char = ;
/** Get the character at [~index] */
external getAt: (string, ~index: [@ns.namedArgLoc] int) => option(char) = ;
/** Reverse a string

    {2 Examples}

    {[
      String.reverse("stressed") == "desserts"
    ]}
*/
external reverse: string => string = ;
/** Extract a substring from the specified indicies.

    See {!Array.slice}.
*/
external slice:
  (~to_: [@ns.namedArgLoc] int=?, string, ~from: [@ns.namedArgLoc] int) =>
  string =
  ;
/** {1 Query} */;
/** Check if a string is empty */ external isEmpty: string => bool = ;
/** Returns the length of the given string.

    {2 Examples}

    {[
      String.length("abc") == 3
    ]}
*/
external length: string => int = ;
/** See if the string starts with [prefix].

    {2 Examples}

    {[
      String.startsWith("theory", ~prefix="the") == true
      String.startsWith("theory", ~prefix="ory") == false
    ]}
*/
external startsWith: (string, ~prefix: [@ns.namedArgLoc] string) => bool = ;
/** See if the string ends with [suffix].

    {2 Examples}

    {[
      String.endsWith("theory", ~suffix="the") == false
      String.endsWith("theory", ~suffix="ory") == true
    ]}
*/
external endsWith: (string, ~suffix: [@ns.namedArgLoc] string) => bool = ;
/** Check if one string appears within another

    {2 Examples}

    {[
      String.includes("team", ~substring="tea") == true
      String.includes("team", ~substring="i") == false
      String.includes("ABC", ~substring="") == true
    ]}
*/
external includes: (string, ~substring: [@ns.namedArgLoc] string) => bool = ;
/** Test if the first letter of a string is upper case.

    {2 Examples}

    {[
      String.isCapitalized("Anastasia") == true
      String.isCapitalized("") == false
    ]}
*/
external isCapitalized: string => bool = ;
/** Drop [count] characters from the left side of a string.

    {2 Examples}

    {[
      String.dropLeft("abcdefg", ~count=3) == "defg"
      String.dropLeft("abcdefg", ~count=0) == "abcdefg"
      String.dropLeft("abcdefg", ~count=7) == ""
      String.dropLeft("abcdefg", ~count=-2) == "fg"
      String.dropLeft("abcdefg", ~count=8) == ""
    ]}
*/
external dropLeft: (string, ~count: [@ns.namedArgLoc] int) => string = ;
/** Drop [count] characters from the right side of a string.

    {2 Examples}

    {[
      String.dropRight("abcdefg", ~count=3) == "abcd"
      String.dropRight("abcdefg", ~count=0) == "abcdefg"
      String.dropRight("abcdefg", ~count=7) == ""
      String.dropRight("abcdefg", ~count=-2) == "abcdefg"
      String.dropRight("abcdefg", ~count=8) == ""
    ]}
*/
external dropRight: (string, ~count: [@ns.namedArgLoc] int) => string = ;
/** Returns the index of the first occurrence of [string] or None if string has no occurences of [string]

    {2 Examples}

    {[
      String.indexOf("Hello World World", "World") == Some(6)
      String.indexOf("Hello World World", "Bye") == None
    ]}
*/
external indexOf: (string, string) => option(int) = ;
/** Returns the index of the last occurrence of [string] or None if string has no occurences of [string]

    {2 Examples}

    {[
      String.indexOfRight("Hello World World", "World") == Some(12)
      String.indexOfRight("Hello World World", "Bye") == None
    ]}
*/
external indexOfRight: (string, string) => option(int) = ;
/** Insert a string at [index].

    The character previously at index will now follow the inserted string.

    {2 Examples}

    {[
      String.insertAt("abcde", ~value="**", ~index=2) == "ab**cde"
      String.insertAt("abcde", ~value="**", ~index=0) == "**abcde"
      String.insertAt("abcde", ~value="**", ~index=5) == "abcde**"
      String.insertAt("abcde", ~value="**", ~index=-2) == "abc**de"
      String.insertAt("abcde", ~value="**", ~index=-9) == "**abcde"
      String.insertAt("abcde", ~value="**", ~index=9) == "abcde**"
    ]}
*/
external insertAt:
  (string, ~index: [@ns.namedArgLoc] int, ~value: [@ns.namedArgLoc] t) =>
  string =
  ;
/** Converts all upper case letters to lower case.

    {2 Examples}

    {[
      String.toLowercase("AaBbCc123") == "aabbcc123"
    ]}
*/
external toLowercase: string => string = ;
/** Converts all lower case letters to upper case.

    {2 Examples}

    {[
      String.toUppercase("AaBbCc123") == "AABBCC123"
    ]}
*/
external toUppercase: string => string = ;
/** Converts the first letter to lower case if it is upper case.

    {2 Examples}

    {[
      String.uncapitalize("Anastasia") == "anastasia"
    ]}
*/
external uncapitalize: string => string = ;
/** Converts the first letter of [s] to lowercase if it is upper case.

    {2 Examples}

    {[
      String.capitalize("den") == "Den"
    ]}
*/
external capitalize: string => string = ;
/** Removes leading and trailing {{!Char.isWhitespace} whitespace} from a string

    {2 Examples}

    {[
      String.trim("  abc  ") == "abc"
      String.trim("  abc def  ") == "abc def"
      String.trim("
	 abc

") == "abc"
    ]}
*/
external trim: string => string = ;
/** Like {!trim} but only drops characters from the beginning of the string. */
external trimLeft: string => string = ;
/** Like {!trim} but only drops characters from the end of the string. */
external trimRight: string => string = ;
/** Pad a string up to a minimum length.

    If the string is shorted than the proivded length, adds [with_]
    to the left of the string until the minimum length is met.

    {2 Examples}

    {[
      String.padLeft("5", 3, ~with_="0") == "005"
    ]}
*/
external padLeft: (string, int, ~with_: [@ns.namedArgLoc] string) => string = ;
/** Pad a string up to a minimum length.

    If the string is shorted than the proivded length, adds [with_]
    to the left of the string until the minimum length is met.

    {2 Examples}

    {[
      String.padRight("Ahh", 7, ~with_="h") == "Ahhhhhh"
    ]}
*/
external padRight: (string, int, ~with_: [@ns.namedArgLoc] string) => string =
  ;
/** Returns, as an {!Option}, a tuple containing the first {!Char} and the remaining String.

    If given an empty string, returns [None].

    {2 Examples}

    {[
      String.uncons("abcde") == Some('a', "bcde")
      String.uncons("a") == Some('a', "")
      String.uncons("") == None
    ]}
*/
external uncons: string => option((char, string)) = ;
/** Divide a string into a list of strings, splitting whenever [on] is encountered.

    {2 Examples}

    {[
      String.split("a/b/c", ~on="/") == list{"a", "b", "c"}
      String.split("a--b--c", ~on="--") == list{"a", "b", "c"}
      String.split("abc", ~on="/") == list{"abc"}
      String.split("", ~on="/") == list{""}
      String.split("abc", ~on="") == list{"a", "b", "c"}
    ]}
*/
external split: (string, ~on: [@ns.namedArgLoc] string) => list(string) = ;
/** {1 Iterate} */;
/** Run [f] on each character in a string. */
external forEach: (string, ~f: [@ns.namedArgLoc] (char => unit)) => unit = ;
/** Like {!Array.fold} but the elements are {!Char}s  */
external fold:
  (
    string,
    ~initial: [@ns.namedArgLoc] 'a,
    ~f: [@ns.namedArgLoc] (('a, char) => 'a)
  ) =>
  'a =
  ;
/** {1 Convert} */;
/** Returns an {!Array} of the individual characters in the given string.

    {2 Examples}

    {[
      String.toArray("") == []
      String.toArray("abc") == ['a', 'b', 'c']
    ]}
*/
external toArray: string => array(char) = ;
/** Returns a {!List} of the individual characters in the given string.

    {2 Examples}

    {[
      String.toList("") == list{}
      String.toList("abc") == list{'a', 'b', 'c'}
    ]}
*/
external toList: string => list(char) = ;
/** {1 Compare} */;
/** Test two string for equality. */
external equal: (string, string) => bool = ;
/** Compare two strings. Strings use 'dictionary' ordering.
1
    Also known as {{: https://en.wikipedia.org/wiki/Lexicographical_order } lexicographical ordering }.

    {2 Examples}

    {[
      String.compare("Z", "A") == 1
      String.compare("Be", "Bee") == -1
      String.compare("Pear", "pear") == 1
      String.compare("Peach", "Peach") == 0
    ]}
*/
external compare: (string, string) => int = ;
/** The unique identity for {!Comparator} */
type nonrec identity;
external comparator: TableclothComparator.t(t, identity) = ;

/** */;
/** Functions for manipulating pairs of values */;
type nonrec t('a, 'b) = ('a, 'b);
/** {1 Create} */;
/** Create a two-tuple with the given values.

    The values do not have to be of the same type.

    {2 Examples}

    {[
      Tuple2.make(3, "Clementine") == (3, "Clementine")
    ]}
*/
external make: ('a, 'b) => ('a, 'b) = ;
/** Create a tuple from the first two elements of an {!Array}.

    If the array is longer than two elements, the extra elements are ignored.

    If the array is less than two elements, returns [None].

    {2 Examples}

    {[
      Tuple2.fromArray([1, 2]) == Some(1, 2)
      Tuple2.fromArray([1]) == None
      Tuple2.fromArray([4, 5, 6]) == Some(4, 5)
    ]}
*/
external fromArray: array('a) => option(('a, 'a)) = ;
/** Create a tuple from the first two elements of a {!List}.

    If the list is longer than two elements, the extra elements are ignored.

    If the list is less than two elements, returns [None].

    {2 Examples}

    {[
      Tuple2.fromList(list{1, 2}) == Some(1, 2)
      Tuple2.fromList(list{1}) == None
      Tuple2.fromList(list{4, 5, 6}) == Some(4, 5)
    ]}
*/
external fromList: list('a) => option(('a, 'a)) = ;
/** Extract the first value from a tuple.

    {2 Examples}

    {[
      Tuple2.first((3, 4)) == 3
      Tuple2.first(("john", "doe")) == "john"
    ]}
*/
external first: (('a, 'b)) => 'a = ;
/** Extract the second value from a tuple.

    {2 Examples}

    {[
      Tuple2.second((3, 4)) == 4
      Tuple2.second(("john", "doe")) == "doe"
    ]}
*/
external second: (('a, 'b)) => 'b = ;
/** {1 Transform} */;
/** Transform the {!first} value in a tuple.

    {2 Examples}

    {[
      Tuple2.mapFirst(("stressed", 16), ~f=String.reverse) == ("desserts", 16)
      Tuple2.mapFirst(("stressed", 16), ~f=String.length) == (8, 16)
    ]}
*/
external mapFirst: (('a, 'b), ~f: [@ns.namedArgLoc] ('a => 'x)) => ('x, 'b) =
  ;
/** Transform the second value in a tuple.

    {2 Examples}

    {[
      Tuple2.mapSecond(("stressed", 16.), ~f=Float.squareRoot) == ("stressed", 4.)
      Tuple2.mapSecond(~f=Int.negate, ("stressed", 16)) == ("stressed", -16)
    ]}
*/
external mapSecond: (('a, 'b), ~f: [@ns.namedArgLoc] ('b => 'c)) => ('a, 'c) =
  ;
/** Transform both values of a tuple, using [f] for the first value and [g] for the second.

    {2 Examples}

    {[
      Tuple2.mapEach(("stressed", 16.), ~f=String.reverse, ~g=Float.squareRoot) == ("desserts", 4.)
      Tuple2.mapEach(~f=String.length, ~g=Int.negate, ("stressed", 16)) == (8, -16)
    ]}
*/
external mapEach:
  (
    ('a, 'b),
    ~f: [@ns.namedArgLoc] ('a => 'x),
    ~g: [@ns.namedArgLoc] ('b => 'y)
  ) =>
  ('x, 'y) =
  ;
/** Transform both of the values of a tuple using the same function.

    [mapAll] can only be used on tuples which have the same type for each value.

    {2 Examples}

    {[
      Tuple2.mapAll(~f=Int.add(1), (3, 4)) == (4, 5)
      Tuple2.mapAll(("was", "stressed"), ~f=String.length) == (3, 8)
    ]}
*/
external mapAll: (('a, 'a), ~f: [@ns.namedArgLoc] ('a => 'b)) => ('b, 'b) = ;
/** Switches the first and second values of a tuple.

    {2 Examples}

    {[
      Tuple2.swap((3, 4)) == (4, 3)
      Tuple2.swap(("stressed", 16)) == (16, "stressed")
    ]}
*/
external swap: (('a, 'b)) => ('b, 'a) = ;
/** {1 Convert} */;
/** Turns a tuple into an {!Array} of length two.

    This function can only be used on tuples which have the same type for each value.

    {2 Examples}

    {[
      Tuple2.toArray((3, 4)) == [3, 4]
      Tuple2.toArray(("was", "stressed")) == ["was", "stressed"]
    ]}
*/
external toArray: (('a, 'a)) => array('a) = ;
/** Turns a tuple into a list of length two. This function can only be used on tuples which have the same type for each value.

    {2 Examples}

    {[
      Tuple2.toList((3, 4)) == list{3, 4}
      Tuple2.toList(("was", "stressed")) == list{"was", "stressed"}
    ]}
*/
external toList: (('a, 'a)) => list('a) = ;
/** Test two {!Tuple2}s for equality, using the provided functions to test the
    first and second components.

    {2 Examples}

    {[
      Tuple2.equal((1, "Fox"), (1, "Fox"), Int.equal, String.equal) == true
      Tuple2.equal((1, "Fox"), (2, "Hen"), Int.equal, String.equal) == false
    ]}
*/
external equal:
  (t('a, 'b), t('a, 'b), ('a, 'a) => bool, ('b, 'b) => bool) => bool =
  ;
/** Compare two {!Tuple2}s, using the provided [f] function to compare the first components.
    Then, if the first components are equal, the second components are compared with [g].

    {2 Examples}

    {[
      Tuple2.compare((1, "Fox"), (1, "Fox"), ~f=Int.compare, ~g=String.compare) == 0
      Tuple2.compare((1, "Fox"), (1, "Eel"), ~f=Int.compare, ~g=String.compare) == 1
      Tuple2.compare((1, "Fox"), (2, "Hen"), ~f=Int.compare, ~g=String.compare) == -1
    ]}
*/
external compare:
  (
    t('a, 'b),
    t('a, 'b),
    ~f: [@ns.namedArgLoc] (('a, 'a) => int),
    ~g: [@ns.namedArgLoc] (('b, 'b) => int)
  ) =>
  int =
  ;

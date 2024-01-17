/** */;
/** A {!Set} represents a collection of unique values.

    [Set] is an immutable data structure which means operations like {!Set.add} and {!Set.remove} do not modify the data structure, but return a new set with the desired changes.

    Since sets of [int]s and [string]s are so common the specialised {!Set.Int} and {!Set.String} modules are available which offer a convenient way to construct new sets.

    Custom data types can be used with sets as long as the module satisfies the {!Comparator.S} interface.

    {[
      module Point = {
        type rec t = (int, int)
        let compare = Tuple2.compare(~f=Int.compare, ~g=Int.compare)
        include Comparator.Make({
          type t = t
          let compare = compare
        })
      }

      let points = Set.fromArray(module(Point), [(0, 0), (3, 4), (6, 7)])
    ]}

    See the {!Comparator} module for a more details.
*/;
type nonrec t('a, 'id) = Belt.Set.t('a, 'id);
/** {1 Create}

  You can create a Set by providing a module conform to the {!Comparator.S} signature by using {!empty}, {!singleton}, {!fromList} or {!fromArray}.

  Specialised versions of the {!empty}, {!singleton}, {!fromList} and {!fromArray} functions available in the {!Set.Int} and {!Set.String} sub-modules.
*/;
/** A set with nothing in it.

    Often used as an initial value for functions like {!Array.fold}

    {2 Examples}

    {[
      Array.fold(
        ['m', 'i', 's', 's', 'i', 's', 's', 'i', 'p', 'p', 'i'],
        ~initial=Set.empty(module(Char)),
        ~f=Set.add,
      )->Set.toArray
      == ['i', 'm', 'p', 's']
    ]}
*/
external empty: TableclothComparator.s('a, 'identity) => t('a, 'identity);
/** Create a set from a single {!Int}.

  {2 Examples}

  {[
      Set.singleton(7, module(Int)) |> Set.toArray == [7]
    ]}
*/
external singleton:
  ('a, TableclothComparator.s('a, 'identity)) => t('a, 'identity)
  ;
/** Create a set from an {!Array}.

    {2 Examples}

    {[
      Set.fromArray(["Ant", "Bat", "Bat", "Goldfish"], module(String))->Set.toArray
       == ["Ant", "Bat", "Goldfish"]
    ]}
*/
external fromArray:
  (array('a), TableclothComparator.s('a, 'identity)) => t('a, 'identity)
  ;
/** Create a set from a {!List}.

    {2 Examples}

    {[
      Set.fromList(list{'A', 'B', 'B', 'G'}, module(Char))->Set.toArray == ['A', 'B', 'G']
    ]}
*/
external fromList:
  (list('a), TableclothComparator.s('a, 'identity)) => t('a, 'identity)
  ;
/** {1 Basic operations} */;
/** Insert a value into a set.

    {2 Examples}

    {[
      Set.add(Set.Int.fromArray([1, 2]), 3) -> Set.toArray == [1, 2, 3]
      Set.add(Set.Int.fromArray([1, 2]), 2) -> Set.toArray == [1, 2]
    ]}
*/
external add: (t('a, 'id), 'a) => t('a, 'id);
/** Remove a value from a set, if the set doesn't contain the value anyway, returns the original set.

    {2 Examples}

    {[
      Set.remove(Set.Int.fromArray([1, 2]), 2)->Set.toArray == [1]

     let originalSet = Set.Int.fromArray([1, 2])
      let newSet = Set.remove(originalSet, 3)
      originalSet == newSet
    ]}
*/
external remove: (t('a, 'id), 'a) => t('a, 'id);
/** Determine if a value is in a set.

    {2 Examples}

   {[
      Set.includes(Set.String.fromArray(["Ant", "Bat", "Cat"]), "Bat") == true
    ]}
*/
external includes: (t('a, _), 'a) => bool;
/** Determine the number of elements in a set.

    {2 Examples}

    {[
      Set.length(Set.Int.fromArray([1, 2, 3])) == 3
    ]}
*/
external length: t(_, _) => int;
/** Returns, as an {!Option}, the first element for which [f] evaluates to [true].
    If [f] doesn't return [true] for any of the elements [find] will return [None].

    {2 Examples}

    {[
      Set.find(Set.Int.fromArray([1, 3, 4, 8]), ~f=Int.isEven) == Some(4)
      Set.find(Set.Int.fromArray([0, 2, 4, 8]), ~f=Int.isOdd) == None
      Set.find(Set.Int.empty, ~f=Int.isEven) == None
    ]}
*/
external find:
  (t('value, _), ~f: [@ns.namedArgLoc] ('value => bool)) => option('value)
  ;
/** {1 Query} */;
/** Check if a set is empty.

    {2 Examples}

    {[
      Set.isEmpty(Set.Int.empty) == true
      Set.isEmpty(Set.Int.singleton(4)) == false
    ]}
*/
external isEmpty: t(_, _) => bool;
/** Determine if [f] returns true for [any] values in a set.

    {2 Examples}

    {[
      Set.any(Set.Int.fromArray([2, 3]), ~f=Int.isEven) == true
      Set.any(Set.Int.fromArray([1, 3]), ~f=Int.isEven) == false
      Set.any(Set.Int.fromArray([]), ~f=Int.isEven) == false
    ]}
*/
external any: (t('value, _), ~f: [@ns.namedArgLoc] ('value => bool)) => bool
  ;
/** Determine if [f] returns true for [all] values in a set.

    {2 Examples}

    {[
      Set.all(Set.Int.fromArray([2, 4]), ~f=Int.isEven) == true
      Set.all(Set.Int.fromArray([2, 3]), ~f=Int.isEven) == false
      Set.all(Set.Int.empty, ~f=Int.isEven) == true
    ]}
*/
external all: (t('value, _), ~f: [@ns.namedArgLoc] ('value => bool)) => bool
  ;
/** {1 Combine} */;
/** Returns a new set with the values from the first set which are not in the second set.

    {2 Examples}

    {[
      Set.difference(
        Set.Int.fromArray([1, 2, 5]),
        Set.Int.fromArray([2, 3, 4])
      )->Set.toArray == [1, 5]

      Set.difference(
        Set.Int.fromArray([2, 3, 4]),
        Set.Int.fromArray([1, 2, 5])
      )->Set.toArray == [3, 4]
    ]}
*/
external difference: (t('a, 'id), t('a, 'id)) => t('a, 'id);
/** Get the intersection of two sets. Keeps values that appear in both sets.

    {2 Examples}

    {[
      Set.intersection(
        Set.Int.fromArray([1, 2, 5]),
        Set.Int.fromArray([2, 3, 4])
      )->Set.toArray == [2]
    ]}
*/
external intersection: (t('a, 'id), t('a, 'id)) => t('a, 'id);
/** Get the union of two sets. Keep all values.

    {2 Examples}

    {[
      Set.union(
        Set.Int.fromArray([1, 2, 5]),
        Set.Int.fromArray([2, 3, 4])
      )->Set.toArray == [1, 2, 3, 4, 5]
    ]}
*/
external union: (t('a, 'id), t('a, 'id)) => t('a, 'id);
/** {1 Transform} */;
/** Keep elements that [f] returns [true] for.

    {2 Examples}

    {[
      Set.filter(Set.Int.fromArray([1, 2, 3]), ~f=Int.isEven)->Set.toArray == [2]
    ]}
*/
external filter:
  (t('a, 'id), ~f: [@ns.namedArgLoc] ('a => bool)) => t('a, 'id)
  ;
/** Divide a set into two according to [f]. The first set will contain the values
    that [f] returns [true] for, values that [f] returns [false] for will end up in the second.

    {2 Examples}

    {[
      let numbers = Set.Int.fromArray([1, 1, 5, 6, 5, 7, 9, 8])
      let (evens, odds) = Set.partition(numbers, ~f=Int.isEven)
      Set.toArray(evens) == [6, 8]
      Set.toArray(odds) == [1, 5, 7, 9]
    ]}
*/
external partition:
  (t('a, 'id), ~f: [@ns.namedArgLoc] ('a => bool)) =>
  (t('a, 'id), t('a, 'id))
  ;
/** Transform a set into a value which is result of running each element in the set through [f],
    where each successive invocation is supplied the return value of the previous.

  See {!Array.fold} for a more in-depth explanation.

  {2 Examples}

  {[
      Set.fold(Set.Int.fromArray([1, 2, 3, 4], ~initial=1, ~f=Int.multiply)) == 24
    ]}
*/
external fold:
  (
    t('a, _),
    ~initial: [@ns.namedArgLoc] 'b,
    ~f: [@ns.namedArgLoc] (('b, 'a) => 'b)
  ) =>
  'b
  ;
/** Runs a function [f] against each element of the set. */
external forEach: (t('a, _), ~f: [@ns.namedArgLoc] ('a => unit)) => unit;
/** {1 Convert} */;
/** Converts a set into an {!Array} */
external toArray: t('a, _) => array('a);
/** Converts a set into a {!List}. */
external toList: t('a, _) => list('a);
/** Construct sets which can hold any data type using the polymorphic [compare] function. */
module Poly: {
  type identity;

  type t('a) = t('a, identity);

  /** The empty set.

      A great starting point.
   */
  let empty: unit => t('a);

  /** Create a set of a single value

      {2 Examples}

      {[
      Set.Poly.singleton((5, "Emu"))->Set.toArray == [(5, "Emu")]
    ]}
  */
  let singleton: 'a => t('a);

  /** Create a set from an {!Array}

      {2 Examples}

      {[
        Set.Poly.fromArray([(1, "Ant"), (2, "Bat"), (2, "Bat")])->Set.toArray
        == [(1, "Ant"), (2, "Bat")]
      ]}
  */
  let fromArray: array('a) => t('a);

  /** Create a set from a {!List}

    {2 Examples}

    {[
      Set.Poly.fromList(list{(1, "Ant"), (2, "Bat"), (2, "Bat")})->Set.toArray
      == [(1, "Ant"), (2, "Bat")]
    ]}
  */
  let fromList: list('a) => t('a);
}
/** Construct sets of {!Int}s */
module Int: {
  type identity;

  type t = t(TableclothInt.t, identity);

  /** A set with nothing in it. */
  external empty: t;

  /** Create a set from a single {!Int}

    {2 Examples}

    {[
      Set.Int.singleton(5)->Set.toArray == [5]
    ]}
  */
  external singleton: int => t;

  /** Create a set from an {!Array}

      {2 Examples}

      {[
      Set.Int.fromArray([1, 2, 3, 3, 2, 1, 7])->Set.toArray == [1, 2, 3, 7]
    ]}
  */
  external fromArray: array(int) => t;

  /** Create a set from a {!List}

      {2 Examples}

      {[
      Set.Int.fromList(list{1, 2, 3, 3, 2, 1, 7})->Set.toArray == [1, 2, 3, 7]
    ]}
  */
  external fromList: list(int) => t;
}
/** Construct sets of {!String}s */
module String: {
  type identity;

  type t = t(TableclothString.t, identity);

  /** A set with nothing in it. */
  external empty: t;

  /** Create a set of a single {!String}.

      {2 Examples}

      {[
      Set.String.singleton("Bat")->Set.toArray == ["Bat"]
    ]}
  */
  external singleton: string => t;

  /** Create a set from an {!Array}.

      {2 Examples}

      {[
      Set.String.fromArray(["a", "b", "g", "b", "g", "a", "a"])->Set.toArray == ["a", "b", "g"]
    ]}
  */
  external fromArray: array(string) => t;

  /** Create a set from a {!List}.

      {2 Examples}

      {[
      Set.String.fromList(["a", "b", "g", "b", "g", "a", "a"])->Set.toArray == ["a", "b", "g"]
    ]}
  */
  external fromList: list(string) => t;
}

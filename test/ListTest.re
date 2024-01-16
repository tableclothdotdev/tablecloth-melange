open Tablecloth;
open Jest;
open Expect;
open List;
describe("empty", () =>
  test("returns int 0 for empty list arg", () =>
    expect(List.length(List.empty))->(toEqual(0))
  )
);
describe("singleton", () => {
  [@ns.braces]
  {
    test("returns array singleton of empty string from arg empty string", () =>
      List.singleton("")->expect->(toEqual([""]))
    );
    test("returns array singleton of int arg", () =>
      expect(List.singleton(1234))->(toEqual([1234]))
    );
    test("returns array singleton of string arg", () =>
      expect(List.singleton("hello"))->(toEqual(["hello"]))
    );
  }
});
describe("repeat", () => {
  [@ns.braces]
  {
    test("returns empty list from repeat arg 0", () =>
      expect(List.repeat(~times=[@ns.namedArgLoc] 0, 7))->(toEqual([]))
    );
    test("returns empty list from negative repeat arg -10", () =>
      expect(List.repeat(~times=[@ns.namedArgLoc] -10, 7))->(toEqual([]))
    );
    test("returns list of char 'a' repeated 5 times", () =>
      expect(List.repeat(~times=[@ns.namedArgLoc] 5, 'a'))
      ->(toEqual(['a', 'a', 'a', 'a', 'a']))
    );
  }
});
describe("range", () => {
  [@ns.braces]
  {
    test("returns empty when is zero", () =>
      expect(List.range(0))->(toEqual([]))
    );
    test("with single", () =>
      expect(List.range(5))->(toEqual([0, 1, 2, 3, 4]))
    );
    test("with to and from", () =>
      expect(List.range(~from=[@ns.namedArgLoc] 2, 5))->(toEqual([2, 3, 4]))
    );
    test("with negative", () =>
      expect(List.range(~from=[@ns.namedArgLoc] -2, 2))
      ->(toEqual([(-2), (-1), 0, 1]))
    );
    test("returns empty with count down", () =>
      expect(List.range(~from=[@ns.namedArgLoc] 5, 2))->(toEqual([]))
    );
  }
});
describe("initalize", () => {
  [@ns.braces]
  {
    test("with identity", () =>
      expect(List.initialize(4, ~f=[@ns.namedArgLoc] index => index))
      ->(toEqual([0, 1, 2, 3]))
    );
    test("with math", () =>
      expect(List.initialize(4, ~f=[@ns.namedArgLoc] index => index * index))
      ->(toEqual([0, 1, 4, 9]))
    );
  }
});
describe("fromArray", () => {
  [@ns.braces]
  {
    test("from empty", () =>
      expect(List.fromArray([||]))->(toEqual([]))
    );
    test("from string", () =>
      expect(List.fromArray([|'h', 'e', 'l', 'l', 'o'|]))
      ->(toEqual(['h', 'e', 'l', 'l', 'o']))
    );
    test("with int", () =>
      expect(List.fromArray([|(-1), 3, 2, 7|]))->(toEqual([(-1), 3, 2, 7]))
    );
  }
});
describe("head", () => {
  [@ns.braces]
  {
    test("from empty", () =>
      expect(List.head([]))->(toEqual(None))
    );
    test("with int", () =>
      expect(List.head([(-3), 2, 3, 4, 6]))->(toEqual(Some(-3)))
    );
  }
});
describe("cons", () => {
  [@ns.braces]
  {
    test("from empty", () =>
      expect(List.cons([], 1))->(toEqual([1]))
    );
    test("with int", () =>
      expect(List.cons([2, 3, 4], 1))->(toEqual([1, 2, 3, 4]))
    );
  }
});
describe("filterMap", () =>
  test("keeps elements which return Some", () =>
    expect(
      List.filterMap([(-1), 80, 99], ~f=[@ns.namedArgLoc] Char.fromCode),
    )
    ->(toEqual(['P', 'c']))
  )
);
describe("filterWithIndex", () => {
  [@ns.braces]
  {
    test("returns elements if index is greater than 1", () =>
      expect(
        filterWithIndex([2, 99, 0, 3], ~f=[@ns.namedArgLoc] (i, _) => i > 1),
      )
      ->(toEqual([0, 3]))
    );
    test("empty list", () =>
      expect(filterWithIndex([], ~f=[@ns.namedArgLoc] (i, _) => i > 1))
      ->(toEqual([]))
    );
  }
});
describe("drop", () => {
  [@ns.braces]
  {
    test("from an empty list", () =>
      expect(drop([], ~count=[@ns.namedArgLoc] 1))->(toEqual([]))
    );
    test("zero elements", () =>
      expect(drop([1, 2, 3], ~count=[@ns.namedArgLoc] 0))
      ->(toEqual([1, 2, 3]))
    );
    test("the first element", () =>
      expect(drop([1, 2, 3], ~count=[@ns.namedArgLoc] 1))
      ->(toEqual([2, 3]))
    );
    test("all elements", () =>
      expect(drop([1, 2, 3], ~count=[@ns.namedArgLoc] 3))->(toEqual([]))
    );
    test("greater than the number of elements", () =>
      expect(drop([1, 2, 3], ~count=[@ns.namedArgLoc] 4))->(toEqual([]))
    );
    test("negative count", () =>
      expect(drop([1, 2, 3], ~count=[@ns.namedArgLoc] -1))
      ->(toEqual([1, 2, 3]))
    );
    test("zero count", () =>
      expect(drop([1, 2, 3], ~count=[@ns.namedArgLoc] -1))
      ->(toEqual([1, 2, 3]))
    );
  }
});
describe("filter", () => {
  [@ns.braces]
  {
    test("normal", () =>
      expect(filter(~f=[@ns.namedArgLoc] Int.isEven, [2, 4, 6, 7, 8, 9]))
      ->(toEqual([2, 4, 6, 8]))
    );
    test("filter none", () =>
      expect(filter(~f=[@ns.namedArgLoc] Int.isEven, [5, 7, 9]))
      ->(toEqual([]))
    );
    test("filter all", () =>
      expect(filter(~f=[@ns.namedArgLoc] Int.isEven, [2, 4, 6]))
      ->(toEqual([2, 4, 6]))
    );
  }
});
describe("dropWhile", () => {
  [@ns.braces]
  {
    test("drops item from list if isEven, returns list of only odd items", () =>
      expect(dropWhile(~f=[@ns.namedArgLoc] Int.isEven, [2, 4, 6, 7, 8, 9]))
      ->(toEqual([7, 8, 9]))
    );
    test(
      "drops none despite items dispersed throughout list because first item returns false for isEven, returns list without changes",
      () =>
      expect(dropWhile(~f=[@ns.namedArgLoc] Int.isEven, [3, 4, 7, 8, 9]))
      ->(toEqual([3, 4, 7, 8, 9]))
    );
    test("drops all because all items are even, returns empty list", () =>
      expect(dropWhile(~f=[@ns.namedArgLoc] Int.isEven, [2, 4, 6, 8]))
      ->(toEqual([]))
    );
    test(
      "drops none because all items are odd, returns list without changes", () =>
      expect(dropWhile(~f=[@ns.namedArgLoc] Int.isEven, [1, 3, 5, 7]))
      ->(toEqual([1, 3, 5, 7]))
    );
  }
});
describe("take", () => {
  [@ns.braces]
  {
    test("normal", () =>
      expect(take([1, 2, 3], ~count=[@ns.namedArgLoc] 2))
      ->(toEqual([1, 2]))
    );
    test("from an empty list", () =>
      expect(take([], ~count=[@ns.namedArgLoc] 2))->(toEqual([]))
    );
    test("overflow", () =>
      expect(take([1, 2, 3, 4], ~count=[@ns.namedArgLoc] 8))
      ->(toEqual([1, 2, 3, 4]))
    );
    test("overflow", () =>
      expect(take([1, 2, 3, 4], ~count=[@ns.namedArgLoc] -1))
      ->(toEqual([]))
    );
  }
});
describe("takeWhile", () => {
  [@ns.braces]
  {
    test(
      "takes items until isEven returns false, returns list of items until first odd item",
      () =>
      expect(takeWhile(~f=[@ns.namedArgLoc] Int.isEven, [2, 4, 6, 7, 8, 9]))
      ->(toEqual([2, 4, 6]))
    );
    test(
      "takes items in list of dispersed items until isEven returns false, returns list of items until first odd item",
      () =>
      expect(
        takeWhile(~f=[@ns.namedArgLoc] Int.isEven, [2, 6, 7, 15, 10, 9, 8]),
      )
      ->(toEqual([2, 6]))
    );
    test(
      "takes no items as first item returns false to isEven, returns empty list",
      () =>
      expect(
        takeWhile(~f=[@ns.namedArgLoc] Int.isEven, [1, 6, 7, 15, 10, 9, 8]),
      )
      ->(toEqual([]))
    );
    test(
      "takes all items as all items return true to isEven, returns list without changes",
      () =>
      expect(takeWhile(~f=[@ns.namedArgLoc] Int.isEven, [2, 4, 6]))
      ->(toEqual([2, 4, 6]))
    );
    test("returns empty list from arg empty list", () =>
      expect(takeWhile(~f=[@ns.namedArgLoc] Int.isEven, []))->(toEqual([]))
    );
    test(
      "takes no items as all items return false to isEven, returns empty list",
      () =>
      expect(takeWhile(~f=[@ns.namedArgLoc] Int.isEven, [1, 3, 5]))
      ->(toEqual([]))
    );
  }
});
describe("findIndex", () => {
  [@ns.braces]
  {
    test(
      "returns the first (index, element) tuple which f returns true for", () =>
      expect(
        findIndex(
          ~f=
            [@ns.namedArgLoc] (index, number) =>
              index > 2 && Int.isEven(number),
          [1, 3, 4, 8],
        ),
      )
      ->(toEqual(Some((3, 8))))
    );
    test("returns `None` if `f` returns false for all elements ", () =>
      expect(findIndex(~f=[@ns.namedArgLoc] (_, _) => false, [0, 2, 4, 8]))
      ->(toEqual(None))
    );
    test("returns `None` for an empty array", () =>
      expect(
        findIndex(
          ~f=
            [@ns.namedArgLoc] (index, number) =>
              index > 2 && Int.isEven(number),
          [],
        ),
      )
      ->(toEqual(None))
    );
  }
});
describe("includes", () => {
  [@ns.braces]
  {
    test("includes int", () =>
      expect(includes([1, 3, 5, 7], 3, ~equal=[@ns.namedArgLoc] Int.equal))
      ->(toEqual(true))
    );
    test("does not includes int", () =>
      expect(includes([1, 3, 5, 7], 4, ~equal=[@ns.namedArgLoc] Int.equal))
      ->(toEqual(false))
    );
    test("empty list", () =>
      expect(includes([], 5, ~equal=[@ns.namedArgLoc] Int.equal))
      ->(toEqual(false))
    );
  }
});
describe("reverse", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(reverse([]))->(toEqual([]))
    );
    test("one element", () =>
      expect(reverse([0]))->(toEqual([0]))
    );
    test("two elements", () =>
      expect(reverse([0, 1]))->(toEqual([1, 0]))
    );
  }
});
describe("map2", () => {
  [@ns.braces]
  {
    test("map2 empty lists", () =>
      expect(map2(~f=[@ns.namedArgLoc] (+), [], []))->(toEqual([]))
    );
    test("map2 one element", () =>
      expect(map2(~f=[@ns.namedArgLoc] (+), [1], [1]))->(toEqual([2]))
    );
    test("map2 two elements", () =>
      expect(map2(~f=[@ns.namedArgLoc] (+), [1, 2], [1, 2]))
      ->(toEqual([2, 4]))
    );
    test("map2 with lists of different lengths", () =>
      expect(map2(~f=[@ns.namedArgLoc] (+), [1, 2, 3], [1, 2]))
      ->(toEqual([2, 4]))
    );
  }
});
describe("map3", () => {
  [@ns.braces]
  {
    test("map3 empty lists", () =>
      expect(map3(~f=[@ns.namedArgLoc] (x, y, z) => x + y + z, [], [], []))
      ->(toEqual([]))
    );
    test("map3 one element", () =>
      expect(
        map3(~f=[@ns.namedArgLoc] (x, y, z) => x + y + z, [1], [1], [1]),
      )
      ->(toEqual([3]))
    );
    test("map3 two elements", () =>
      expect(
        map3(
          ~f=[@ns.namedArgLoc] (x, y, z) => x + y + z,
          [1, 2],
          [1, 2],
          [1, 2],
        ),
      )
      ->(toEqual([3, 6]))
    );
    test("map3 elements on lists of different lengths", () =>
      expect(
        map3(
          ~f=[@ns.namedArgLoc] (x, y, z) => x + y + z,
          [1, 2, 3],
          [1, 2, 3],
          [1, 2],
        ),
      )
      ->(toEqual([3, 6]))
    );
  }
});
describe("mapWithIndex", () => {
  [@ns.braces]
  {
    test("on an empty list", () =>
      expect(mapWithIndex(~f=[@ns.namedArgLoc] (i, _) => i, []))
      ->(toEqual([]))
    );
    test("with a single element", () =>
      expect(mapWithIndex(~f=[@ns.namedArgLoc] (i, _) => i, ['a']))
      ->(toEqual([0]))
    );
    test("with two elements", () =>
      expect(mapWithIndex(~f=[@ns.namedArgLoc] (i, _) => i, ['a', 'b']))
      ->(toEqual([0, 1]))
    );
  }
});
describe("flatMap", () => {
  [@ns.braces]
  {
    test("normal", () =>
      expect(flatMap(~f=[@ns.namedArgLoc] x => [x, x], [1, 2, 3]))
      ->(toEqual([1, 1, 2, 2, 3, 3]))
    );
    test("on an empty list", () =>
      expect(flatMap(~f=[@ns.namedArgLoc] x => [x, x], []))->(toEqual([]))
    );
    test("deeper list", () =>
      expect(
        flatMap(
          ~f=[@ns.namedArgLoc] x => append(x, [1]),
          [[1, 1], [2], [3]],
        ),
      )
      ->(toEqual([1, 1, 1, 2, 1, 3, 1]))
    );
  }
});
describe("sliding", () => {
  [@ns.braces]
  {
    test("size 1", () =>
      expect(sliding([1, 2, 3, 4, 5], ~size=[@ns.namedArgLoc] 1))
      ->(toEqual([[1], [2], [3], [4], [5]]))
    );
    test("size 2", () =>
      expect(sliding([1, 2, 3, 4, 5], ~size=[@ns.namedArgLoc] 2))
      ->(toEqual([[1, 2], [2, 3], [3, 4], [4, 5]]))
    );
    test("step 3 ", () =>
      expect(sliding([1, 2, 3, 4, 5], ~size=[@ns.namedArgLoc] 3))
      ->(toEqual([[1, 2, 3], [2, 3, 4], [3, 4, 5]]))
    );
    test("size 2, step 2", () =>
      expect(
        sliding(
          [1, 2, 3, 4, 5],
          ~size=[@ns.namedArgLoc] 2,
          ~step=[@ns.namedArgLoc] 2,
        ),
      )
      ->(toEqual([[1, 2], [3, 4]]))
    );
    test("size 1, step 3", () =>
      expect(
        sliding(
          [1, 2, 3, 4, 5],
          ~size=[@ns.namedArgLoc] 1,
          ~step=[@ns.namedArgLoc] 3,
        ),
      )
      ->(toEqual([[1], [4]]))
    );
    test("size 2, step 3", () =>
      expect(
        sliding(
          [1, 2, 3, 4, 5],
          ~size=[@ns.namedArgLoc] 2,
          ~step=[@ns.namedArgLoc] 3,
        ),
      )
      ->(toEqual([[1, 2], [4, 5]]))
    );
    test("step 7", () =>
      expect(sliding([1, 2, 3, 4, 5], ~size=[@ns.namedArgLoc] 7))
      ->(toEqual([]))
    );
  }
});
describe("groupWhile", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(groupWhile(~f=[@ns.namedArgLoc] String.equal, []))
      ->(toEqual([]))
    );
    test("normal char", () =>
      expect(
        groupWhile(
          ~f=[@ns.namedArgLoc] (!=),
          ["a", "b", "b", "a", "a", "a", "b", "a"],
        ),
      )
      ->(toEqual([["a"], ["b", "b"], ["a", "a", "a"], ["b"], ["a"]]))
    );
    test("normal int", () =>
      expect(
        groupWhile(
          ~f=[@ns.namedArgLoc] (x, y) => x mod 2 !== y mod 2,
          [2, 4, 6, 5, 3, 1, 8, 7, 9],
        ),
      )
      ->(toEqual([[2, 4, 6], [5, 3, 1], [8], [7, 9]]))
    );
  }
});
describe("join", () => {
  [@ns.braces]
  {
    test("normal", () =>
      expect(join(["Ant", "Bat", "Cat"], ~sep=[@ns.namedArgLoc] ", "))
      ->(toEqual("Ant, Bat, Cat"))
    );
    test("empty list", () =>
      expect(join([], ~sep=[@ns.namedArgLoc] ", "))->(toEqual(""))
    );
  }
});
describe("partition", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(partition(~f=[@ns.namedArgLoc] Int.isEven, []))
      ->(toEqual(([], [])))
    );
    test("one element", () =>
      expect(partition(~f=[@ns.namedArgLoc] Int.isEven, [1]))
      ->(toEqual(([], [1])))
    );
    test("four elements", () =>
      expect(partition(~f=[@ns.namedArgLoc] Int.isEven, [1, 2, 3, 4]))
      ->(toEqual(([2, 4], [1, 3])))
    );
  }
});
describe("sort", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(sort(~compare=[@ns.namedArgLoc] Int.compare, []))
      ->(toEqual([]))
    );
    test("one element", () =>
      expect(sort(~compare=[@ns.namedArgLoc] Int.compare, [5]))
      ->(toEqual([5]))
    );
    test("multiple elements", () =>
      expect(sort(~compare=[@ns.namedArgLoc] Int.compare, [5, 6, 8, 3, 6]))
      ->(toEqual([3, 5, 6, 6, 8]))
    );
    test("with negative", () =>
      expect(
        sort(~compare=[@ns.namedArgLoc] Int.compare, [5, 6, (-8), 3, 6]),
      )
      ->(toEqual([(-8), 3, 5, 6, 6]))
    );
  }
});
describe("sortBy", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(sortBy(~f=[@ns.namedArgLoc] x => x, []))->(toEqual([]))
    );
    test("one element", () =>
      expect(sortBy(~f=[@ns.namedArgLoc] x => x, [5]))->(toEqual([5]))
    );
    test("sort records", () =>
      [@ns.braces]
      {
        let s1 = {JestStubs.Student.id: 200, JestStubs.Student.name: "Syd"};
        let s2 = {JestStubs.Student.id: 53, JestStubs.Student.name: "Bill"};
        let s3 = {JestStubs.Student.id: 30, JestStubs.Student.name: "Carmen"};
        let studentList = [s1, s2, s3];
        let sortedRecs =
          sortBy(
            ~f=[@ns.namedArgLoc] x => x.JestStubs.Student.id,
            studentList,
          );
        expect(sortedRecs)->(toEqual([s3, s2, s1]));
      }
    );
    test("empty list", () =>
      expect(sortBy(~f=[@ns.namedArgLoc] x => x * x, [3, 2, 5, (-2), 4]))
      ->(toEqual([2, (-2), 3, 4, 5]))
    );
  }
});
describe("uniqueBy", () => {
  [@ns.braces]
  {
    test("int self", () =>
      expect(
        uniqueBy(
          ~f=[@ns.namedArgLoc] element => string_of_int(element),
          [1, 3, 4, 3, 7, 7, 6],
        ),
      )
      ->(toEqual([1, 3, 4, 7, 6]))
    );
    test("math", () =>
      expect(
        uniqueBy(
          ~f=[@ns.namedArgLoc] element => string_of_int(5 mod element),
          [1, 3, 4, 3, 7, 7, 6],
        ),
      )
      ->(toEqual([1, 3, 4, 7]))
    );
    test("string self", () =>
      expect(
        uniqueBy(
          ~f=[@ns.namedArgLoc] element => element,
          ["hello", "h", "e", "hello", "l", "l", "o"],
        ),
      )
      ->(toEqual(["hello", "h", "e", "l", "o"]))
    );
  }
});
describe("minimumBy", () => {
  [@ns.braces]
  {
    test("minimumBy non-empty list", () =>
      expect(
        List.minimumBy(
          ~f=[@ns.namedArgLoc] x => x mod 12,
          [7, 9, 15, 10, 3, 22],
        ),
      )
      ->(toEqual(Some(15)))
    );
    test("minimumBy empty list", () =>
      expect(List.minimumBy(~f=[@ns.namedArgLoc] x => x mod 12, []))
      ->(toEqual(None))
    );
  }
});
describe("maximumBy", () => {
  [@ns.braces]
  {
    test("maximumBy non-empty list", () =>
      expect(
        List.maximumBy(
          ~f=[@ns.namedArgLoc] x => x mod 12,
          [7, 9, 15, 10, 3, 22],
        ),
      )
      ->(toEqual(Some(10)))
    );
    test("maximumBy empty list", () =>
      expect(List.maximumBy(~f=[@ns.namedArgLoc] x => x mod 12, []))
      ->(toEqual(None))
    );
  }
});
describe("minimum", () => {
  [@ns.braces]
  {
    test("minimum non-empty list", () =>
      expect(
        minimum([7, 9, 15, 10, 3], ~compare=[@ns.namedArgLoc] Int.compare),
      )
      ->(toEqual(Some(3)))
    );
    test("minimum empty list", () =>
      expect(minimum([], ~compare=[@ns.namedArgLoc] Int.compare))
      ->(toEqual(None))
    );
  }
});
describe("maximum", () => {
  [@ns.braces]
  {
    test("maximum non-empty list", () =>
      expect(
        maximum([7, 9, 15, 10, 3], ~compare=[@ns.namedArgLoc] Int.compare),
      )
      ->(toEqual(Some(15)))
    );
    test("maximum empty list", () =>
      expect(maximum([], ~compare=[@ns.namedArgLoc] Int.compare))
      ->(toEqual(None))
    );
  }
});
describe("extent", () => {
  [@ns.braces]
  {
    test("return tuple of min and max", () =>
      expect(extent([7, 5, 8, 6], ~compare=[@ns.namedArgLoc] Int.compare))
      ->(toEqual(Some((5, 8))))
    );
    test("return tuple of min and max from single element list", () =>
      expect(extent([5], ~compare=[@ns.namedArgLoc] Int.compare))
      ->(toEqual(Some((5, 5))))
    );
    test("return tuple of min and max from empty list", () =>
      expect(extent([], ~compare=[@ns.namedArgLoc] Int.compare))
      ->(toEqual(None))
    );
  }
});
describe("sum", () => {
  [@ns.braces]
  {
    test("sum of empty", () =>
      expect(sum([], (module Int)))->(toEqual(0))
    );
    test("sum of ints", () =>
      expect(sum([1, 1, 2, 3], (module Int)))->(toEqual(7))
    );
    test("sum with module struct", () =>
      expect(
        sum(
          ["a", "b", "c"],
          (module
           {
             type nonrec t = string;
             let zero = "";
             let add = (++);
           }),
        ),
      )
      ->(toEqual("abc"))
    );
  }
});
describe("map", () => {
  [@ns.braces]
  {
    test("map sqrt", () =>
      expect(map(~f=[@ns.namedArgLoc] Float.squareRoot, [1.0, 4.0, 9.0]))
      ->(toEqual([1.0, 2.0, 3.0]))
    );
    test("list char", () =>
      expect(
        map(
          ~f=[@ns.namedArgLoc] element => cons(element, 'h'),
          [['i'], ['a'], ['o', 'p']],
        ),
      )
      ->(toEqual([['h', 'i'], ['h', 'a'], ['h', 'o', 'p']]))
    );
    test("empty list", () =>
      expect(map(~f=[@ns.namedArgLoc] Float.squareRoot, []))->(toEqual([]))
    );
  }
});
describe("find", () => {
  [@ns.braces]
  {
    test("find first of 2 matches", () =>
      expect(List.find(~f=[@ns.namedArgLoc] Int.isEven, [1, 3, 4, 8]))
      ->(toEqual(Some(4)))
    );
    test("find 0 of 0 matches", () =>
      expect(List.find(~f=[@ns.namedArgLoc] Int.isOdd, [0, 2, 4, 8]))
      ->(toEqual(None))
    );
    test("empty list", () =>
      expect(List.find(~f=[@ns.namedArgLoc] Int.isEven, []))
      ->(toEqual(None))
    );
  }
});
describe("isEmpty", () => {
  [@ns.braces]
  {
    test("from empty list", () =>
      expect(isEmpty(List.empty))->(toEqual(true))
    );
    test("from empty list", () =>
      expect(isEmpty([]))->(toEqual(true))
    );
    test("from list with elements", () =>
      expect(isEmpty([1, (-4), 5, 6]))->(toEqual(false))
    );
  }
});
describe("length", () => {
  [@ns.braces]
  {
    test("from empty list", () =>
      expect(length([]))->(toEqual(0))
    );
    test("from list with elements", () =>
      expect(length([1, (-4), 5, 6]))->(toEqual(4))
    );
  }
});
describe("any", () => {
  [@ns.braces]
  {
    test("from empty list", () =>
      expect(any([], ~f=[@ns.namedArgLoc] Int.isEven))->(toEqual(false))
    );
    test("from even list", () =>
      expect(any([2, 3], ~f=[@ns.namedArgLoc] Int.isEven))->(toEqual(true))
    );
    test("from odd list", () =>
      expect(any([1, 3], ~f=[@ns.namedArgLoc] Int.isEven))
      ->(toEqual(false))
    );
  }
});
describe("all", () => {
  [@ns.braces]
  {
    test("from empty list", () =>
      expect(all([], ~f=[@ns.namedArgLoc] Int.isEven))->(toEqual(true))
    );
    test("from even list", () =>
      expect(all([2, 3], ~f=[@ns.namedArgLoc] Int.isEven))
      ->(toEqual(false))
    );
    test("from all even list", () =>
      expect(all([2, 4], ~f=[@ns.namedArgLoc] Int.isEven))->(toEqual(true))
    );
    test("from odd list", () =>
      expect(any([1, 3], ~f=[@ns.namedArgLoc] Int.isEven))
      ->(toEqual(false))
    );
  }
});
describe("count", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(count([], ~f=[@ns.namedArgLoc] Int.isEven))->(toEqual(0))
    );
    test("one even element", () =>
      expect(count([2, 3], ~f=[@ns.namedArgLoc] Int.isEven))->(toEqual(1))
    );
    test("all even elements", () =>
      expect(count([2, 4], ~f=[@ns.namedArgLoc] Int.isEven))->(toEqual(2))
    );
  }
});
describe("splitAt", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(splitAt([], ~index=[@ns.namedArgLoc] 1))->(toEqual(([], [])))
    );
    test("at evens", () =>
      expect(splitAt(~index=[@ns.namedArgLoc] 0, [2, 4, 6]))
      ->(toEqual(([], [2, 4, 6])))
    );
    test("four elements", () =>
      expect(splitAt(~index=[@ns.namedArgLoc] 2, [1, 3, 2, 4]))
      ->(toEqual(([1, 3], [2, 4])))
    );
    test("at end", () =>
      expect(splitAt(~index=[@ns.namedArgLoc] 3, [1, 3, 5]))
      ->(toEqual(([1, 3, 5], [])))
    );
    test("past end", () =>
      expect(splitAt(~index=[@ns.namedArgLoc] 6, [1, 3, 5]))
      ->(toEqual(([1, 3, 5], [])))
    );
    test("negative", () =>
      expect(splitAt(~index=[@ns.namedArgLoc] -1, [1, 3, 5]))
      ->(toEqual(([], [1, 3, 5])))
    );
  }
});
describe("splitWhen", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(splitWhen(~f=[@ns.namedArgLoc] Int.isEven, []))
      ->(toEqual(([], [])))
    );
    test("the first element satisfies f", () =>
      expect(splitWhen(~f=[@ns.namedArgLoc] Int.isEven, [2, 4, 6]))
      ->(toEqual(([], [2, 4, 6])))
    );
    test("the last element satisfies f", () =>
      expect(splitWhen(~f=[@ns.namedArgLoc] Int.isEven, [1, 3, 2, 4]))
      ->(toEqual(([1, 3], [2, 4])))
    );
    test("no element satisfies f", () =>
      expect(splitWhen(~f=[@ns.namedArgLoc] Int.isEven, [1, 3, 5]))
      ->(toEqual(([1, 3, 5], [])))
    );
  }
});
describe("intersperse", () => {
  [@ns.braces]
  {
    test("intersperse empty list", () =>
      expect(intersperse([], ~sep=[@ns.namedArgLoc] "on"))->(toEqual([]))
    );
    test("intersperse one turtle", () =>
      expect(intersperse(~sep=[@ns.namedArgLoc] "on", ["turtles"]))
      ->(toEqual(["turtles"]))
    );
    test("intersperse three turtles", () =>
      expect(
        intersperse(
          ~sep=[@ns.namedArgLoc] "on",
          ["turtles", "turtles", "turtles"],
        ),
      )
      ->(toEqual(["turtles", "on", "turtles", "on", "turtles"]))
    );
  }
});
describe("initial", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(initial([]))->(toEqual(None))
    );
    test("one element", () =>
      expect(initial(['a']))->(toEqual(Some([])))
    );
    test("two elements", () =>
      expect(initial(['a', 'b']))->(toEqual(Some(['a'])))
    );
  }
});
describe("last", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(last([]))->(toEqual(None))
    );
    test("one element", () =>
      expect(last(['a']))->(toEqual(Some('a')))
    );
    test("two elements", () =>
      expect(last(['a', 'b']))->(toEqual(Some('b')))
    );
  }
});
describe("getAt", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(List.getAt([], ~index=[@ns.namedArgLoc] 2))->(toEqual(None))
    );
    test("normal", () =>
      expect(List.getAt([1, 2, 3], ~index=[@ns.namedArgLoc] 1))
      ->(toEqual(Some(2)))
    );
    test("overflow", () =>
      expect(List.getAt([1, 2, 3], ~index=[@ns.namedArgLoc] 100))
      ->(toEqual(None))
    );
    test("negative index", () =>
      expect(List.getAt([1, 2, 3], ~index=[@ns.namedArgLoc] -2))
      ->(toEqual(None))
    );
  }
});
describe("append", () => {
  [@ns.braces]
  {
    test("append empty lists", () =>
      expect(append([], []))->(toEqual([]))
    );
    test("append empty list", () =>
      expect(append([], ["turtles"]))->(toEqual(["turtles"]))
    );
    test("append empty list", () =>
      expect(append(["turtles"], []))->(toEqual(["turtles"]))
    );
    test("append two lists", () =>
      expect(append(["on"], ["turtles"]))->(toEqual(["on", "turtles"]))
    );
  }
});
describe("fold", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(
        fold(~f=[@ns.namedArgLoc] cons, ~initial=[@ns.namedArgLoc] [], []),
      )
      ->(toEqual([]))
    );
    test("one element", () =>
      expect(
        fold(~f=[@ns.namedArgLoc] cons, ~initial=[@ns.namedArgLoc] [], [1]),
      )
      ->(toEqual([1]))
    );
    test("three elements", () =>
      expect(
        fold(
          ~f=[@ns.namedArgLoc] cons,
          ~initial=[@ns.namedArgLoc] [],
          [1, 2, 3],
        ),
      )
      ->(toEqual([3, 2, 1]))
    );
    test("foldr empty list", () =>
      expect(
        foldRight(
          ~f=[@ns.namedArgLoc] cons,
          ~initial=[@ns.namedArgLoc] [],
          [],
        ),
      )
      ->(toEqual([]))
    );
    test("foldr one element", () =>
      expect(
        foldRight(
          ~f=[@ns.namedArgLoc] cons,
          ~initial=[@ns.namedArgLoc] [],
          [1],
        ),
      )
      ->(toEqual([1]))
    );
    test("foldr three elements", () =>
      expect(
        foldRight(
          ~f=[@ns.namedArgLoc] cons,
          ~initial=[@ns.namedArgLoc] [],
          [1, 2, 3],
        ),
      )
      ->(toEqual([1, 2, 3]))
    );
    test("-", () =>
      expect(
        fold(
          ~f=[@ns.namedArgLoc] (-),
          ~initial=[@ns.namedArgLoc] 0,
          [1, 2, 3],
        ),
      )
      ->(toEqual(-6))
    );
    test("- foldRight", () =>
      expect(
        foldRight(
          ~f=[@ns.namedArgLoc] (-),
          ~initial=[@ns.namedArgLoc] 0,
          [1, 2, 3],
        ),
      )
      ->(toEqual(-6))
    );
  }
});
describe("insertAt", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(
        insertAt(~index=[@ns.namedArgLoc] 0, ~value=[@ns.namedArgLoc] 1, []),
      )
      ->(toEqual([1]))
    );
    test("in the middle", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 1,
          ~value=[@ns.namedArgLoc] 2,
          [1, 3],
        ),
      )
      ->(toEqual([1, 2, 3]))
    );
    test("in the front", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 0,
          ~value=[@ns.namedArgLoc] 2,
          [1, 3],
        ),
      )
      ->(toEqual([2, 1, 3]))
    );
    test("after end of list", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 4,
          ~value=[@ns.namedArgLoc] 2,
          [1, 3],
        ),
      )
      ->(toEqual([1, 3, 2]))
    );
    test("#216", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 5,
          ~value=[@ns.namedArgLoc] 1,
          [0, 2, 3, 4, 5, 6, 7, 8, 9],
        ),
      )
      ->(toEqual([0, 2, 3, 4, 5, 1, 6, 7, 8, 9]))
    );
    test("doc 1", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 2,
          ~value=[@ns.namedArgLoc] 999,
          [100, 101, 102, 103],
        ),
      )
      ->(toEqual([100, 101, 999, 102, 103]))
    );
    test("doc 2", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 0,
          ~value=[@ns.namedArgLoc] 999,
          [100, 101, 102, 103],
        ),
      )
      ->(toEqual([999, 100, 101, 102, 103]))
    );
    test("doc 3", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 4,
          ~value=[@ns.namedArgLoc] 999,
          [100, 101, 102, 103],
        ),
      )
      ->(toEqual([100, 101, 102, 103, 999]))
    );
    test("doc 4", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] -1,
          ~value=[@ns.namedArgLoc] 999,
          [100, 101, 102, 103],
        ),
      )
      ->(toEqual([999, 100, 101, 102, 103]))
    );
    test("doc 5", () =>
      expect(
        insertAt(
          ~index=[@ns.namedArgLoc] 5,
          ~value=[@ns.namedArgLoc] 999,
          [100, 101, 102, 103],
        ),
      )
      ->(toEqual([100, 101, 102, 103, 999]))
    );
  }
});
describe("updateAt", () => {
  [@ns.braces]
  {
    test("updateAt index smaller 0", () =>
      expect(
        updateAt(
          ~index=[@ns.namedArgLoc] -1,
          ~f=[@ns.namedArgLoc] x => x + 1,
          [1, 3],
        ),
      )
      ->(toEqual([1, 3]))
    );
    test("updateAt empty list", () =>
      expect(
        updateAt(
          ~index=[@ns.namedArgLoc] 0,
          ~f=[@ns.namedArgLoc] x => x + 1,
          [],
        ),
      )
      ->(toEqual([]))
    );
    test("updateAt empty list", () =>
      expect(
        updateAt(
          ~index=[@ns.namedArgLoc] 2,
          ~f=[@ns.namedArgLoc] x => x + 1,
          [],
        ),
      )
      ->(toEqual([]))
    );
    test("updateAt inside the list", () =>
      expect(
        updateAt(
          ~index=[@ns.namedArgLoc] 1,
          ~f=[@ns.namedArgLoc] x => x + 1,
          [1, 3],
        ),
      )
      ->(toEqual([1, 4]))
    );
    test("updateAt in the front", () =>
      expect(
        updateAt(
          ~index=[@ns.namedArgLoc] 0,
          ~f=[@ns.namedArgLoc] x => x + 1,
          [1, 3],
        ),
      )
      ->(toEqual([2, 3]))
    );
    test("updateAt after end of list", () =>
      expect(
        updateAt(
          ~index=[@ns.namedArgLoc] 4,
          ~f=[@ns.namedArgLoc] x => x + 1,
          [1, 3],
        ),
      )
      ->(toEqual([1, 3]))
    );
  }
});
describe("flatten", () => {
  [@ns.braces]
  {
    test("two empty lists", () =>
      expect(flatten([[], []]))->(toEqual([]))
    );
    test("one empty list", () =>
      expect(flatten([[1], []]))->(toEqual([1]))
    );
    test("one empty list", () =>
      expect(flatten([[], [1]]))->(toEqual([1]))
    );
    test("several lists", () =>
      expect(flatten([[1], [2], [3]]))->(toEqual([1, 2, 3]))
    );
    test("several lists", () =>
      expect(flatten([[1], [], [2], [], [3]]))->(toEqual([1, 2, 3]))
    );
  }
});
describe("zip", () => {
  [@ns.braces]
  {
    test("zip num and string", () =>
      expect(zip([1, 2, 3, 4, 5], ["Dog", "Eagle", "Ferret"]))
      ->(toEqual([(1, "Dog"), (2, "Eagle"), (3, "Ferret")]))
    );
    test("zip num and empty", () =>
      expect(zip([1, 2, 3, 4, 5], []))->(toEqual([]))
    );
  }
});
describe("unzip", () =>
  test("unzip num and bool", () =>
    expect(unzip([(0, true), (17, false), (1337, true)]))
    ->(toEqual(([0, 17, 1337], [true, false, true])))
  )
);
describe("chunksOf", () => {
  [@ns.braces]
  {
    test("empty list", () =>
      expect(chunksOf(~size=[@ns.namedArgLoc] 2, []))->(toEqual([]))
    );
    test("normal", () =>
      expect(
        chunksOf(
          ~size=[@ns.namedArgLoc] 2,
          ["#FFBA49", "#9984D4", "#20A39E", "#EF5B5B", "#23001E"],
        ),
      )
      ->(toEqual([["#FFBA49", "#9984D4"], ["#20A39E", "#EF5B5B"]]))
    );
  }
});
describe("initialize", () => {
  [@ns.braces]
  {
    test("initialize length 0", () =>
      expect(initialize(0, ~f=[@ns.namedArgLoc] i => i))->(toEqual([]))
    );
    test("initialize length 1", () =>
      expect(initialize(1, ~f=[@ns.namedArgLoc] i => i))->(toEqual([0]))
    );
    test("initialize length 2", () =>
      expect(initialize(2, ~f=[@ns.namedArgLoc] i => i))->(toEqual([0, 1]))
    );
  }
});
describe("removeAt", () => {
  [@ns.braces]
  {
    test("removeAt index smaller 0", () =>
      expect(removeAt(~index=[@ns.namedArgLoc] -1, [1, 3]))
      ->(toEqual([1, 3]))
    );
    test("removeAt empty list", () =>
      expect(removeAt(~index=[@ns.namedArgLoc] 0, []))->(toEqual([]))
    );
    test("removeAt empty list", () =>
      expect(removeAt(~index=[@ns.namedArgLoc] 2, []))->(toEqual([]))
    );
    test("removeAt index 1", () =>
      expect(removeAt(~index=[@ns.namedArgLoc] 1, [1, 3]))->(toEqual([1]))
    );
    test("removeAt index 0", () =>
      expect(removeAt(~index=[@ns.namedArgLoc] 0, [1, 3]))->(toEqual([3]))
    );
    test("removeAt after end of list", () =>
      expect(removeAt(~index=[@ns.namedArgLoc] 4, [1, 3]))
      ->(toEqual([1, 3]))
    );
  }
});
describe("groupBy", () => {
  [@ns.braces]
  {
    test("returns an empty map for an empty array", () =>
      expect(
        Map.length(
          List.groupBy([], (module Int), ~f=[@ns.namedArgLoc] String.length),
        ),
      )
      ->(toEqual(0))
    );
    test("example test case", () =>
      [@ns.braces]
      {
        let animals = ["Ant", "Bear", "Cat", "Dewgong"];
        expect(
          Map.toList(
            List.groupBy(
              animals,
              (module Int),
              ~f=[@ns.namedArgLoc] String.length,
            ),
          ),
        )
        ->(
            toEqual([
              (3, ["Cat", "Ant"]),
              (4, ["Bear"]),
              (7, ["Dewgong"]),
            ])
          );
      }
    );
  }
});
describe("toArray", () => {
  [@ns.braces]
  {
    test("returns an array of int", () =>
      expect(toArray([2, 4, 6, 8]))->(toEqual([|2, 4, 6, 8|]))
    );
    test("empty", () =>
      expect(toArray([]))->(toEqual([||]))
    );
    test("returns an array of char", () =>
      expect(toArray(['h', 'i']))->(toEqual([|'h', 'i'|]))
    );
  }
});
describe("equal", () => {
  [@ns.braces]
  {
    test("normal int", () =>
      expect(equal([2, 5, 6, 11], [2, 5, 6, 11], Int.equal))
      ->(toEqual(true))
    );
    test("normal int", () =>
      expect(equal([2, 5, (-6), 11], [2, 5, 6, 11], Int.equal))
      ->(toEqual(false))
    );
    test("normal string", () =>
      expect(
        equal(["hi", "hello", "hey"], ["hi", "hello", "hey"], String.equal),
      )
      ->(toEqual(true))
    );
  }
});
describe("compare", () => {
  [@ns.braces]
  {
    test("normal int", () =>
      expect(compare([2, 5, 6, 11], [2, 5, 6, 11], Int.compare))
      ->(toEqual(0))
    );
    test("normal int with different element", () =>
      expect(compare([2, 5, (-6), 11], [2, 5, 6, 11], Int.compare))
      ->(toEqual(-1))
    );
    test("normal int with shorter and longer array", () =>
      expect(compare([2, 5, 6, 11], [2, 5, 6], Int.compare))->(toEqual(1))
    );
    test("normal string", () =>
      expect(
        compare(
          ["hi", "hello", "hey"],
          ["hi", "hello", "hey"],
          String.compare,
        ),
      )
      ->(toEqual(0))
    );
  }
});

open Tablecloth;
open Jest;
open Expect;
open String;
testAll(
  "fromChar",
  [('a', "a"), ('z', "z"), (' ', " "), ('\n', "\n")],
  ((char, string)) =>
  expect(fromChar(char))->(toEqual(string))
);
describe("fromArray", () => {
  [@ns.braces]
  {
    test("creates an empty string from an empty array", () =>
      expect(fromArray([||]))->(toEqual(""))
    );
    test("creates a string of characters", () =>
      expect(fromArray([|'K', 'u', 'b', 'o'|]))->(toEqual("Kubo"))
    );
    test("creates a string of characters", () =>
      expect(fromArray([|' ', '\n', '\t'|]))->(toEqual(" \n\t"))
    );
  }
});
describe("indexOf", () => {
  [@ns.braces]
  {
    test("returns some index of the first matching substring", () =>
      expect(indexOf("hello", "h"))->(toEqual(Some(0)))
    );
    test("returns the first index even though multiple present", () =>
      expect(indexOf("hellh", "h"))->(toEqual(Some(0)))
    );
    test("returns first substring that matches with multiple characters", () =>
      expect(indexOf("hellh", "ell"))->(toEqual(Some(1)))
    );
    test("returns None when no substring matches", () =>
      expect(indexOf("hello", "xy"))->(toEqual(None))
    );
  }
});
describe("indexOfRight", () => {
  [@ns.braces]
  {
    test("returns some index of the last matching string", () =>
      expect(indexOfRight("helloh", "oh"))->(toEqual(Some(4)))
    );
    test("returns the last index even though multiple present", () =>
      expect(indexOfRight("ohelloh", "oh"))->(toEqual(Some(5)))
    );
    test("returns None when no character matches", () =>
      expect(indexOfRight("hello", "x"))->(toEqual(None))
    );
  }
});
describe("fromList", () => {
  [@ns.braces]
  {
    test("creates an empty string from an empty array", () =>
      expect(fromList([]))->(toEqual(""))
    );
    test("creates a string of characters", () =>
      expect(fromList(['K', 'u', 'b', 'o']))->(toEqual("Kubo"))
    );
    test("creates a string of characters", () =>
      expect(fromList([' ', '\n', '\t']))->(toEqual(" \n\t"))
    );
  }
});
describe("repeat", () => {
  [@ns.braces]
  {
    test("returns an empty string for count zero", () =>
      expect(repeat("bun", ~count=[@ns.namedArgLoc] 0))->(toEqual(""))
    );
    test("raises for negative count", () =>
      toThrow(expect(() =>
                repeat("bun", ~count=[@ns.namedArgLoc] -1)
              ))
    );
    test("returns the input string repeated count times", () =>
      expect(repeat("bun", ~count=[@ns.namedArgLoc] 3))
      ->(toEqual("bunbunbun"))
    );
  }
});
describe("initialize", () => {
  [@ns.braces]
  {
    test("returns an empty string for count zero", () =>
      expect(initialize(0, ~f=[@ns.namedArgLoc] i => Fun.constant('A', i)))
      ->(toEqual(""))
    );
    test("raises for negative count", () =>
      toThrow(
        expect(() =>
          initialize(-1, ~f=[@ns.namedArgLoc] i => Fun.constant('A', i))
        ),
      )
    );
    test("returns the input string repeated count times", () =>
      expect(initialize(3, ~f=[@ns.namedArgLoc] i => Fun.constant('A', i)))
      ->(toEqual("AAA"))
    );
  }
});
describe("isEmpty", () => {
  [@ns.braces]
  {
    test("true for zero length string", () =>
      expect(isEmpty(""))->(toEqual(true))
    );
    testAll("false for length > 0 strings", ["abc", " ", "\n"], string =>
      expect(isEmpty(string))->(toEqual(false))
    );
  }
});
test("length empty string", () =>
  expect(String.length(""))->(toEqual(0))
);
test("length", () =>
  expect(String.length("123"))->(toEqual(3))
);
test("reverse empty string", () =>
  expect(String.reverse(""))->(toEqual(""))
);
test("reverse", () =>
  expect(String.reverse("stressed"))->(toEqual("desserts"))
);
describe("split", () => {
  [@ns.braces]
  {
    test("middle", () =>
      expect(String.split("abc", ~on=[@ns.namedArgLoc] "b"))
      ->(toEqual(["a", "c"]))
    );
    test("start", () =>
      expect(String.split("ab", ~on=[@ns.namedArgLoc] "a"))
      ->(toEqual(["", "b"]))
    );
    test("end", () =>
      expect(String.split("ab", ~on=[@ns.namedArgLoc] "b"))
      ->(toEqual(["a", ""]))
    );
  }
});
describe("insertAt", () => {
  [@ns.braces]
  {
    test("middle", () =>
      expect(
        String.insertAt(
          "abcde",
          ~value=[@ns.namedArgLoc] "**",
          ~index=[@ns.namedArgLoc] 2,
        ),
      )
      ->(toEqual("ab**cde"))
    );
    test("start", () =>
      expect(
        String.insertAt(
          "abcde",
          ~value=[@ns.namedArgLoc] "**",
          ~index=[@ns.namedArgLoc] 0,
        ),
      )
      ->(toEqual("**abcde"))
    );
    test("end", () =>
      expect(
        String.insertAt(
          "abcde",
          ~value=[@ns.namedArgLoc] "**",
          ~index=[@ns.namedArgLoc] 5,
        ),
      )
      ->(toEqual("abcde**"))
    );
    test("negative", () =>
      expect(
        String.insertAt(
          "abcde",
          ~value=[@ns.namedArgLoc] "**",
          ~index=[@ns.namedArgLoc] -2,
        ),
      )
      ->(toEqual("abc**de"))
    );
    test("negative overflow", () =>
      expect(
        String.insertAt(
          "abcde",
          ~value=[@ns.namedArgLoc] "**",
          ~index=[@ns.namedArgLoc] -9,
        ),
      )
      ->(toEqual("**abcde"))
    );
    test("overflow", () =>
      expect(
        String.insertAt(
          "abcde",
          ~value=[@ns.namedArgLoc] "**",
          ~index=[@ns.namedArgLoc] 9,
        ),
      )
      ->(toEqual("abcde**"))
    );
  }
});
test("toArray", () =>
  expect(String.toArray("Standard"))
  ->(toEqual([|'S', 't', 'a', 'n', 'd', 'a', 'r', 'd'|]))
);
test("toList", () =>
  expect(String.toList("Standard"))
  ->(toEqual(['S', 't', 'a', 'n', 'd', 'a', 'r', 'd']))
);

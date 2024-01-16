open Tablecloth;
open Jest;
open Expect;
describe("unwrapUnsafe", () => {
  [@ns.braces]
  {
    test("returns the wrapped value for a Some", () =>
      expect(Option.unwrapUnsafe(Some(1)))->(toEqual(1))
    );
    test("raises for a None", () =>
      toThrow(expect(() =>
                ignore(Option.unwrapUnsafe(None))
              ))
    );
  }
});
describe("and_", () => {
  [@ns.braces]
  {
    test("returns second argument", () =>
      expect(Option.and_(Some(1), Some(15)))->(toEqual(Some(15)))
    );
    test("returns none", () =>
      expect(Option.and_(None, Some(15)))->(toEqual(None))
    );
    test("returns none", () =>
      expect(Option.and_(Some(1), None))->(toEqual(None))
    );
    test("returns none", () =>
      expect(Option.and_(None, None))->(toEqual(None))
    );
  }
});
describe("or_", () => {
  [@ns.braces]
  {
    test("returns first argument", () =>
      expect(Option.or_(Some(1), Some(15)))->(toEqual(Some(1)))
    );
    test("returns second argument some", () =>
      expect(Option.or_(None, Some(15)))->(toEqual(Some(15)))
    );
    test("returns first argument some", () =>
      expect(Option.or_(Some(1), None))->(toEqual(Some(1)))
    );
    test("returns none", () =>
      expect(Option.or_(None, None))->(toEqual(None))
    );
  }
});
describe("orElse", () => {
  [@ns.braces]
  {
    test("returns second argument", () =>
      expect(Option.orElse(Some(1), Some(15)))->(toEqual(Some(15)))
    );
    test("returns second argument", () =>
      expect(Option.orElse(None, Some(15)))->(toEqual(Some(15)))
    );
    test("returns first argument some", () =>
      expect(Option.orElse(Some(1), None))->(toEqual(Some(1)))
    );
    test("returns none", () =>
      expect(Option.orElse(None, None))->(toEqual(None))
    );
  }
});
describe("both", () => {
  [@ns.braces]
  {
    test("returns both as pair", () =>
      expect(Option.both(Some(3004), Some("Ant")))
      ->(toEqual(Some((3004, "Ant"))))
    );
    test("returns none", () =>
      expect(Option.both(None, Some("Ant")))->(toEqual(None))
    );
    test("returns none", () =>
      expect(Option.both(Some(3004), None))->(toEqual(None))
    );
    test("returns none", () =>
      expect(Option.both(None, None))->(toEqual(None))
    );
  }
});
describe("flatten", () => {
  [@ns.braces]
  {
    test("returns option layers as single option layer", () =>
      expect(Option.flatten(Some(Some(4))))->(toEqual(Some(4)))
    );
    test("returns none", () =>
      expect(Option.flatten(Some(None)))->(toEqual(None))
    );
    test("returns none", () =>
      expect(Option.flatten(None))->(toEqual(None))
    );
  }
});
describe("map", () => {
  [@ns.braces]
  {
    test("returns transformed value from inside option arg", () =>
      expect(Option.map(~f=[@ns.namedArgLoc] x => x * x, Some(9)))
      ->(toEqual(Some(81)))
    );
    test("returns transformed value from inside option arg", () =>
      expect(Option.map(~f=[@ns.namedArgLoc] Int.toString, Some(9)))
      ->(toEqual(Some("9")))
    );
    test("returns none", () =>
      expect(Option.map(~f=[@ns.namedArgLoc] x => x * x, None))
      ->(toEqual(None))
    );
  }
});
describe("map2", () => {
  [@ns.braces]
  {
    test("returns transformed value from two option arg", () =>
      expect(Option.map2(Some(3), Some(4), ~f=[@ns.namedArgLoc] Int.add))
      ->(toEqual(Some(7)))
    );
    test("returns none", () =>
      expect(Option.map2(Some(3), None, ~f=[@ns.namedArgLoc] Int.add))
      ->(toEqual(None))
    );
    test("returns none", () =>
      expect(Option.map2(None, Some(4), ~f=[@ns.namedArgLoc] Int.add))
      ->(toEqual(None))
    );
  }
});
describe("andThen", () => {
  [@ns.braces]
  {
    test("returns result of callback", () =>
      expect(
        Option.andThen(Some([1, 2, 3]), ~f=[@ns.namedArgLoc] List.head),
      )
      ->(toEqual(Some(1)))
    );
    test("returns none", () =>
      expect(Option.andThen(Some([]), ~f=[@ns.namedArgLoc] List.head))
      ->(toEqual(None))
    );
  }
});
describe("unwrap", () => {
  [@ns.braces]
  {
    test("returns unwrapped [option('a)]", () =>
      expect(Option.unwrap(~default=[@ns.namedArgLoc] 99, Some(42)))
      ->(toEqual(42))
    );
    test("returns default", () =>
      expect(Option.unwrap(~default=[@ns.namedArgLoc] 99, None))
      ->(toEqual(99))
    );
  }
});
describe("isSome", () => {
  [@ns.braces]
  {
    test("returns true if is a Some", () =>
      expect(Option.isSome(Some(3004)))->(toEqual(true))
    );
    test("returns false if is a None", () =>
      expect(Option.isSome(None))->(toEqual(false))
    );
  }
});
describe("isNone", () => {
  [@ns.braces]
  {
    test("returns false if is a Some", () =>
      expect(Option.isNone(Some(3004)))->(toEqual(false))
    );
    test("returns true if is a None", () =>
      expect(Option.isNone(None))->(toEqual(true))
    );
  }
});
describe("toArray", () => {
  [@ns.braces]
  {
    test("returns option as array", () =>
      expect(Option.toArray(Some(3004)))->(toEqual([|3004|]))
    );
    test("returns empty array if None", () =>
      expect(Option.toArray(None))->(toEqual([||]))
    );
  }
});
describe("toList", () => {
  [@ns.braces]
  {
    test("returns option as list", () =>
      expect(Option.toList(Some(3004)))->(toEqual([3004]))
    );
    test("returns empty list if None", () =>
      expect(Option.toList(None))->(toEqual([]))
    );
  }
});
describe("equal", () => {
  [@ns.braces]
  {
    test("returns bool true if options are equal", () =>
      expect(Option.equal(Some(1), Some(1), Int.equal))->(toEqual(true))
    );
    test("returns bool true if options are equal", () =>
      expect(Option.equal(Some(1), Some(3), Int.equal))->(toEqual(false))
    );
    test("returns bool true if options are equal", () =>
      expect(Option.equal(Some(1), None, Int.equal))->(toEqual(false))
    );
    test("returns bool true if options are equal", () =>
      expect(Option.equal(None, None, Int.equal))->(toEqual(true))
    );
  }
});
describe("compare", () => {
  [@ns.braces]
  {
    test("returns comparative value -1, 0, or 1", () =>
      expect(
        Option.compare(Some(1), Some(3), ~f=[@ns.namedArgLoc] Int.compare),
      )
      ->(toEqual(-1))
    );
    test("returns comparative value -1, 0, or 1", () =>
      expect(
        Option.compare(Some(1), None, ~f=[@ns.namedArgLoc] Int.compare),
      )
      ->(toEqual(1))
    );
    test("returns comparative value -1, 0, or 1", () =>
      expect(Option.compare(None, None, ~f=[@ns.namedArgLoc] Int.compare))
      ->(toEqual(0))
    );
  }
});

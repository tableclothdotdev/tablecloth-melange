open Tablecloth;
open Jest;
open Expect;
open Result;
describe("ok", () => {
  [@ns.braces]
  {
    test("returns ok type", () =>
      expect(Result.ok(String.reverse("desserts")))
      ->(toEqual(Ok("stressed")))
    );
    test("returns ok type", () =>
      expect(List.map([1, 2, 3], ~f=[@ns.namedArgLoc] Result.ok))
      ->(toEqual([Ok(1), Ok(2), Ok(3)]))
    );
  }
});
describe("error", () => {
  [@ns.braces]
  {
    test("returns error type", () =>
      expect(Result.error(Int.negate(3)))->(toEqual(Error(-3)))
    );
    test("returns error type", () =>
      expect(List.map([1, 2, 3], ~f=[@ns.namedArgLoc] Result.error))
      ->(toEqual([Error(1), Error(2), Error(3)]))
    );
  }
});
describe("fromOption", () => {
  [@ns.braces]
  {
    test("maps None into Error", () =>
      expect(fromOption(~error=[@ns.namedArgLoc] "error message", None))
      ->(toEqual(Error("error message")))
    );
    test("maps Some into Ok", () =>
      expect(fromOption(~error=[@ns.namedArgLoc] "error message", Some(10)))
      ->(toEqual(Ok(10)))
    );
  }
});
describe("isOk", () => {
  [@ns.braces]
  {
    test("returns true if result is Ok", () =>
      expect(Result.isOk(Ok(3)))->(toEqual(true))
    );
    test("returns false if result is Error", () =>
      expect(Result.isOk(Error(3)))->(toEqual(false))
    );
  }
});
describe("isError", () => {
  [@ns.braces]
  {
    test("returns false if result is Ok", () =>
      expect(Result.isError(Ok(3)))->(toEqual(false))
    );
    test("returns true if result is Error", () =>
      expect(Result.isError(Error(3)))->(toEqual(true))
    );
  }
});
describe("and_", () => {
  [@ns.braces]
  {
    test("returns second arg if both are Ok", () =>
      expect(Result.and_(Ok("Antelope"), Ok("Salmon")))
      ->(toEqual(Ok("Salmon")))
    );
    test("returns first error arg", () =>
      expect(Result.and_(Error("Finch"), Ok("Salmon")))
      ->(toEqual(Error("Finch")))
    );
    test("returns first error arg", () =>
      expect(Result.and_(Ok("Antelope"), Error("Finch")))
      ->(toEqual(Error("Finch")))
    );
    test("returns first error arg", () =>
      expect(Result.and_(Error("Honey bee"), Error("Finch")))
      ->(toEqual(Error("Honey bee")))
    );
  }
});
describe("or_", () => {
  [@ns.braces]
  {
    test("returns first arg if both are Ok", () =>
      expect(Result.or_(Ok("Boar"), Ok("Gecko")))->(toEqual(Ok("Boar")))
    );
    test("returns ok arg", () =>
      expect(Result.or_(Error("Periwinkle"), Ok("Gecko")))
      ->(toEqual(Ok("Gecko")))
    );
    test("returns ok arg", () =>
      expect(Result.or_(Ok("Boar"), Error("Periwinkle")))
      ->(toEqual(Ok("Boar")))
    );
    test("returns second arg", () =>
      expect(Result.or_(Error("Periwinkle"), Error("Robin")))
      ->(toEqual(Error("Robin")))
    );
    describe("unwrapLazy", () =>
      test("returns forced default arg if error", () =>
        expect(
          Result.unwrapLazy(
            Error("Periwinkle"),
            ~default=[@ns.namedArgLoc] (lazy("Gecko")),
          ),
        )
        ->(toEqual("Gecko"))
      )
    );
  }
});

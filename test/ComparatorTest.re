open Tablecloth;
open Jest;
open Expect;
module Book = {
  type nonrec t = {
    isbn: string,
    title: string,
  };
};
module BookByIsbn = {
  type nonrec t = Book.t;
  include Comparator.Make({
    type nonrec t = t;
    let compare = (bookA: Book.t, bookB: Book.t) =>
      String.compare(bookA.isbn, bookB.isbn);
  });
};
module BookByTitle = {
  type nonrec t = Book.t;
  include Comparator.Make({
    type nonrec t = t;
    let compare = (bookA: Book.t, bookB: Book.t) =>
      String.compare(bookA.title, bookB.title);
  });
};
module BookByIsbnThenTitle = {
  type nonrec t = Book.t;
  include Comparator.Make({
    type nonrec t = t;
    let compare = (bookA: Book.t, bookB: Book.t) =>
      [@ns.braces]
      {
        let isbnComparison = String.compare(bookA.isbn, bookB.isbn);
        if (isbnComparison == 0) {
          String.compare(bookA.title, bookB.title);
        } else {
          isbnComparison;
        };
      };
  });
};
let book = (a: Book.t, b: Book.t): bool => a == b;
let mobyDick: Book.t = (
  {isbn: "9788460767923", title: "Moby Dick or The Whale"}: Book.t
);
let mobyDickReissue: Book.t = (
  {isbn: "9788460767924", title: "Moby Dick or The Whale"}: Book.t
);
let frankenstein: Book.t = (
  {isbn: "9781478198406", title: "Frankenstein"}: Book.t
);
let frankensteinAlternateTitle: Book.t = (
  {isbn: "9781478198406", title: "The Modern Prometheus"}: Book.t
);
describe("Make", () =>
  test("module documentation example", () =>
    [@ns.braces]
    {
      let result: list(Book.t) = (
        Set.fromList(
          [frankenstein, frankensteinAlternateTitle],
          (module BookByIsbn),
        )
        ->Set.toList:
          list(Book.t)
      );
      expect(result)->(toEqual([frankenstein]));
    }
  )
);
describe("make", () =>
  test("module documentation example", () =>
    [@ns.braces]
    {
      let result: list(Book.t) = (
        Set.toList(
          Set.fromList([mobyDick, mobyDickReissue], (module BookByTitle)),
        ):
          list(Book.t)
      );
      expect(result)->(toEqual([mobyDick]));
    }
  )
);

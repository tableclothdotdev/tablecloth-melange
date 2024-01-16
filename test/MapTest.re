open Tablecloth;
open Jest;
open Expect;
module Coordinate: {
  type nonrec t = (int, int);
  let compare: (t, t) => int;
  type nonrec identity;
  let comparator: Tablecloth.Comparator.comparator(t, identity);
} = {
  module T = {
    type nonrec t = (int, int);
    let compare = (a, b) =>
      Tuple2.compare(
        a,
        b,
        ~f=[@ns.namedArgLoc] Int.compare,
        ~g=[@ns.namedArgLoc] Int.compare,
      );
  };
  include T;
  include Tablecloth.Comparator.Make(T);
};
describe("fromArray", () => {
  [@ns.braces]
  {
    test(
      "returns map of key value pairs from array of pairs with ordered type key String",
      () =>
      [@ns.braces]
      {
        let fromArrayMap =
          Map.fromArray(
            (module String),
            [|
              ("Cat", 4),
              ("Owl", 2),
              ("Fox", 5),
              ("Frog", 12),
              ("Camel", 2),
            |],
          );
        let ansList = Map.toList(fromArrayMap);
        ansList
        ->expect
        ->(
            toEqual([
              ("Camel", 2),
              ("Cat", 4),
              ("Fox", 5),
              ("Frog", 12),
              ("Owl", 2),
            ])
          );
      }
    );
    test("returns empty map from empty array of key value pairs", () =>
      [@ns.braces]
      {
        let fromArrayMap = Map.fromArray((module String), [||]);
        let ansList = Map.toList(fromArrayMap);
        expect(ansList)->(toEqual([]));
      }
    );
  }
});
describe("singleton", () =>
  test("key value pair", () =>
    [@ns.braces]
    {
      let singletonMap =
        Map.singleton(
          (module Int),
          ~key=[@ns.namedArgLoc] 1,
          ~value=[@ns.namedArgLoc] "Ant",
        );
      let ans = Map.toList(singletonMap);
      expect(ans)->(toEqual([(1, "Ant")]));
    }
  )
);
describe("empty", () =>
  test("has length zero", () =>
    [@ns.braces]
    (expect(Map.length(Tablecloth.Map.empty((module Char))))->(toEqual(0)))
  )
);
describe("Poly.fromList", () =>
  test("creates a map from a list", () =>
    [@ns.braces]
    {
      let map = Map.Poly.fromList([(`Ant, "Ant"), (`Bat, "Bat")]);
      expect(Map.get(map, `Ant))->(toEqual(Some("Ant")));
    }
  )
);
describe("Int.fromList", () =>
  test("creates a map from a list", () =>
    [@ns.braces]
    {
      let map = Map.Int.fromList([(1, "Ant"), (2, "Bat")]);
      expect(Map.get(map, 1))->(toEqual(Some("Ant")));
    }
  )
);
describe("String.fromList", () =>
  test("creates a map from a list", () =>
    [@ns.braces]
    {
      let map = Map.String.fromList([("Ant", 1), ("Bat", 1)]);
      expect(Map.get(map, "Ant"))->(toEqual(Some(1)));
    }
  )
);
describe("filterMap", () =>
  test("maps values by their results and filters out items with no result", () =>
    [@ns.braces]
    {
      let filterMapMap =
        Map.String.fromArray([|
          ("Cat", 4),
          ("Owl", 2),
          ("Fox", 5),
          ("Frog", 12),
          ("Camel", 2),
        |]);
      let ansList =
        filterMapMap
        ->(
            Map.filterMap(
              ~f=[@ns.namedArgLoc]
                 (
                   ~key as [@ns.namedArgLoc] _,
                   ~value as [@ns.namedArgLoc] value,
                 ) =>
              if (value->Int.isEven) {
                Some(value / 2);
              } else {
                None;
              }
            )
          )
        ->Map.toList;
      expect(ansList)
      ->(toEqual([("Camel", 1), ("Cat", 2), ("Frog", 6), ("Owl", 1)]));
    }
  )
);

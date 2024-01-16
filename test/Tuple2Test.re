open Tablecloth;
open Jest;
open Expect;
test("make", () =>
  expect(Tuple2.make(3, 4))->(toEqual((3, 4)))
);
test("first", () =>
  expect(Tuple2.first((3, 4)))->(toEqual(3))
);
test("second", () =>
  expect(Tuple2.second((3, 4)))->(toEqual(4))
);
test("mapFirst", () =>
  expect(
    Tuple2.mapFirst(~f=[@ns.namedArgLoc] String.reverse, ("stressed", 16)),
  )
  ->(toEqual(("desserts", 16)))
);
test("mapSecond", () =>
  expect(
    Tuple2.mapSecond(
      ~f=[@ns.namedArgLoc] Float.squareRoot,
      ("stressed", 16.),
    ),
  )
  ->(toEqual(("stressed", 4.)))
);
test("mapEach", () =>
  expect(
    Tuple2.mapEach(
      ~f=[@ns.namedArgLoc] String.reverse,
      ~g=[@ns.namedArgLoc] Float.squareRoot,
      ("stressed", 16.),
    ),
  )
  ->(toEqual(("desserts", 4.)))
);
test("mapAll", () =>
  expect(
    Tuple2.mapAll(~f=[@ns.namedArgLoc] String.reverse, ("was", "stressed")),
  )
  ->(toEqual(("saw", "desserts")))
);
test("swap", () =>
  expect(Tuple2.swap((3, 4)))->(toEqual((4, 3)))
);
test("toArray", () =>
  expect(Tuple2.toArray((3, 4)))->(toEqual([|3, 4|]))
);
test("toList", () =>
  expect(Tuple2.toList((3, 4)))->(toEqual([3, 4]))
);

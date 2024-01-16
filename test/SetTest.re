open Tablecloth;
open JestStubs;
open Jest;
open Expect;
module Coordinate = {
  include Coordinate;
  include Comparator.Make({
    type nonrec t = t;
    let compare = compare;
  });
};
test("creates a set from a list", () =>
  [@ns.braces]
  {
    let set = Set.fromList([1, 2], (module Int));
    expect(Set.includes(set, 1))->(toEqual(true));
  }
);
test("fromArray", () =>
  [@ns.braces]
  {
    let set = Set.fromArray([|(0, 0), (0, 1)|], (module Coordinate));
    expect(Set.includes(set, (0, 1)))->(toEqual(true));
  }
);
test("union", () =>
  [@ns.braces]
  {
    let xAxis = Set.fromList([(0, 0), (0, 1)], (module Coordinate));
    let yAxis = Set.fromList([(0, 0), (1, 0)], (module Coordinate));
    let union = Set.union(xAxis, yAxis);
    expect(Set.toArray(union))->(toEqual([|(0, 0), (0, 1), (1, 0)|]));
  }
);
describe("Int", () =>
  test("creates a set from a list", () =>
    [@ns.braces]
    {
      let set = Set.Int.fromList([1, 2]);
      expect(Set.includes(set, 1))->(toEqual(true));
    }
  )
);
describe("String", () =>
  test("creates a set from a list", () =>
    [@ns.braces]
    {
      let set = Set.String.fromList(["Ant", "Bat"]);
      expect(Set.includes(set, "Ant"))->(toEqual(true));
    }
  )
);

type nonrec t('a, 'id) = Belt.Set.t('a, 'id);
let empty = comparator =>
  Belt.Set.make(~id=[@ns.namedArgLoc] Internal.toBeltComparator(comparator));
let singleton =
    (element: 'a, comparator: TableclothComparator.s('a, 'identity))
    : t('a, 'identity) =>
  Belt.Set.fromArray(
    ~id=[@ns.namedArgLoc] Internal.toBeltComparator(comparator),
    [|element|],
  );
let fromArray =
    (elements: array('a), comparator: TableclothComparator.s('a, 'identity))
    : t('a, 'identity) =>
  Belt.Set.fromArray(
    ~id=[@ns.namedArgLoc] Internal.toBeltComparator(comparator),
    elements,
  );
let fromList =
    (elements: list('a), comparator: TableclothComparator.s('a, 'identity))
    : t('a, 'identity) =>
  Belt.Set.fromArray(
    ~id=[@ns.namedArgLoc] Internal.toBeltComparator(comparator),
    Array.of_list(elements),
  );
let length = t => Belt.Set.size(t);
let isEmpty = t => Belt.Set.isEmpty(t);
let includes = (t, a) => Belt.Set.has(t, a);
let add = (t, a) => Belt.Set.add(t, a);
let remove = (t, a) => Belt.Set.remove(t, a);
let difference = (t, a) => Belt.Set.diff(t, a);
let intersection = (t, a) => Belt.Set.intersect(t, a);
let union = (t, a) => Belt.Set.union(t, a);
let filter = (s, ~f as [@ns.namedArgLoc] f) => Belt.Set.keep(s, a => f(a));
let partition = (s, ~f as [@ns.namedArgLoc] f) =>
  Belt.Set.partition(s, a => f(a));
let find = (s, ~f as [@ns.namedArgLoc] f) =>
  Belt.Set.toArray(s)->(Belt.Array.getBy(a => f(a)));
let all = (s, ~f as [@ns.namedArgLoc] f) => Belt.Set.every(s, a => f(a));
let any = (s, ~f as [@ns.namedArgLoc] f) => Belt.Set.some(s, a => f(a));
let forEach = (s, ~f as [@ns.namedArgLoc] f) =>
  Belt.Set.forEach(s, a => f(a));
let fold =
    (s, ~initial as [@ns.namedArgLoc] initial, ~f as [@ns.namedArgLoc] f) =>
  Belt.Set.reduce(s, initial, (a, b) => f(a, b));
let toArray = t => Belt.Set.toArray(t);
let toList = t => Belt.Set.toList(t);
module Poly = {
  type nonrec identity;
  type nonrec t('a) = t('a, identity);
  let fromArray = (type a, a: array(a)): t(a) =>
    Belt.Set.fromArray(
      a,
      ~id=
        [@ns.namedArgLoc]
        (module
         {
           type nonrec t = a;
           type nonrec identity = identity;
           let cmp = Obj.magic(Stdlib.compare);
         }),
    );
  let fromList = l => fromArray(Array.of_list(l));
  let empty = () => fromArray([||]);
  let singleton = a => fromArray([|a|]);
};
module Int = {
  type nonrec identity;
  type nonrec t = t(TableclothInt.t, identity);
  let fromArray = a => Obj.magic(Poly.fromArray(a));
  let empty = fromArray([||]);
  let singleton = a => fromArray([|a|]);
  let fromList = l => fromArray(Array.of_list(l));
};
module String = {
  type nonrec identity;
  type nonrec t = t(TableclothString.t, identity);
  let fromArray = a => Obj.magic(Poly.fromArray(a));
  let empty = fromArray([||]);
  let singleton = a => fromArray([|a|]);
  let fromList = l => fromArray(Array.of_list(l));
};

module Option = TableclothOption;
type nonrec t('key, 'value, 'cmp) = Belt.Map.t('key, 'value, 'cmp);
let fromArray =
    (
      comparator: TableclothComparator.s('key, 'id),
      values: array(('key, 'v)),
    )
    : t('key, 'value, 'id) =>
  Belt.Map.fromArray(
    values,
    ~id=[@ns.namedArgLoc] Internal.toBeltComparator(comparator),
  );
let empty = comparator => fromArray(comparator, [||]);
let fromList = (comparator, l) => fromArray(comparator, Array.of_list(l));
let singleton =
    (
      comparator,
      ~key as [@ns.namedArgLoc] key,
      ~value as [@ns.namedArgLoc] value,
    ) =>
  fromArray(comparator, [|(key, value)|]);
let isEmpty = t => Belt.Map.isEmpty(t);
let includes = (t, k) => Belt.Map.has(t, k);
let length = t => Belt.Map.size(t);
let add =
    (m, ~key as [@ns.namedArgLoc] key, ~value as [@ns.namedArgLoc] value) =>
  Belt.Map.set(m, key, value);
let remove = (t, k) => Belt.Map.remove(t, k);
let get = (t, k) => Belt.Map.get(t, k);
let update = (m, ~key as [@ns.namedArgLoc] key, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.update(m, key, a => f(a));
let merge = (m1, m2, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.merge(m1, m2, (m, a, b) => f(m, a, b));
let map = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.map(m, value => f(value));
let mapWithIndex = (t, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.mapWithKey(t, (a, b) => f(a, b));
let filter = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.keep(m, (_, value) => f(value));
let filterMap = (m, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let f' = ((key, value)) =>
      f(~key=[@ns.namedArgLoc] key, ~value=[@ns.namedArgLoc] value)
      ->(Belt.Option.map(value' => (key, value')));
    m
    ->Belt.Map.toArray
    ->(Belt.Array.keepMap(f'))
    ->(Belt.Map.fromArray(~id=[@ns.namedArgLoc] Belt.Map.getId(m)));
  };
let partition = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.partition(m, (key, value) =>
    f(~key=[@ns.namedArgLoc] key, ~value=[@ns.namedArgLoc] value)
  );
let find = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.findFirstBy(m, (key, value) =>
    f(~key=[@ns.namedArgLoc] key, ~value=[@ns.namedArgLoc] value)
  );
let any = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.some(m, (_, value) => f(value));
let all = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.every(m, (_, value) => f(value));
let forEach = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.forEach(m, (_, value) => f(value));
let forEachWithIndex = (m, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.forEach(m, (key, value) =>
    f(~key=[@ns.namedArgLoc] key, ~value=[@ns.namedArgLoc] value)
  );
let fold =
    (m, ~initial as [@ns.namedArgLoc] initial, ~f as [@ns.namedArgLoc] f) =>
  Belt.Map.reduce(m, initial, (acc, key, data) =>
    f(acc, ~key=[@ns.namedArgLoc] key, ~value=[@ns.namedArgLoc] data)
  );
let keys = m => Array.to_list(Belt.Map.keysToArray(m));
let values = m => Array.to_list(Belt.Map.valuesToArray(m));
let maximum = t => Belt.Map.maxKey(t);
let minimum = t => Belt.Map.minKey(t);
let extent = t => Option.both(minimum(t), maximum(t));
let toArray = t => Belt.Map.toArray(t);
let toList = t => Belt.Map.toList(t);
module Poly = {
  type nonrec identity;
  type nonrec t('k, 'v) = t('k, 'v, identity);
  let fromArray = (type k, type v, a: array((k, v))): t(k, v) =>
    Belt.Map.fromArray(
      a,
      ~id=
        [@ns.namedArgLoc]
        (module
         {
           type nonrec t = k;
           type nonrec identity = identity;
           let cmp = Obj.magic(Pervasives.compare);
         }),
    );
  let empty = () => fromArray([||]);
  let fromList = l => fromArray(Array.of_list(l));
  let singleton =
      (~key as [@ns.namedArgLoc] key, ~value as [@ns.namedArgLoc] value) =>
    fromArray([|(key, value)|]);
};
module Int = {
  type nonrec identity;
  type nonrec t('value) = t(TableclothInt.t, 'value, identity);
  let fromArray = a => Obj.magic(Poly.fromArray(a));
  let empty = fromArray([||]);
  let singleton =
      (~key as [@ns.namedArgLoc] key, ~value as [@ns.namedArgLoc] value) =>
    fromArray([|(key, value)|]);
  let fromList = l => fromArray(Array.of_list(l));
};
module String = {
  type nonrec identity;
  type nonrec t('value) = t(TableclothString.t, 'value, identity);
  let fromArray = a => Obj.magic(Poly.fromArray(a));
  let empty = fromArray([||]);
  let singleton =
      (~key as [@ns.namedArgLoc] key, ~value as [@ns.namedArgLoc] value) =>
    fromArray([|(key, value)|]);
  let fromList = l => fromArray(Array.of_list(l));
};

type nonrec t('a) = option('a);
let some = a => Some(a);
let isSome = t => Belt.Option.isSome(t);
let isNone = t => Belt.Option.isNone(t);
let or_ = (ta, tb) =>
  [@ns.ternary]
  (
    if (isSome(ta)) {
      ta;
    } else {
      tb;
    }
  );
let orElse = (ta, tb) =>
  [@ns.ternary]
  (
    if (isSome(tb)) {
      tb;
    } else {
      ta;
    }
  );
let and_ = (ta, tb) =>
  [@ns.ternary]
  (
    if (isSome(ta)) {
      tb;
    } else {
      ta;
    }
  );
let andThen = (t, ~f as [@ns.namedArgLoc] f) =>
  switch (t) {
  | None => None
  | Some(x) => f(x)
  };
let flatten = x =>
  switch (x) {
  | Some(option) => option
  | None => None
  };
let both = (a, b) =>
  switch (a, b) {
  | (Some(a), Some(b)) => Some((a, b))
  | _ => None
  };
let map = (t, ~f as [@ns.namedArgLoc] f) => Belt.Option.map(t, a => f(a));
let map2 = (a, b, ~f as [@ns.namedArgLoc] f) =>
  switch (a, b) {
  | (Some(a), Some(b)) => Some(f(a, b))
  | _ => None
  };
let unwrap = (t, ~default as [@ns.namedArgLoc] default) =>
  Belt.Option.getWithDefault(t, default);
let unwrapOrFailWith = (t, ~exn as [@ns.namedArgLoc] exn) =>
  switch (t) {
  | Some(value) => value
  | None => raise(exn)
  };
let unwrapUnsafe = t =>
  unwrapOrFailWith(
    ~exn=
      [@ns.namedArgLoc]
      Invalid_argument("Option.unwrapUnsafe called with None"),
    t,
  );
let toArray = t =>
  switch (t) {
  | None => [||]
  | Some(value) => [|value|]
  };
let toList = t =>
  switch (t) {
  | None => []
  | Some(value) => [value]
  };
let tap = (t, ~f as [@ns.namedArgLoc] f) =>
  switch (t) {
  | None => ()
  | Some(x) => f(x)
  };
let equal = (a, b, equal) =>
  switch (a, b) {
  | (None, None) => true
  | (Some(a'), Some(b')) => equal(a', b')
  | _ => false
  };
let compare = (a, b, ~f as [@ns.namedArgLoc] compare) =>
  switch (a, b) {
  | (None, None) => 0
  | (Some(a'), Some(b')) => compare(a', b')
  | (None, Some(_)) => (-1)
  | (Some(_), None) => 1
  };

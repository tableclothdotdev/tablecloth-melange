type nonrec t = int;
include TableclothComparator.Make({
  type nonrec t = t;
  let compare = (a, b) => compare(a, b);
});
let minimumValue = Js.Int.min;
let maximumValue = Js.Int.max;
let zero = 0;
let one = 1;
let fromString = s =>
  switch (int_of_string(s)) {
  | i => Some(i)
  | exception (Failure(_)) => None
  };
let add = (+);
let subtract = (-);
let multiply = ( * );
let divide = (n, ~by as [@ns.namedArgLoc] by) => n / by;
let divideFloat = (n, ~by as [@ns.namedArgLoc] by) =>
  Js.Int.toFloat(n) /. Js.Int.toFloat(by);
let power =
    (~base as [@ns.namedArgLoc] base, ~exponent as [@ns.namedArgLoc] exponent) =>
  [@ns.braces]
  {
    let result =
      Js.Math.pow_float(
        ~base=[@ns.namedArgLoc] Js.Int.toFloat(base),
        ~exp=[@ns.namedArgLoc] Js.Int.toFloat(exponent),
      );
    let result =
      if (result > TableclothFloat.maximumSafeInteger) {
        TableclothFloat.maximumSafeInteger;
      } else if (result < TableclothFloat.minimumSafeInteger) {
        TableclothFloat.minimumSafeInteger;
      } else {
        result;
      };
    Js.Math.unsafe_trunc(result);
  };
let negate = (~-);
let remainder = (n, ~by as [@ns.namedArgLoc] by) => n mod by;
let modulo = (n, ~by as [@ns.namedArgLoc] by) =>
  (
    if (n <= 0) {
      abs(n) * 2;
    } else {
      n;
    }
  )
  mod by;
let maximum = (a, b) => Js.Math.max_int(a, b);
let minimum = (a, b) => Js.Math.min_int(a, b);
let absolute = abs;
let isEven = n => n mod 2 == 0;
let isOdd = n => n mod 2 != 0;
let clamp =
    (n, ~lower as [@ns.namedArgLoc] lower, ~upper as [@ns.namedArgLoc] upper) =>
  if (upper < lower) {
    raise(Invalid_argument("~lower must be less than or equal to ~upper"));
  } else {
    max(lower, min(upper, n));
  };
let inRange =
    (n, ~lower as [@ns.namedArgLoc] lower, ~upper as [@ns.namedArgLoc] upper) =>
  if (upper < lower) {
    raise(Invalid_argument("~lower must be less than or equal to ~upper"));
  } else {
    n >= lower && n < upper;
  };
let toFloat = t => Js.Int.toFloat(t);
let toString = t => Js.Int.toString(t);
let equal = (==);
let compare = compare;

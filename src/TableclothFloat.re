type nonrec t = float;
let fromInt = t => Js.Int.toFloat(t);
let fromString = string =>
  switch (String.lowercase_ascii(string)) {
  | "nan" => Some(Js.Float._NaN)
  | _ =>
    switch (Js.Float.fromString(string)) {
    | result when Js.Float.isNaN(result) => None
    | result => Some(result)
    }
  };
let add = (+.);
let subtract = (-.);
let multiply = ( *. );
let divide = (n, ~by as [@ns.namedArgLoc] by) => n /. by;
let power =
    (~base as [@ns.namedArgLoc] base, ~exponent as [@ns.namedArgLoc] exponent) =>
  Js.Math.pow_float(~base=[@ns.namedArgLoc] base, ~exp=[@ns.namedArgLoc] exponent);
let negate = (~-.);
let absolute = t => Js.Math.abs_float(t);
let clamp =
    (n, ~lower as [@ns.namedArgLoc] lower, ~upper as [@ns.namedArgLoc] upper) =>
  if (upper < lower) {
    raise(
      Invalid_argument(
        "~lower:"
        ++ Js.Float.toString(lower)
        ++ " must be less than or equal to ~upper:"
        ++ Js.Float.toString(upper),
      ),
    );
  } else if (Js.Float.isNaN(lower)
             || Js.Float.isNaN(upper)
             || Js.Float.isNaN(n)) {
    nan;
  } else {
    max(lower, min(upper, n));
  };
let inRange =
    (n, ~lower as [@ns.namedArgLoc] lower, ~upper as [@ns.namedArgLoc] upper) =>
  if (upper < lower) {
    raise(
      Invalid_argument(
        "~lower:"
        ++ Js.Float.toString(lower)
        ++ " must be less than or equal to ~upper:"
        ++ Js.Float.toString(upper),
      ),
    );
  } else {
    n >= lower && n < upper;
  };
let squareRoot = sqrt;
let log = (n, ~base as [@ns.namedArgLoc] base) =>
  Js.Math.log(n) /. Js.Math.log(base);
let zero = 0.0;
let one = 1.0;
let nan = Js.Float._NaN;
let infinity = infinity;
let negativeInfinity = neg_infinity;
let e = Js.Math._E;
let pi = Js.Math._PI;
let epsilon = epsilon_float;
[@scope "Number"] external largestValue: t = "MAX_VALUE";
[@scope "Number"] external smallestValue: t = "MIN_VALUE";
[@scope "Number"] external maximumSafeInteger: t = "MAX_SAFE_INTEGER";
[@scope "Number"] external minimumSafeInteger: t = "MIN_SAFE_INTEGER";
let isNaN = t => Js.Float.isNaN(t);
let isFinite = t => Js.Float.isFinite(t);
let isInfinite = n => !Js.Float.isFinite(n) && !isNaN(n);
[@scope "Number"] external isInteger: t => bool = "isInteger";
[@scope "Number"] external isSafeInteger: t => bool = "isSafeInteger";
let maximum = (x, y) =>
  if (isNaN(x) || isNaN(y)) {
    nan;
  } else if (y > x) {
    y;
  } else {
    x;
  };
let minimum = (x, y) =>
  if (isNaN(x) || isNaN(y)) {
    nan;
  } else if (y < x) {
    y;
  } else {
    x;
  };
let hypotenuse = (a, b) => Js.Math.hypot(a, b);
type nonrec radians = float;
let degrees = n => n *. (pi /. 180.0);
external radians: float => float = "%identity";
let turns = n => n *. 2. *. pi;
let cos = t => Js.Math.cos(t);
let acos = t => Js.Math.acos(t);
let sin = t => Js.Math.sin(t);
let asin = t => Js.Math.asin(t);
let tan = t => Js.Math.tan(t);
let atan = t => Js.Math.atan(t);
let atan2 = (~y as [@ns.namedArgLoc] y, ~x as [@ns.namedArgLoc] x) =>
  Js.Math.atan2(~y=[@ns.namedArgLoc] y, ~x=[@ns.namedArgLoc] x, ());
type nonrec direction = [
  | `Zero
  | `AwayFromZero
  | `Up
  | `Down
  | `Closest([ | `Zero | `AwayFromZero | `Up | `Down | `ToEven])
];
let round = (~direction as [@ns.namedArgLoc] direction=`Closest(`Up), n) =>
  switch (direction) {
  | `Up => Js.Math.ceil_float(n)
  | `Down => Js.Math.floor_float(n)
  | `Zero => Js.Math.trunc(n)
  | `AwayFromZero =>
    if (n > 0.) {
      Js.Math.ceil_float(n);
    } else {
      Js.Math.floor_float(n);
    }
  | `Closest(`Zero) =>
    if (n > 0.) {
      Js.Math.ceil_float(n -. 0.5);
    } else {
      Js.Math.floor_float(n +. 0.5);
    }
  | `Closest(`AwayFromZero) =>
    if (n > 0.) {
      Js.Math.floor_float(n +. 0.5);
    } else {
      Js.Math.ceil_float(n -. 0.5);
    }
  | `Closest(`Down) => Js.Math.ceil_float(n -. 0.5)
  | `Closest(`Up) => Js.Math.round(n)
  | `Closest(`ToEven) =>
    let roundNearestLowerBound = -. (2. ** 52.);
    let roundNearestUpperBound = 2. ** 52.;
    if (n <= roundNearestLowerBound || n >= roundNearestUpperBound) {
      n +. 0.;
    } else {
      let floor = floor(n);
      let ceil_or_succ = floor +. 1.;
      let diff_floor = n -. floor;
      let diff_ceil = ceil_or_succ -. n;
      if (diff_floor < diff_ceil) {
        floor;
      } else if (diff_floor > diff_ceil) {
        ceil_or_succ;
      } else if (mod_float(floor, 2.) == 0.) {
        floor;
      } else {
        ceil_or_succ;
      };
    };
  };
let floor = t => Js.Math.floor_float(t);
let ceiling = t => Js.Math.ceil_float(t);
let truncate = t => Js.Math.trunc(t);
let fromPolar = ((r, theta)) => (r *. cos(theta), r *. sin(theta));
let toPolar = ((x, y)) => (
  hypotenuse(x, y),
  atan2(~x=[@ns.namedArgLoc] x, ~y=[@ns.namedArgLoc] y),
);
let toInt = f =>
  if (Js.Float.isFinite(f)) {
    Some(Js.Math.unsafe_trunc(f));
  } else {
    None;
  };
let toString = t => Js.Float.toString(t);
let equal = (==);
let compare = (a, b) => compare(a, b);

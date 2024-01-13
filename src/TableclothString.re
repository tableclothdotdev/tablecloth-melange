type nonrec t = string;
include TableclothComparator.Make({
  type nonrec t = t;
  let compare = (a, b) => compare(a, b);
});
let initialize = (length, ~f as [@ns.namedArgLoc] f) =>
  Js.Array.joinWith(
    "",
    Array.init(length, index => TableclothChar.toString(f(index))),
  );
let get = (string: string, index: int) => string.[index];
let getAt = (string: string, ~index as [@ns.namedArgLoc] (index: int)) =>
  if (index < 0 || index >= Js.String.length(string)) {
    None;
  } else {
    Some(string.[index]);
  };
let fromArray = characters =>
  Js.Array.joinWith(
    "",
    Array.map(
      character => Js.String.fromCharCode(TableclothChar.toCode(character)),
      characters,
    ),
  );
let fromList = t =>
  Js.Array.joinWith(
    "",
    Array.map(
      character => Js.String.fromCharCode(TableclothChar.toCode(character)),
      Array.of_list(t),
    ),
  );
let fromChar = c => Js.String.fromCharCode(TableclothChar.toCode(c));
let indexOf = (haystack, needle): option(int) =>
  [@ns.braces]
  {
    let result = Js.String.indexOf(needle, haystack);
    if (result == (-1)) {
      None;
    } else {
      Some(result);
    };
  };
let indexOfRight = (haystack, needle): option(int) =>
  [@ns.braces]
  {
    let result = Js.String.lastIndexOf(needle, haystack);
    if (result == (-1)) {
      None;
    } else {
      Some(result);
    };
  };
let isEmpty = t => t == "";
let length = t => Js.String.length(t);
let uncons = s =>
  switch (s) {
  | "" => None
  | s => Some((s.[0], String.sub(s, 1, Js.String.length(s) - 1)))
  };
let dropLeft = (s, ~count as [@ns.namedArgLoc] count) =>
  Js.String.substr(~from=[@ns.namedArgLoc] count, s);
let dropRight = (s, ~count as [@ns.namedArgLoc] count) =>
  if (count < 1) {
    s;
  } else {
    Js.String.slice(
      ~from=[@ns.namedArgLoc] 0,
      ~to_=[@ns.namedArgLoc] (- count),
      s,
    );
  };
let split = (t, ~on as [@ns.namedArgLoc] on) =>
  Array.to_list(Js.String.split(on, t));
let endsWith = (t, ~suffix as [@ns.namedArgLoc] suffix) =>
  Js.String.endsWith(suffix, t);
let startsWith = (t, ~prefix as [@ns.namedArgLoc] prefix) =>
  Js.String.startsWith(prefix, t);
let trim = t => Js.String.trim(t);
[@send] external trimLeft: string => string = "trimStart";
[@send] external trimRight: string => string = "trimEnd";
[@send] external padLeft: (string, int, string) => string = "padStart";
let padLeft = (string, count, ~with_ as [@ns.namedArgLoc] with_) =>
  padLeft(string, count, with_);
[@send] external padRight: (string, int, string) => string = "padEnd";
let padRight = (string, count, ~with_ as [@ns.namedArgLoc] with_) =>
  padRight(string, count, with_);
let toLowercase = t => Js.String.toLowerCase(t);
let toUppercase = t => Js.String.toUpperCase(t);
let uncapitalize = str =>
  Js.String.toLowerCase(Js.String.charAt(0, str))
  ++ Js.String.sliceToEnd(~from=[@ns.namedArgLoc] 1, str);
let capitalize = str =>
  Js.String.toUpperCase(Js.String.charAt(0, str))
  ++ Js.String.sliceToEnd(~from=[@ns.namedArgLoc] 1, str);
let isCapitalized = s => s == capitalize(s);
let includes = (t, ~substring as [@ns.namedArgLoc] substring) =>
  Js.String.includes(substring, t);
let repeat = (s, ~count as [@ns.namedArgLoc] count) =>
  Js.String.repeat(count, s);
let reverse = s =>
  Js.Array.joinWith("", Js.Array.reverseInPlace(Js.String.split("", s)));
let toArray = (t: string): array(char) =>
  Js.Array.map(
    characterString =>
      Belt.Option.getExn(TableclothChar.fromString(characterString)),
    Js.Array.from(Js.String.castToArrayLike(t)),
  );
let toList = (s: string): list(char) => Belt.List.fromArray(toArray(s));
let slice =
    (
      ~to_ as [@ns.namedArgLoc] to_=?,
      t: string,
      ~from as [@ns.namedArgLoc] from,
    )
    : string =>
  Js.String.slice(
    ~[@ns.namedArgLoc] from,
    ~to_=[@ns.namedArgLoc] Belt.Option.getWithDefault(to_, length(t)),
    t,
  );
let insertAt =
    (t, ~index as [@ns.namedArgLoc] index, ~value as [@ns.namedArgLoc] value) =>
  Js.String.slice(~from=[@ns.namedArgLoc] 0, ~to_=[@ns.namedArgLoc] index, t)
  ++ value
  ++ Js.String.sliceToEnd(~from=[@ns.namedArgLoc] index, t);
let forEach = (t, ~f as [@ns.namedArgLoc] f) =>
  Js.Array.forEach(a => f(a), toArray(t));
let fold =
    (t, ~initial as [@ns.namedArgLoc] initial, ~f as [@ns.namedArgLoc] f) =>
  Belt.Array.reduce(toArray(t), initial, (a, ch) => f(a, ch));
let equal = (==);
let compare = compare;

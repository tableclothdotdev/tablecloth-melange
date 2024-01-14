type nonrec t('a) = array('a);
let singleton = a => [|a|];
let clone = t => Array.map(TableclothFun.identity, t);
let length = t => Belt.Array.length(t);
let isEmpty = a => length(a) == 0;
let initialize = (length, ~f as [@ns.namedArgLoc] f) =>
  Belt.Array.makeBy(length, a => f(a));
let range = (~from as [@ns.namedArgLoc] from=0, to_) =>
  Belt.Array.makeBy(to_ - from, i => i + from);
let fromList = t => Belt.List.toArray(t);
let toList: array('a) => list('a) = (
  t => Belt.List.fromArray(t): array('a) => list('a)
);
let toIndexedList = (array: array('a)): list((int, 'a)) =>
  snd(
    Belt.Array.reduceReverse(array, (length(array) - 1, []), ((i, acc), x) =>
      (i - 1, [(i, x), ...acc])
    ),
  );
let get = (t, k) => Belt.Array.getExn(t, k);
let getAt = (t, ~index as [@ns.namedArgLoc] index) =>
  Belt.Array.get(t, index);
let first = t => getAt(t, ~index=[@ns.namedArgLoc] 0);
let last = t => getAt(t, ~index=[@ns.namedArgLoc] (Array.length(t) - 1));
let set = (t, index, value) => t[index] = value;
let setAt =
    (t, ~index as [@ns.namedArgLoc] index, ~value as [@ns.namedArgLoc] value) =>
  t[index] = value;
let filter = (t, ~f as [@ns.namedArgLoc] f) => Belt.Array.keep(t, a => f(a));
let swap = (t, i, j) =>
  [@ns.braces]
  {
    let temp = t[i];
    t[i] = t[j];
    t[j] = temp;
    ();
  };
let fold =
    (t, ~initial as [@ns.namedArgLoc] initial, ~f as [@ns.namedArgLoc] f) =>
  Belt.Array.reduce(t, initial, (a, b) => f(a, b));
let foldRight =
    (t, ~initial as [@ns.namedArgLoc] initial, ~f as [@ns.namedArgLoc] f) =>
  Belt.Array.reduceReverse(t, initial, (a, b) => f(a, b));
let maximum = (t, ~compare as [@ns.namedArgLoc] compare) =>
  fold(
    t, ~initial=[@ns.namedArgLoc] None, ~f=[@ns.namedArgLoc] (max, element) =>
    switch (max) {
    | None => Some(element)
    | Some(current) =>
      [@ns.ternary]
      (
        if (compare(element, current) > 0) {
          Some(element);
        } else {
          max;
        }
      )
    }
  );
let minimum = (t, ~compare as [@ns.namedArgLoc] compare) =>
  fold(
    t, ~initial=[@ns.namedArgLoc] None, ~f=[@ns.namedArgLoc] (min, element) =>
    switch (min) {
    | None => Some(element)
    | Some(current) =>
      [@ns.ternary]
      (
        if (compare(element, current) < 0) {
          Some(element);
        } else {
          min;
        }
      )
    }
  );
let extent = (t, ~compare as [@ns.namedArgLoc] compare) =>
  fold(
    t, ~initial=[@ns.namedArgLoc] None, ~f=[@ns.namedArgLoc] (range, element) =>
    switch (range) {
    | None => Some((element, element))
    | Some((min, max)) =>
      Some((
        [@ns.ternary]
        (
          if (compare(element, min) < 0) {
            element;
          } else {
            min;
          }
        ),
        [@ns.ternary]
        (
          if (compare(element, max) > 0) {
            element;
          } else {
            max;
          }
        ),
      ))
    }
  );
let sum = (type a, t, module M: TableclothContainer.Sum with type t = a): a =>
  Array.fold_left(M.add, M.zero, t);
let map = (t, ~f as [@ns.namedArgLoc] f) => Belt.Array.map(t, a => f(a));
let mapWithIndex = (t, ~f as [@ns.namedArgLoc] f) =>
  Belt.Array.mapWithIndex(t, (a, i) => f(a, i));
let map2 = (a, b, ~f as [@ns.namedArgLoc] (f: ('a, 'b) => 'c)): array('c) =>
  Belt.Array.zipBy(a, b, f);
let map3 = (as_, bs, cs: t('c), ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let minLength =
      Belt.Array.reduce([|length(bs), length(cs)|], length(as_), min);
    Belt.Array.makeBy(minLength, i => f(as_[i], bs[i], cs[i]));
  };
let zip = (a, b) => map2(a, b, ~f=[@ns.namedArgLoc] (a, b) => (a, b));
let flatMap = (t, ~f as [@ns.namedArgLoc] f) =>
  Belt.Array.concatMany(Belt.Array.map(t, a => f(a)));
let sliding =
    (~step as [@ns.namedArgLoc] step=1, a, ~size as [@ns.namedArgLoc] size) =>
  [@ns.braces]
  {
    let n = Array.length(a);
    if (size > n) {
      [||];
    } else {
      initialize(1 + (n - size) / step, ~f=[@ns.namedArgLoc] i =>
        initialize(size, ~f=[@ns.namedArgLoc] j => a[i * step + j])
      );
    };
  };
let find = (t, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let rec find_loop =
            (
              t,
              ~f as [@ns.namedArgLoc] f,
              ~length as [@ns.namedArgLoc] length,
              i,
            ) =>
      if (i >= length) {
        None;
      } else if (f(t[i])) {
        Some(t[i]);
      } else {
        find_loop(t, ~f=[@ns.namedArgLoc] f, ~length=[@ns.namedArgLoc] length, i + 1);
      };
    find_loop(
      t,
      ~f=[@ns.namedArgLoc] f,
      ~length=[@ns.namedArgLoc] length(t),
      0,
    );
  };
let findIndex = (array, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let rec loop = index =>
      if (index >= length(array)) {
        None;
      } else if (f(index, array[index])) {
        Some((index, array[index]));
      } else {
        loop(index + 1);
      };
    loop(0);
  };
let any = (t, ~f as [@ns.namedArgLoc] f) => Belt.Array.some(t, a => f(a));
let all = (t, ~f as [@ns.namedArgLoc] f) => Belt.Array.every(t, a => f(a));
let includes = (t, v, ~equal as [@ns.namedArgLoc] equal) =>
  any(t, ~f=[@ns.namedArgLoc] a => equal(v, a));
let append = (a, a') => Belt.Array.concat(a, a');
let flatten = (ars: array(array('a))) => Belt.Array.concatMany(ars);
let intersperse = (t, ~sep as [@ns.namedArgLoc] sep) =>
  Belt.Array.makeBy(max(0, length(t) * 2 - 1), i =>
    if (i mod 2 != 0) {
      sep;
    } else {
      t[i / 2];
    }
  );
let slice =
    (~to_ as [@ns.namedArgLoc] to_=?, array, ~from as [@ns.namedArgLoc] from) =>
  [@ns.braces]
  {
    let defaultTo =
      switch (to_) {
      | None => length(array)
      | Some(i) => i
      };
    let sliceFrom =
      if (from >= 0) {
        min(length(array), from);
      } else {
        max(0, min(length(array), length(array) + from));
      };
    let sliceTo =
      if (defaultTo >= 0) {
        min(length(array), defaultTo);
      } else {
        max(0, min(length(array), length(array) + defaultTo));
      };
    if (sliceFrom >= sliceTo) {
      [||];
    } else {
      Belt.Array.makeBy(sliceTo - sliceFrom, i => array[i + sliceFrom]);
    };
  };
let count = (t, ~f as [@ns.namedArgLoc] f) =>
  fold(t, ~initial=[@ns.namedArgLoc] 0, ~f=[@ns.namedArgLoc] (total, element) =>
    total
    + [@ns.ternary]
      (
        if (f(element)) {
          1;
        } else {
          0;
        }
      )
  );
let chunksOf = (t, ~size as [@ns.namedArgLoc] size) =>
  sliding(t, ~step=[@ns.namedArgLoc] size, ~size=[@ns.namedArgLoc] size);
let reverse = t => Belt.Array.reverseInPlace(t);
let forEach = (t, ~f as [@ns.namedArgLoc] f): unit =>
  Belt.Array.forEach(t, a => f(a));
let forEachWithIndex = (t, ~f as [@ns.namedArgLoc] f): unit =>
  for (i in 0 to length(t) - 1) {
    f(i, t[i]);
  };
let partition = (t, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let (left, right) =
      foldRight(
        t,
        ~initial=[@ns.namedArgLoc] ([], []),
        ~f=[@ns.namedArgLoc] ((lefts, rights), element) =>
        if (f(element)) {
          ([element, ...lefts], rights);
        } else {
          (lefts, [element, ...rights]);
        }
      );
    (fromList(left), fromList(right));
  };
let splitAt = (t, ~index as [@ns.namedArgLoc] index) => (
  slice(t, ~from=[@ns.namedArgLoc] 0, ~to_=[@ns.namedArgLoc] index),
  slice(t, ~from=[@ns.namedArgLoc] index, ~to_=[@ns.namedArgLoc] length(t)),
);
let splitWhen = (t, ~f as [@ns.namedArgLoc] f) =>
  switch (findIndex(t, ~f=[@ns.namedArgLoc] (_, e) => f(e))) {
  | None => (t, [||])
  | Some((index, _)) => splitAt(t, ~index=[@ns.namedArgLoc] index)
  };
let unzip = t => (
  Array.init(length(t), i => fst(t[i])),
  Array.init(length(t), i => snd(t[i])),
);
let repeat = (element, ~length as [@ns.namedArgLoc] length) =>
  Array.init(max(length, 0), _ => element);
let filterMap = (t, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let result =
      fold(
        t,
        ~initial=[@ns.namedArgLoc] [],
        ~f=[@ns.namedArgLoc] (results, element) =>
        switch (f(element)) {
        | None => results
        | Some(value) => [value, ...results]
        }
      )
      ->fromList;
    reverse(result);
    result;
  };
let sort = (a, ~compare as [@ns.namedArgLoc] compare) =>
  Array.sort((a, b) => compare(a, b), a);
let values = t =>
  [@ns.braces]
  {
    let result =
      fold(
        t,
        ~initial=[@ns.namedArgLoc] [],
        ~f=[@ns.namedArgLoc] (results, element) =>
        switch (element) {
        | None => results
        | Some(value) => [value, ...results]
        }
      )
      ->fromList;
    reverse(result);
    result;
  };
let join = (t, ~sep as [@ns.namedArgLoc] sep) => Js.Array.joinWith(sep, t);
let groupBy = (t, comparator, ~f as [@ns.namedArgLoc] f) =>
  fold(
    t,
    ~initial=[@ns.namedArgLoc] TableclothMap.empty(comparator),
    ~f=[@ns.namedArgLoc] (map, element) =>
    [@ns.braces]
    {
      let key = f(element);
      TableclothMap.update(map, ~key=[@ns.namedArgLoc] key, ~f=[@ns.namedArgLoc] x =>
        switch (x) {
        | None => Some([element])
        | Some(elements) => Some([element, ...elements])
        }
      );
    }
  );
let equal = (a, b, equal) =>
  if (length(a) != length(b)) {
    false;
  } else if (length(a) == 0) {
    true;
  } else {
    let rec loop = index =>
      if (index == length(a)) {
        true;
      } else {
        equal(a[index], b[index]) && loop(index + 1);
      };
    loop(0);
  };
let compare = (a, b, compare) =>
  switch (TableclothInt.compare(length(a), length(b))) {
  | 0 =>
    if (length(a) === 0) {
      0;
    } else {
      let rec loop = index =>
        if (index == length(a)) {
          0;
        } else {
          switch (compare(a[index], b[index])) {
          | 0 => loop(index + 1)
          | result => result
          };
        };
      loop(0);
    }
  | result => result
  };

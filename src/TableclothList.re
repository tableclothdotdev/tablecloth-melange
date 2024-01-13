type nonrec t('a) = list('a);
let empty = [];
let singleton = x => [x];
let fromArray = array => List.init(Array.length(array), i => array[i]);
let range = (~from as [@ns.namedArgLoc] from=0, to_) =>
  if (to_ < from) {
    [];
  } else {
    List.init(to_ - from, i => i + from);
  };
let rec repeat = (element, ~times as [@ns.namedArgLoc] times) =>
  if (times <= 0) {
    [];
  } else {
    [element, ...repeat(element, ~times=[@ns.namedArgLoc] (times - 1))];
  };
let flatten = t => Belt.List.flatten(t);
let reverse = t => Belt.List.reverse(t);
let append = (a, b) => Belt.List.concat(a, b);
let sum = (type a, t, module M: TableclothContainer.Sum with type t = a) =>
  List.fold_left(M.add, M.zero, t);
let map = (t, ~f as [@ns.namedArgLoc] f) => Belt.List.map(t, a => f(a));
let flatMap = (t, ~f as [@ns.namedArgLoc] f) =>
  flatten(map(t, ~[@ns.namedArgLoc] f));
let mapWithIndex = (list, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.mapWithIndex(list, (a, b) => f(a, b));
let map2 = (a, b, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.zipBy(a, b, (a, b) => f(a, b));
let zip = (a, b) => map2(a, b, ~f=[@ns.namedArgLoc] (a, b) => (a, b));
let rec map3 = (a, b, c, ~f as [@ns.namedArgLoc] f) =>
  switch (a, b, c) {
  | ([x, ...xs], [y, ...ys], [z, ...zs]) => [
      f(x, y, z),
      ...map3(xs, ys, zs, ~[@ns.namedArgLoc] f),
    ]
  | _ => []
  };
let rec last = l =>
  switch (l) {
  | [] => None
  | [x] => Some(x)
  | [_, ...rest] => last(rest)
  };
let unzip = list => (
  List.map(((a, _)) => a, list),
  List.map(((_, b)) => b, list),
);
let includes = (t, value, ~equal as [@ns.namedArgLoc] equal) =>
  Belt.List.has(t, value, (a, b) => equal(a, b));
let uniqueBy =
    (l: list('a), ~f as [@ns.namedArgLoc] (f: 'a => string)): list('a) =>
  [@ns.braces]
  {
    let rec uniqueHelper =
            (
              f: 'a => string,
              existing: Belt.Set.String.t,
              remaining: list('a),
              accumulator: list('a),
            ) =>
      switch (remaining) {
      | [] => reverse(accumulator)
      | [first, ...rest] =>
        let computedFirst = f(first);
        if (Belt.Set.String.has(existing, computedFirst)) {
          uniqueHelper(f, existing, rest, accumulator);
        } else {
          uniqueHelper(
            f,
            Belt.Set.String.add(existing, computedFirst),
            rest,
            [first, ...accumulator],
          );
        };
      };
    uniqueHelper(f, Belt.Set.String.empty, l, []);
  };
let find = (t, ~f as [@ns.namedArgLoc] f) => Belt.List.getBy(t, a => f(a));
let getAt = (t, ~index as [@ns.namedArgLoc] index) =>
  Belt.List.get(t, index);
let any = (t, ~f as [@ns.namedArgLoc] f) => List.exists(a => f(a), t);
let head = l => Belt.List.head(l);
let drop = (t, ~count as [@ns.namedArgLoc] count) =>
  switch (Belt.List.drop(t, count)) {
  | None =>
    if (count <= 0) {
      t;
    } else {
      [];
    }
  | Some(v) => v
  };
let take = (t, ~count as [@ns.namedArgLoc] count) =>
  switch (Belt.List.take(t, count)) {
  | None =>
    if (count <= 0) {
      [];
    } else {
      t;
    }
  | Some(v) => v
  };
let initial = l =>
  switch (reverse(l)) {
  | [] => None
  | [_, ...rest] => Some(reverse(rest))
  };
let filterMap = (t, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.keepMap(t, a => f(a));
let filter = (t, ~f as [@ns.namedArgLoc] f) => Belt.List.keep(t, a => f(a));
let filterWithIndex = (t, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.keepWithIndex(t, (e, i) => f(i, e));
let partition = (t, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.partition(t, a => f(a));
let fold =
    (t, ~initial as [@ns.namedArgLoc] initial, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.reduce(t, initial, (a, b) => f(a, b));
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
let foldRight =
    (t, ~initial as [@ns.namedArgLoc] initial, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.reduceReverse(t, initial, (a, b) => f(a, b));
let findIndex = (list, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let rec loop = (i, l) =>
      switch (l) {
      | [] => None
      | [x, ...rest] =>
        if (f(i, x)) {
          Some((i, x));
        } else {
          loop(i + 1, rest);
        }
      };
    loop(0, list);
  };
let splitAt = (t, ~index as [@ns.namedArgLoc] index) => (
  take(~count=[@ns.namedArgLoc] index, t),
  drop(~count=[@ns.namedArgLoc] index, t),
);
let updateAt:
  (t('a), ~index: [@ns.namedArgLoc] int, ~f: [@ns.namedArgLoc] ('a => 'a)) =>
  t('a) = (
  (t, ~index as [@ns.namedArgLoc] index, ~f as [@ns.namedArgLoc] f) =>
    Belt.List.mapWithIndex(t, (i, element) =>
      if (i == index) {
        f(element);
      } else {
        element;
      }
    ):
    (
      t('a),
      ~index: [@ns.namedArgLoc] int,
      ~f: [@ns.namedArgLoc] ('a => 'a)
    ) =>
    t('a)
);
let length = l => Belt.List.length(l);
let rec dropWhile = (t, ~f as [@ns.namedArgLoc] f) =>
  switch (t) {
  | [] => []
  | [x, ...rest] =>
    if (f(x)) {
      dropWhile(rest, ~[@ns.namedArgLoc] f);
    } else {
      t;
    }
  };
let isEmpty = t => t == [];
let sliding =
    (~step as [@ns.namedArgLoc] step=1, t, ~size as [@ns.namedArgLoc] size) =>
  [@ns.braces]
  {
    let rec loop = t =>
      if (isEmpty(t)) {
        [];
      } else {
        let sample = Belt.List.take(t, size);
        let rest = Belt.List.drop(t, step);
        switch (sample, rest) {
        | (None, _) => []
        | (Some(x), None) => [x]
        | (Some(x), Some(xs)) => [x, ...loop(xs)]
        };
      };
    loop(t);
  };
let chunksOf = (t, ~size as [@ns.namedArgLoc] size) =>
  sliding(t, ~step=[@ns.namedArgLoc] size, ~[@ns.namedArgLoc] size);
let cons = (t, element) => [element, ...t];
let takeWhile = (t, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let rec takeWhileHelper = (acc, t) =>
      switch (t) {
      | [] => reverse(acc)
      | [x, ...rest] =>
        if (f(x)) {
          takeWhileHelper([x, ...acc], rest);
        } else {
          reverse(acc);
        }
      };
    takeWhileHelper([], t);
  };
let all = (t, ~f as [@ns.namedArgLoc] f) => Belt.List.every(t, a => f(a));
let tail = t =>
  switch (t) {
  | [] => None
  | [_, ...rest] => Some(rest)
  };
let removeAt = (t, ~index as [@ns.namedArgLoc] index) =>
  if (index < 0) {
    t;
  } else {
    let (front, back): (t('a), t('a)) =
      splitAt(t, ~[@ns.namedArgLoc] index);
    switch (tail(back)) {
    | None => t
    | Some(t) => append(front, t)
    };
  };
let minimumBy =
    (~f as [@ns.namedArgLoc] (f: 'a => 'comparable), l: list('a))
    : option('a) =>
  [@ns.braces]
  {
    let minBy = ((y, fy), x) =>
      [@ns.braces]
      {
        let fx = f(x);
        if (fx < fy) {
          (x, fx);
        } else {
          (y, fy);
        };
      };
    switch (l) {
    | [] => None
    | [x] => Some(x)
    | [x, ...rest] =>
      Some(
        fst(
          fold(
            ~f=[@ns.namedArgLoc] minBy,
            ~initial=[@ns.namedArgLoc] (x, f(x)),
            rest,
          ),
        ),
      )
    };
  };
let maximumBy =
    (~f as [@ns.namedArgLoc] (f: 'a => 'comparable), l: list('a))
    : option('a) =>
  [@ns.braces]
  {
    let maxBy = ((y, fy), x) =>
      [@ns.braces]
      {
        let fx = f(x);
        if (fx > fy) {
          (x, fx);
        } else {
          (y, fy);
        };
      };
    switch (l) {
    | [] => None
    | [x] => Some(x)
    | [x, ...rest] =>
      Some(
        fst(
          fold(
            ~f=[@ns.namedArgLoc] maxBy,
            ~initial=[@ns.namedArgLoc] (x, f(x)),
            rest,
          ),
        ),
      )
    };
  };
let minimum = (t, ~compare as [@ns.namedArgLoc] compare) =>
  fold(
    t, ~initial=[@ns.namedArgLoc] None, ~f=[@ns.namedArgLoc] (min, element) =>
    switch (min) {
    | None => Some(element)
    | Some(value) =>
      [@ns.ternary]
      (
        if (compare(element, value) < 0) {
          Some(element);
        } else {
          min;
        }
      )
    }
  );
let maximum = (t, ~compare as [@ns.namedArgLoc] compare) =>
  fold(
    t, ~initial=[@ns.namedArgLoc] None, ~f=[@ns.namedArgLoc] (max, element) =>
    switch (max) {
    | None => Some(element)
    | Some(value) =>
      [@ns.ternary]
      (
        if (compare(element, value) > 0) {
          Some(element);
        } else {
          max;
        }
      )
    }
  );
let extent = (t, ~compare as [@ns.namedArgLoc] compare) =>
  fold(
    t,
    ~initial=[@ns.namedArgLoc] None,
    ~f=[@ns.namedArgLoc] (current, element) =>
    switch (current) {
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
let sort = (t, ~compare as [@ns.namedArgLoc] compare) =>
  Belt.List.sort(t, (a, b) => compare(a, b));
let sortBy = (l: t('a), ~f as [@ns.namedArgLoc] (f: 'a => 'b)): t('a) =>
  Belt.List.sort(l, (a, b) =>
    [@ns.braces]
    {
      let a' = f(a);
      let b' = f(b);
      if (a' == b') {
        0;
      } else if (a' < b') {
        (-1);
      } else {
        1;
      };
    }
  );
let groupi = (l, ~break as [@ns.namedArgLoc] break) =>
  [@ns.braces]
  {
    let groups =
      Belt.List.reduceWithIndex(l, [], (acc, x, i) =>
        switch (acc) {
        | [] => [[x]]
        | [current_group, ...tl] =>
          if (break(i, Belt.List.headExn(current_group), x)) {
            [[x], current_group, ...tl];
          } else {
            [[x, ...current_group], ...tl];
          }
        }
      );
    switch (groups) {
    | [] => []
    | l => Belt.List.mapReverse(l, reverse)
    };
  };
let groupWhile = (l, ~f as [@ns.namedArgLoc] f) =>
  groupi(l, ~break=[@ns.namedArgLoc] (_, x, y) => f(x, y));
let insertAt =
    (t, ~index as [@ns.namedArgLoc] index, ~value as [@ns.namedArgLoc] value) =>
  [@ns.braces]
  {
    let (front, back) = splitAt(t, ~[@ns.namedArgLoc] index);
    append(front, [value, ...back]);
  };
let splitWhen = (t, ~f as [@ns.namedArgLoc] f) =>
  [@ns.braces]
  {
    let rec loop = (front, back) =>
      switch (back) {
      | [] => (t, [])
      | [element, ...rest] =>
        if (f(element)) {
          (reverse(front), back);
        } else {
          loop([element, ...front], rest);
        }
      };
    loop([], t);
  };
let intersperse = (t, ~sep as [@ns.namedArgLoc] sep) =>
  switch (t) {
  | [] => []
  | [x] => [x]
  | [x, ...rest] => [
      x,
      ...foldRight(
           rest, ~initial=[@ns.namedArgLoc] [], ~f=[@ns.namedArgLoc] (acc, x) =>
           [sep, x, ...acc]
         ),
    ]
  };
let initialize = (length, ~f as [@ns.namedArgLoc] f) =>
  Belt.List.makeBy(length, a => f(a));
let forEach = (t, ~f as [@ns.namedArgLoc] f): unit =>
  Belt.List.forEach(t, a => f(a));
let forEachWithIndex = (t, ~f as [@ns.namedArgLoc] f): unit =>
  Belt.List.forEachWithIndex(t, (a, b) => f(a, b));
let toArray = t => Array.of_list(t);
let join = (strings, ~sep as [@ns.namedArgLoc] sep) =>
  Js.Array.joinWith(sep, toArray(strings));
let groupBy = (t, comparator, ~f as [@ns.namedArgLoc] f) =>
  fold(
    t,
    ~initial=[@ns.namedArgLoc] TableclothMap.empty(comparator),
    ~f=[@ns.namedArgLoc] (map, element) =>
    [@ns.braces]
    {
      let key = f(element);
      TableclothMap.update(map, ~[@ns.namedArgLoc] key, ~f=[@ns.namedArgLoc] x =>
        switch (x) {
        | None => Some([element])
        | Some(elements) => Some([element, ...elements])
        }
      );
    }
  );
let rec equal = (a, b, equalElement) =>
  switch (a, b) {
  | ([], []) => true
  | ([x, ...xs], [y, ...ys]) =>
    equalElement(x, y) && equal(xs, ys, equalElement)
  | _ => false
  };
let rec compare = (a, b, compareElement) =>
  switch (a, b) {
  | ([], []) => 0
  | ([], _) => (-1)
  | (_, []) => 1
  | ([x, ...xs], [y, ...ys]) =>
    switch (compareElement(x, y)) {
    | 0 => compare(xs, ys, compareElement)
    | result => result
    }
  };

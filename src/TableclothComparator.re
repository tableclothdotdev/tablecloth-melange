type nonrec t('a, 'identity) = Belt.Id.cmp('a, 'identity);
type nonrec comparator('a, 'identity) = t('a, 'identity);
module type T = {
  type nonrec t;
  let compare: (t, t) => int;
};
module type S = {
  type nonrec t;
  type nonrec identity;
  let comparator: comparator(t, identity);
};
type nonrec s('a, 'identity) = (module S with
                                   type identity = 'identity and type t = 'a);
module Make = (M: T) : (S with type t = M.t) => {
  module BeltComparator =
    Belt.Id.MakeComparableU({
      type nonrec t = M.t;
      let cmp = (. a, b) => M.compare(a, b);
    });
  type nonrec t = M.t;
  type nonrec identity = BeltComparator.identity;
  let comparator = BeltComparator.cmp;
};

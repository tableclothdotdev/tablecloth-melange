let toBeltComparator =
    (
      type a,
      type id,
      module M: TableclothComparator.S with type identity = id and type t = a,
    )
    : Belt.Id.comparable(a, id) =>
  (module
   {
     type nonrec t = M.t;
     type nonrec identity = M.identity;
     let cmp = Obj.magic(M.comparator);
   });

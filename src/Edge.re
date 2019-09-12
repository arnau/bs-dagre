[@bs.deriving abstract]
type t = {
  [@bs.optional]
  name: string,
  v: string,
  w: string,
};

[@bs.deriving abstract]
type point = {
  x: int,
  y: int,
};

[@bs.deriving abstract]
type attrs = {
  [@bs.optional]
  minlen: int,
  [@bs.optional]
  weight: int,
  [@bs.optional]
  width: int,
  [@bs.optional]
  height: int,
  [@bs.optional]
  labelpos: string,
  [@bs.optional]
  labeloffset: int,
  [@bs.optional]
  points: array(point),
};

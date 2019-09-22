type t = {
  graph: Dagre_graph.t,
  width: int,
  height: int,
};

[@bs.deriving abstract]
type point = {
  x: int,
  y: int,
};

[@bs.val] [@bs.module "dagre"]
external makeRaw: Dagre_graph.t => unit = "layout";

let make: Dagre_graph.t => t;

let size: t => (int, int);

let nodeCoords: (t, Dagre_node.t) => option((int, int));

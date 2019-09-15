type t;

module Attrs = {
  type t = {
    rankdir: Rank.Dir.t,
    align: Rank.Align.t,
    nodesep: int,
    edgesep: int,
    ranksep: int,
    marginx: int,
    marginy: int,
    acyclicer: Acyclicer.t,
    ranker: Rank.Strategy.t,
  };

  /** See https://github.com/dagrejs/dagre/wiki#configuring-the-layout

        Note that [align] defaults to [UpLeft] instead of [undefined]. */
  let make =
      (
        ~rankdir: Rank.Dir.t=TopBottom,
        ~align: Rank.Align.t=UpLeft,
        ~nodesep: int=50,
        ~edgesep: int=10,
        ~ranksep: int=50,
        ~marginx: int=0,
        ~marginy: int=0,
        ~acyclicer: Acyclicer.t=Lazy,
        ~ranker: Rank.Strategy.t=NetworkSimplex,
        unit,
      )
      : t => {
    rankdir,
    align,
    nodesep,
    edgesep,
    ranksep,
    marginx,
    marginy,
    acyclicer,
    ranker,
  };

  let toDict = (attrs: t) => {
    "rankdir": Rank.Dir.toString(attrs.rankdir),
    "align": Rank.Align.toString(attrs.align),
    "nodesep": attrs.nodesep,
    "edgesep": attrs.edgesep,
    "ranksep": attrs.ranksep,
    "marginx": attrs.marginx,
    "marginy": attrs.marginy,
    "acyclicer": Acyclicer.toString(attrs.acyclicer),
    "ranker": Rank.Strategy.toString(attrs.ranker),
  };
};

[@bs.deriving abstract]
type config = {
  directed: bool,
  compound: bool,
  multigraph: bool,
};

/** Creates a graph with the given config. It's recommended that you use the
      [make] function instead */
[@bs.new] [@bs.module "dagre"] [@bs.scope "graphlib"]
external makeWith: config => t = "Graph";

[@bs.send] external setGraphRaw: (t, Js.t('a)) => unit = "setGraph";
let setGraph = (graph: t, attrs: Attrs.t) =>
  setGraphRaw(graph, Attrs.toDict(attrs));

[@bs.send] external graph: t => Js.t('a) = "graph";
[@bs.send] external setNode: (t, Node.t, Node.attrs) => unit = "setNode";
[@bs.send] [@bs.return nullable]
external node: (t, Node.t) => option(Node.attrs) = "node";

[@bs.send] external isDirected: t => bool = "isDirected";
[@bs.send] external isMultigraph: t => bool = "isMultigraph";
[@bs.send] external isCompound: t => bool = "isCompound";

[@bs.send] external nodeCount: t => int = "nodeCount";
[@bs.send] external edgeCount: t => int = "edgeCount";

[@bs.send]
external setDefaultNodeLabel: (t, unit => Js.t('a)) => unit =
  "setDefaultNodeLabel";
[@bs.send]
external setDefaultEdgeLabel: (t, unit => Js.t('a)) => unit =
  "setDefaultEdgeLabel";

[@bs.send] external nodes: t => array(Node.t) = "nodes";
[@bs.send] external edges: t => array(Edge.t) = "edges";
[@bs.send] external sources: t => array(Node.t) = "sources";
[@bs.send] external sinks: t => array(Node.t) = "sinks";

[@bs.send] external hasNode: (t, Node.t) => bool = "hasNode";
[@bs.send] external removeNode: (t, Node.t) => unit = "removeNode";

[@bs.send]
external predecessors: (t, Node.t) => option(array(Node.t)) = "predecessors";
[@bs.send]
external successors: (t, Node.t) => option(array(Node.t)) = "successors";

[@bs.send]
external neighbors: (t, Node.t) => option(array(Node.t)) = "neighbors";

[@bs.send]
external inEdges:
  (t, Node.t, ~filter: Node.t=?, unit) => option(array(Edge.t)) =
  "inEdges";

[@bs.send]
external outEdges:
  (t, Node.t, ~filter: Node.t=?, unit) => option(array(Edge.t)) =
  "outEdges";

[@bs.send]
external nodeEdges:
  (t, Node.t, ~filter: Node.t=?, unit) => option(array(Edge.t)) =
  "nodeEdges";

[@bs.send] [@bs.return nullable]
external parent: (t, Node.t) => option(Node.t) = "parent";
[@bs.send] external setParent: (t, Node.t, Node.t) => unit = "setParent";
[@bs.send] [@bs.return nullable]
external childrenRaw: (t, Node.t) => option(array(Node.t)) = "children";

[@bs.send] external hasEdge: (t, Edge.t) => bool = "hasEdge";

[@bs.send] external setEdgeWith: (t, Edge.t, Edge.attrs) => unit = "setEdge";

[@bs.send] external setEdge: (t, Edge.t) => unit = "setEdge";

[@bs.send] [@bs.return nullable]
external edge: (t, Edge.t) => option(Edge.attrs) = "edge";

[@bs.send] external removeEdge: (t, Edge.t) => unit = "removeEdge";

[@bs.send] external filterNodes: (t, Js.t('a) => bool) => t = "filterNodes";

/** Creates a new graph with the given attributes.

      {[
          let attrs = Graph.Attrs.make(~rankdir=Rank.Dir.LeftRight, ());
          let graph = Graph.make(~attrs, ());

          Graph.isDirected(graph) == true;
          Graph.attrs(graph) == attrs;
      ]}

    */
let make =
    (
      ~directed: bool=true,
      ~compound: bool=false,
      ~multigraph: bool=false,
      ~attrs: Attrs.t=Attrs.make(),
      unit,
    )
    : t => {
  let g = makeWith(config(~directed, ~compound, ~multigraph));

  setGraph(g, attrs);

  g;
};

/** Returns the graph attributes. This is a less confusing alias for the
      original [Graph.graph]. */
let attrs = (g: t): Attrs.t => {
  let obj = graph(g);

  Attrs.make(
    ~rankdir=Rank.Dir.fromStringExn(obj##rankdir),
    ~align=Rank.Align.fromStringExn(obj##align),
    ~nodesep=obj##nodesep,
    ~edgesep=obj##edgesep,
    ~ranksep=obj##ranksep,
    ~marginx=obj##marginx,
    ~marginy=obj##marginy,
    ~acyclicer=Acyclicer.fromStringExn(obj##acyclicer),
    ~ranker=Rank.Strategy.fromStringExn(obj##ranker),
    (),
  );
};

/** Returns the children for the given node. When the graph is not compound,
      returns [None]. This is aligns the behaviour with [parent].

      Use [childrenRaw] if you need the original behaviour. */
let children = (graph: t, v: Node.t): option(array(Node.t)) =>
  isCompound(graph) ? childrenRaw(graph, v) : None;

let copy = (g: t): t => filterNodes(g, _ => true);

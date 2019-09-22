module Node = {
  [@react.component]
  let make = (~id: Dagre.Node.t, ~attrs: Dagre.Node.attrs) => {
    let x' = Dagre.Node.xGet(attrs)->Belt.Option.getExn;
    let y' = Dagre.Node.yGet(attrs)->Belt.Option.getExn;
    let width' = Dagre.Node.widthGet(attrs);
    let height' = Dagre.Node.heightGet(attrs);
    let label = Dagre.Node.labelGet(attrs);

    Js.log((x', y'));
    let xt = (x' + 20)->Js.Int.toString;
    let yt = (y' + 5 + height' / 2)->Js.Int.toString;
    let x = Js.Int.toString(x');
    let y = Js.Int.toString(y');
    let width = Js.Int.toString(width');
    let height = Js.Int.toString(height');

    <g>
      <rect fill="white" stroke="orange" x y width height />
      <text x=xt y=yt> {ReasonReact.string(label)} </text>
    </g>;
  };
};

module Edge = {
  [@react.component]
  let make = (~id: Dagre.Edge.t, ~attrs: Dagre.Edge.attrs) => {
    let points = Dagre.Edge.pointsGet(attrs)->Belt.Option.getExn;

    let d =
      Belt.Array.map(points, p =>
        Dagre.Edge.pointToString(p, ~correction=(70, 20), ())
      )
      ->Belt.Array.reduce(None, (acc, p) =>
          switch (acc) {
          | None => Some({j|M $p Q|j})
          | Some(a) => Some({j|$a $p|j})
          }
        )
      ->Belt.Option.getWithDefault("");

    <path stroke="black" fill="none" d />;
  };
};

[@react.component]
let make = (~layout: Dagre.Layout.t) => {
  let graph = layout.graph;
  let (width, height) = Dagre.Layout.size(layout);
  let nodes = Dagre.Graph.nodes(graph);
  let edges = Dagre.Graph.edges(graph);

  Js.log((width, height));
  <svg
    width={Js.Int.toString(width + 170)}
    height={Js.Int.toString(height + 40)}>
    {ReactDOMRe.createElement(
       ReasonReact.fragment,
       Belt.Array.map(nodes, id =>
         <Node id attrs={Dagre.Graph.node(graph, id)->Belt.Option.getExn} />
       ),
     )}
    {ReactDOMRe.createElement(
       ReasonReact.fragment,
       Belt.Array.map(edges, id =>
         <Edge id attrs={Dagre.Graph.edge(graph, id)->Belt.Option.getExn} />
       ),
     )}
  </svg>;
};

module Node = {
  [@react.component]
  let make = (~id: BsDagre.Node.t, ~attrs: BsDagre.Node.attrs) => {
    let x' = BsDagre.Node.xGet(attrs)->Belt.Option.getExn;
    let y' = BsDagre.Node.yGet(attrs)->Belt.Option.getExn;
    let width' = BsDagre.Node.widthGet(attrs);
    let height' = BsDagre.Node.heightGet(attrs);
    let label = BsDagre.Node.labelGet(attrs);

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
  let make = (~id: BsDagre.Edge.t, ~attrs: BsDagre.Edge.attrs) => {
    let points = BsDagre.Edge.pointsGet(attrs)->Belt.Option.getExn;

    let d =
      Belt.Array.map(points, p =>
        BsDagre.Edge.pointToString(p, ~correction=(70, 20), ())
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
let make = (~layout: BsDagre.Layout.t) => {
  let graph = layout.graph;
  let (width, height) = BsDagre.Layout.size(layout);
  let nodes = BsDagre.Graph.nodes(graph);
  let edges = BsDagre.Graph.edges(graph);

  Js.log((width, height));
  <svg
    width={Js.Int.toString(width + 170)}
    height={Js.Int.toString(height + 40)}>
    {ReactDOMRe.createElement(
       ReasonReact.fragment,
       Belt.Array.map(nodes, id =>
         <Node id attrs={BsDagre.Graph.node(graph, id)->Belt.Option.getExn} />
       ),
     )}
    {ReactDOMRe.createElement(
       ReasonReact.fragment,
       Belt.Array.map(edges, id =>
         <Edge id attrs={BsDagre.Graph.edge(graph, id)->Belt.Option.getExn} />
       ),
     )}
  </svg>;
};

open BsDagre;

type state = Graph.t;

let init = () => {
  let nodes = [
    ("kspacey", "Kevin Spacey"),
    ("swilliams", "Saul Williams"),
    ("bpitt", "Brad Pitt"),
    ("hford", "Harrison Ford"),
    ("lwilson", "Luke Wilson"),
    ("kbacon", "Kevin Bacon"),
  ];
  let edges = [
    ("kspacey", "swilliams"),
    ("swilliams", "kbacon"),
    ("bpitt", "kbacon"),
    ("hford", "lwilson"),
    ("lwilson", "kbacon"),
  ];

  let graph = Graph.make();
  Graph.setDefaultEdgeAttrs(graph, () => {"minlen": 2});

  Belt.List.forEach(nodes, ((id, label)) =>
    Graph.setNodeWith(
      graph,
      id,
      Node.attrs(~label, ~width=140, ~height=40, ()),
    )
  );

  Belt.List.forEach(edges, ((v, w)) =>
    Graph.setEdge(graph, Edge.t(~v, ~w, ()))
  );

  graph;
};

[@react.component]
let make = () => {
  let (state, _) = React.useState(init);

  let layout = Layout.make(state);

  <div>
    <h1> {ReasonReact.string("A simple graph layout")} </h1>
    <Plot layout />
  </div>;
};

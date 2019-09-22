open Jest;
open Expect;
open Dagre.Rank;

describe("Rank", () => {
  describe("Dir", () => {
    test("Known", () =>
      expect((
        Dir.fromStringExn(Dir.toString(Dir.TopBottom)),
        Dir.fromStringExn(Dir.toString(Dir.BottomTop)),
        Dir.fromStringExn(Dir.toString(Dir.LeftRight)),
        Dir.fromStringExn(Dir.toString(Dir.RightLeft)),
      ))
      |> toEqual((Dir.TopBottom, Dir.BottomTop, Dir.LeftRight, Dir.RightLeft))
    );

    test("unknown", () =>
      expect(() =>
        Dir.fromStringExn("TT")
      )
      |> toThrowException(Dir.UnexpectedDir("TT"))
    );
  });

  describe("Align", () => {
    test("Known", () =>
      expect((
        Align.fromStringExn(Align.toString(Align.UpLeft)),
        Align.fromStringExn(Align.toString(Align.UpRight)),
        Align.fromStringExn(Align.toString(Align.DownLeft)),
        Align.fromStringExn(Align.toString(Align.DownRight)),
      ))
      |> toEqual((
           Align.UpLeft,
           Align.UpRight,
           Align.DownLeft,
           Align.DownRight,
         ))
    );

    test("unknown", () =>
      expect(() =>
        Align.fromStringExn("TT")
      )
      |> toThrowException(Align.UnexpectedAlign("TT"))
    );
  });

  describe("Strategy", () => {
    test("Known", () =>
      expect((
        Strategy.fromStringExn(Strategy.toString(Strategy.NetworkSimplex)),
        Strategy.fromStringExn(Strategy.toString(Strategy.TightTree)),
        Strategy.fromStringExn(Strategy.toString(Strategy.LongestPath)),
      ))
      |> toEqual((
           Strategy.NetworkSimplex,
           Strategy.TightTree,
           Strategy.LongestPath,
         ))
    );

    test("unknown", () =>
      expect(() =>
        Strategy.fromStringExn("TT")
      )
      |> toThrowException(Strategy.UnexpectedStrategy("TT"))
    );
  });
});

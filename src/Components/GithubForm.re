type state = {
  username: string
};

type action =
  | NoOp;

let component = ReasonReact.reducerComponent("GithubForm");

let make = (_children) => {
  ...component,

  initialState: () => {
    username: ""
  },

  reducer: (action, _state: state) => switch action {
  | NoOp => NoUpdate
  },

  render: (_self) =>
    <div>{ReasonReact.string("Hello")}</div>
};

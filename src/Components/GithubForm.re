open BsRemotedata;

type state = {
  username: string,
  githubUser: RemoteData.t(string, GithubUser.t)
};

type action =
  | SetUsername(string)
  | FetchUser
  | UpdateGithubUser(RemoteData.t(string, GithubUser.t))

let component = ReasonReact.reducerComponent("GithubForm");

let make = (_children) => {
  ...component,

  initialState: () => {
    username: "test",
    githubUser: RemoteData.NotAsked
  },

  reducer: (action, state: state) => switch action {
    | SetUsername(username) => ReasonReact.Update({...state, username})
    | FetchUser => ReasonReact.UpdateWithSideEffects(
      {...state, githubUser: RemoteData.Loading}, self =>
        Api.getUser(state.username)
        |> Js.Promise.then_(data => {
          self.send(UpdateGithubUser(RemoteData.Success(data)));
          Js.Promise.resolve(data);
        })
        |> ignore
    )
    | UpdateGithubUser(githubUser) => ReasonReact.Update({...state, githubUser})
  },

  render: (self) =>
    <div>
    <input value={self.state.username} onChange={event => self.send(SetUsername(ReactEvent.Form.target(event)##value))} />
    <button onClick={_e => self.send(FetchUser)} />
    </div>
};

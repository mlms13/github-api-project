type state = {
  username: string,
  githubUser: RemoteData.t(string, GithubUser.t)
};

/* At app launch say you set your data state to `NotAsked` */
let data: WebData.t(person) = RemoteData.NotAsked;

/* You received an event and you need to retrieve your data */
let data: WebData.t(person) = RemoteData.Loading;

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
        |> Js.Promise.then_(data => self.send(UpdateGithubUser(RemoteData.Success(data)))))
    | UpdateGithubUser(githubUser) => ReasonReact.Update({...state, githubUser})
  },

  render: (self) =>
    <div>
    <input value={self.state.username} onChange={event => self.send(SetUsername(ReactEvent.Form.target(event)##value))} />
    <button onClick={e => self.send(FetchUser)} />
    </div>
};

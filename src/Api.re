let baseUrl = "https://api.github.com/";

type result('a, 'err) =
  | Ok('a)
  | Error('err);

let getJSON = (url: string): Js.Promise.t(Js.Json.t) => {
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
  );
};

let getUser = (username: string): Js.Promise.t(GithubUser.t) =>
  getJSON(baseUrl ++ "users/" ++ username)
    |> Js.Promise.then_(json => Js.Promise.resolve(GithubUser.decode(json)));

type t = {
  login: string,
  avatarUrl: string,
  profileUrl: string
};

let decode = (json: Js.Json.t): t =>
  Json.Decode.{
    login:      json |> field("login", string),
    avatarUrl:  json |> field("avatar_url", string),
    profileUrl: json |> field("url", string)
  };

/* {
  "login": "octocat",
  "id": 1,
  "node_id": "MDQ6VXNlcjE=",
  "avatar_url": "https://github.com/images/error/octocat_happy.gif",
  "gravatar_id": "",
  "url": "https://api.github.com/users/octocat",
} */

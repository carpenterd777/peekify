# peekify

A toy command line program to check the currently playing song on your Spotify account.

## Building

```bash
make install # get libcurl
make all     # build the exe file
```

## Running

Before running, obtain a token from the ![Developer Console](https://developer.spotify.com/console/get-user-player/). Grab this token and set it to `$SPOTIFY_AUTH_TOKEN` in your environment.

Then just run the executable:
```bash
./peekify
```

## Limitations
The token obtained from the developer console lasts a short time (around 2 hours). In order to obtain an authorization token that lasts for longer, one would have to register an app and set up a more sophisticated authorization flow. Perhaps in the future :D

/**
 * Author: carpenterd777
 * Date: 2022-05-06
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <curl/curl.h>
#include "json.hpp"

#include "display.hpp"
#include "requests.hpp"

using namespace std;
using namespace peekify;
using json = nlohmann::json;

static listening_info build_listening_info(json res)
{
    listening_info li;

    vector<string> artists;
    string song_name;
    int duration_ms;
    try
    {
        json item = res.at("item");
        vector<json> artist_jsons = item.at("artists");

        // get all artists
        for (auto &artist : artist_jsons)
        {
            artists.push_back(artist.at("name"));
        }

        duration_ms = item.at("duration_ms");
        song_name = item.at("name");
    }
    catch (nlohmann::detail::out_of_range const &)
    {
        artists.push_back("");
        song_name = "";
        duration_ms = 0;
    }

    li.progress_ms = res.value("progress_ms", 0);
    li.artists = artists;
    li.duration_ms = duration_ms;
    li.song_name = song_name;
    li.is_playing = res.value("is_playing", false);

    return li;
}

int main()
{
    // initialize some of the libcurl functionality globally
    curl_global_init(CURL_GLOBAL_ALL);

    json res = request_json();

    // check that an error was not produced by the request
    try
    {
        // only line that can produce an error
        json err = res.at("error");

        // if we've gotten this far without an out-of-range error then we know there was an actual
        // error with the request
        int err_code = err.value("status", -1);
        string message = err.value("message", "Could not retrieve message");
        cerr << "Error: Received error code " << err_code << " with the following message:\n"
             << message << '\n';
        return EXIT_FAILURE;
    }
    // there was no error with the request, continue as normal
    catch (nlohmann::detail::out_of_range const &)
    {
    }

    listening_info li = build_listening_info(res);
    render_frame(li);

    return EXIT_SUCCESS;
}
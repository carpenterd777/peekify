/**
 * Author: carpenterd777
 * Date: 2022-05-06
 *
 * This tutorial is referred to throughout:
 * https://curl.se/libcurl/c/libcurl-tutorial.html
 */

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <curl/curl.h>
#include "requests.hpp"

using namespace std;

typedef struct bufchunk
{
    char *response;
    size_t size;
} bufchunk;

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *userdata);

char *peekify::request()
{
    // set up the auth header
    char *spotify_token = getenv("SPOTIFY_AUTH_TOKEN");
    if (spotify_token == NULL)
    {
        cerr << "Error: $SPOTIFY_AUTH_TOKEN not defined"
             << '\n';
        exit(EXIT_FAILURE);
    }
    string prefix = "Authorization: Bearer ";
    char *auth = (char *)malloc(prefix.length() + strlen(spotify_token));
    strncat(auth, prefix.c_str(), prefix.length());
    strncat(auth, spotify_token, strlen(spotify_token));

    // create a handle for the "easy" interface, which is synchronous and blocking
    // handles are a logical entity for the upcoming transfers
    CURL *easyhandle = curl_easy_init();

    // place errors in an error buffer to print on an error
    char error[CURL_ERROR_SIZE];
    curl_easy_setopt(easyhandle, CURLOPT_ERRORBUFFER, error);

    // set the url to download from
    curl_easy_setopt(easyhandle, CURLOPT_URL, "https://api.spotify.com/v1/me/player");

    // send all data to the write_data function
    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_data);

    // no progress bar
    curl_easy_setopt(easyhandle, CURLOPT_NOPROGRESS, 1L);

    // set up the headers
    struct curl_slist *list = NULL;
    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, auth);
    curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, list);

    // do a GET request
    curl_easy_setopt(easyhandle, CURLOPT_HTTPGET, 1L);

    bufchunk chunk = {0};
    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, (void *)&chunk);

    // perform the request
    error[0] = 0; // zero the buffer before the request
    CURLcode success = curl_easy_perform(easyhandle);
    if (success != CURLE_OK)
    {
        cerr << "Error: request failed - ";
        if (strlen(error))
        {
            cerr << error << '\n';
        }
        else
        {

            cerr << curl_easy_strerror(success) << " (" << success << ")" << '\n';
        }
        curl_slist_free_all(list);
        curl_easy_cleanup(easyhandle);
        delete auth;
        exit(EXIT_FAILURE);
    }

    // Cleanup
    curl_easy_cleanup(easyhandle);
    curl_slist_free_all(list);
    delete auth;

    return chunk.response;
}

/**
 * Writes the data received from the request. Is invoked many times
 * and every invocation delivers another chunk of data.
 *
 * @param ptr Points to the delivered data
 * @param size always 1
 * @param nmemb the size of the data pointed to by ptr
 * @param userdata the pointer to the data accessible by the process
 */
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    // based on the example at https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html

    size_t realsize = size * nmemb;

    // cast the userdata pointer to the struct used for holding the data
    bufchunk *mem = (bufchunk *)userdata;

    // reallocate the user process data to accomodate the new data
    char *new_res = (char *)realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL)
        return 0; /* out of memory! */

    // set the response from the passed data to the larger memory
    mem->response = new_res;

    // copy the data back into the user process struct
    memcpy(&(mem->response[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}
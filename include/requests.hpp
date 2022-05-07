/**
 * Author: carpenterd777
 * Date: 2022-05-06
 */
#pragma once
#include <curl/curl.h>
#include "json.hpp"
namespace peekify
{
    /**
     * Performs the request to the Spotify Web API to get the JSON information. Returns the JSON
     * response.
     * @param easyhandle a cURL "easy api" handle
     * @returns the response as a JSON string
     */
    char *request(CURL *easyhandle); 

    /**
     * Performs the request to the Spotify Web API to get the JSON information. Returns the JSON
     * response.
     * @param easyhandle a cURL "easy api" handle
     * @returns the response as a JSON object
     */
    nlohmann::json request_json(CURL *easyhandle); 

    /**
     * Set all of the opts to prepare to contact the Spotify web API.
     * @param easyhandle a cURL "easy api" handle 
     */
    void setopts(CURL *easyhandle);
}

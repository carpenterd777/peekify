/**
 * Author: carpenterd777
 * Date: 2022-05-06
 */
#pragma once
#include "json.hpp"
namespace peekify
{
    /**
     * Performs the request to the Spotify Web API to get the JSON information. Returns the JSON
     * response.
     * @returns the response as a JSON string
     */
    char *request(); 

    /**
     * Performs the request to the Spotify Web API to get the JSON information. Returns the JSON
     * response.
     * @returns the response as a JSON object
     */
    nlohmann::json request_json(); 
}

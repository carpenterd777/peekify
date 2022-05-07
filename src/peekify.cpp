/**
 * Author: carpenterd777
 * Date: 2022-05-06
 */

#include <iostream>
#include <cstdlib>
#include <curl/curl.h>
#include "display.hpp"
#include "requests.hpp"

using namespace std;
using namespace peekify;

int main()
{
    // initialize some of the libcurl functionality globally
    curl_global_init(CURL_GLOBAL_ALL);

    cout << request() << '\n';
    return EXIT_SUCCESS;
}
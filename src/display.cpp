/**
 * Author: carpenterd777
 * Date: 2022-05-06
 */
#include <iomanip>
#include <iostream>
#include <sstream>
#include "display.hpp"

using namespace std;
using namespace peekify;

static string ms_to_mins_secs(int ms);
static string blue(string s);
static string red(string s);

void peekify::render_frame(listening_info li)
{
    cout << blue(li.song_name) 
         << " - " << li.artists.at(0) << '\n'
         << red(ms_to_mins_secs(li.progress_ms)) << " / " 
         << red(ms_to_mins_secs(li.duration_ms)) << "\n";
}

void peekify::clear_screen()
{
    // apparently this string of characters translates to a screen clear?
    // found it here: https://stackoverflow.com/questions/17335816/clear-screen-using-c
    cout << "\033[2J\033[1;1H";
}

static string ms_to_mins_secs(int ms)
{
    // ms * (1 s / 1000 ms)
    int ms_to_secs = ms / 1000;

    // s * (1 min / 60 s)
    int secs_to_mins = ms_to_secs / 60;
    int secs_to_mins_r = ms_to_secs % 60; //remainder

    ostringstream oss;
    oss << setw(2) << std::setfill('0') << to_string(secs_to_mins_r);

    return to_string(secs_to_mins) + ":" + oss.str();
}

static string blue(string s)
{
    return "\x1b[36m" + s + "\033[0m";
}

static string red(string s)
{
    return "\x1b[31m" + s + "\033[0m";
}
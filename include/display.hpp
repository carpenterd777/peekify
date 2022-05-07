/**
 * Author: carpenterd777
 * Date: 2022-05-06
 */
#pragma once
#include <string>
#include <vector>

namespace peekify
{
    /**
     * A collection of information received from the web API about the listener's current song.
     */
    typedef struct listening_info
    {
        int progress_ms;
        std::vector<std::string> artists;
        std::string song_name;
        int duration_ms;
        bool is_playing;
    } listening_info;

    /**
     * Draws one frame of the Peekify interface.
     * @param li information about the song to display
     */
    void render_frame(listening_info li);
}

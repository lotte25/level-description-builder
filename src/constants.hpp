#pragma once

namespace constants {
    std::string exampleTemplate = "Level ID: {ID}\n"
        "Level name: {NAME}\n"
        "Description: {DESCRIPTION}\n"
        "Coins: {COINS}\n"
        "Rate status: {RATE}\n"
        "Creator: {CREATOR}\n"
        "Stars: {STARS}\n"
        "Attempts: {ATTEMPTS}\n"
        "Jumps: {JUMPS}\n"
        "Clicks: {CLICKS}\n"
        "Downloads: {DOWNLOADS}\n"
        "Likes: {LIKES}\n"
        "Difficulty: {DIFFICULTY}\n"
        "Length: {LENGTH}\n"
        "Song: {SONGNAME} ({SONGID})\n";
    
    static const std::map<GJDifficulty, std::string> difficultyMap = {
        {GJDifficulty::NA, "NA"},
        {GJDifficulty::Easy,   "Easy"},
        {GJDifficulty::Normal, "Normal"},
        {GJDifficulty::Hard,   "Hard"},
        {GJDifficulty::Harder, "Harder"},
        {GJDifficulty::Insane, "Insane"},
    };
    
    static const std::map<int, std::string> demonDifficultyMap = {
        {0,  "Hard Demon"},
        {3,  "Easy Demon"},
        {4,  "Medium Demon"},
        {5,  "Insane Demon"},
        {6, "Extreme Demon"}
    };
    
    static const std::map<int, std::string> lengthMap = {
            {0, "Tiny"},
            {1, "Short"},
            {2, "Medium"},
            {3, "Long"},
            {4, "XL"},
            {5, "Platformer"}
    };
}

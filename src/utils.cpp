#include <Geode/Geode.hpp>
#include <Geode/binding/GJGameLevel.hpp>
#include "constants.hpp"
#include "utils.hpp"

namespace Utils {
    std::string replace(std::string& descTemplate, const std::string& placeholder, const std::string& value) {
        size_t pos = 0;

        while ((pos = descTemplate.find(placeholder, pos)) != std::string::npos) {
            descTemplate.replace(pos, placeholder.length(), value);
            pos += value.length();
        }

        return descTemplate;
    }

    std::string buildTemplate(GJGameLevel* level) {
        std::string text = loadTemplateFile();

        std::string creatorName = level->m_creatorName.empty() ? "RobTop" : level->m_creatorName;
        std::string songName = (level->m_songID == 0) ? LevelTools::getAudioTitle(level->m_audioTrack) : level->getSongName();
        std::string songID = (level->m_songID == 0) ? "Official" : std::to_string(level->m_songID);

        replace(text, "{ID}", level->m_friendsOnly ? "REDACTED" : std::to_string(level->m_levelID.value()));
        replace(text, "{NAME}", level->m_levelName);
        replace(text, "{DESCRIPTION}", level->m_levelDesc);
        replace(text, "{COINS}", std::to_string(level->m_coins));
        replace(text, "{RATE}", getLevelRatingString(level));
        replace(text, "{CREATOR}", creatorName);
        replace(text, "{STARS}", std::to_string(level->m_stars));
        replace(text, "{ATTEMPTS}", std::to_string(level->m_attempts));
        replace(text, "{JUMPS}", std::to_string(level->m_jumps));
        replace(text, "{CLICKS}", std::to_string(level->m_clicks));
        replace(text, "{DOWNLOADS}", std::to_string(level->m_downloads));
        replace(text, "{LIKES}", std::to_string(level->m_likes));
        replace(text, "{DIFFICULTY}", getDifficultyName(level));
        replace(text, "{LENGTH}", getLengthName(level->m_levelLength));
        replace(text, "{SONGNAME}", songName);
        replace(text, "{SONGID}", songID);

        return text;
    }

    std::string loadTemplateFile() {
        auto path = geode::Mod::get()->getConfigDir() / "template.txt";

        if (!std::filesystem::exists(path)) {
            if (!geode::utils::file::writeString(path, constants::exampleTemplate).isOk()) {
                FLAlertLayer::create(
                    "Error",
                    "Failed to create template file!\nCheck if your user has write permissions",
                    "OK"
                )->show();
            };

            return constants::exampleTemplate;
        };
        
        auto result = geode::utils::file::readString(path);
        return result.isOk() ? result.unwrap() : "";
    }

    std::string getDifficultyName(GJGameLevel* level) {
        // geode::log::info("Difficulty {}, Demon Difficulty {}", static_cast<int>(level->m_difficulty), level->m_demonDifficulty);

        std::string result;
        if (level->m_demon) {
            auto it = constants::demonDifficultyMap.find(level->m_demonDifficulty);
            if (it != constants::demonDifficultyMap.end()) result = it->second;
        } else {
            auto it = constants::difficultyMap.find(level->m_difficulty);
            if (it != constants::difficultyMap.end()) result = it->second;
        }

        return result.empty() ? "Unknown" : result;
    }

    std::string getLengthName(int lengthID) {
        auto it = constants::lengthMap.find(lengthID);

        if (it == constants::lengthMap.end()) {
            return "Unknown";
        }

        return it->second;
    }

    // Function from EclipseMenu/EclipseMenu
    std::string getLevelRatingString(GJGameLevel* level) {
        if (!level) return "Unknown";
        int featured = level->m_featured;
        int epic = level->m_isEpic;
        switch (epic) {
            default: // Not epic (featured, rated, unrated)
                if (level->m_stars.value() == 0 && featured <= 0) {
                    return "Unrated";
                } else {
                    return (featured <= 0) ? "Rated" : "Featured";
                }
            case 1: // Epic
                return "Epic";
            case 2: // Legendary
                return "Legendary";
            case 3: // Mythic
                return "Mythic";
        }
    }
}
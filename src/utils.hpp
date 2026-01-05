#pragma once

#include <Geode/binding/GJGameLevel.hpp>

namespace Utils {
    std::string replace(std::string& descTemplate, const std::string& placeholder, const std::string& value);
    std::string buildTemplate(GJGameLevel* level);
    std::string loadTemplateFile();
    std::string getDifficultyName(GJGameLevel* diff);
    std::string getLengthName(int lengthID);
    std::string getLevelRatingString(GJGameLevel* level);
}
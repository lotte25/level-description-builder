#pragma once

using namespace cocos2d;

class TemplatePreviewPopup : public geode::Popup<std::string const&> {
protected:
    std::string m_text;

    bool setup(std::string const& text) override;
    void onCopy(CCObject*);

public:
    static TemplatePreviewPopup* create(std::string const& text);
};
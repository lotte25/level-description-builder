#include "previewPopup.hpp"

using namespace cocos2d;


bool TemplatePreviewPopup::setup(std::string const& text) {
    m_text = text;
    // m_title->setFntFile("bigFont.fnt");
    // 1m_title->updateLabel();

    m_bgSprite->setColor({ 51, 68, 153 });

    this->setTitle("Description Preview");

    auto bg = cocos2d::extension::CCScale9Sprite::create("square02_001.png");
    bg->setColor({ 0, 0, 0 });
    bg->setContentSize({ 340.f, 160.f });
    bg->setOpacity(80);

    m_mainLayer->addChildAtPosition(bg, geode::Anchor::Center, { 0.f, 5.f });

    auto geodeTextArea = geode::SimpleTextArea::create(
        text.c_str(),
        "chatFont.fnt",
        0.8f
    );

    geodeTextArea->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
    geodeTextArea->setAnchorPoint({ 0.55f, 0.45f });
    geodeTextArea->setWrappingMode(geode::WrappingMode::SPACE_WRAP);

    bg->addChildAtPosition(geodeTextArea, geode::Anchor::Center);

    auto copyBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Copy", "bigFont.fnt", "GJ_button_03.png"),
        this,
        menu_selector(TemplatePreviewPopup::onCopy)
    );
    copyBtn->setScale(0.8f);

    auto menu = CCMenu::create();
    menu->addChild(copyBtn);
    menu->setPosition({ m_size.width / 2, 25.f });
    m_mainLayer->addChild(menu);

    return true;
}

void TemplatePreviewPopup::onCopy(CCObject*) {
    geode::utils::clipboard::write(m_text);

    auto notification = geode::Notification::create(
        "Copied description to clipboard!", 
        geode::NotificationIcon::Info
    );
    notification->setZOrder(1000);
    notification->setTime(0.3f);
    notification->show();
}

TemplatePreviewPopup* TemplatePreviewPopup::create(std::string const& text) {
    auto ret = new TemplatePreviewPopup();
    if (ret && ret->initAnchored(380.f, 240.f, text, "GJ_square06.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
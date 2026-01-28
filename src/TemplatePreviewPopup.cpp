#include "TemplatePreviewPopup.hpp"

using namespace geode::prelude;

bool TemplatePreviewPopup::setup(std::string const& text) {
    this->setID("template-preview-popup"_spr);
    m_noElasticity = true;

    m_template = text;
    // m_bgSprite->setColor({ 51, 68, 153 });
    this->setTitle("Template Preview");

    CCSize contentSize = { 340.f, 180.f };

    auto bg = cocos2d::extension::CCScale9Sprite::create("square02_001.png");
    bg->setColor({ 0, 0, 0 });
    bg->setContentSize(contentSize);
    bg->setOpacity(85);
    m_mainLayer->addChildAtPosition(bg, Anchor::Center, { 0.f, -10.f });

    auto scrollLayer = ScrollLayer::create(contentSize);
    scrollLayer->ignoreAnchorPointForPosition(false);

    auto contentMenu = CCMenu::create();
    contentMenu->setAnchorPoint({ 0.f, 1.f });
    
    std::stringstream ss(text);
    std::string segment;

    while (std::getline(ss, segment)) {
        if (segment.empty()) segment = " ";

        auto label = CCLabelBMFont::create(segment.c_str(), "chatFont.fnt");
        label->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
        contentMenu->addChild(label);
    }

    contentMenu->setLayout(
        ColumnLayout::create()
        ->setGap(0.f)
        ->setAxisAlignment(AxisAlignment::End)
        ->setCrossAxisLineAlignment(AxisAlignment::Start)
        ->setAxisReverse(true)
    );

    contentMenu->updateLayout();

    float menuHeight = contentMenu->getContentSize().height;
    float contentHeight = std::max(contentSize.height, menuHeight);

    scrollLayer->m_contentLayer->setContentSize({ contentSize.width, contentHeight });

    contentMenu->setPosition({ 10.f, contentHeight - 5 });
    scrollLayer->m_contentLayer->addChild(contentMenu);

    scrollLayer->moveToTop();

    m_mainLayer->addChildAtPosition(scrollLayer, Anchor::Center, { 0.f, -10.f });

    auto copySpr = ButtonSprite::create("Copy", 66, 0, 0.6f, false, "bigFont.fnt", "GJ_button_03.png", 30);
    copySpr->setScale(0.8f);
    auto copyBtn = CCMenuItemSpriteExtra::create(copySpr, this, menu_selector(TemplatePreviewPopup::onCopy));
    m_buttonMenu->addChildAtPosition(copyBtn, Anchor::BottomRight, { -10.f, 10.f });

    return true;
}

void TemplatePreviewPopup::onCopy(CCObject*) {
    geode::utils::clipboard::write(m_template);

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
    if (ret && ret->initAnchored(380.f, 240.f, text, "GJ_square03.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
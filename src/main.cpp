#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "TemplatePreviewPopup.hpp"
#include "utils.hpp"

using namespace geode::prelude;

class $modify(MPL, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = this->getChildByID("left-button-menu");
        if (!menu) return;
        
        auto btn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_copyBtn_001.png"),
            this,
            menu_selector(MPL::onCopyDescription)
        );

        btn->setScale(0.7f);
        menu->addChild(btn);
        menu->updateLayout();
    }

    void onCopyDescription(CCObject*) {
        auto playLayer = PlayLayer::get();
        if (!playLayer) return;

        auto level = playLayer->m_level;

        std::string text = Utils::buildTemplate(level);
        TemplatePreviewPopup::create(text)->show();
    }
};
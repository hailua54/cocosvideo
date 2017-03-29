#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIVideoPlayer.h"
#include "ui/UILayout.h"
#include<functional>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
	cocos2d::LayerColor* cl = cocos2d::LayerColor::create();
	scene->addChild(cl);
	cl->setBlendFunc(BlendFunc::DISABLE);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	cl->setContentSize(visibleSize);

	cl->setBlendFunc(BlendFunc::DISABLE);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setName("game");

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);
    // add the sprite as a child to this layer
	
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	
	auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
	float vw = visibleSize.width;
	float vh = (240.0f / 432.0f)*vw;
	videoPlayer->setContentSize(CCSize(vw, vh));
	videoPlayer->setAnchorPoint(Vec2(0,0));
	videoPlayer->setPosition(cocos2d::Vec2(0, visibleSize.height - vh));
	videoPlayer->setFileName("res/cocosvideo.mp4");
	this->addChild(videoPlayer);

	cocos2d::ui::Layout* layout = cocos2d::ui::Layout::create();
	layout->setContentSize(Size(240.0f, 432.0f));
	videoPlayer->setAnchorPoint(Vec2(0, 0));
	videoPlayer->setPosition(cocos2d::Vec2(0, visibleSize.height - vh));
	this->addChild(layout);
	/*
	enum class EventType
            {
                PLAYING = 0,
                PAUSED,
                STOPPED,
                COMPLETED
            };
	*/
	
	videoPlayer->addEventListener([this, videoPlayer](cocos2d::Ref* target, cocos2d::experimental::ui::VideoPlayer::EventType type) {
		CCLOG("video event %ld ", type);
		if (type == cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING)
		{
			if (videoPlayer) CCLOG("videoPlayer available");
			videoPlayer->getVideoSize([](cocos2d::Ref* p, int w, int h) {CCLOG("getVideoSize ========= %d, %d", w, h); }); // run
		}
	});
	videoPlayer->play();
	
//#endif
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

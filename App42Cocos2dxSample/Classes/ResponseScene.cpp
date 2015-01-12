//
//  ResponseScene.cpp
//  App42Cocos2dXSample
//
//  Created by Shephertz Technologies Pvt Ltd on 10/09/14.
//
//

#include "ResponseScene.h"
#include "TestPushNotificationService.h"


USING_NS_CC;


Scene* ResponseScene::createScene()
{
    //printf("ResponseScene::loadResponse");
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResponseScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}




// on "init" you need to initialize your instance
bool ResponseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //printf("ResponseScene::init");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float button_y_Offset =30;
    y_pos = origin.y+visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/2;
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "CloseNormal.png",
                                                "CloseSelected.png",
                                                CC_CALLBACK_1(ResponseScene::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Response Scene", "Marker Felt", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 20));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    return true;
}

void ResponseScene::loadResponse(string response)
{
   // printf("ResponseScene::loadResponse");
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = LabelTTF::create(response, "Marker Felt", 24);
    y_pos -= 40;
    label->setAnchorPoint(Vec2(0,0));
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x+10,y_pos));
    // add the label as a child to this layer
    this->addChild(label, 1);
}

void ResponseScene::menuCloseCallback(Ref* pSender)
{
    // create a scene. it's an autorelease object
    auto scene = TestPushNotificationService::createScene();
    
    // run
    Director::getInstance()->replaceScene(scene);

}

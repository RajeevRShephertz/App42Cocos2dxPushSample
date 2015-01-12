//
//  App42PushHelper.h
//  MyGame
//
//  Created by Rajeev Ranjan on 29/12/14.
//
//

#ifndef __MyGame__App42PushHelper__
#define __MyGame__App42PushHelper__

#include <stdio.h>
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "App42Bridge.h"
#endif

typedef std::function<void(const char*)> app42PushCallback;

class App42PushHelper
{
public:
    //static void getCallBack(const char* devToken);
    static void registerForPush(const app42PushCallback& callback);
    static void didRegisterForRemoteNotificationsWithDeviceToken(const char* deviceToken);
    static void didReceiveRemoteNotification(const char* message);
    static void setPushCallBack(const app42PushCallback& _callback);
};

#endif /* defined(__MyGame__App42PushHelper__) */

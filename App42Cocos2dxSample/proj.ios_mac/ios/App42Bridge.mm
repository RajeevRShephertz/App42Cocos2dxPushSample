//
//  App42Bridge.m
//  MyGame
//
//  Created by Rajeev Ranjan on 29/12/14.
//
//

#import "App42Bridge.h"
#include "App42PushHelper.h"

void App42Bridge::registerForPush()
{
    NSLog(@"%s",__func__);
    registerApplicationForPushNotification();
}


void App42Bridge::deviceDidRegisteredForPush(const char* deviceToken)
{
    NSLog(@"%s",deviceToken);
    //callback(deviceToken);
    App42PushHelper::didRegisterForRemoteNotificationsWithDeviceToken(deviceToken);
}


void App42Bridge::registerApplicationForPushNotification()
{
    NSLog(@"%s",__func__);
    UIApplication *application = [UIApplication sharedApplication];
    // Register for Push Notitications, if running on iOS 8
    if ([application respondsToSelector:@selector(registerUserNotificationSettings:)])
    {
        UIUserNotificationType userNotificationTypes = (UIUserNotificationTypeAlert |
                                                        UIUserNotificationTypeBadge |
                                                        UIUserNotificationTypeSound);
        UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:userNotificationTypes
                                                                                 categories:nil];
        [application registerUserNotificationSettings:settings];
        [application registerForRemoteNotifications];
    }
    else
    {
        // Register for Push Notifications, if running iOS version < 8
        [application registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge |
                                                         UIRemoteNotificationTypeAlert |
                                                         UIRemoteNotificationTypeSound)];
    }
}

void App42Bridge::didReceiveRemoteNotification(const char* message)
{
    App42PushHelper::didReceiveRemoteNotification(message);
}



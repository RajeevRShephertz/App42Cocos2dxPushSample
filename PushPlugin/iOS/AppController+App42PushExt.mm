//
//  AppController+App42PushExt.m
//  MyGame
//
//  Created by Rajeev Ranjan on 29/12/14.
//
//

#import "AppController+App42PushExt.h"
#import "App42Bridge.h"

@implementation AppController (App42PushExt)


-(void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSLog(@"%s",__func__);
}


-(void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
{
    NSLog(@"%s",__func__);
}

-(void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    NSLog(@"%s",__func__);
    NSString *devToken = [[[[deviceToken description]
                            stringByReplacingOccurrencesOfString:@"<" withString:@""]
                           stringByReplacingOccurrencesOfString:@">" withString:@""]
                          stringByReplacingOccurrencesOfString: @" " withString: @""];
    NSLog(@"%s....devToken = %@",__func__,devToken);
    App42Bridge::deviceDidRegisteredForPush([devToken UTF8String]);
}

-(void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    NSLog(@"%s...userInfo =%@",__func__,userInfo);
    if (userInfo)
    {
        NSError *error = nil;
        NSData *jsonData = [NSJSONSerialization dataWithJSONObject:userInfo options:0 error:&error];
        if (!error) {
            NSString *string = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            const char* msg = [string UTF8String];
            App42Bridge::didReceiveRemoteNotification(msg);
        }
        else
        {
            const char* msg = "Error in parsing received message";
            App42Bridge::didReceiveRemoteNotification(msg);
        }
    }
}

@end

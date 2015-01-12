//
//  App42Bridge.h
//  MyGame
//
//  Created by Rajeev Ranjan on 29/12/14.
//
//

#include <iostream>


class App42Bridge {
    
public:
    
    static void registerForPush();
    
    static void deviceDidRegisteredForPush(const char* deviceToken);
    
    static void registerApplicationForPushNotification();
    
    static void didReceiveRemoteNotification(const char* message);
};

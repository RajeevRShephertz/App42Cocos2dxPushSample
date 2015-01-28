//
//  App42PushHelper.cpp
//  MyGame
//
//  Created by Rajeev Ranjan on 29/12/14.
//
//

#include "App42PushHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

#define GOOGLE_PROJECT_NUMBER "1043599038916" //Needed for android

static app42PushCallback onDeviceToken;
static app42PushCallback onPushReceived;

void getCallBack(const char* devToken)
{
    log("\n\ngetCallBack = %s\n\n",devToken);
    onDeviceToken(devToken);
}

void setCallBack(const app42PushCallback& _callback)
{
    onDeviceToken = _callback;
}

void callOnPushReceived(const char* msg)
{
    onPushReceived(msg);
}


extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jint Java_app42_push_coco_PushHelper_sendRegId(JNIEnv *env, jobject obj,jstring regId){
        const char* devToken= (const char*)(env)->GetStringUTFChars(regId,0);
        getCallBack(devToken);
        return 1;
    }
#endif
}

extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    jint Java_app42_push_coco_PushHelper_sendMessage(JNIEnv *env, jobject obj,jstring message){
        printf("Send message");
        
        const char* msg= (const char*)(env)->GetStringUTFChars(message,0);
        callOnPushReceived(msg);
        return 11;
    }
#endif
}

void App42PushHelper::registerForPush(const app42PushCallback& _callback)
{
    setCallBack(_callback);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    
    if(JniHelper::getStaticMethodInfo(t,"app42/push/coco/PushHelper","registerForPush","(Ljava/lang/String;)V"))
    {
        const char* googleProjectNumber = GOOGLE_PROJECT_NUMBER;
        jstring stringArg1 = t.env->NewStringUTF(googleProjectNumber);
        t.env->CallStaticVoidMethod(t.classID,
                                    t.methodID,
                                    stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    App42Bridge::registerForPush();
#endif
}

void getLastMsg()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    JniMethodInfo t;
    if(JniHelper::getStaticMethodInfo(t,"app42/push/coco/PushHelper","getLastMeassage","(V;)Ljava/lang/String;"))
    {
        jstring message= (jstring)t.env->CallStaticObjectMethod(t.classID,
                                                                t.methodID);
        char* msg= (char*)(t.env)->GetStringUTFChars(message,0);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(message);
    }
#endif
}

void App42PushHelper::didRegisterForRemoteNotificationsWithDeviceToken(const char* deviceToken)
{
    onDeviceToken(deviceToken);
}

void App42PushHelper::didReceiveRemoteNotification(const char* message)
{
    onPushReceived(message);
}

void App42PushHelper::setPushCallBack(const app42PushCallback& _callback)
{
    onPushReceived = _callback;
}



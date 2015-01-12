package app42.push.coco;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;
import org.cocos2dx.lib.Cocos2dxActivity;

import com.google.android.gcm.GCMRegistrar;

public class PushHelper {
	
	private static final String LastMessage="lastMessage";
	private static final String AppName="cocoApp42Push";
	static {
        try {
        	Log.i("App42Push","####################");
            Log.i("App42Push", "Trying to load cpp_empty_test.so");
            System.loadLibrary("cpp_empty_test");
            Log.i("App42Push", "Library sussceccccc;padd");
        }
        catch (UnsatisfiedLinkError ule) {
            Log.e("App42Push", "WARNING: Could not load cpp_empty_test.so");
        }
    
    }
	/*
	 * This function allows to register device for PushNotification service
	 */
	public static void registerForPush(String projectNo){
		Log.i("App42Push","Call From Native Side");
		Log.i("App42Push","####################");
		Log.i("App42Push",projectNo);
		Context context=Cocos2dxActivity.getContext();
		GCMRegistrar.checkDevice(context);
		GCMRegistrar.checkManifest(context);
		final String deviceId = GCMRegistrar.getRegistrationId(context);
		if (deviceId.equals("")) {
			try {
				GCMRegistrar.register(context, projectNo);
			} catch (Throwable e) {
				e.printStackTrace();
			}
		}
		else{
			Log.i("App42Push","####################");
			Log.i("App42Push",deviceId);
			int id=sendRegId(deviceId);
			Log.i("App42Push",""+id);
		}
	}

	public static String getLastMeassage(){
		Log.i("App42Push","###########getLastMeassage#########");
		App42GCMService.msgCount=0;
		SharedPreferences sharedPreference = Cocos2dxActivity.getContext().getSharedPreferences(
				AppName, Cocos2dxActivity.getContext().MODE_PRIVATE);
		return sharedPreference
				.getString(LastMessage, "");
		//return "Hey Whts Up get the  messahe";

	}
	
	static void saveLastMessage(String message){
		SharedPreferences sharedPreference = Cocos2dxActivity.getContext().getSharedPreferences(
				AppName, Cocos2dxActivity.getContext().MODE_PRIVATE);
		SharedPreferences.Editor prefEditor = sharedPreference.edit();
		prefEditor.putString(LastMessage, message);
		prefEditor.commit();
	}
	public static native int sendRegId(String regId);
	public static native int sendMessage(String message);
	
}

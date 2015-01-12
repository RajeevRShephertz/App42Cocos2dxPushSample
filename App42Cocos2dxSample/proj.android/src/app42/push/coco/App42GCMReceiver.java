package app42.push.coco;

import com.google.android.gcm.GCMBroadcastReceiver;

import android.content.Context;

public class App42GCMReceiver extends GCMBroadcastReceiver{
	@Override
	protected String getGCMIntentServiceClassName(Context context) { 
		return "app42.push.coco.App42GCMService"; 
	} 
}

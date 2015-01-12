package app42.push.coco;

import java.io.IOException;
import java.io.InputStream;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.util.Log;

import com.google.android.gcm.GCMBaseIntentService;

public class App42GCMService extends GCMBaseIntentService {

	public static int msgCount = 0;
	public static String notificationMessage = "";
	static String projectNo = "<Your Project No>";
	public App42GCMService() {
		super(projectNo);
	}

	@Override
	protected void onError(Context arg0, String arg1) {
		Log.i(TAG, "Device registered: regId = " + arg1);
	}

	@Override
	protected void onMessage(Context context, Intent intent) {

		Bundle b = intent.getExtras();
		String message = (String) b.get("message");
		Log.i("App42Push", "Received message " + message);
		notificationMessage = message;
		generateNotification(context, message);
		try {
			PushHelper.sendMessage(message);
		} catch (Throwable e) {
			Log.e("App42 Exception", e.getMessage());

		}
		// TODO: handle exception
	}

	@Override
	protected void onDeletedMessages(Context context, int total) {
		Log.i("App42Push", "Received deleted messages notification");
		String message = "" + total + "Message deleted ";
		generateNotification(context, message);
	}

	@Override
	protected void onRegistered(Context context, String registrationId) {
		try {
			Log.i("App42Push", "Device registered: regId = " + registrationId);
			PushHelper.sendRegId(registrationId);
		} catch (Throwable e) {
			Log.e("App42 Exception", e.getMessage());

		}

	}

	@Override
	protected void onUnregistered(Context arg0, String arg1) {
		Log.i("App42Push", "onUnregistered " + arg1);
	}

	/**
	 * Issues a notification to inform the user that server has sent a message.
	 */
	private void generateNotification(Context context, String message) {

		long when = System.currentTimeMillis();
		String activityName = null;
		try {
			activityName = getActivtyName();
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		NotificationManager notificationManager = (NotificationManager) context
				.getSystemService(Context.NOTIFICATION_SERVICE);
		Intent notificationIntent;
		try {
			notificationIntent = new Intent(context,
					Class.forName(activityName));
		} catch (Exception e) {
			notificationIntent = new Intent();

		}
		// set intent so it does not start a new activity
		notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP
				| Intent.FLAG_ACTIVITY_SINGLE_TOP);
		PendingIntent intent = PendingIntent.getActivity(context, 0,
				notificationIntent, PendingIntent.FLAG_UPDATE_CURRENT);

		Notification notification = new NotificationCompat.Builder(context)
				.setContentTitle("App42Sample").setContentText(message)
				.setContentIntent(intent)
				.setSmallIcon(android.R.drawable.ic_dialog_info).setWhen(when)
				.setNumber(++msgCount).setLargeIcon(getBitmapFromAssets())
				.setLights(Color.YELLOW, 1, 2).setAutoCancel(true).build();

		notification.defaults |= Notification.DEFAULT_SOUND;
		notification.defaults |= Notification.DEFAULT_VIBRATE;
		notificationManager.notify(0, notification);
	}

	public Bitmap getBitmapFromAssets() {
		AssetManager assetManager = getAssets();
		InputStream istr;
		try {
			istr = assetManager.open("app_icon.png");
			Bitmap bitmap = BitmapFactory.decodeStream(istr);
			return bitmap;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}

	}
	private String getActivtyName() {

		String activityName = null;
		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(
					this.getPackageName(), PackageManager.GET_META_DATA);
			Bundle aBundle = ai.metaData;
			return aBundle.getString("onMessageOpen");
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();

		}
		return activityName;
	}

}

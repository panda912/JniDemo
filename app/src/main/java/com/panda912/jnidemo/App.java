package com.panda912.jnidemo;

import android.app.Application;

/**
 * Created by panda on 2018/5/3 上午10:50.
 */
public class App extends Application {

    private static App sInstance;

    public static App getInstance() {
        return sInstance;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        sInstance = this;
    }
}

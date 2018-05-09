package com.panda912.jnidemo.blur;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by panda on 2018/5/2 下午6:29.
 */
public class BlurManager {
    static final int EXECUTOR_THREADS = Runtime.getRuntime().availableProcessors();
    static final ExecutorService EXECUTOR = Executors.newFixedThreadPool(EXECUTOR_THREADS);
}

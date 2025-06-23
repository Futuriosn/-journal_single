package com.huatai.ficc.aurora.journal.proxy;

public class FrameNative {
    public static native void destroy(long pFrame);

    public static native boolean hasData(long pFrame);

    public static native long genTime(long pFrame);

    public static native int msgType(long pFrame);

    public static native byte[] dataAsBytes(long pFrame);
}

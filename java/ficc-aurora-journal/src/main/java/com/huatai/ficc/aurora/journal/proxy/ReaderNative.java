package com.huatai.ficc.aurora.journal.proxy;

public class ReaderNative {
    public static native void destroy(long pReader);

    public static native long createReader(boolean lazy);

    public static native int join(long pReader,
                                   String home,
                                   String name,
                                   long fromTime,
                                   int ps,
                                   int destId);

    public static native void disJoin(long pReader, int location_uid);

    public static native boolean dataAvailable(long pReader);

    public static native void seekToTime(long pReader, long nanoTime);

    public static native long currentFrame(long pReader);

    public static native void next(long pReader);
}

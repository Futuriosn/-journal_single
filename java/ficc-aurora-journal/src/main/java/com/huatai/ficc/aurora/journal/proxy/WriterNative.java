package com.huatai.ficc.aurora.journal.proxy;

public class WriterNative {
    public static native long createWriter(String home,
                                           String name,
                                           int ps,
                                           int destId,
                                           boolean lazy);

    public static native void destroy(long pWriter);

    public static native void writeBytesWithTime(long pWriter,
                                                 long genTime,
                                                 int msgType,
                                                 byte[] data,
                                                 int length);
}

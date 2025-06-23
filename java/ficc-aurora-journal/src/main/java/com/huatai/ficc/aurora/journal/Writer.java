package com.huatai.ficc.aurora.journal;

import com.huatai.ficc.aurora.journal.proxy.WriterNative;

public class Writer {
    private long pWriter;

    public Writer(String home,
                  String name,
                  PageSize ps) {
        this(home, name, ps, 0, false);
    }

    public Writer(String home,
                  String name,
                  PageSize ps,
                  int destId,
                  boolean lazy) {
        pWriter = WriterNative.createWriter(home, name, ps.ordinal(), destId, lazy);
    }

    public void finalize() {
        WriterNative.destroy(pWriter);
    }

    public void writeBytesWithTime(long genTime, int msgType, byte[] data, long triggerTime) {
        WriterNative.writeBytesWithTime(pWriter, genTime, msgType, data, data.length, triggerTime);
    }

    public void writeBytes(int msgType, byte[] data, long triggerTime) {
        WriterNative.writeBytes(pWriter,triggerTime, msgType, data, data.length);
    }

}

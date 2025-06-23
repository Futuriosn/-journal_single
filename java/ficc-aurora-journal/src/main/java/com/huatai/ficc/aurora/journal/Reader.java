package com.huatai.ficc.aurora.journal;

import com.huatai.ficc.aurora.journal.proxy.ReaderNative;

public class Reader {
    private long pReader;

    public Reader() {
        this(false);
    }

    public Reader(boolean lazy) {
        pReader = ReaderNative.createReader(lazy);
    }

    public void finalize() {
        ReaderNative.destroy(pReader);
    }

    public void join(String home,
                     String name,
                     long fromTime,
                     PageSize ps) {
        join(home, name, fromTime, ps, 0);
    }

    public int join(String home,
                    String name,
                    long fromTime,
                    PageSize ps,
                    int destId) {
        return ReaderNative.join(pReader, home, name, fromTime, ps.ordinal(), destId);
    }

    public void disJoin(int location_uid) {
        ReaderNative.disJoin(pReader, location_uid);
    }

    public boolean dataAvailable() {
        return ReaderNative.dataAvailable(pReader);
    }

    public void seekToTime(long nanoTime) {
        ReaderNative.seekToTime(pReader, nanoTime);
    }

    public Frame currentFrame() {
        long pFrame = ReaderNative.currentFrame(pReader);
        return new Frame(pFrame);
    }

    public void next() {
        ReaderNative.next(pReader);
    }

}

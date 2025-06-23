package com.huatai.ficc.aurora.journal;

import com.huatai.ficc.aurora.journal.proxy.FrameNative;

public class Frame {
    private long pFrame;

    public Frame(long pFrame) {
        this.pFrame = pFrame;
    }

    public void finalize() {
        FrameNative.destroy(pFrame);
    }

    public boolean hasData() {
        return FrameNative.hasData(pFrame);
    }

    public long genTime() {
        return FrameNative.genTime(pFrame);
    }

    public int msgType() {
        return FrameNative.msgType(pFrame);
    }

    public byte[] dataAsBytes() {
        return FrameNative.dataAsBytes(pFrame);
    }
}

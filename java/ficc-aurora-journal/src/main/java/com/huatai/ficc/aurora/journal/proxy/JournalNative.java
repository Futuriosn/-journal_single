package com.huatai.ficc.aurora.journal.proxy;

public class JournalNative {
    public static void loadLibrary(String cppLibName) {
        System.loadLibrary(cppLibName);
    }
}

//
// Created by root on 2023/8/16.
//

#ifndef JOURNAL_UTILS_H
#define JOURNAL_UTILS_H


static std::string jstringToStdString(JNIEnv *env, jstring jstr) {
    if (jstr == NULL) {
        return "";
    }
    char *chars = (char *) env->GetStringUTFChars(jstr, NULL);
    std::string ret(chars);
    env->ReleaseStringUTFChars(jstr, chars);
    return ret;
}

#endif //JOURNAL_UTILS_H

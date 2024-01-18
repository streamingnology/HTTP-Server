#include "HttpServerJNI.h"
#include <jni.h>
#include "HttpServer.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_streamingnology_httpserver_HttpServer_nativeHttpServerCreate(JNIEnv *env, jobject thiz) {
    HttpServer* http_server = new HttpServer();
    return reinterpret_cast<long>(http_server);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_streamingnology_httpserver_HttpServer_nativeHttpServerOpen(JNIEnv *env, jobject thiz,
                                                                    jlong native_http_server_instance,
                                                                    jstring root, jint port) {
    const char *web_root = env->GetStringUTFChars(root, NULL);
    HttpServer* http_server = (HttpServer*) native_http_server_instance;
    if (http_server != nullptr)
        return http_server->open(web_root, port);

    return -1;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_streamingnology_httpserver_HttpServer_nativeHTTPServerStart(JNIEnv *env, jobject thiz,
                                                                     jlong native_http_server_instance) {
    HttpServer* http_server = (HttpServer*) native_http_server_instance;
    if (http_server != nullptr)
        return http_server->start();

    return -1;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_streamingnology_httpserver_HttpServer_nativeHttpServerStop(JNIEnv *env, jobject thiz,
                                                                    jlong native_http_server_instance) {
    HttpServer* http_server = (HttpServer*) native_http_server_instance;
    if (http_server != nullptr)
        http_server->stop();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_streamingnology_httpserver_HttpServer_nativeHttpServerDelete(JNIEnv *env, jobject thiz,
                                                                     jlong native_http_server_instance) {
    HttpServer* http_server = (HttpServer*) native_http_server_instance;
    if (http_server) {
        delete http_server;
    }
}
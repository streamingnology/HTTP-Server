package com.streamingnology.httpserver;

public class HttpServer {
    private String TAG = "HttpServer";
    private String root = "";
    private int port = 8080;
    private long   nativeHttpServer = 0;

    static {
        System.loadLibrary("httpserver");
    }

    public HttpServer(String root, int port) {
        this.root = root;
        this.port = port;
    }

    public int open() {
        if (nativeHttpServer != 0)
            return 0;

        nativeHttpServer = nativeHttpServerCreate();
        return nativeHttpServerOpen(nativeHttpServer, this.root, this.port);
    }

    public int start() {
        if (nativeHttpServer == 0)
            return -1;

        return nativeHTTPServerStart(nativeHttpServer);
    }

    public void stop() {
        if (nativeHttpServer == 0)
            return;

        nativeHttpServerStop(nativeHttpServer);
    }

    public void close() {
        if (nativeHttpServer == 0)
            return;

        nativeHttpServerDelete(nativeHttpServer);
        nativeHttpServer = 0;
    }

    private native long nativeHttpServerCreate();
    private native int nativeHttpServerOpen(long nativeHttpServerInstance, String root, int port);
    private native int nativeHTTPServerStart(long nativeHttpServerInstance);
    private native void nativeHttpServerStop(long nativeHttpServerInstance);
    private native void nativeHttpServerDelete(long nativeHttpServerInstance);

}

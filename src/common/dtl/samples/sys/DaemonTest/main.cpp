/***************************************************************************************************
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	测试后台服务

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/
#include <dtprec.h>
#include <dtl/dtl.h>

#include <event.h>
#include <evhttp.h>



/* 子进程信号处理 */
void kill_signal_worker(const int sig) {

	// TODO 工作线程在正常退出时做安全处理

    exit(0);
}


/* 处理模块 */
void httpsqs_handler(struct evhttp_request *req, void *arg)
{
        struct evbuffer *buf;
        buf = evbuffer_new();

		/* 分析URL参数 */	
		const char *httpsqs_query_part;
		struct evkeyvalq httpsqs_http_query;
		httpsqs_query_part = evhttp_uri_get_query(req->uri_elems);
		evhttp_parse_query_str(httpsqs_query_part, &httpsqs_http_query);
		
		/* 接收GET表单参数 */
		const char *httpsqs_input_auth = evhttp_find_header (&httpsqs_http_query, "auth"); /* 队列名称 */

		evbuffer_add_printf(buf, "%s", httpsqs_input_auth);


		/* 输出内容给客户端 */	
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
		
		/* 内存释放 */
		evhttp_clear_headers(&httpsqs_http_query);
		evbuffer_free(buf);
}


int main(int argc, char *argv[], char *envp[])
{

	Daemon::init ("hanxin", argc, argv, envp, kill_signal_worker);



	char *httpsqs_settings_listen = "0.0.0.0";
	int httpsqs_settings_port = 1220;


	int httpsqs_settings_timeout = 60; /* 单位：秒 */



	/* 请求处理部分 */
    struct evhttp *httpd;

    event_init();
    httpd = evhttp_start(httpsqs_settings_listen, httpsqs_settings_port);
	if (httpd == NULL) {
		fprintf(stderr, "Error: Unable to listen on %s:%d\n\n", httpsqs_settings_listen, httpsqs_settings_port);
		kill(0, SIGTERM);
		exit(1);		
	}

	evhttp_set_timeout(httpd, httpsqs_settings_timeout);

    /* Set a callback for requests to "/specific". */
    /* evhttp_set_cb(httpd, "/select", select_handler, NULL); */

    /* Set a callback for all other requests. */
    evhttp_set_gencb(httpd, httpsqs_handler, NULL);

    event_dispatch();

    /* Not reached in this code as it is now. */
    evhttp_free(httpd);

}


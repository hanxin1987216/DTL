/***************************************************************************************************
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	���Ժ�̨����

Author:
	����

Creating Time:
	2011-10-10
***************************************************************************************************/
#include <dtprec.h>
#include <dtl/dtl.h>

#include <event.h>
#include <evhttp.h>



/* �ӽ����źŴ��� */
void kill_signal_worker(const int sig) {

	// TODO �����߳��������˳�ʱ����ȫ����

    exit(0);
}


/* ����ģ�� */
void httpsqs_handler(struct evhttp_request *req, void *arg)
{
        struct evbuffer *buf;
        buf = evbuffer_new();

		/* ����URL���� */	
		const char *httpsqs_query_part;
		struct evkeyvalq httpsqs_http_query;
		httpsqs_query_part = evhttp_uri_get_query(req->uri_elems);
		evhttp_parse_query_str(httpsqs_query_part, &httpsqs_http_query);
		
		/* ����GET������ */
		const char *httpsqs_input_auth = evhttp_find_header (&httpsqs_http_query, "auth"); /* �������� */

		evbuffer_add_printf(buf, "%s", httpsqs_input_auth);


		/* ������ݸ��ͻ��� */	
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
		
		/* �ڴ��ͷ� */
		evhttp_clear_headers(&httpsqs_http_query);
		evbuffer_free(buf);
}


int main(int argc, char *argv[], char *envp[])
{

	Daemon::init ("hanxin", argc, argv, envp, kill_signal_worker);



	char *httpsqs_settings_listen = "0.0.0.0";
	int httpsqs_settings_port = 1220;


	int httpsqs_settings_timeout = 60; /* ��λ���� */



	/* �������� */
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


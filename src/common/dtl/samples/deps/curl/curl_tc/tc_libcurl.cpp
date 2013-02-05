/***************************************************************************************************
tc_libcurl.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: libcurl

Author:
	chen.dawei@datatom.com

Creating Time:
	2012-11-1
***************************************************************************************************/
#include <dtprec.h>
#include <dtl/dtl.h> 	
#include <curl/curl.h>

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb,
                        void *stream)
{
  // struct FtpFile *out=(struct FtpFile *)stream;
  // if(out && !out->stream) {
    // /* open file for writing */
    // out->stream=fopen(out->filename, "wb");
    // if(!out->stream)
      // return -1; /* failure, can't open file to write */
  // }
  // cout << (char*)buffer << endl;
  // return fwrite(buffer, size, nmemb, out->stream);

	cout << (char*)buffer << endl;
	return nmemb;
 }

int main(void)
{
	InitDTLibrary();
	try{
INIT_MS_TIME
START_MS_TIME
		for(int i = 0; i< 1000 ; i++) {	
			CURL *curl;
			CURLcode res;
			struct curl_slist *headerlist=NULL;	
			//初始化curl
			curl_global_init(CURL_GLOBAL_ALL);	
			curl = curl_easy_init();
			
			if(curl){
				//发送url
				curl_easy_setopt(curl,CURLOPT_URL,"http://192.168.1.126:8888");
				//发送KV值
				headerlist = curl_slist_append(headerlist, "name:hanxin");;
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=dawei");
				//curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);	
				
				/* Define our callback to get called when there's data to be written */
				//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
			}
						
			res = curl_easy_perform(curl);
			curl_slist_free_all(headerlist);
			//若是发送失败，显示失败信息
			if(res != CURLE_OK)
				fprintf(stderr,"curl_easy_perform() failed:%s",(char*)curl_easy_strerror(res));
			//curl_share_cleanup(share);
			curl_easy_cleanup(curl);		
			curl_global_cleanup();		
		}
		FINISH_MS_TIME
		PRINT_MS_TIME
	}catch(Exception &e){
		printf("faied: %s\n",e.toString().getCStr());
	}

		return 0;
}

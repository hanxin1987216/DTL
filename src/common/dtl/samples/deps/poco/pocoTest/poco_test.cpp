#include <dtprec.h>
#include <dtl/dtl.h>
#import <Poco/Net/HTTPClientSession.h>
#import <Poco/URI.h>
#import <Poco/Net/HTTPCredentials.h>
#import <Poco/Net/HTTPBasicCredentials.h>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/Net.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Net/PartSource.h"
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/StringPartSource.h>
#include <Poco/FileStream.h>
#include <Poco/Foundation.h>
#include <Poco/RefCountedObject.h>
#include <Poco/PipeImpl.h>
#include <Poco/Pipe.h>
#include <Poco/Process_UNIX.h>
#include "Poco/Process.h"
#include "Poco/PipeStream.h"


#include <sdevmgm/devmgm.h>


using Poco::Net::ServerSocket;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::StreamCopier;
using Poco::PipeImpl;
using Poco::ProcessHandle;
using Poco::Pipe;
using Poco::PipeInputStream;
using Poco::PipeOutputStream;

int main(int argc, char** argv)
{
	try
	{
		int64 capacity;
		int64 free;
		cout << DevMgm::getCapacity("/mnt/hgfs", capacity) << endl;
		cout << capacity << endl;
		
		cout << DevMgm::getFreeSpace("/mnt/hgfs", free) << endl;
		cout << free << endl;
		
		cout << DevMgm::mount("/home/idmldata","/home/idmldata")  << endl;
		
					// static int getCapacity(const String &devname, int64 &capacity);
			// static int getFreeSpace(const String &devname, int64 &freespace);
			// static int umount(const String &devpath);
			// static int isMount(const String &devpath);
			// static int getMountPoint(const String &devpath, String &mountpoint);
			// static int mount(const String &srcpath
											// , const String &destpath
											// , const int storageType = LOCAL_STORAGE
											// , const String &hostip = String::EMPTY
											// , const String &user = String::EMPTY
											// , const String &passwd = String::EMPTY);
		
		
	}
	catch(Exception &e)
	{
		cout << e.toString().getCStr()  << endl;
	}
}
#include <dtprec.h>
#include <dtl/dtl.h>

INIT_TIME;

int main (int argc, char** argv)
{	
	try {

		InitDTLibrary ();
		
		
		JsonTextWriter writer;	
		writer.StartObject();
			writer.WriteElement("code",1111);
			writer.WriteElement("msg", "create file success!");
			writer.StartObject ("result");
				writer.StartArray ("idml_data");
					writer.StartObject ();
						writer.WriteElement("fileid", "aaaaaaaaaaaaa");	
						writer.WriteElement ("uid", "ttttttttttt");	
						writer.WriteElement ("name", "xxxxxxxxxxxxxxx");
					writer.EndObject ();
					writer.StartObject ();
						writer.WriteElement("fileid", "aaaaaaaaaaaaa");	
						writer.WriteElement ("uid", "ttttttttttt");	
						writer.WriteElement ("name", "xxxxxxxxxxxxxxx");
					writer.EndObject ();					
				writer.EndArray ();	
			writer.EndObject ();
		writer.EndObject ();	
		
		cout << writer.getJsonStr().getCStr() << endl;
		
		
		cJSON* pRoot = cJSON_Parse(writer.getJsonStr().getCStr());

		String res = cJSON_GetValueToStr(pRoot, "result");	
		cout << res.getCStr() << endl;
		
		cJSON* idmldata = cJSON_Parse(res.getCStr());
		String data = cJSON_GetValueToStr(idmldata, "idml_data");
		
		if (!data.isEmpty()) {
			cJSON* arr = cJSON_Parse(data.getCStr());
			
			cout << "arr size:" << cJSON_GetArraySize(arr) << endl;
			
			cJSON* item1 = cJSON_GetArrayItem(arr, 0);
			cout << "item1: " << cJSON_Print(item1) << endl;
		}
		return 0; 
	}
	catch (Exception& e)
	{
		cout << e.toString().getCStr() << endl;
	}
	
	return 0;
}


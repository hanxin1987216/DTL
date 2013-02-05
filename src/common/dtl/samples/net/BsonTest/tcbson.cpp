#include <dtprec.h>
#include <dtl/dtl.h>

void testfunc1 ()
{
	DTL_ADD_PROFILER_CODE ();
	
	cout << genMachineCode ().getCStr() << endl;
}

void testfunc2()
{
	DTL_ADD_PROFILER_CODE ();
	int64 a = 0;
	for (int i= 0; i< 100000000; i++)
		a += i;
	
	cout << "a = " << a << endl;
 }



int main ()
{	

	InitDTLibrary ();
	
	testfunc1 ();
	testfunc2 ();
	
	PerformanceProfiler::getInstance ()->print ();

	return 0;

	//
	// 测试bson简单构造 和 to Buffer
	bson a;
	bson_init( &a);
	bson_append_string (&a, "name", "hanxin");
	bson_finish (&a);

	bson b;

	bson_init( &b );
	bson_append_string( &b, "name", "Joe" );
	bson_append_binary (&b, "data", BSON_BIN_BINARY, 0, 0);

	bson_append_bson (&b, "parent", &a);
	bson_finish( &b );


	cout << "bson_size: " <<bson_size (&b) << endl;
	bson_print (&b);

	const char *data = bson_data (&b); 
	 
	// 
	// 测试通过 buffer 构造 bson_iterator 迭代器
	bson *bnew = bson_create ();
	bson_iterator it;
	bson_iterator_from_buffer (&it, data);
	if (bson_iterator_more (&it))
		cout << "has more" << endl;
	else
		cout << "has no more" << endl;
	  
	cout << "current point to:" << bson_iterator_key (&it) << ", bson_iterator_type : " << bson_iterator_type (&it)<< endl;
	
	
	//bson_iterator itbind2;
	//bson_find (&itbind2, bnew, "name");
	//cout << bson_iterator_string (&itbind2) << endl;
	
	
	cout << "begin to loop:" << endl;
	while (bson_iterator_more (&it)) {
	
		cout << "now: " << bson_iterator_key (&it) << ", ";

		if (String(bson_iterator_key (&it)) != String("data")) {
			cout  << bson_iterator_string (&it) << endl;

			bson_iterator_next (&it);
		}
		else {
			break;
		}
	}
	
	int len = bson_iterator_bin_len (&it);
	cout << "bson_iterator_bin_type = " << bson_iterator_bin_type (&it) << endl;
	cout << "datalen =" << len << ", data = " << String(bson_iterator_bin_data (&it), len).getCStr () << endl;
	
	if (bson_iterator_more (&it))
		cout << "has more" << endl;
	else
		cout << "has no more" << endl;
		
	bson_iterator_next (&it);	
	bson *sub = bson_create ();;
	bson_iterator_subobject (&it, sub);
	bson_print (sub);

	
	
	//
	// 测试通过 Buffer构造 Bson 对象
	bson *in = bson_create ();
	bson_init_data (in, (char *)data);
	cout << "---------------------------------" << endl;
	bson_print (in);
	
	bson_iterator itbind;
	bson_find (&itbind, in, "name");
	cout << "name = " << bson_iterator_string (&itbind) << endl;
	
	int type = bson_find (&itbind, in, "hhhhhh");
	cout << "type = " << type << endl;
	
	
	
	 // free
	bson_destroy (&a);
	bson_destroy (&b); 
	bson_dispose (bnew);
	bson_dispose (sub);
	bson_dispose (in);
	  
	return 0;
}


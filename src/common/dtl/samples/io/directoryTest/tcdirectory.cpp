#include <dtprec.h>
#include <dtl/dtl.h>
#include <pthread.h>

#define LIMIT 100000
#define _TOSTR(v) #v
#define TOSTR(v) _TOSTR(v)

void create(void) {
    File fs = File("/home/fan/test99999");
    printf("\ntesting %s\n",fs.getName().getCStr());
    if (fs.exists()) { return; }

    char fname[40] = {0};
    printf("\n-----creating file----");
    for (int i=0; i<LIMIT; i++) {
        sprintf(fname, "/home/fan/test%d",i);
        FILE *p = fopen(fname,"w");
        if (p == NULL) { continue; }
        fprintf(p, "stub 1024\n");
        fclose(p);
    }
    printf("\n-----finished----\n");
}

int main() {
    String a = "01234567";
    size_t f2 = a.find("5");
    String b = String(a, f2+1 );
    printf("%s\n",b.getCStr());
    //create();
    Directory dr = Directory("./testdir");
    //dr.create();
    vector<String> vlist;
    if (dr.exists()) {
        dr.listFiles(vlist);
    }
    dr.removeTree();
    //printf("lenth of vlist %u\n",vlist.size());
    //Directory dr2 = Directory(".");
    //printf("dr2 is %s\n",dr2.getName().getCStr());
    //dr2.listFiles(vlist);
    //for(int i=0; i<vlist.size(); i++) {
    //    cout<< vlist[i].getCStr() <<" ";
    //}
    cout<<endl;
}

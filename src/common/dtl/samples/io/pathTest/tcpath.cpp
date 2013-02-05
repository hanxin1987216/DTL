#include <dtprec.h>
#include <dtl/dtl.h>
#include <pthread.h>


int main() {
//test adaptSep
    String p1 = "///abcdefg/////sdf//dfdf/";
    String p1s = Path::adaptSep(p1).getCStr();
    vector<String> substr;
    p1.split("/", substr);

    for(vector<String>::iterator it = substr.begin();
            it != substr.end();
            ++it) {
        cout<< (*it).getCStr()<<"|";
    }
    cout<< endl;

    cout<< p1s.getCStr()
        << " / pos end:"
        << p1s.findLastOf(Path::separator,String::NO_POSITION)
        << " / pos0:"
        << p1s.findLastOf(Path::separator)
        << endl;

    String p2 = "//server/mnt//sdf//dfdf\\s?dfd";
    String p2s = Path::adaptSep(p2).getCStr();
    cout<< p2s.getCStr()<<endl;

    String p3 = "//c";
    String p4 = "//./.../";
    String p5 = "asdfasdfvcvc?<MNIOIUJ";

    String d,f;
    Path::split(p1, d, f);
    cout<< d.getCStr()<<"----"<< f.getCStr()<< endl;
    Path::split(p2, d, f);
    cout<< d.getCStr()<<"----"<< f.getCStr()<< endl;
    Path::split(p3, d, f);
    cout<< d.getCStr()<<"----"<< f.getCStr()<< endl;
    Path::split(p4, d, f);
    cout<< d.getCStr()<<"----"<< f.getCStr()<< endl;
    Path::split(p5, d, f);
    cout<< d.getCStr()<<"----"<< f.getCStr()<< endl;

    String t111 = "/a/";
    Path::split(t111, d, f);
    cout<< t111.getCStr()<<"----"<< d.getCStr()<< endl;

    String t112 = "/a";
    Path::split(t112, d, f);
    cout<< t112.getCStr()<<"----"<< d.getCStr()<< endl;


//    String segstring = "//a/.././b/c/..";
//    String c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "/";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "//";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "../../";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "../abc/efg/./../asd";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "a/";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "ab";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "./";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;
//
//    segstring = "..";
//    c = Path::posixHandleSegmentPath(segstring);
//    cout<< segstring.getCStr()<< " handeld:"<< c.getCStr()<< endl;

}

/*
 * protoc -I=./ --cpp_out=./ glist.proto
 * g++ glist.cpp glist.pb.cc `pkg-config --cflags --libs glib-2.0 protobuf` -g
 * */


#include <stdio.h>
#include <glib.h>
#include <string>
#include <sstream>
#include <google/protobuf/util/time_util.h>
#include "glist.pb.h"

using namespace std;

#if 1
typedef struct _sample_list_
{
    GList *list;
}sample_list;


int main ()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    GList *li;
    string ss = "";
    int j = 0;

    sample_list sl;
    sl.list = NULL;
    sl.list = g_list_append(sl.list,g_strdup("NVIDIA"));
    sl.list = g_list_append(sl.list,g_strdup("AMD"));
    sl.list = g_list_append(sl.list,g_strdup("INTEL"));
    sl.list = g_list_append(sl.list,g_strdup("QUALCOMM"));
    sl.list = g_list_append(sl.list,g_strdup("BROADCOM"));
    sl.list = g_list_append(sl.list,g_strdup("APPLE"));

    g_print ("Before Serialization\n");
    for(li = sl.list; li!= NULL; li = g_list_next(li))
    {
        char *string = (char *) li->data;
        g_print ("string = %s\n", string);
    }

    sample_glist sg;
    for(li = sl.list, j=0; li!= NULL; li = g_list_next(li), j++)
    {
        char *string = (char *) li->data;
        sg.add_data(string);
    }

    g_list_free(sl.list);
    
    ss.clear();
    sg.SerializeToString(&ss);

    cout << "serialized string size = " << ss.size() << endl;
    cout << "serialized string = " << ss.c_str() << endl;

    g_print ("After De-Serialization\n");

    sample_glist sg2;
    sg2.ParseFromString (ss);


    for (int j = 0; j < sg2.data_size(); j++)
    {
        string s = sg2.data(j);
        cout << "string = " << s << endl;
    }


    google::protobuf::ShutdownProtobufLibrary();
}
#else

int main ()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    string msg;

    Name name;

    name.set_name("viranjan");
    name.set_id(28);
    name.set_address("pune");

    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
            name.add_belongings ("car");
        else if (i == 1)
            name.add_belongings ("bicycle");
        else if (i == 2)
            name.add_belongings ("scooter");
        else if (i == 3)
            name.add_belongings ("plane");
    }

    name.SerializeToString(&msg);

    cout << "serialized string = " << msg << endl;

    Name name2;

    name2.ParseFromString(msg);

    cout << endl << "Deserialized string " << endl;
    cout << "name = " << name2.name() << endl;
    cout << "id = " << name2.id() << endl;
    cout << "address = " << name2.address() << endl;
    for (int j = 0; j < name2.belongings_size(); j++)
    {
        string s = name2.belongings(j);
        cout << "belongings = " << s << endl;
    }
}
#endif

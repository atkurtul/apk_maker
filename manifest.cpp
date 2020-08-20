
struct manifest {
    const char* package_name = "package";
    const char* app_label = "app";
    const char* activity_label = "app";
    const char* lib = "package";
    int target_sdk = 30;
    int min_sdk = 25;
};

#include "stdlib.h"
#include "stdio.h"
#include "fstream"
#include "string.h"
#include "unistd.h"
using namespace std;
int main(int argv, char** argc) {
    manifest man;
    char cwd[255];
    string out = getcwd(cwd, 255);

    for (int i = 1; i < argv; ++i)
    {
        if(argc[i][0] == '-') {
            if (strcmp(argc[i], "-p") == 0) man.package_name = argc[++i];
            if (strcmp(argc[i], "-d") == 0) man.activity_label = argc[++i];
            if (strcmp(argc[i], "-a") == 0) man.app_label = argc[++i];
            if (strcmp(argc[i], "-l") == 0) man.lib = argc[++i];
            if (strcmp(argc[i], "-sdk") == 0) {
                man.target_sdk = atoi(argc[++i]);
                man.min_sdk = atoi(argc[++i]);
            }
            if (strcmp(argc[i], "-o") == 0) out = argc[++i];
        } 
        else {
            printf("Invalid usage\n");
            return -1;
        }
    }
    printf("%s\n", out.data());
    ofstream xml(out + "/AndroidManifest.xml");

    xml << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";

    xml << "<manifest xmlns:android=\"http://schemas.android.com/apk/res/android\"\n";

    xml << "\t\tpackage=\"com." << man.package_name << "\"\n";
    xml << "\t\tandroid:versionCode=\"1\"\n";
    xml << "\t\tandroid:versionName=\"1.0\">\n\n";

    xml << "<uses-sdk android:targetSdkVersion=\"" << man.target_sdk << 
	    "\" android:minSdkVersion=\"" << man.min_sdk << "\"/>\n\n";

    xml << "<application android:allowBackup=\"false\"\n";
    xml << "\t\tandroid:fullBackupContent=\"false\"\n";
    xml << "\t\tandroid:label=\"" << man.app_label << "\"\n";
    xml << "\t\tandroid:hasCode=\"false\">\n\n";
    xml << "<activity android:name=\"android.app.NativeActivity\"\n";
    xml << "\t\tandroid:label=\"" << man.activity_label << "\"\n";
    xml << "\t\tandroid:configChanges=\"orientation|keyboardHidden\">\n\n";

    xml << "<meta-data android:name=\"android.app.lib_name\" android:value=\"" << man.lib << "\"/>\n\n";
    xml << "<intent-filter>\n";
    xml << "\t<action android:name=\"android.intent.action.MAIN\"/>\n";
    xml << "\t<category android:name=\"android.intent.category.LAUNCHER\"/>\n";
    xml << "</intent-filter>\n";
    xml << "</activity>\n";
    xml << "</application>\n";
    xml << "</manifest>\n";
}

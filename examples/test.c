//1. The .cc .cpp .cxx related header files
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/Object.h"
#include "lang/String.h"
#include "lang/StringBuffer.h"
#include "lang/Thread.h"
#include "lang/Integer.h"
#include "io/UnixFileSystem.h"
#include "io/FileOutputStream.h"
#include "io/BufferedOutputStream.h"
#include "util/HashMap.h"
#include "util/LinkedList.h"
#include "util/Vector.h"
#include "util/Size.h"
#include "net/UriCodec.h"
#include "sys/Bundle.h"
#include "content/Intent.h"
#include "net/Uri.h"
#include "Animal.h"
#include "Dog.h"
#include "PrimeRun.h"

void feedAnimal(Animal* a)
{
    printf("start feeding animals..\n");
    _M(a, eat);
    DELETE(a);
}

void test0()
{
    UnixFileSystem* fs = (UnixFileSystem*)Class(FileSystem).getFileSystem();
    String* path = NEW(String, "//usr//local//..//lib");
    String* newpath = _M(fs, normalize, path);
    printf("path = %s\n", _M(newpath, getCString));

    String* filepath = NEW(String, "/system/bin/test_oo");
    File* file = NEW(File, filepath);

    printf("file exists %d\n", _M(file, exists));
    String* canonicalPath = _M(file, getCanonicalPath);
    printf("canonicalPath = %s\n", _M(canonicalPath, getCString));

    DELETE(canonicalPath);
    DELETE(file);
    DELETE(filepath);
    DELETE(newpath);
    DELETE(path);
}

void test1()
{
    String* listItem1 = NEW(String, "List Item1");
    String* listItem2 = NEW(String, "List Item2");
    String* listItem3 = NEW(String, "List Item3");
    String* listItem4 = NEW(String, "List Item4");

    ObjectLinkedList* list = NEW(ObjectLinkedList);

    _M(list, add, (Object*)listItem1);
    _M(list, add, (Object*)listItem2);
    _M(list, add, (Object*)listItem3);
    _M(list, add, (Object*)listItem4);

    ObjectListIterator* it = _M(list, listIterator);
    while (_IM(it, hasNext)) {
        String* item = (String*)_IM(it, next);
        printf("%s %d>>> %s\n", __func__, __LINE__, _M(item, getCString));
    }
    DELETE(OBJECTOF(it));

    DELETE(listItem1);DELETE(listItem2);DELETE(listItem3);DELETE(listItem4);

    DELETE(list);
}

void test2()
{
    O2OHashMap* hashmap = NEW(O2OHashMap);
    String* key1 = NEW(String, "key1");
    String* value1 = NEW(String, "value1");
    _M(hashmap, put, (Object*)key1, (Object*)value1);
    String* key2 = NEW(String, "key2");
    String* value2 = NEW(String, "value2");
    _M(hashmap, put, (Object*)key2, (Object*)value2);

    String* key3 = NEW(String, "key3");
    String* value3 = NEW(String, "value3");
    _M(hashmap, put, (Object*)key3, (Object*)value3);

    String* key4 = NEW(String, "key4");
    String* value4 = NEW(String, "value4");
    _M(hashmap, put, (Object*)key4, (Object*)value4);

    for (int i = 0; i < 100; i++) {
        Object* objKey = NEW(Object);
        Object* objValue = NEW(Object);
        _M(hashmap, put, objKey, objValue);
        DELETE(objKey);
        DELETE(objValue);
    }

    printf("hashmap contains value3 ? %d\n", _M(hashmap, containsValue, (Object*)value3));
    //String* value3Removal = (String*)_M(hashmap, remove, (Object*)key3);
    //printf("hashmap contains value3 ? %d\n", _M(hashmap, containsValue, (Object*)value3));
    // printf("value3Removal %s\n", _M(value3Removal, getCString));
    //DELETE(value3Removal);
    printf("%s %d >>>>>\n", __func__, __LINE__);
    DELETE(key1); DELETE(value1);
    DELETE(key2); DELETE(value2);
    DELETE(key3); DELETE(value3);
    DELETE(key4); DELETE(value4);
    printf("%s %d >>>>>\n", __func__, __LINE__);
    DELETE(hashmap);
    printf("%s %d >>>>>\n", __func__, __LINE__);
}

void test3()
{
     Object* obj = NEW(Object);
     Animal* animal1 = NEW(Animal);
     Animal* animal2 = NEW(Animal, false, 10);
     _M(animal1, setAge, 100);
     printf("Animal1's age is %d\n", _M(animal1, getAge));
     printf("Animal2's age is %d\n", _M(animal2, getAge));

     _M(animal1, eat);
     _M(animal1, grow);

     Dog* dog = NEW(Dog);
     _M(dog, eat);
     _M(dog, grow);

     String* str = _M(dog, toString);
     printf("dog's type name:%s\n", _M(str, getCString));
     DELETE(str);

     str = _M(animal1, toString);
     printf("animal1's type name:%s\n", _M(str, getCString));
     DELETE(str);

     // if pass by pointer, reference count remains unchanged.
     // if pass by reference, reference count plus 1,
     //   and the callee need to DELETE it.
     feedAnimal(REFER(animal1));

     if (INSTANCEOF(dog, Animal))
         feedAnimal((Animal*)REFER(dog));

     str = NEW(String, "Hello,");
     printf("%s\n", _M(str, getCString));
     _M(str, concatCString, "World!");
     printf("%s\n", _M(str, getCString));

     _M0(str, format, "Hello, %s, 1+1=%d", "World", 2);
     printf("%s\n", _M(str, getCString));
     DELETE(str);

     DELETE(obj);
     DELETE(animal1);
     DELETE(animal2);
     DELETE(dog);

     StringBuffer* sb = NEW(StringBuffer);
     _M(sb, appendCString, "Hello, StringBuffer!");
     printf("StringBuffer : %s\n", _M(sb, getCString));

     _M(sb, insertCString, 7, "Can I have your name please ");
     printf("StringBuffer : %s, capacity = %d, len = %d\n", _M(sb, getCString), _M(sb, capacity), _M(sb, length));

     DELETE(sb);

     PrimeRun* p = NEW(PrimeRun);
     Thread* thread = NEW(Thread, INTERFACEOF(p, Runnable));
     _M(thread, start);
     _M(thread, join);
     DELETE(thread);
     DELETE(p);
}

void test4()
{
    String* filepath = NEW(String, "/tmp/1/2");
    File* file = NEW(File, filepath);

    if (_M(file, exists)) {
        printf("delete file %d\n", _M(file, delete));
    }
    _M(file, mkdirs);

    DELETE(filepath);
    DELETE(file);
}

void test5()
{
    printf("=======test5 start >>==========\n");
    String* str = NEW(String, "ftp://george@x.com:90/public/notes%E5%9C%A8%E7%BA%BF%E7%BC%96%E7%A0%81?text=shakespeare#hamlet");
    StringUri* stringUri = NEW(StringUri, str);
    DELETE(str);
    String* scheme = _M(stringUri, getScheme);
    String* path = _M(stringUri, getPath);
    String* encodedPath = _M(stringUri, getEncodedPath);
    String* query = _M(stringUri, getQuery);
    String* fragment = _M(stringUri, getFragment);
    String* encodedFragment = _M(stringUri, getEncodedFragment);
    String* host = _M(stringUri, getHost);

    printf("scheme:%s\n", _M(scheme, getCString));
    printf("host:%s\n", _M(host, getCString));
    printf("path:%s\n", _M(path, getCString));
    printf("encoded path:%s\n", _M(encodedPath, getCString));

    printf("fragment:%s\n", _M(fragment, getCString));
    printf("encoded fragment:%s\n", _M(encodedFragment, getCString));

    printf("query:%s\n", _M(query, getCString));
    printf("port:%d\n", _M(stringUri, getPort));
    DELETE(stringUri);
}

void test6()
{
    String* item1 = NEW(String, "Vector Item1");
    String* item2 = NEW(String, "Vector Item2");
    String* item3 = NEW(String, "Vector Item3");
    String* item4 = NEW(String, "Vector Item4");

    ObjectVector* vector = NEW(ObjectVector);

    _M(vector, add, (Object*)item1);
    _M(vector, add, (Object*)item2);
    _M(vector, add, (Object*)item3);
    _M(vector, add, (Object*)item4);

    ObjectVectorIterator* it = _M(vector, listIterator);
    while (_IM(it, hasNext)) {
        String* item = (String*)_IM(it, next);
        printf("%s %d>>> %s\n", __func__, __LINE__, _M(item, getCString));
    }
    DELETE(OBJECTOF(it));

    DELETE(item1);DELETE(item2);DELETE(item3);DELETE(item4);

    DELETE(vector);
}

void test7()
{
    Integer* integer1 = NEW(Integer, 1234);
    Integer* integer2 = NEW(Integer, 4567);
    Integer* integer3 = NEW(Integer, 1234);

    String* s1 = _M(integer1, toString);
    printf("integer1 toString %s\n", _M(s1, getCString));
    printf("integer1 == integer2  %d\n", _M(integer1, equals, (Object*)integer2));
    printf("integer1 == integer3  %d\n", _M(integer1, equals, (Object*)integer3));
    DELETE(s1);

    String* hexStr = _SM(Integer, toString, 1234, 2);
    printf("1234 toHexString %s\n", _M(hexStr, getCString));
    DELETE(hexStr);

    DELETE(integer1);DELETE(integer2);DELETE(integer3);
}

void test8()
{
    Bundle* bundle = NEW(Bundle);
    String* key1 = NEW(String, "key1");
    _M(bundle, putInt, key1, 100);
    int i = _M(bundle, getInt, key1);
    printf("i = %d\n", i);
    DELETE(key1);
    DELETE(bundle);

    String* sizeStr = NEW(String, "1024*768");
    Size* size = _SM(Size, parseSize, sizeStr);
    printf("%p\n", size);
    String* toSizeStr = _M(size, toString);
    printf("size(%s)\n", _M(toSizeStr, getCString));
    DELETE(sizeStr);
    DELETE(size);
    DELETE(toSizeStr);
}

void test9()
{
    String* name = NEW(String, "/tmp/1.txt");
    FileOutputStream* fileOutputStream = NEW(FileOutputStream, name, false);
    const char* text = "Hello World!\n";
    _M(fileOutputStream, write, (const byte*)text, strlen(text));

    BufferedOutputStream* bos = NEW(BufferedOutputStream, (OutputStream*)fileOutputStream);
    const char* text2 = "Hello BufferedOutputStream!!!\n";
     _M(bos, write, (const byte*)text2, strlen(text2));
     _M(bos, flush);
    DELETE(bos);
    DELETE(name);
    DELETE(fileOutputStream);
}

void test10()
{
    String* str = NEW(String, "http://yourluxury.shop");
    StringUri* uri = NEW(StringUri, str);

    String* action = NEW(String, "action");
    Intent* intent = NEW(Intent, action, (Uri*)uri);

    String* name1 = NEW(String, "integer");
    String* name2 = NEW(String, "float");
    String* name3 = NEW(String, "bool");
    String* name4 = NEW(String, "String");

    _M(intent, putIntExtra, name1, 199);
    _M(intent, putFloatExtra, name2, 0.999);
    _M(intent, putBoolExtra, name3, true);
    _M(intent, putStringExtra, name4, str);

    int intExtra = _M(intent, getIntExtra, name1, -1);
    float floatExtra = _M(intent, getFloatExtra, name2, 0.0);
    bool boolExtra = _M(intent, getBoolExtra, name3, false);
    String* strExtra = _M(intent, getStringExtra, name4, NULL);

    printf("int %d float %f bool %d string %s\n", intExtra, floatExtra, boolExtra, _M(strExtra, getCString));

    DELETE(name1);DELETE(name2);DELETE(name3);DELETE(name4);

    DELETE(action);
    DELETE(intent);
    DELETE(uri);
    DELETE(str);
}

int main()
{
    int i = 1;
    while (i--) {
        test0();
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        test8();
        test9();
        test10();
    }
    return 0;
}

//1. The .cc .cpp .cxx related header files
#include "ArrayMap.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "util/ContainerHelpers.h"
#include "util/Log.h"
#include "lang/String.h"

#define DEBUG 1

#if DEBUG
static BUILD(global_const)(TAG, String, "ArrayMap")
static BUILD(global)(msg, String)
#endif

/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */
/*              \\\\\\\            | Class O2OArrayMap |            ///////            */
/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(O2OArrayMap)
{
    CONSTRUCTOR(super)(O2OArrayMap, 0, false);
}

static CONSTRUCTOR()(O2OArrayMap, int capacity)
{
    CONSTRUCTOR(super)(O2OArrayMap, capacity, false);
}

static CONSTRUCTOR()(O2OArrayMap, int capacity, boolean identityHashCode)
{
    CONSTRUCTOR(super)(Object);

    self->_mIdentityHashCode = identityHashCode;
    assert(capacity >= 0);
    allocArrays(capacity);
    self->_mSize = 0;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(O2OArrayMap)
{
    self(clear);
    free(self->_mTable);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static int binarySearchHashes(int[] hashes, int N, int hash)
{
    return _SM(ContainerHelpers, binarySearch, hashes, N, hash);
}

static Object* CLASS_METHOD()(O2OArrayMap, allocArrays, int size)
{
    self->_mHashes = (int*)calloc(size, sizeof(int));
    self->_mArray = (Object**)calloc(size<<1, sizeof(Object*));
}

static void freeArrays(int* hashes, Object** array, int len, int size) {
    if (len == (BASE_SIZE*2)) {
        if (mTwiceBaseCacheSize < CACHE_SIZE) {
            array[0] = mTwiceBaseCache;
            array[1] = hashes;
            for (int i=(size<<1)-1; i>=2; i--) {
                array[i] = null;
            }
            mTwiceBaseCache = array;
            mTwiceBaseCacheSize++;
            if (DEBUG) {
                _M0(msg, format, "Storing 2x cache %p now have %d entries", array, self->mTwiceBaseCacheSize);
                LOG.d(TAG, msg);
            }
        }
    } else if (len == BASE_SIZE) {
        if (mBaseCacheSize < CACHE_SIZE) {
            array[0] = mBaseCache;
            array[1] = hashes;
            for (int i=(size<<1)-1; i>=2; i--) {
                array[i] = null;
            }
            mBaseCache = array;
            mBaseCacheSize++;
            if (DEBUG) {
                _M0(msg, format, "Storing 1x cache %p now have %d entries", array, self->_mBaseCacheSize);
                LOG.d(TAG, msg);
            }
        }
    }
}

/**
 * Ensure the array map can hold at least <var>minimumCapacity</var>
 * items.
 */
static Object* CLASS_METHOD()(T, ensureCapacity, int minimumCapacity)
{
    int osize = mSize;
    if (_M(self->_mHashes, length) < minimumCapacity) {
        int* ohashes = self->_mHashes;
        Object** oarray = self->_mArray;
        self(allocArrays, minimumCapacity);

        if (self->_mSize > 0) {
            System.arraycopy(ohashes, 0, mHashes, 0, osize);
            System.arraycopy(oarray, 0, mArray, 0, osize<<1);
        }
        freeArrays(ohashes, oarray, osize);
    }
}

BEGIN_CLASS(O2OArrayMap, Object)
    CONSTRUCTOR(map)(O2OArrayMap)
    CONSTRUCTOR(map)(O2OArrayMap, int initialCapacity, float loadFactor)
     DESTRUCTOR(map)(O2OArrayMap)
   CLASS_METHOD(map)(O2OArrayMap, size)
   CLASS_METHOD(map)(O2OArrayMap, resize, int newCapacity)
   CLASS_METHOD(map)(O2OArrayMap, isEmpty)
   CLASS_METHOD(map)(O2OArrayMap, capacity)
   CLASS_METHOD(map)(O2OArrayMap, loadFactor)
   CLASS_METHOD(map)(O2OArrayMap, addEntry, int hash, Object* key, Object* value, int bucketIndex)
   CLASS_METHOD(map)(O2OArrayMap, put, Object* key, Object* value)
   CLASS_METHOD(map)(O2OArrayMap, get, Object* key)
   CLASS_METHOD(map)(O2OArrayMap, removeEntryForKey, Object* key)
   CLASS_METHOD(map)(O2OArrayMap, remove, Object* key)
   CLASS_METHOD(map)(O2OArrayMap, clear)
   CLASS_METHOD(map)(O2OArrayMap, getEntry, Object* key)
   CLASS_METHOD(map)(O2OArrayMap, containsKey, Object* key)
   CLASS_METHOD(map)(O2OArrayMap, containsValue, Object* value)
   CLASS_METHOD(map)(O2OArrayMap, transfer, SimpleO2OEntry** newTable, int newCapacity)
END_CLASS


//1. The .cc .cpp .cxx related header files
#include "HashMap.h"
//2. C system include files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/String.h"

/* - - - - - - - - - - - - - - +-----------------------+ - - - - - - - - - - - - - - */
/*              \\\\\\\        |  Class SimpleO2OEntry |          ///////            */
/* - - - - - - - - - - - - - - +-----------------------+ - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(SimpleO2OEntry)
{
    CONSTRUCTOR(super)(SimpleO2OEntry, 0, NULL, NULL, NULL);
}

static CONSTRUCTOR()(SimpleO2OEntry, int h, Object* k, Object* v, SimpleO2OEntry* n)
{
    CONSTRUCTOR(super)(Object);

    self->hash = h;
    self->key = k ? REFER(k) : NULL;
    self->value = v ? REFER(v) : NULL;
    self->next = n ? REFER(n):NULL;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(SimpleO2OEntry)
{
    DELETE(self->key);
    DELETE(self->value);
    if (self->next) DELETE(self->next);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static Object* CLASS_METHOD()(SimpleO2OEntry, getKey)
{
    return self->key;
}

static Object* CLASS_METHOD()(SimpleO2OEntry, getValue)
{
    return self->value;
}

Object* CLASS_METHOD()(SimpleO2OEntry, setValue, Object* newValue)
{
    Object* oldValue = self->value;
    self->value = newValue;
    return oldValue;
}

static void CLASS_METHOD()(SimpleO2OEntry, recordAccess, O2OHashMap* m)
{
}

static void CLASS_METHOD()(SimpleO2OEntry, recordRemoval, O2OHashMap* m)
{
}

static String* CLASS_METHOD()(SimpleO2OEntry, toString)
{
    String* keyStr = self->key ? _M(self->key, toString) : NULL;
    String* valueStr = self->value ? _M(self->value, toString) : NULL;

    const char* keyCStr = keyStr ? _M(keyStr, getCString) : "null";
    const char* valueCStr = valueStr ? _M(valueStr, getCString) : "null";

    String* str = NEW(String);
    _M0(str, format, "%s=%s", keyCStr, valueCStr);

    DELETE(keyStr);
    DELETE(valueStr);
    return str;
}

static bool CLASS_METHOD()(SimpleO2OEntry, equals, Object* o)
{
    if (!INSTANCEOF(o, SimpleO2OEntry))
        return false;

    SimpleO2OEntry* e = (SimpleO2OEntry*)o;

    Object* k1 = self->key;
    Object* k2 = e->key;
    if (k1 == k2 || (k1 != NULL && _M(k1, equals, k2))) {
        Object* v1 = self->value;
        Object* v2 = e->value;
        if (v1 == v2 || (v1 != NULL && _M(v1, equals, v2)))
            return true;
    }
    return false;
}

BEGIN_CLASS(SimpleO2OEntry, Object)
    CONSTRUCTOR(map)(SimpleO2OEntry)
    CONSTRUCTOR(map)(SimpleO2OEntry, int h, Object* k, Object* v, SimpleO2OEntry* n)
     DESTRUCTOR(map)(SimpleO2OEntry)
   CLASS_METHOD(map)(SimpleO2OEntry, getKey)
   CLASS_METHOD(map)(SimpleO2OEntry, getValue)
   CLASS_METHOD(map)(SimpleO2OEntry, setValue, Object* newValue)
   CLASS_METHOD(map)(SimpleO2OEntry, recordAccess, O2OHashMap* m)
   CLASS_METHOD(map)(SimpleO2OEntry, recordRemoval, O2OHashMap* m)
   CLASS_METHOD(map)(SimpleO2OEntry, toString)
   CLASS_METHOD(map)(SimpleO2OEntry, equals, Object* o)
END_CLASS

/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */
/*              \\\\\\\            |  Class O2OHashMap |            ///////            */
/* - - - - - - - - - - - - - - - - +-------------------+ - - - - - - - - - - - - - - - */

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++
static CONSTRUCTOR()(O2OHashMap)
{
    CONSTRUCTOR(super)(O2OHashMap, DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR);
}

static CONSTRUCTOR()(O2OHashMap, int initialCapacity, float loadFactor)
{
    CONSTRUCTOR(super)(Object);

    // Find a power of 2 >= initialCapacity
    int capacity = 1;
    while (capacity < initialCapacity)
        capacity <<= 1;

    self->_mCapacity = capacity;

    self->_mLoadFactor = loadFactor;
    self->_mThreshold = (int)(capacity * loadFactor);
    self->_mTable = (SimpleO2OEntry**)calloc(capacity, sizeof(self->_mTable));
    self->_mSize = 0;
}

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++
static DESTRUCTOR()(O2OHashMap)
{
    self(clear);
    free(self->_mTable);
    DESTRUCTOR(super)(Object);
}

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
/**
 * Returns the number of key-value mappings in this map.
 */
static int CLASS_METHOD()(O2OHashMap, size)
{
    return self->_mSize;
}

/**
 * Returns true if this map contains no key-value mappings.
 */
static bool CLASS_METHOD()(O2OHashMap, isEmpty)
{
    return self->_mSize == 0;
}

/**
 * Applies a supplemental hash function to a given hashCode, which
 * defends against poor quality hash functions.  This is critical
 * because HashMap uses power-of-two length hash tables, that
 * otherwise encounter collisions for hashCodes that do not differ
 * in lower bits. Note: Null keys always map to hash 0, thus index 0.
 */
static int hashFor(unsigned h)
{
    // This function ensures that hashCodes that differ only by
    // constant multiples at each bit position have a bounded
    // number of collisions (approximately 8 at default load factor).
    h ^= (h >> 20) ^ (h >> 12);
    return h ^ (h >> 7) ^ (h >> 4);
}

/**
 * Returns index for hash code h.
 */
static int indexFor(int h, int length)
{
    return h & (length-1);
}

static Object* CLASS_METHOD()(O2OHashMap, get, Object* key)
{
    // TODO
    //if (key == null)
    //    return getForNullKey();
    int hash = hashFor(_M(key, hashCode));
    int i = indexFor(hash, self->_mCapacity);
    SimpleO2OEntry* e;
    for (e = self->_mTable[i]; e != NULL; e = e->next) {
        if (e->hash == hash && (e->key == key || _M(key, equals, e->key)))
            return e->value;
    }

    return NULL;
}

static int CLASS_METHOD()(O2OHashMap, capacity)
{
    return self->_mCapacity;
}

static int CLASS_METHOD()(O2OHashMap, loadFactor)
{
    return self->_mLoadFactor;
}

/**
 * Adds a new entry with the specified key, value and hash code to
 * the specified bucket.  It is the responsibility of this
 * method to resize the table if appropriate.
 *
 * Subclass overrides this to alter the behavior of put method.
 */
static void CLASS_METHOD()(O2OHashMap, addEntry, int hash, Object* key, Object* value, int bucketIndex)
{
    SimpleO2OEntry* e = self->_mTable[bucketIndex];
    self->_mTable[bucketIndex] = NEW(SimpleO2OEntry, hash, key, value, e);
    if (self->_mSize++ >= self->_mThreshold)
        self(resize, 2 * self->_mCapacity);
    if (e) DELETE(e);
}

/**
 * Associates the specified value with the specified key in this map.
 * If the map previously contained a mapping for the key, the old
 * value is replaced.
 *
 * @param key key with which the specified value is to be associated
 * @param value value to be associated with the specified key
 * @return the previous value associated with <tt>key</tt>, or
 *         <tt>null</tt> if there was no mapping for <tt>key</tt>.
 *         (A <tt>null</tt> return can also indicate that the map
 *         previously associated <tt>null</tt> with <tt>key</tt>.)
 */
static Object* CLASS_METHOD()(O2OHashMap, put, Object* key, Object* value)
{
    //TODO
    //if(key == NULL)
    int hash = hashFor(_M(key, hashCode));
    int i = indexFor(hash, self->_mCapacity);
    SimpleO2OEntry* e;
    for (e = self->_mTable[i]; e != NULL; e = e->next) {
        if (e->hash == hash && (e->key == key || _M(key, equals, e->key))) {
            Object* oldValue = e->value;
            e->value = REFER(value);
            _M(e, recordAccess, self);
            return oldValue;
        }
    }

    self(addEntry, hash, key, value, i);
    return NULL;
}

/**
 * Removes and returns the entry associated with the specified key
 * in the HashMap.  Returns null if the HashMap contains no mapping
 * for this key.
 */
static SimpleO2OEntry* CLASS_METHOD()(O2OHashMap, removeEntryForKey, Object* key)
{
    int hash = (key == NULL) ? 0 : hashFor(_M(key, hashCode));
    int i = indexFor(hash, self->_mCapacity);
    SimpleO2OEntry* prev = self->_mTable[i];
    SimpleO2OEntry* e = prev;

    while (e != NULL) {
        SimpleO2OEntry* next = e->next;
        Object* k;
        if (e->hash == hash && (e->key == key || _M(key, equals, e->key))) {
            self->_mSize--;
            if (prev == e)
                self->_mTable[i] = next;
            else
                prev->next = next;
            _M(e, recordRemoval, self);
            return e;
        }
        prev = e;
        e = next;
    }

    return e;
}

/**
 * Removes the mapping for the specified key from this map if present.
 *
 * @param  key key whose mapping is to be removed from the map
 * @return the previous value associated with <tt>key</tt>, or
 *         <tt>null</tt> if there was no mapping for <tt>key</tt>.
 *         (A <tt>null</tt> return can also indicate that the map
 *         previously associated <tt>null</tt> with <tt>key</tt>.)
 */
static Object* CLASS_METHOD()(O2OHashMap, remove, Object* key)
{
    Object* value = NULL;

    SimpleO2OEntry* e = self(removeEntryForKey, key);
    if (e) {
        value = REFER(e->value);
        DELETE(e);
    }
    return value;
}

/**
 * Removes all of the mappings from this map.
 * The map will be empty after this call returns.
 */
static void CLASS_METHOD()(O2OHashMap, clear)
{
    int i;
    for (i = 0; i < self->_mCapacity; i++) {
        if(self->_mTable[i]) {
            DELETE(self->_mTable[i]);
            self->_mTable[i] = NULL;
        }
    }

    self->_mSize = 0;
}

/**
 * Returns <tt>true</tt> if this map contains a mapping for the
 * specified key.
 *
 * @param   key   The key whose presence in this map is to be tested
 * @return <tt>true</tt> if this map contains a mapping for the specified
 * key.
 */
static bool CLASS_METHOD()(O2OHashMap, containsKey, Object* key)
{
    return self(getEntry, key) != NULL;
}

/**
 * Returns the entry associated with the specified key in the
 * HashMap.  Returns null if the HashMap contains no mapping
 * for the key.
 */
static SimpleO2OEntry* CLASS_METHOD()(O2OHashMap, getEntry, Object* key)
{
    int hash = (key == NULL) ? 0 : hashFor(_M(key, hashCode));

    SimpleO2OEntry* e;
    for (e = self->_mTable[indexFor(hash, self->_mCapacity)];
         e != NULL;
         e = e->next) {
        Object* k;
        if (e->hash == hash && (e->key == key || _M(key, equals, e->key)))
            return e;
    }
    return NULL;
}

/**
  * Returns <tt>true</tt> if this map maps one or more keys to the
  * specified value.
  *
  * @param value value whose presence in this map is to be tested
  * @return <tt>true</tt> if this map maps one or more keys to the
  *         specified value
  */
static bool CLASS_METHOD()(O2OHashMap, containsValue, Object* value)
{
     SimpleO2OEntry* e;
     for (int i = 0; i < self->_mCapacity ; i++)
         for (e = self->_mTable[i] ; e != NULL ; e = e->next)
             if (_M(value, equals, e->value))
                 return true;
     return false;
}

/**
 * Transfers all entries from current table to newTable.
 */
static void CLASS_METHOD()(O2OHashMap, transfer, SimpleO2OEntry** newTable, int newCapacity)
{
    int i, j;
    SimpleO2OEntry** src = self->_mTable;
    for (int i = 0; i < self->_mCapacity; i++) {
        SimpleO2OEntry* e = src[i];
        if (e != NULL) {
            src[i] = NULL;
            do {
                SimpleO2OEntry* next = e->next;
                int j = indexFor(e->hash, newCapacity);
                e->next = newTable[i];
                newTable[i] = e;
                e = next;
            } while (e != NULL);
        }
    }
}

static void CLASS_METHOD()(O2OHashMap, resize, int newCapacity)
{
    SimpleO2OEntry** newTable = (SimpleO2OEntry**)calloc(newCapacity, sizeof(self->_mTable));
    self(transfer, newTable, newCapacity);
    free(self->_mTable);
    self->_mTable = newTable;
    self->_mCapacity = newCapacity;
    self->_mThreshold = (int)(newCapacity * self->_mLoadFactor);
}

BEGIN_CLASS(O2OHashMap, Object)
    CONSTRUCTOR(map)(O2OHashMap)
    CONSTRUCTOR(map)(O2OHashMap, int initialCapacity, float loadFactor)
     DESTRUCTOR(map)(O2OHashMap)
   CLASS_METHOD(map)(O2OHashMap, size)
   CLASS_METHOD(map)(O2OHashMap, resize, int newCapacity)
   CLASS_METHOD(map)(O2OHashMap, isEmpty)
   CLASS_METHOD(map)(O2OHashMap, capacity)
   CLASS_METHOD(map)(O2OHashMap, loadFactor)
   CLASS_METHOD(map)(O2OHashMap, addEntry, int hash, Object* key, Object* value, int bucketIndex)
   CLASS_METHOD(map)(O2OHashMap, put, Object* key, Object* value)
   CLASS_METHOD(map)(O2OHashMap, get, Object* key)
   CLASS_METHOD(map)(O2OHashMap, removeEntryForKey, Object* key)
   CLASS_METHOD(map)(O2OHashMap, remove, Object* key)
   CLASS_METHOD(map)(O2OHashMap, clear)
   CLASS_METHOD(map)(O2OHashMap, getEntry, Object* key)
   CLASS_METHOD(map)(O2OHashMap, containsKey, Object* key)
   CLASS_METHOD(map)(O2OHashMap, containsValue, Object* value)
   CLASS_METHOD(map)(O2OHashMap, transfer, SimpleO2OEntry** newTable, int newCapacity)
END_CLASS


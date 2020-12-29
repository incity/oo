//1. The .cc .cpp .cxx related header files
#include "Buffer.h"
//2. C system include files.
//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++
// Creates a new buffer with the given mark, position, limit, and capacity
static CONSTRUCTOR()(Buffer, int mark, int pos, int lim, int cap)
{
    CONSTRUCTOR(super)(Object);
    assert(cap >= 0);
    self->_mCapacity = cap;
    self(limit, lim);
    self(position, pos);
    if (mark >= 0) {
        assert(mark <= pos);
        self->_mMark = mark;
    }
}

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
/**
 * Returns this buffer's capacity. </p>
 *
 * @return  The capacity of this buffer
 */
static int CLASS_METHOD()(Buffer, capacity)
{
    return self->_mCapacity;
}

/**
 * Returns this buffer's position. </p>
 *
 * @return  The position of this buffer
 */
static int CLASS_METHOD()(Buffer, position)
{
    return self->_mPosition;
}

/**
 * Sets this buffer's position.  If the mark is defined and larger than the
 * new position then it is discarded. </p>
 *
 * @param  newPosition
 *         The new position value; must be non-negative
 *         and no larger than the current limit
 *
 * @return  This buffer
 */
static Buffer* CLASS_METHOD()(Buffer, position, int newPosition)
{
    assert(newPosition <= self->_mLimit && newPosition >= 0);
    self->_mPosition = newPosition;
    if (self->_mMark > self->_mPosition) self->_mMark = -1;
    return self;
}

/**
 * Returns this buffer's limit. </p>
 *
 * @return  The limit of this buffer
 */
static int CLASS_METHOD()(Buffer, limit)
{
    return self->_mLimit;
}

/**
 * Sets this buffer's limit.  If the position is larger than the new limit
 * then it is set to the new limit.  If the mark is defined and larger than
 * the new limit then it is discarded. </p>
 *
 * @param  newLimit
 *         The new limit value; must be non-negative
 *         and no larger than this buffer's capacity
 *
 * @return  This buffer
 */
static Buffer* CLASS_METHOD()(Buffer, limit, int newLimit)
{
    assert(newLimit <= self->_mCapacity && newLimit >= 0);
    self->_mLimit = newLimit;
    if (self->_mPosition > self->_mLimit) self->_mPosition = self->_mLimit;
    if (self->_mMark > self->_mLimit) self->_mMark = -1;
    return self;
}

/**
 * Sets this buffer's mark at its position. </p>
 *
 * @return  This buffer
 */
static Buffer* CLASS_METHOD()(Buffer, mark)
{
    self->_mMark = self->_mPosition;
    return self;
}

/**
 * Resets this buffer's position to the previously-marked position.
 *
 * <p> Invoking this method neither changes nor discards the mark's
 * value. </p>
 *
 * @return  This buffer
 */
static Buffer* CLASS_METHOD()(Buffer, reset)
{
    int m = self->_mMark;
    assert(m >= 0);
    self->_mPosition = m;
    return self;
}

static Buffer* CLASS_METHOD()(Buffer, clear)
{
    self->_mPosition = 0;
    self->_mLimit = self->_mCapacity;
    self->_mMark = -1;
    return self;
}

static Buffer* CLASS_METHOD()(Buffer, flip)
{
    self->_mLimit = self->_mPosition;
    self->_mPosition = 0;
    self->_mMark = -1;
    return self;
}

static Buffer* CLASS_METHOD()(Buffer, rewind)
{
    self->_mPosition = 0;
    self->_mMark = -1;
    return self;
}

static int CLASS_METHOD()(Buffer, remaining)
{
    return self->_mLimit - self->_mPosition;
}

static bool CLASS_METHOD()(Buffer, hasRemaining)
{
    return self->_mPosition - self->_mLimit;
}

BEGIN_CLASS(Buffer, Object)
  CONSTRUCTOR(map)(Buffer, int mark, int pos, int lim, int cap)
 CLASS_METHOD(map)(Buffer, capacity)
 CLASS_METHOD(map)(Buffer, position)
 CLASS_METHOD(map)(Buffer, position, int newPosition)
 CLASS_METHOD(map)(Buffer, limit)
 CLASS_METHOD(map)(Buffer, limit, int newLimit)
 CLASS_METHOD(map)(Buffer, mark)
 CLASS_METHOD(map)(Buffer, reset)
 CLASS_METHOD(map)(Buffer, clear)
 CLASS_METHOD(map)(Buffer, flip)
 CLASS_METHOD(map)(Buffer, rewind)
 CLASS_METHOD(map)(Buffer, remaining)
 CLASS_METHOD(map)(Buffer, hasRemaining)
//  CLASS_METHOD(map)(Buffer, isReadOnly)
END_CLASS

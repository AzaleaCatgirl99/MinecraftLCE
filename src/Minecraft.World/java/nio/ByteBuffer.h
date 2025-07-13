#pragma once

#include "types.h"

class IntBuffer;

class ByteBuffer {
public:
    ByteBuffer(byte);
    ~ByteBuffer();

    IntBuffer* asIntBuffer();

    void flip();

    static ByteBuffer* allocate(int);

    byte* getBuffer();
};
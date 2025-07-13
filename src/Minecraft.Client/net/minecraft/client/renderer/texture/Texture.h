#pragma once

#include "types.h"
#include <string>

class BufferedImage;
class Rect2i;
class Renderer;
class ByteBuffer;

class Texture {
public:
    Texture(const std::wstring&, int, int, int, int, int, int, int, BufferedImage*, bool);
    Texture(const std::wstring&, int, int, int, int, int, int, int, int, BufferedImage*, bool);
    ~Texture();
    void init(const std::wstring&, int, int, int, int, int, int, int, int, bool);
    void init(const std::wstring&, int, int, int, int, int, int, int, int, BufferedImage*, bool);
    void updateOnGPU();
    void transferFromImage(BufferedImage*);
    void getData(u32);
    int getHeight();
    int getWidth();
    static int crispBlend(int c0, int c1);
    unsigned int getManagerId();
    void bind(int);

    int dword_0;
    unsigned int mTextureManagerId;
    int dword_8;
    int mWidth;
    int mHeight;
    int dword_14;
    int dword_18;
    int dword_1c;
    unsigned int dword_20;
    unsigned int dword_24;
    unsigned int dword_28;
    bool mIsAnimated;
    std::wstring std_wstring_filename;
    Rect2i* mTextureRect;
    char mTransferred;
    char byte_51;
    bool bool_52;
    char gap_53;
    int dword_54;
    ByteBuffer* qword_58;
    ByteBuffer* qword_60;
    void* qword_68;
    void* qword_70;
    void* qword_78;
    void* qword_80;
    void* qword_88;
    void* qword_90;
    void* qword_98;
    void* qword_a0;
    bool bool_a8;
};

ASSERT_SIZEOF(Texture, 0xB0)

#include "4JLibraries_Source/NX/Render/RendererCore.h"
#include "java/nio/ByteBuffer.h"
#include "net/minecraft/client/renderer/texture/Texture.h"

int Texture::crispBlend(int c0, int c1) {
    int a0 = c0 >> 24 & 255;
    int a1 = c1 >> 24 & 255;
    int a = 255;
    if (a0 + a1 < 255) {
        a0 = 1;
        a1 = 1;
        a = 0;
    } else if (a0 > a1) {
        a0 = 255;
        a1 = 1;
    } else {
        a0 = 1;
        a1 = 255;
    }

    int r0 = (c0 >> 16 & 255) * a0;
    int g0 = (c0 >> 8 & 255) * a0;
    int b0 = (c0 & 255) * a0;
    int r1 = (c1 >> 16 & 255) * a1;
    int g1 = (c1 >> 8 & 255) * a1;
    int b1 = (c1 & 255) * a1;
    int r = (r0 + r1) / (a0 + a1);
    int g = (g0 + g1) / (a0 + a1);
    int b = (b0 + b1) / (a0 + a1);
    return a << 24 | r << 16 | g << 8 | b;
}

int Texture::getWidth() {
    return this->mWidth;
}

int Texture::getHeight() {
    return this->mHeight;
}

unsigned int Texture::getManagerId() {
    return this->mTextureManagerId;
}

// NON-MATCHING: not tested to see if this actually works
void Texture::updateOnGPU() {
    Renderer* renderer;
    long long lVar8;
    long long lVar9;
    ByteBuffer* buffer;

    this->qword_58->flip();
    if (this->mIsAnimated && 1 < this->dword_54) {
        lVar9 = 0xc;
        do {
            buffer = this->qword_60;
            if (buffer == nullptr)
                break;
            buffer->flip();
            lVar8 = lVar9 + -10;
            lVar9 = lVar9 + 1;
        } while (lVar8 < this->dword_54);
    }

    renderer = Renderer::sInstance;
    int w0;
    int h0;
    int h1;
    int w1;
    byte* data;
    uint uVar4;

    if (this->bool_a8) {
        renderer->TextureSetTextureLevels(this->dword_54);
        w0 = this->mWidth;
        h0 = this->mHeight;
        data = this->qword_58->getBuffer();

        renderer->TextureData(w0, h0, data, 0, (C4JRender::eTextureFormat)0);
        if (this->mIsAnimated && 1 < this->dword_54) {
            lVar9 = 0xc;
            do {
                w1 = this->mWidth;
                h1 = this->mHeight;
                uVar4 = (uint)(lVar9 - 0xbU);
                data = this->qword_60->getBuffer();
                renderer->TextureData(w1 >> (uVar4 & 0x1f), h1 >> (uVar4 & 0x1f), data,
                                      lVar9 - 0xbU & 0xffffffff, (C4JRender::eTextureFormat)0);
                lVar8 = lVar9 + -10;
                lVar9 = lVar9 + 1;
            } while (lVar8 < this->dword_54);
        }
    } else {
        w0 = this->mWidth;
        h0 = this->mHeight;
        data = this->qword_58->getBuffer();
        renderer->TextureDataUpdate(0, 0, w0, h0, data, 0);
        if (this->mIsAnimated && (w1 = renderer->TextureGetTextureLevels(), 1 < w1) && 1 < this->dword_54) {
            lVar9 = 0xc;
            do {
                w1 = this->mWidth;
                h1 = this->mHeight;
                uVar4 = (uint)(lVar9 - 0xbU);
                data = this->qword_60->getBuffer();
                renderer->TextureDataUpdate(0, 0, w1 >> (uVar4 & 0x1f), h1 >> (uVar4 & 0x1f), data,
                                            lVar9 - 0xbU & 0xffffffff);
                lVar8 = lVar9 + -10;
                lVar9 = lVar9 + 1;
            } while (lVar8 < this->dword_54);
        }
        this->bool_a8 = true;
    }
    this->bool_52 = true;
}

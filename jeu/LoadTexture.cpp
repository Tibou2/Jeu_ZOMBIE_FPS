#include "LoadTexture.h"
#include "ceti.h"

GLuint LoadTexture::LoadTextureImagFile(const char* Filename, bool Fast)
{
    GLuint textureID = 0;
    unsigned long x;
    unsigned long y;
    unsigned short int bpp; //bits per pixels   unsigned short int
    GLbyte* texData;             //the data of the image
    GLuint ID;                //the id ogl gives it
    unsigned long size;     //length of the file
    int channels;      //the channels of the image 3 = RGA 4 = RGBA
    GLuint type;

    FILE* file = fopen(Filename, "rb");  //open the file
    struct jpeg_decompress_struct info;  //the jpeg decompress info
    struct jpeg_error_mgr err;           //the error handler

    info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
    jpeg_create_decompress(&info);       //sets info to all the default stuff

    //if the jpeg file didnt load exit
    if (!file)
    {
        fprintf(stderr, "Error reading JPEG file %s!!!", Filename);
        return false;
    }

    jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

    jpeg_read_header(&info, TRUE);   //tell it to start reading it

    //if it wants to be read fast or not
    if (Fast)
    {
        info.do_fancy_upsampling = FALSE;
    }

    jpeg_start_decompress(&info);    //decompress the file

    //set the x and y
    x = info.output_width;
    y = info.output_height;
    channels = info.num_components;

    type = GL_RGB;

    if (channels == 4)
    {
        type = GL_RGBA;
    }

    bpp = channels * 8;

    size = x * y * 3;

    //read turn the uncompressed data into something ogl can read
    texData = new GLbyte[size];      //setup data for the data its going to be handling

    GLbyte* p1 = texData;
    GLbyte** p2 = &p1;
    int numlines = 0;

    while (info.output_scanline < info.output_height)
    {
        numlines = jpeg_read_scanlines(&info, (JSAMPLE**)p2, 1);
        *p2 += numlines * 3 * info.output_width;
    }

    jpeg_finish_decompress(&info);   //finish decompressing this file

    fclose(file);

    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    // free buffer  
    free(texData);

    return textureID;
}

void LoadTexture::FreeCreatedTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}
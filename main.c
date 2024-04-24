#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_DXT_IMPLEMENTATION
#include "stb_dxt.h"
#include <stdio.h>
#include <stdlib.h>

void save_dds(const char* filename, const unsigned char* dxt_data, int width, int height) {
    // 一个简单的 DDS 保存函数，省略了 DDS 文件头的细节
    FILE* file = fopen(filename, "wb");
    if (!file) return;
    fwrite(dxt_data, 1, width * height, file); // 注意，这里没有写入DDS头
    fclose(file);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <input.png> <output.dds>\n", argv[0]);
        return 1;
    }

    int width, height, channels;
    unsigned char* rgb_image = stbi_load(argv[1], &width, &height, &channels, 3);
    if (!rgb_image) {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }

    int dxt_size = width * height;
    unsigned char* dxt_data = (unsigned char*)malloc(dxt_size);
    if (!dxt_data) {
        stbi_image_free(rgb_image);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    stb_compress_dxt_block(dxt_data, rgb_image, 1, STB_DXT_HIGHQUAL);

    save_dds(argv[2], dxt_data, width, height);

    free(dxt_data);
    stbi_image_free(rgb_image);

    printf("Compression completed successfully\n");
    return 0;
}
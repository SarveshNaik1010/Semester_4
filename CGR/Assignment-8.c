#include <stdio.h>

struct ImageFormat {
    char name[10];
    char extension[5];
    char description[100];
    char exampleFile[20];
};

int main() {
    struct ImageFormat formats[] = {
        {"BMP", "bmp", "Bitmap format, uncompressed, large size but easy to process.", "image.bmp"},
        {"JPEG", "jpg", "Lossy compression, used for photos. Smaller size, reduced quality.", "photo.jpg"},
        {"PNG", "png", "Lossless compression, supports transparency. Used for web graphics.", "logo.png"},
        {"GIF", "gif", "Supports animation, limited to 256 colors. Used for simple graphics.", "animation.gif"},
        {"TIFF", "tiff", "High-quality format used in printing and scanning.", "scan.tiff"}
    };

    int count = sizeof(formats) / sizeof(formats[0]);

    printf("Study of Various Graphical File Formats:\n\n");
    for (int i = 0; i < count; i++) {
        printf("Format Name   : %s\n", formats[i].name);
        printf("Extension     : .%s\n", formats[i].extension);
        printf("Description   : %s\n", formats[i].description);
        printf("Example File  : %s\n", formats[i].exampleFile);
        printf("-------------------------------------------\n");
    }

    return 0;
}

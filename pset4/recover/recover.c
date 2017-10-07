#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    char *imageName = argv[1];
    
    FILE *image = fopen(imageName, "r");
    if (image == NULL)
    {
        fprintf(stderr, "Unable to open image\n");
        return 2;
    }
    
    int jpegIndex = 0;
    BYTE buffer[512];
    
    FILE *outputFile = NULL;
    
    // Search image for JPEG files
    while (fread(buffer, 512, 1, image))
    {
        // Check for beginning of new JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            
            // Clear output pointer
            if (outputFile != NULL)
            {
                fclose(outputFile);
            }
            
            // Create new output file
            char outputFilename[8];
            sprintf(outputFilename, "%03i.jpg", jpegIndex);
            outputFile = fopen(outputFilename, "w");
            
            jpegIndex++;
        }
        
        // Write to outputFile
        if (outputFile != NULL)
        {
            fwrite(buffer, 512, 1, outputFile);
        }
    }
    
    // Close last JPEG output file
    if (outputFile != NULL)
    {
        fclose(outputFile);
    }
    
    fclose(image);
    
    return 0;
}
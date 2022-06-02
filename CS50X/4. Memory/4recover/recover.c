#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int checkjpg (uint8_t FAT[512]);

int main(int argc, char *argv[])
{
    //Check for correct usage
    if (argc!=2)
    {
        printf ("Error. Please use following format: %c./recover filename%c",34,34);
        return 1;
    }

    //open data for reading & check if it could be opened
    FILE *data = fopen (argv[1], "r");
    if (data==NULL)
    {
        printf ("Could not read data");
        return 1;
    }

    // Initialise values for writing.
    // int counter:         Counts up for the output filename - starts from 001.jpg -> 002.jpg and so on. Up to 999.jpg.
    // char outfilename[8]: Output filename stored here.
    // uint8_t FAT[512]:    Buffer to read each 512-byte block of data.
    // FILE *output         Output file pointer. Initialised for now to NULL. 001.jpg created once first JPG found.

    int counter = 0;
    char outfilename[8];
    uint8_t FAT[512];
    FILE *output = NULL;

    // Reads 512-byte block of data into buffer, and checks if successful, else exits the loop (e.g. at end of file)
    while (fread(FAT, sizeof(uint8_t), 512, data)==512)
    {
        //Check if block of data corresponds to the signature at the start of a .jpg file. If so, create and write to a new file. Steps:
        //  1. Set output filename depending on value of counter.
        //  2. Close previous .jpg, if any.
        //  3. Open new .jpg based on set output filename.
        //  4. Update the file counter
        if (checkjpg (FAT))
        {
            //1. Set output filename depending on value of counter.
            if (counter < 10)
            {
                sprintf(outfilename, "00%i.jpg",counter);
            }
            else if (counter < 100)
            {
                sprintf(outfilename, "0%i.jpg",counter);
            }
            else if (counter < 1000)
            {
                sprintf(outfilename, "%i.jpg",counter);
            }
            else
            {
                printf ("Too many files. Only accepts up to 999.");
                return 2;
            }

            //2. Close previous .jpg, if any.
            if (output != NULL)
            {
                fclose (output);
            }

            //3. Open new .jpg based on set output filename
            output = fopen (outfilename, "w");
            if (output == NULL)
            {
                printf ("Could not open output file: %s", outfilename);
                return 2;
            }

            //4. Update the file counter
            counter ++;
        }

        //Writes buffer to output file if it exists.

        if (output != NULL)
        {
            if (fwrite (FAT, sizeof(uint8_t), 512, output)!=512)
            {
                printf ("Error writing file: %s", outfilename);
                return 2;
            }
        }
    }
    return 0;
}

int checkjpg (uint8_t FAT[512])
{
    if (FAT[0]==0xff && FAT[1]==0xd8 && FAT[2]==0xff && (FAT[3] ==0xe0 || FAT[3]==0xe1 || FAT[3]==0xe2 || FAT[3]==0xe3 || FAT[3]==0xe4 ||
        FAT[3]==0xe5 || FAT[3]==0xe6 || FAT[3]==0xe7 || FAT[3]==0xe8 || FAT[3]==0xe9 || FAT[3]==0xea || FAT[3]==0xeb || FAT[3]==0xec ||
        FAT[3]==0xed || FAT[3]==0xee || FAT[3]==0xef))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
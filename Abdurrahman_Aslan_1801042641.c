#include <stdio.h>

#include <string.h>

void output_file(char * filename, char * word, int row, int column, int flag);
void horizontal_cmp(char * word, char table[100][250], int array_size);
void readfile_2();
void readfile_1(char table[100][250], int * array_size);
void vertical_cmp(char * word, char table[100][250], int array_size);
void clear_file(char * filename);

int main() {
    clear_file("output.txt");     
    readfile_2();

    return 0;
}

void clear_file(char * filename) {
    FILE * fp;
    fp = fopen(filename, "w");          //file cleanup process
    fclose(fp);
}

void output_file(char * filename, char * word, int row, int column, int flag) {
    FILE * fp;
    fp = fopen(filename, "a+");
    fprintf(fp, "%s ", word);
    fprintf(fp, "(%d,%d) ", row, column);	//write the horizontal and vertical positions of words to the output file
    if (flag == 1) {	
        fprintf(fp, "%s\n", "vertical");
    } else
        fprintf(fp, "%s\n", "horizontal");
    fclose(fp);
}

void vertical_cmp(char * word, char table[100][250], int array_size) {
    int i = 0, flag = 0, counter = 0, j = 0;
    char letter;
    while (j != array_size) {

        j = 0;
        while (table[j][counter] != '*') {
            flag = 0;
            letter = table[j][counter];

            if (word[0] == letter) {
                flag++;

                for (i = 1; i < strlen(word) - 1; i++) {

                    j++;
                    letter = table[j][counter];         //process of finding vertical positions of words

                    if (word[i] != letter) {

                        break;
                    }
                    flag++;
                    if (flag == strlen(word) - 1) {
                        output_file("output.txt", word, j - strlen(word) + 3, counter, 1);

                        flag = 0;
                    }

                }

            }
            j++;
        }
        counter++;
    }

}

void horizontal_cmp(char * word, char table[100][250], int array_size) {

    int i = 0, flag = 0, counter = 0, j = 0;
    char letter;
    while (j != array_size) {

        counter = 0;
        while (table[j][counter] != '*') {
            flag = 0;
            letter = table[j][counter];

            if (word[0] == letter) {
                flag++;

                for (i = 1; i < strlen(word) - 1; i++) {
                    counter++;                                 //process of finding vertical positions of words
                    letter = table[j][counter];

                    if (word[i] != letter) {

                        break;
                    }
                    flag++;
                    if (flag == strlen(word) - 1) {
                        output_file("output.txt", word, j + 1, counter - strlen(word) + 2, 0);

                        flag = 0;
                    }

                }

            }
            counter++;
        }
        j++;
    }
}

void readfile_2() {
    int counter, i = 0;
    char table[100][250];

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 250; j++) {    //filling array with a star for vertical search
            table[i][j] = '*';
        }

    }

    readfile_1(table, & counter);
    char * token;
    char ch[100];
    FILE * fp2;
    fp2 = fopen("input1.txt", "r"); //input file opened read mode
    while (!feof(fp2)) {
        fgets(ch, 100, fp2);
        token = strtok(ch, "\n");  // \n to get rid of
        horizontal_cmp(ch, table, counter);
        vertical_cmp(ch, table, counter);

    }
}

void readfile_1(char table[100][250], int * array_size) {
    int i = 0, counter = 0;
    char c;

    FILE * fp3;
    fp3 = fopen("input2.txt", "r");

    while (!feof(fp3)) {
        fscanf(fp3, "%c", & c);
        if (c == '\n') {
            i = 0;
            counter++;
        }

        table[counter][i] = c;
        i++;
    }

    * array_size = counter;
}
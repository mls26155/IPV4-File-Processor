#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// function prototypes
char *getDateAndTime();
void Read_Data_File();
void Bubble_sort(char selection);
void convert_To_Uppercase();
void swap_rows(int cols, int rowA);
void Generate_Alias_List();

// Global Variables
char global_array[100][32];
int usedRows = 0;

int main() {
    Read_Data_File();
    convert_To_Uppercase();

    char selection;
    printf("\nEnter \'a\' for ascending order or \'d\' for descending order:\n");
    scanf(" %c", &selection);

    while (selection != 'a' && selection != 'd') {
        printf("Error: illegal value. Enter \'a\' or \'d\'\n");
        scanf(" %c", &selection);
    }

    Bubble_sort(selection);

    Generate_Alias_List();

    printf("File generated. Thank you for using this program.");
    return 0;
}

void Read_Data_File() {
    FILE *pF = fopen("CS222_Inet.txt","r");
    char buffer[255];
    int index = 0;
    
    // Verify file can be opened
    if (pF == NULL) {
        printf("Error opening file.\n");
        exit(0);
    }
    // Add each line into 2D array if acceptable
    else {
        printf("File sucessfully opened.\n");
        while(fgets(buffer,255,pF) != NULL && (strcmp(buffer, "0.0.0.0 NONE\n") != 0 && strcmp(buffer, "0.0.0.0 NONE") != 0)) {
            //printf("Buffer: %s", buffer);
            strcpy(global_array[index], buffer);
            //printf("Global Array[%d]: %s", index, global_array[index]);
            index++;
        }
        printf("\nFile sucessfully processed.\n");
    }
}

void convert_To_Uppercase() {
    char ch;
    int i = 0;
    int j = 0;
    int rows = sizeof(global_array)/sizeof(global_array[0]);

    // Convert each line to uppcase
    while (i < rows) {
		while(global_array[i][j]){
            ch = global_array[i][j];
            //printf("CHARACTER IN CAPS: %c\n", toupper(ch));
		    global_array[i][j] = toupper(ch);
		    j++;
        }
        j = 0;
        i++;
	}
    //for(int k = 0; k < rows; k++) {
    //    printf("UPPERCASED Global Array[%d] = %s\n", k, global_array[k]);
    //}
    printf("File sucessfully uppercased.\n");
}

void Bubble_sort(char selection) {
    char str1[32] = " ";
    char str2[32] = " ";
    int rows = sizeof(global_array)/sizeof(global_array[0]);
    int cols = sizeof(global_array[0])/sizeof(global_array[0][0]);
    int m = 0, n = 0;

    for (int z = 0; z < rows; z++) {
       if(global_array[z][0] == '\0'){
            break;
       }
       usedRows += 1;
    }
    printf("usedRows: %d\n", usedRows);

    // Bubble Sort the 2D array
    for(int k = 0; k < usedRows-1; k++) {
        for(int i = 0; i < usedRows-k-1; i++) {
            // Create strings for row j and row j+1
            for(int j = 0; j < cols; j++){
                if(isalpha(global_array[i][j]) != 0) {
                    str1[m] = global_array[i][j];
                    m++;
                }
                if(isalpha(global_array[i+1][j]) != 0){
                    str2[n] = global_array[i+1][j];
                    n++;
                }
            }
            m = 0; n = 0;
            //printf("STR1: %s\n", str1);
            //printf("STR2: %s\n", str2);

            // Compare strings to identify greater row
            if(strcmp(str1, str2) > 0 && selection == 'a'){
                //printf("A WAS SELECTED\n");
                swap_rows(cols, i);
                //printf("%s > %s", str1, str2);
            }
            else if (strcmp(str1, str2) < 0 && selection == 'd') {
                swap_rows(cols, i);
            }
        }
    }
    printf("Sorted Rows: \n");
    for (int z = 0; z < usedRows; z++) {
        printf("GA[%d]: %s\n", z, global_array[z]);
    }
}

// Function to swap rows in 2D array
void swap_rows(int cols, int rowA) {
    int rowB = rowA + 1;
    int temp = 0;
    for(int i = 0; i < cols; i++) {
        temp = global_array[rowA][i];
        global_array[rowA][i] = global_array[rowB][i];
        global_array[rowB][i] = temp;
    }
    //printf("GLOBAL ARRAY[0]: %s",global_array[0]);
    // printf("GLOBAL ARRAY[1]: %s",global_array[1]);
}

// Output File
void Generate_Alias_List() {
    int cols = sizeof(global_array[0])/sizeof(global_array[0][0]);
    char strName[32] = " ";
    char strIP[32] = " ";
    char name_date[25];
    int m = 0, n = 0;

    char temp[25];
    fgets(temp, sizeof(temp), stdin);

    printf("Enter your name: ");
    fgets(name_date, sizeof(name_date), stdin);

    FILE *pF2 = fopen("222_Alias_List.txt", "w");
    fprintf(pF2, "%s", name_date);
    fprintf(pF2, "Today's date: %s", getDateAndTime()); 
    fprintf(pF2, "CS222 Network Alias Listing\n");

    for(int j = 0; j < usedRows; j++) {
        for (int i = 0; i < cols; i++) {
            if(isalpha(global_array[j][i]) != 0) {
                strName[m] = global_array[j][i];
                m++;
            }
            if(isalpha(global_array[j][i]) == 0) {
                strIP[n] = global_array[j][i];
                n++;
            }
        }
        m = 0; n = 0;
        strcat(strName, " \t\t");
        strcat(strName, strIP);
        printf("STRING: %s", strName);
        fprintf(pF2, "%s", strName);

        for(int k = 0; k < cols; k++) {
            strName[k] = '\0';
        }

    }
    fclose(pF2);
}

char *getDateAndTime() {
    time_t t;
    time(&t);
    return ctime(&t);
}
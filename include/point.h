#ifndef POINT_H_
#define POINT_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
unsigned char getPoint(char *username)
{
    FILE *fp = fopen("points.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char line[100];
    while (fgets(line, sizeof(line), fp))
    {
        char *token = strtok(line, " ");
        if (strcmp(token, username) == 0)
        {
            token = strtok(NULL, " ");
            fclose(fp);
            return atoi(token);
        }
    }
    fclose(fp);
    return 0;
}
void exportPoint(char *username, unsigned char point)
{
    FILE *fp = fopen("points.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char str[20];
    char line[100];
    char stored[50][100];
    int count = 0, found = 0;
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%s", str);
        if (strcmp(str, username) == 0)
        {
            sprintf(line, "%s %d\n", username, point);
            found = 1;
        }
        strcpy(stored[count], line);
        count++;
    }
    if (!found)
    {
        sprintf(line, "%s %d\n", username, point);
        strcpy(stored[count], line);
        count++;
    }
    fclose(fp);
    fp = fopen("points.txt", "w+");
    for (int i = 0; i < count; i++)
    {
        fputs(stored[i], fp);
    }
    fclose(fp);
}
#endif // POINT_H_
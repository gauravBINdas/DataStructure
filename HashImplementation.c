#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERR -1
typedef struct HashInfo
{
    char chain[100][100];
    char key[20];
    int top;
} Hash;
void p_error(char *err)
{
    printf("%s\n",err);
    printf("Press any key to exit...");
    getchar();
    exit(ERR);
}
Hash *createHashTable(int n)
{
    Hash *directAccessTable=(Hash *)calloc(sizeof(Hash),n);
    if(directAccessTable==NULL)
        p_error("Cannot Initialize Direct Access Table-Check Memory Capacity");
    return directAccessTable;
}
int hashFunction(char key[],int size)
{
    int len=0,generated_index=0;
    while(key[len]!=NULL)
    {
        generated_index+=key[len];
        ++len;
    }
    if(len==0)
        p_error("Invalid Key");
    /*
    Future Scope: Try implementation dynamically
    size=sizeof(*directAccessTable)/sizeof(Hash);
    directAccessTable[generated_index].chain=(int *)malloc(sizeof(int)*100);
    */

    generated_index=(generated_index%size)-1;
    return generated_index;
}
void put(char key[],char value[],Hash *directAccessTable,int size)
{
    int generated_index=hashFunction(key,size);
    strcpy(directAccessTable[generated_index].key,key);
    strcpy(directAccessTable[generated_index].chain[directAccessTable[generated_index].top],value);
    /*
    Uncomment to see the detail value of insertion
    printf("generated_index:%d,Top:%d,Value:%s\n",generated_index,directAccessTable[generated_index].top,directAccessTable[generated_index].chain[directAccessTable[generated_index].top]);
    getchar();
    */
    directAccessTable[generated_index].top++;
    return;
}
char **get(char key[],int number,Hash *directAccessTable,int size)
{
    int generated_index=hashFunction(key,size);
    return directAccessTable[generated_index].chain+number-1;
}
void main(int argc,char *argv[])
{
    Hash *directAccessTable=NULL;
    char **value1=NULL,**value2=NULL;
    directAccessTable=createHashTable(10);
    put("abc","gaurav",directAccessTable,10);
    put("xyz","gd",directAccessTable,10);
    put("abc","gaurav2",directAccessTable,10);
    for(int i=0,j=0; i<10; ++i,j=0)
    {
        // printf("top:%d\n",directAccessTable[i].top);
        printf("[ Key:%s | Value: ",directAccessTable[i].key);
        for(j=0; j<directAccessTable[i].top; ++j)
        {
            printf("%s ,",directAccessTable[i].chain[j]);
        }
        printf("\b]\n");
    }

    /*Development Phase, Unstable Implementation*/
    printf("Get Implementation--------\n");
    value1=get("abc",1,directAccessTable,10);
    value2=get("abc",2,directAccessTable,10);
    printf("value1:%s ,value2:%s\n",value1,value2);
}
